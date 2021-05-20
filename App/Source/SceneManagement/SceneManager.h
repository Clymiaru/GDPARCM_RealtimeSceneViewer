#pragma once

class SceneManager final
{
public:
	static SceneManager& GetInstance();
	~SceneManager() = default;
};
