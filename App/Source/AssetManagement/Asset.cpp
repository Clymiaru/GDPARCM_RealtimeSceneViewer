#include "pch.h"
#include "Asset.h"

Asset::Asset(StringRef name,
             StringRef filepath) :
	m_Name(name),
	m_Filepath(filepath)
{
}

Asset::~Asset()
{
}

AssetTag Asset::GetTag() const
{
	return "Untagged";
}
