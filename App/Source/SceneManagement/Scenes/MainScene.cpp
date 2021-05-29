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

const int MAX_MESH_SCENES = 5;

constexpr float CalculateAverage(std::array<float, MAX_MESH_SCENES> sceneProgress)
{
	float result = 0.0f;
	for (auto progress : sceneProgress)
	{
		result += progress;
	}
	result /= MAX_MESH_SCENES;
	return result;
}

MainScene::MainScene() :
	AScene{STRINGIFY(MainScene)}
{
}

MainScene::~MainScene()
{
}

void MainScene::RenderMeshes()
{
	this->mesh->Draw(m_Camera->GetViewProjectionMatrix());
}

void MainScene::RenderUI()
{
	m_Ticks += 0.01f;

	if (m_Ticks > 2.0f)
	{
		for (int i = 0; i < MAX_MESH_SCENES; i++)
		{
			if (m_LoadingProgress[i] < 1.0f && i != 2)
			{
				m_LoadingProgress[i] += 0.002f;
			}
		}
	}
	
	CreateDebugWindow();
	SetDebugRespectiveAttributes();
	
	CreateViewAllButton({150.0f, 60.0f}, 25.0f);
	CreateSceneButtons(5, {125.0f, 125.0f}, 50.0f);
	CreateAllSceneLoadingBar({App::Width - 200.0f, 30.0f});
}

void MainScene::LoadResources()
{
	m_Camera = new Camera(glm::radians(45.0f), static_cast<float>(App::Width) / static_cast<float>(App::Height));

	this->shader = new Shader("Content/Shaders/vertShader.glsl", "Content/Shaders/fragShader.glsl");
	this->mesh = Mesh::Load("Content/3D_Models/", "", *this->shader);
	//this->mesh->GetTransform().
}

void MainScene::UnloadResources()
{
}

void MainScene::CreateDebugWindow()
{
	ImGuiWindowFlags windowFlags = 0;
	windowFlags |= ImGuiWindowFlags_NoSavedSettings;
	windowFlags |= ImGuiWindowFlags_NoScrollbar;
	windowFlags |= ImGuiWindowFlags_NoResize;
 
	const ImGuiViewport* viewport = ImGui::GetMainViewport();

	const ImVec2 windowSize = {
		300.0f,
        150.0f
    };
	
	const ImVec2 windowPos = {
		viewport->WorkPos.x,
		viewport->WorkPos.y + viewport->Size.y - windowSize.y
	};
	ImGui::SetNextWindowPos(windowPos, ImGuiCond_Once);
	ImGui::SetNextWindowSize(windowSize, ImGuiCond_Once);
	
	if(!ImGui::Begin("Debug Window", nullptr, windowFlags))
	{
		ImGui::End();
	}
	else
	{
		if (ImGui::TreeNode("Camera"))
		{
			ImGui::DragFloat3("Position", &m_DebugData.CameraPosition.x, 0.01f);
			ImGui::DragFloat3("Rotation", &m_DebugData.CameraRotation.x, 0.01f);

			if (ImGui::Button("Reset", {100.0f, 20.0f}))
			{
				m_DebugData.CameraPosition = {0.0f, 0.0f, 0.0f};
				m_DebugData.CameraRotation = {0.0f, 0.0f, 0.0f};
			}

			ImGui::TreePop();
		}
		
		ImGui::End();
	}
}

void MainScene::SetDebugRespectiveAttributes() const
{
	m_Camera->SetPosition(m_DebugData.CameraPosition);
	m_Camera->SetRotation(m_DebugData.CameraRotation.x,
						  m_DebugData.CameraRotation.y,
						  m_DebugData.CameraRotation.z);

}

void MainScene::CreateViewAllButton(const glm::vec2& size,
                                    const float spacing)
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
									 
	if (!ImGui::Begin("View All Button", nullptr, windowFlags))
	{
		ImGui::End();
	}
	else
	{
		if (m_ViewAllScenes)
		{
			ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
		}
			
		if (ImGui::Button("View All", {size.x, size.y}))
		{
			if (!m_ViewAllScenes)
			{
				ViewAllScenes();
				ImGui::End();
				return;
			}
		}
		
		if (m_ViewAllScenes)
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

		if(!ImGui::Begin(windowName.c_str(), &m_ScenesLoaded[i], windowFlags))
		{
			ImGui::End();
		}
		else
		{
			CreateUnloadSceneButton(i, {size.x, 30.0f});
			CreateViewSceneButton(i, {size.x, size.y});
			CreatePerSceneLoadingBar(i, {size.x, 20.0f});
			ImGui::End();
		}
	}
}

