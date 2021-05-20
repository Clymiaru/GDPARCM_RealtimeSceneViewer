#pragma once
#include <memory>
#include <queue>
#include <unordered_map>
#include <vector>

#define STRINGIFY(x) (#x)

using Uint = unsigned int;
using Uint8 = uint8_t;
using Uint16 = uint16_t;
using Uint32 = uint32_t;
using Uint64 = uint64_t;
using String = std::string;
using StringRef = const String&;
using CString = const char*;

template <typename T>
using List = std::vector<T>;

template <typename T>
using Queue = std::queue<T>;

template <typename Key, typename Value>
using HashTable = std::unordered_map<Key, Value>;

template <typename T>
using ScopePtr = std::unique_ptr<T>;

template <typename T, typename ... Args>
constexpr ScopePtr<T> createScopePtr(Args&& ... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T>
using SharedPtr = std::shared_ptr<T>;

template <typename T, typename ... Args>
constexpr SharedPtr<T> createSharedPtr(Args&& ... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}
