#pragma once
#include "IWorkerAction.h"
#include "Utils/Log.h"
#include "Utils/TypeAlias.h"
#include <mutex>
#include "RenderSystem/Shader.h"
#include "AssetManagement/AssetManager.h"


class LoadMeshAction final : public IWorkerAction
{
public:
	LoadMeshAction(StringRef assetName,
				   StringRef filepath,
				   StringRef basepath,
				   StringRef sceneOwner,
				   std::mutex& resourceMutex,
				   AssetTable& assetTable,
				   HashTable<String, int>& currentAssetCountPerScene,
				   int &currentAsset);
	~LoadMeshAction() override = default;

	void OnStartTask() override;
private:
	String m_AssetName;
	String m_Filepath;
	String m_Basepath;
	String m_SceneOwnerName;
	std::mutex& m_ResourceMutex;
	AssetTable& m_AssetTable;
	HashTable<String, int>& m_CurrentAssetCountPerScene;
	int& m_CurrentAsset;
};

