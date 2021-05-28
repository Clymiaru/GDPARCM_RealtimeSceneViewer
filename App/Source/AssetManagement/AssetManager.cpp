#include "pch.h"
#include "AssetManager.h"

AssetManager& AssetManager::GetInstance()
{
	static AssetManager instance;
	return instance;
}

AssetManager::AssetManager() :
	m_AssetStorage(HashTable<AssetTag, AssetTable>())
{
}

AssetManager::~AssetManager()
{
	m_AssetStorage.clear();
}