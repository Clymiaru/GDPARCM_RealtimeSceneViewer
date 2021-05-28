#pragma once
#include "Asset.h"
#include "Utils/Log.h"
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

private:
	AssetManager();
	HashTable<AssetTag, AssetTable> m_AssetStorage;
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
	auto& selectedAssetStorage = m_AssetStorage[Resource::GetStaticTag()];
	const auto found           = selectedAssetStorage.find(name);
	ASSERT(found != selectedAssetStorage.end(),
	       "Attempted to delete a non-existent " << Resource::GetStaticTag() << " (" << name << ")!")
	auto* deletedAsset = selectedAssetStorage[name];
	selectedAssetStorage.erase(name);
	delete deletedAsset;
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