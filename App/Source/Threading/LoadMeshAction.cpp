#include "pch.h"
#include "LoadMeshAction.h"
#include "AssetManagement/Model/Model.h"

LoadMeshAction::LoadMeshAction(StringRef assetName, StringRef filename, StringRef basepath, Shader& shader, StringRef sceneOwner, std::mutex& m_ResourceMutex, AssetTable& m_AssetTable, HashTable<String, int>& m_CurrentAssetCountPerScene, int& m_CurrentAsset)
	: m_ResourceMutex(m_ResourceMutex), m_AssetTable(m_AssetTable), m_CurrentAssetCountPerScene(m_CurrentAssetCountPerScene), m_CurrentAsset(m_CurrentAsset), shader(shader)
{
	this->assetName = assetName;
	this->filename = filename;
	this->basepath = basepath;
	this->sceneOwner = sceneOwner;
}

void LoadMeshAction::OnStartTask()
{
	Model* model = new Model(this->assetName, this->filename, this->basepath, this->shader, this->sceneOwner);

	this->m_ResourceMutex.lock();
	LOG("Threading!!!!!");
	this->m_AssetTable[assetName] = model;
	this->m_CurrentAssetCountPerScene[sceneOwner]++;
	this->m_ResourceMutex.unlock();
}
