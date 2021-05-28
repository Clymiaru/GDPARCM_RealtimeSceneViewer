#include "pch.h"
#include "AScene.h"

AScene::AScene(StringRef name) :
	m_Name{name}
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

StringRef AScene::GetName() const
{
	return m_Name;
}
