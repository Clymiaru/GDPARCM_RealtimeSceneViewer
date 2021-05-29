#include "pch.h"
#include "MainScene.h"

#include <string>
#include <ImGui/imgui.h>
#include <ImGui/imgui_internal.h>
#include <glm/vec2.hpp>
#include "Core/App.h"

#include "SceneManagement/SceneManager.h"
#include "SceneManagement/SceneNames.h"

#include "Utils/Log.h"

constexpr float CalculateAverageProgress(std::array<float, MAX_MESH_SCENES> sceneProgress)
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
	// this->mesh->Draw(m_Camera->GetViewProjectionMatrix());
}

void MainScene::RenderUI()
{
	CreateDebugWindow();
	SetDebugRespectiveAttributes();
	
	CreateSceneButtons(MAX_MESH_SCENES, {125.0f, 125.0f}, 50.0f);
	CreateMainSceneLoadingBar({App::Width - 200.0f, 30.0f});
	CreateViewAllButton({150.0f, 60.0f}, 25.0f);
}

void MainScene::Update(const float deltaTime)
{
	m_Ticks += deltaTime;

	if (m_Ticks > 0.7f)
	{
		for (int i = 0; i < MAX_MESH_SCENES; i++)
		{
			if (m_ScenesStartedLoading[i])
			{
				if (m_ScenesLoadingProgress[i] < 1.0f)
				{
					// Fake loading simulation
					m_ScenesLoadingProgress[i] += 0.05f;
				}

				if (m_ScenesLoadingProgress[i] >= 1.0f)
				{
					// When loading is complete, the scene is considered loaded
					m_ScenesFinishedLoading[i] = true;
					m_ScenesStartedLoading[i] = false;
				}
			}
		}
		m_Ticks = 0.0f;
	}
}

