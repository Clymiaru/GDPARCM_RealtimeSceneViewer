#include "pch.h"
#include "MainScene.h"

#include <string>

#include <ImGui/imgui.h>

#include <glm/vec2.hpp>

#include "Core/App.h"

#include "Utils/Log.h"

MainScene::MainScene() :
	AScene{STRINGIFY(MainScene)},
	m_Progress{0.1f}
{
}

MainScene::~MainScene()
{
}

void MainScene::LoadResources()
{
}

void MainScene::RenderUI()
{
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
	
	CreateViewAllButton({150.0f, 60.0f}, 25.0f);
	
	for (int i = 0; i < 5; i++)
	{
		CreateSceneButton(i, {150.0f, 150.0f}, 50.0f);
	}
}

void MainScene::UnloadResources()
{
}

void MainScene::CreateViewAllButton(const glm::vec2& size,
									float spacing)
{
	ImGuiWindowFlags viewAllButtonFlags = 0;
	viewAllButtonFlags |= ImGuiWindowFlags_NoTitleBar;
	viewAllButtonFlags |= ImGuiWindowFlags_NoScrollbar;
	viewAllButtonFlags |= ImGuiWindowFlags_NoMove;
	viewAllButtonFlags |= ImGuiWindowFlags_NoResize;
	viewAllButtonFlags |= ImGuiWindowFlags_NoBackground;

	const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + main_viewport->Size.x - size.x - spacing,
                                   main_viewport->WorkPos.y + main_viewport->Size.y - size.y - spacing),
									 ImGuiCond_Once);
	
	ImGui::Begin("MainSceneViewAllArea", nullptr, viewAllButtonFlags);
	{
		if (ImGui::Button("View All", {size.x, size.y}))
		{
			// Button press action
		}
	}
	ImGui::End();
}

void MainScene::CreateSceneButton(int sceneID,
								  const glm::vec2& size,
								  float xSpacing)
{
	ImGuiWindowFlags viewAllButtonFlags = 0;
	viewAllButtonFlags |= ImGuiWindowFlags_NoTitleBar;
	viewAllButtonFlags |= ImGuiWindowFlags_NoScrollbar;
	viewAllButtonFlags |= ImGuiWindowFlags_NoMove;
	viewAllButtonFlags |= ImGuiWindowFlags_NoResize;
	viewAllButtonFlags |= ImGuiWindowFlags_NoBackground;

	const ImGuiViewport* main_viewport = ImGui::GetMainViewport();

	const float halfScreenSizeX = App::Width / 2.0f;
	const float sizeXAndSpacingX       = size.x + xSpacing;
	
	ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + halfScreenSizeX - (sizeXAndSpacingX * 2 + sizeXAndSpacingX / 2) + sizeXAndSpacingX * sceneID,
                                   main_viewport->WorkPos.y + 30.0f),
                                     ImGuiCond_Once);
	
	String windowName = String("Scene##") + std::to_string(sceneID);
	ImGui::Begin((windowName + "Window").c_str(), nullptr, viewAllButtonFlags);
	{
		if (ImGui::Button(windowName.c_str(), {size.x, size.y}))
		{
			// Button press action
		}
	}
	ImGui::End();
}
