#pragma once
#include "Utils/TypeAlias.h"

using AssetTag = CString;
#define MAKE_ASSET(assetTag) static AssetTag GetStaticTag() { return #assetTag; }\
							virtual AssetTag GetTag() const override { return GetStaticTag(); }

class Asset
{
public:
	Asset(const Asset& other)					= delete;
	Asset(Asset&& other) noexcept				= delete;
	Asset& operator=(const Asset& other)		= delete;
	Asset& operator=(Asset&& other) noexcept	= delete;

	Asset(StringRef name,
	      StringRef filepath);
	virtual ~Asset();
	virtual AssetTag GetTag() const;
protected:
	String m_Name;
	String m_Filepath;
};
