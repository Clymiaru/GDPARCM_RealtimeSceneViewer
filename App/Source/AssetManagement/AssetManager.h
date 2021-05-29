#pragma once
#include "Asset.h"
#include "Utils/Log.h"
#include <mutex>
#include "RenderSystem/Shader.h"
#include "Threading/ThreadPoolManager.h"
#include "Threading/LoadMeshAction.h"

using AssetTable = HashTable<String, Asset*>;

class AssetManager final
{
public:
	AssetManager(const AssetManager& other)                = delete;
	AssetManager(AssetManager&& other) noexcept            = delete;
	AssetManager& operator=(const AssetManager& other)     = delete;
	AssetManager& operator=(AssetManager&& other) noexcept = delete;
	
	static AssetManager& GetInstance();
	~AssetManager();

	template <typename Resource, typename ...Args>
	void Load(StringRef name,
	          StringRef filepath,
			  Args&& ... args);

	template <typename Resource>
	void Unload(StringRef name);

	template <typename Resource>
	Resource& Acquire(StringRef name);


	template <typename Resource>
	void LoadAsync(StringRef sceneName, StringRef assetName, StringRef filename, StringRef basepath, Shader& shader);




private:
	AssetManager();
	HashTable<AssetTag, AssetTable> m_AssetStorage;

	AssetTable m_AssetTable;
	HashTable<String, int> m_MaxAssetCountPerScene;
	HashTable<String, int> m_CurrentAssetCountPerScene;
	int m_CurrentAsset;
	int m_MaxAssetCount = 0;
	std::mutex* m_ResourceMutex;

};

template <typename Resource, typename ...Args>
void AssetManager::Load(StringRef name,
                       StringRef filepath,
						Args&& ... args)
{
	auto& selectedAssetStorage = m_AssetStorage[Resource::GetStaticTag()];
	const auto found           = selectedAssetStorage.find(name);
	if (found == selectedAssetStorage.end())
		selectedAssetStorage[name] = new Resource(name, filepath, std::forward<Args>(args) ...);
	ASSERT(found == selectedAssetStorage.end(),
	       Resource::GetStaticTag() << " (" << name << ") has already been loaded!")
}

template <typename Resource>
void AssetManager::Unload(StringRef name)
{

	const auto found           = m_AssetTable.find(name);
	ASSERT(found != m_AssetTable.end(),
	       "Attempted to delete a non-existent " << Resource::GetStaticTag() << " (" << name << ")!")
	auto* deletedAsset = m_AssetTable[name];
	m_AssetTable.erase(name);
	delete deletedAsset;

	this->m_MaxAssetCountPerScene[sceneOwner]--;
	this->m_CurrentAssetCountPerScene[sceneOwner]--;
	this->m_CurrentAsset--;
	this->m_MaxAssetCount--;
}

template <typename Resource>
Resource& AssetManager::Acquire(StringRef name)
{
	auto& selectedAssetStorage = m_AssetStorage[Resource::GetStaticTag()];
	auto* found                = selectedAssetStorage[name];
	ASSERT(found != nullptr,
	       Resource::GetStaticTag() << " (" << name << ") does not exist!")
	return *static_cast<Resource*>(found);
}

template<typename Resource>
inline void AssetManager::LoadAsync(StringRef sceneName, StringRef assetName, StringRef filename, StringRef basepath, Shader& shader)
{
	auto isFound = this->m_AssetTable.find(assetName);
	if (isFound == this->m_AssetStorage.end())
	{
		m_MaxAssetCountPerScene[sceneOwner]++;
		m_MaxAssetCount++;

		LoadMeshAction* action = new LoadMeshAction(assetName,
			filename,
			basepath,
			shader,
			sceneOwner,
			&m_ResourceMutex,
			&m_AssetTable,
			&m_CurrentAssetCountPerScene,
			&m_CurrentAsset);

		ThreadPoolManager::GetInstance().scheduleTask(sceneName, action);
	}
}

