#pragma once
#include "Asset.h"
#include "Utils/Log.h"
#include <mutex>

#include "Model/Model.h"
#include "RenderSystem/Shader.h"
#include "Threading/ThreadPoolManager.h"

using AssetTable = HashTable<String, Model*>;

class AssetManager final
{
public:
	AssetManager(const AssetManager& other)                = delete;
	AssetManager(AssetManager&& other) noexcept            = delete;
	AssetManager& operator=(const AssetManager& other)     = delete;
	AssetManager& operator=(AssetManager&& other) noexcept = delete;
	
	static AssetManager& GetInstance();
	~AssetManager();

	void LoadAsync(StringRef sceneOwnerName,
				   StringRef assetName,
                   StringRef filepath,
                   StringRef basepath);

	void Unload(StringRef sceneOwnerName,
				StringRef assetName);

	Model& Acquire(StringRef assetName);

	int GetAssetsLoaded(StringRef sceneName);
	
private:
	AssetManager();
	AssetTable m_AssetTable;
	std::mutex* m_ResourceMutex;

	HashTable<String, int> m_MaxAssetCountPerScene = HashTable<String, int>();
	HashTable<String, int> m_CurrentAssetCountPerScene = HashTable<String, int>();
	int m_CurrentAssetCount = 0;
	int m_MaxAssetCount = 0;
};