#include "pch.h"
#include "AssetManager.h"

#include "Threading/LoadMeshAction.h"

AssetManager& AssetManager::GetInstance()
{
	static AssetManager instance;
	return instance;
}

AssetManager::AssetManager() :
	m_AssetTable(AssetTable()),
	m_ResourceMutex{new std::mutex()}
{
}

AssetManager::~AssetManager()
{
	m_AssetTable.clear();
}

void AssetManager::LoadAsync(StringRef sceneOwnerName,
							 StringRef assetName,
							 StringRef filepath,
							 StringRef basepath)
{
	const auto found = m_AssetTable.find(assetName);
	
	ASSERT(found == m_AssetTable.end(),
          Model::GetStaticTag() << " (" << assetName << ") has already been loaded!");

	// m_AssetTable[assetName] = new Model(assetName, filepath, basepath);

	LoadMeshAction* action = new LoadMeshAction(assetName,
                                                filepath,
											    basepath,
											    sceneOwnerName,
											*m_ResourceMutex,
									         m_AssetTable,
									         m_CurrentAssetCountPerScene,
											 m_CurrentAssetCount);

	ThreadPoolManager::GetInstance().ScheduleTask(sceneOwnerName, action);
}

void AssetManager::Unload(StringRef sceneOwnerName,
						  StringRef assetName)
{
	const auto found           = m_AssetTable.find(assetName);
	ASSERT(found != m_AssetTable.end(),
	       "Attempted to delete a non-existent " << Model::GetStaticTag() << " (" << assetName << ")!")
	auto* deletedAsset = m_AssetTable[assetName];
	m_AssetTable.erase(assetName);
	delete deletedAsset;
	
	this->m_MaxAssetCountPerScene[sceneOwnerName]--;
	this->m_CurrentAssetCountPerScene[sceneOwnerName]--;
	this->m_CurrentAssetCount--;
	this->m_MaxAssetCount--;
}

Model& AssetManager::Acquire(StringRef assetName)
{
	auto* found = m_AssetTable[assetName];
	ASSERT(found != nullptr,
	       Model::GetStaticTag() << " (" << assetName << ") does not exist!")
	return *found;
}

int AssetManager::GetAssetsLoaded(StringRef sceneName)
{
	return m_CurrentAssetCountPerScene[sceneName];
}
