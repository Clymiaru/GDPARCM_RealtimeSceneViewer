#pragma once
#include "IWorkerAction.h"
#include "Utils/Log.h"
#include "Utils/TypeAlias.h"
#include <mutex>
#include "RenderSystem/Shader.h"
#include "AssetManagement/Asset.h"

using AssetTable = HashTable<String, Asset*>;

class LoadMeshAction : public IWorkerAction
{
public:
	LoadMeshAction(StringRef assetName,
		StringRef filename,
		StringRef basepath,
		Shader &shader,
		StringRef sceneOwner,
		std::mutex &m_ResourceMutex,
		AssetTable &m_AssetTable,
		HashTable<String, int> &m_CurrentAssetCountPerScene,
		int &m_CurrentAsset);


	void OnStartTask() override;

private:
	std::string assetName;
	std::string filename;
	std::string basepath;
	
	std::string sceneOwner;

	LoadMeshAction();
	Shader& shader;
	std::mutex& m_ResourceMutex;
	AssetTable& m_AssetTable;
	HashTable<String, int>& m_CurrentAssetCountPerScene;
	int& m_CurrentAsset;
};