void MainScene::LoadResources()
{
	m_Camera = new Camera(glm::radians(45.0f), static_cast<float>(App::Width) / static_cast<float>(App::Height));

	this->shader = new Shader("Content/Shaders/vertShader.glsl", "Content/Shaders/fragShader.glsl");
	this->mesh = Mesh::Load("Content/3D_Models/", "teapot", *this->shader);
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
			ImGui::DragFloat3("Position", &m_DebugData.CameraPosition.x, 0.001f);
			ImGui::DragFloat3("Rotation", &m_DebugData.CameraRotation.x, 0.001f);

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

	const String buttonName = m_ViewAllScenes ? "Hide All" : "View All";
	
	if (!ImGui::Begin("ViewHide All Button", nullptr, windowFlags))
	{
		ImGui::End();
	}
	else
	{
		if (ImGui::Button(buttonName.c_str(), {size.x, size.y}))
		{
			if (!m_ViewAllScenes)
			{
				ViewAllScenes();
			}
			else
			{
				HideAllScenes();
			}
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
	windowFlags |= ImGuiWindowFlags_AlwaysAutoResize;
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

		if(!ImGui::Begin(windowName.c_str(), nullptr, windowFlags))
		{
			ImGui::End();
		}
		else
		{
			CreateUnloadSceneButton(i, {20.0f, 20.0f});

			CreateViewSceneButton(i, {size.x, size.y});

			CreateLoadSceneButton(i, {size.x, 20.0f});

			CreateSceneLoadingBar(i, {size.x, 20.0f});

			ImGui::End();
		}
	}
}

void MainScene::CreateUnloadSceneButton(const int sceneID,
                                        const glm::vec2& size)
{
	const String closeButtonName = String("X##Scene") + std::to_string(sceneID);
	const bool sceneIsLoaded = m_ScenesFinishedLoading[sceneID];
	
	if (!sceneIsLoaded)
	{
		ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
	}
	
	ImGui::PushStyleColor(ImGuiCol_Button, {0.8f, 0.0f, 0.0f, 1.0f});
	if (ImGui::Button(closeButtonName.c_str(), {size.x, size.y}))
	{
		if (sceneIsLoaded)
		{
			UnloadScene(sceneID);
		}
	}
	ImGui::PopStyleColor();
	
	if (!sceneIsLoaded)
	{
		ImGui::PopItemFlag();
		ImGui::PopStyleVar();
	}
}

void MainScene::CreateViewSceneButton(const int sceneID,
                                      const glm::vec2& size)
{
	const String viewSceneName = String("View Scene ") + std::to_string(sceneID);

	const bool sceneIsActive = m_ScenesActive[sceneID];
	const bool sceneIsLoaded = m_ScenesFinishedLoading[sceneID];
	
	if (sceneIsActive)
	{
		ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
	}
	
	if (ImGui::Button(viewSceneName.c_str(), {size.x, size.y}))
	{
		if (!sceneIsActive)
		{
			ViewScene(sceneID);	
		}
	}
	
	if (sceneIsActive)
	{
		ImGui::PopItemFlag();
		ImGui::PopStyleVar();
	}
}

void MainScene::CreateLoadSceneButton(int sceneID,
									  const glm::vec2& size)
{
	const bool sceneIsStartedLoading = m_ScenesStartedLoading[sceneID];
	const bool sceneIsLoaded = m_ScenesFinishedLoading[sceneID];
	if (sceneIsStartedLoading || sceneIsLoaded)
	{
		return;
	}
	const String sceneName = String("Scene ") + std::to_string(sceneID);
	const String loadSceneName = String("Load Scene ") + std::to_string(sceneID);
	String sceneButtonName = "";

	ImGui::PushStyleColor(ImGuiCol_Button, {0.6f, 0.6f, 0.2f, 1.0f});
	if (ImGui::Button(loadSceneName.c_str(), {size.x, size.y}))
	{
		LoadScene(sceneID);
	}
	ImGui::PopStyleColor();
}

void MainScene::CreateSceneLoadingBar(const int sceneID,
                                         const glm::vec2& size)
{
	if (m_ScenesStartedLoading[sceneID])
	{
		if (!m_ScenesFinishedLoading[sceneID])
		{
			ImGui::ProgressBar(m_ScenesLoadingProgress[sceneID],
                        {size.x, size.y});
		}
	}
}

void MainScene::CreateMainSceneLoadingBar(const glm::vec2& size) const
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


	bool isThereAnActiveMesh = false;
	int sceneID = -1;
	for (int i = 0; i < MAX_MESH_SCENES; i++)
	{
		if (m_ScenesActive[i])
		{
			isThereAnActiveMesh = true;
			sceneID = i;
			break;
		}
	}

	
	if (isThereAnActiveMesh)
	{
		// Show loading bar of that scene
		if (m_ScenesLoadingProgress[sceneID] < 1.0f)
		{
			if (!ImGui::Begin("ActiveSceneLoadingBar", nullptr, windowFlags))
			{
				ImGui::End();
			}
			else
			{
				const float progress = m_ScenesLoadingProgress[sceneID];
				char overlay[32];
				ImFormatString(overlay, IM_ARRAYSIZE(overlay), "%.0f%%", progress * 100 + 0.01f);

				if (!m_ScenesStartedLoading[sceneID] || m_ScenesFinishedLoading[sceneID])
				{
					ImGui::ProgressBar(progress,
                                {size.x, size.y}, "Not yet loaded!");
				}
				else
				{
					ImGui::ProgressBar(progress,
                                {size.x, size.y}, overlay);
				}
				
				ImGui::End();
			}
		}
	}
	else if (m_ViewAllScenes)
	{
		// Show summary loading bar
		const float averageLoadingProgress = CalculateAverageProgress(m_ScenesLoadingProgress);

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

	// show nothing
}

void MainScene::ViewAllScenes()
{
	// SceneManager::GetInstance().ActivateScenes({ SceneNames::SCENE_0,
	// 													  SceneNames::SCENE_1,
	// 													  SceneNames::SCENE_2,
	// 													  SceneNames::SCENE_3,
	// 													  SceneNames::SCENE_4});
	
	for (int i = 0; i < m_ScenesActive.size(); i++)
	{
		m_ScenesActive[i] = true;			
	}
	m_ViewAllScenes = true;
}

void MainScene::HideAllScenes()
{
	// SceneManager::GetInstance().ActivateScenes({ SceneNames::SCENE_0,
 //                                                          SceneNames::SCENE_1,
 //                                                          SceneNames::SCENE_2,
 //                                                          SceneNames::SCENE_3,
 //                                                          SceneNames::SCENE_4});
	
	for (int i = 0; i < m_ScenesActive.size(); i++)
	{
		m_ScenesActive[i] = false;			
	}
	m_ViewAllScenes = false;
}

void MainScene::ViewScene(const int sceneID)
{
	for (int i = 0; i < m_ScenesActive.size(); i++)
	{
		if (i != sceneID && m_ScenesFinishedLoading[i])
		{
			// Make other scenes inactive
			m_ScenesActive[i] = false;			
		}
	}
	
	// Make this scene active
	m_ScenesActive[sceneID] = true;
	LOG("View scene " << sceneID);
}

void MainScene::LoadScene(const int sceneID)
{
	m_ScenesStartedLoading[sceneID] = true;
	LOG("Load scene " << sceneID);
}

void MainScene::UnloadScene(const int sceneID)
{
	m_ScenesLoadingProgress[sceneID] = 0.0f;
	m_ScenesFinishedLoading[sceneID] = false;
	m_ScenesActive[sceneID] = false;
 	LOG("Unload scene " << sceneID);
}