void MainScene::CreateUnloadSceneButton(const int sceneID,
                                        const glm::vec2& size)
{
	const String closeButtonName = String("Close##Scene") + std::to_string(sceneID);
	if (!m_ScenesLoaded[sceneID])
	{
		ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
	}
			
	if (ImGui::Button(closeButtonName.c_str(), {size.x, size.y}))
	{
		if (m_ScenesLoaded[sceneID])
		{
			UnloadScene(sceneID);
			return;
		}
	}
		
	if (!m_ScenesLoaded[sceneID])
	{
		ImGui::PopItemFlag();
		ImGui::PopStyleVar();
	}
}

void MainScene::CreateViewSceneButton(const int sceneID,
                                      const glm::vec2& size)
{
	const String sceneName = String("Scene ") + std::to_string(sceneID);
	
	if (!m_ViewAllScenes &&
		m_ActiveScenes[sceneID] && m_ScenesLoaded[sceneID])
	{
		ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
	}

	if (ImGui::Button(sceneName.c_str(), {size.x, size.y}))
	{
		if (!m_ActiveScenes[sceneID] && m_ScenesLoaded[sceneID])
		{
			ViewScene(sceneID);
			return;
		}

		if (!m_ActiveScenes[sceneID] && !m_ScenesLoaded[sceneID])
		{
			LoadScene(sceneID);
			return;
		}
	}

	if (!m_ViewAllScenes &&
		m_ActiveScenes[sceneID] && m_ScenesLoaded[sceneID])
	{
		ImGui::PopItemFlag();
		ImGui::PopStyleVar();
	}
}

void MainScene::CreatePerSceneLoadingBar(const int sceneID,
                                         const glm::vec2& size)
{
	if (m_LoadingProgress[sceneID] < 1.0f)
	{
		ImGui::ProgressBar(m_LoadingProgress[sceneID],
					{size.x, size.y});
	}
}

void MainScene::CreateAllSceneLoadingBar(const glm::vec2& size) const
{
	ImGuiWindowFlags windowFlags = 0;
	windowFlags |= ImGuiWindowFlags_NoSavedSettings;
	windowFlags |= ImGuiWindowFlags_NoTitleBar;
	windowFlags |= ImGuiWindowFlags_NoScrollbar;
	windowFlags |= ImGuiWindowFlags_NoMove;
	windowFlags |= ImGuiWindowFlags_NoResize;
	windowFlags |= ImGuiWindowFlags_NoBackground;

	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(ImVec2(viewport->WorkPos.x + viewport->Size.x / 2.0f - size.x / 2.0f,
                                   viewport->WorkPos.y + viewport->Size.y / 2.0f),
                                     ImGuiCond_Once);
	
	const float averageLoadingProgress = CalculateAverage(m_LoadingProgress);

	if (averageLoadingProgress < 1.0f)
	{
		if (!ImGui::Begin("GlobalLoadingBar", nullptr, windowFlags))
		{
			ImGui::End();
		}
		else
		{
			ImGui::ProgressBar(averageLoadingProgress,
	                {size.x, size.y});

			ImGui::End();
		}
	}
}

void MainScene::ViewAllScenes()
{
	m_ViewAllScenes = true;
}

void MainScene::ViewScene(const int sceneID)
{
	for (int i = 0; i < m_ActiveScenes.size(); i++)
	{
		if (i != sceneID)
		{
			m_ActiveScenes[i] = false;			
		}
	}
	
	m_ActiveScenes[sceneID] = true;
	LOG("View scene " << sceneID);
}

void MainScene::LoadScene(const int sceneID)
{
	m_ScenesLoaded[sceneID] = true;
	LOG("Load scene " << sceneID);
}

void MainScene::UnloadScene(const int sceneID)
{
	m_ScenesLoaded[sceneID] = false;
	LOG("Unload scene " << sceneID);
}