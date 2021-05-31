#include "pch.h"
#include "LoadMeshAction.h"
#include "AssetManagement/Model/Model.h"

LoadMeshAction::LoadMeshAction(StringRef assetName,
							   StringRef filepath,
							   StringRef basepath,
							   StringRef sceneOwner,
							   std::mutex& resourceMutex,
							   AssetTable& assetTable,
							   HashTable<String, int>& currentAssetCountPerScene,
							   int& currentAsset) :
	  m_AssetName{assetName},
	  m_Filepath{filepath},
	  m_Basepath{basepath},
	  m_SceneOwnerName{sceneOwner},
	  m_ResourceMutex(resourceMutex),
	  m_AssetTable(assetTable),
	  m_CurrentAssetCountPerScene(currentAssetCountPerScene),
	  m_CurrentAsset(currentAsset)
{
}

void LoadMeshAction::OnStartTask()
{
	Model* model = new Model(this->m_AssetName,
							 this->m_Filepath,
					  this->m_Basepath);

	this->m_ResourceMutex.lock();
	LOG("Threading!!!!!" << m_SceneOwnerName);
	this->m_AssetTable[m_AssetName] = model;
	this->m_CurrentAssetCountPerScene[m_SceneOwnerName]++;
	this->m_ResourceMutex.unlock();
}