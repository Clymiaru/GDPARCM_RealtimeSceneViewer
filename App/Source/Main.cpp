#include "pch.h"
#include "Core/App.h"

#include "SceneManagement/SceneManager.h"
#include "SceneManagement/Scenes/MainScene.h"
#include "SceneManagement/Scenes/FirstScene.h"

class RealtimeSceneViewer final : public App
{
public:
	RealtimeSceneViewer() :
		App(1280, 720)
	{
		// App specific initialization
		SceneManager::GetInstance().RegisterScenes(
        {
			new MainScene(),
			new FirstScene()
        });
	}

	~RealtimeSceneViewer() override
	{
		// App specific deinitialization
	}
};

int main()
{
	RealtimeSceneViewer app = RealtimeSceneViewer();
	app.Run();

	return 0;
}
