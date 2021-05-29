#include "pch.h"
#include "AScene.h"

#include "Core/App.h"

AScene::AScene(StringRef name) :
	m_Name{name},
	m_Camera{nullptr}
{
}

void AScene::Load()
{
	m_Camera = new Camera(glm::radians(60.0f), static_cast<float>(App::Width) / App::Height);
	LoadResources();
}

void AScene::Unload()
{
	UnloadResources();
}

StringRef AScene::GetName() const
{
	return m_Name;
}
