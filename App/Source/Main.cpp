#include "pch.h"
#include "Core/App.h"

#include "SceneManagement/SceneManager.h"
#include "SceneManagement/Scenes/MainScene.h"

class RealtimeSceneViewer final : public App
{
public:
	RealtimeSceneViewer() :
		App()
	{
		// App specific initialization
		SceneManager::GetInstance().RegisterScenes(
        {
			new MainScene()
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
