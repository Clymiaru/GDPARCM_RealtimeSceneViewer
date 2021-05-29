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
	LoadResources();
}

void AScene::Unload()
{
	UnloadResources();
}

void AScene::SetCamera(Camera& mainCamera)
{
	m_Camera = &mainCamera;
}

StringRef AScene::GetName() const
{
	return m_Name;
}
