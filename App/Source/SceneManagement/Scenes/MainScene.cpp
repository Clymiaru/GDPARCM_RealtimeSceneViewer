#include "pch.h"
#include "MainScene.h"

#include <string>

#include <ImGui/imgui.h>
#include <ImGui/imgui_internal.h>

#include <glm/vec2.hpp>

#include "Core/App.h"

#include "Utils/Log.h"

// UI needed to render:
    // * Global loading bar for all assets to load
    // * View all button
    // Concerning 5 scenes
    // * 5 Scenes view button
    //		Must be clickable only when loading is complete
    // * 5 Scenes close button
    //		Can't be selected or view if loading bar is still present
    // * 5 Scenes loading bar
    //		Must only be visible if there are actual loading process

MainScene::MainScene() :
	AScene{STRINGIFY(MainScene)},
	m_Progress{0.1f}
{
}

MainScene::~MainScene()
{
}

void MainScene::RenderMeshes()
{
}

void MainScene::RenderUI()
{
	CreateViewAllButton({150.0f, 60.0f}, 25.0f);
	CreateSceneButtons(5, {150.0f, 150.0f}, 50.0f);
}

void MainScene::LoadResources()
{
}

void MainScene::UnloadResources()
{
}

void MainScene::CreateViewAllButton(const glm::vec2& size,
									float spacing)
{
	ImGuiWindowFlags windowFlags = 0;
	windowFlags |= ImGuiWindowFlags_NoSavedSettings;
	windowFlags |= ImGuiWindowFlags_NoTitleBar;
	windowFlags |= ImGuiWindowFlags_NoScrollbar;
	windowFlags |= ImGuiWindowFlags_NoMove;
	windowFlags |= ImGuiWindowFlags_NoResize;
	windowFlags |= ImGuiWindowFlags_NoBackground;

	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(ImVec2(viewport->WorkPos.x + viewport->Size.x - size.x - spacing,
                                   viewport->WorkPos.y + viewport->Size.y - size.y - spacing),
									 ImGuiCond_Once);
	const bool allScenesAreLoaded = AreAllScenesLoaded();

	if (!ImGui::Begin("ViewAllButton", nullptr, windowFlags))
	{
		ImGui::End();
	}
	else
	{
		if (allScenesAreLoaded)
		{
			ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
		}
			
		if (ImGui::Button("ViewAllButton", {size.x, size.y}))
		{
			if (!allScenesAreLoaded)
			{
				ViewAllScenes();
				ImGui::End();
				return;
			}
		}
		
		if (allScenesAreLoaded)
		{
			ImGui::PopItemFlag();
			ImGui::PopStyleVar();
		}

		ImGui::End();
	}
}

void MainScene::CreateSceneButtons(const int amountOfScenes,
								   const glm::vec2& size,
								   const float xSpacing)
{
	ImGuiWindowFlags windowFlags = 0;
	windowFlags |= ImGuiWindowFlags_NoSavedSettings;
	windowFlags |= ImGuiWindowFlags_NoTitleBar;
	windowFlags |= ImGuiWindowFlags_NoScrollbar;
	windowFlags |= ImGuiWindowFlags_NoMove;
	windowFlags |= ImGuiWindowFlags_NoResize;
	windowFlags |= ImGuiWindowFlags_NoBackground;

	const ImGuiViewport* viewport = ImGui::GetMainViewport();

	const float halfScreenSizeX = App::Width / 2.0f;
	const float widthWithXSpacing       = size.x + xSpacing;
	const float widthEdgeToMiddleButtonCenter = widthWithXSpacing * (amountOfScenes / 2) + widthWithXSpacing / 2;

	for (int i = 0; i < amountOfScenes; i++)
	{
		String windowName         = String("SceneWindow##") + std::to_string(i);
		const float uiElementPosX = halfScreenSizeX - widthEdgeToMiddleButtonCenter + widthWithXSpacing * i;
		ImGui::SetNextWindowPos(ImVec2(viewport->WorkPos.x + uiElementPosX,
                                   viewport->WorkPos.y + 30.0f),
                                     ImGuiCond_Once);

		if(!ImGui::Begin(windowName.c_str(), &m_ActiveScenes[i], windowFlags))
		{
			ImGui::End();
		}
		else
		{
			CreateUnloadSceneButton(i, {size.x, 30.0f},
							[i]() -> void
									{
										LOG("Scene " << i << " is unloaded!")
									});

			CreateViewSceneButton(i, {size.x, size.y},
							[i]() -> void
                                  {
										LOG("Scene " << i << " is loaded!")
                                  });
			ImGui::End();
		}
	}
}

void MainScene::CreateUnloadSceneButton(const int sceneID,
                                        const glm::vec2& size,
                                        const std::function<void()> onUnload)
{
	const String closeButtonName = String("Close##Scene") + std::to_string(sceneID);
	if (!m_ActiveScenes[sceneID])
	{
		ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
	}
			
	if (ImGui::Button(closeButtonName.c_str(), {size.x, size.y}))
	{
		if (m_ActiveScenes[sceneID])
		{
			m_ActiveScenes[sceneID] = false;
			onUnload();
			return;
		}
	}
		
	if (!m_ActiveScenes[sceneID])
	{
		ImGui::PopItemFlag();
		ImGui::PopStyleVar();
	}
}

void MainScene::CreateViewSceneButton(int sceneID,
								      const glm::vec2& size,
								      const std::function<void()> onView)
{
	const String sceneName = String("Scene ") + std::to_string(sceneID);
	
	if (m_ActiveScenes[sceneID])
	{
		ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
	}

	if (ImGui::Button(sceneName.c_str(), {size.x, size.y}))
	{
		if (!m_ActiveScenes[sceneID])
		{
			m_ActiveScenes[sceneID] = true;
			onView();
			return;
		}
	}

	if (m_ActiveScenes[sceneID])
	{
		ImGui::PopItemFlag();
		ImGui::PopStyleVar();
	}
}

bool MainScene::AreAllScenesLoaded()
{
	for (auto& flag : m_ActiveScenes)
	{
		if (!flag)
		{
			return false;
		}
	}
	return true;
}

void MainScene::ViewAllScenes()
{
	
}
