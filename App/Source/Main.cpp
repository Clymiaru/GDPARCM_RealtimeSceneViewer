#include "pch.h"
#include "Core/App.h"

#include "SceneManagement/SceneManager.h"
#include "SceneManagement/Scenes/MainScene.h"
#include "SceneManagement/Scenes/Scene0.h"
#include "SceneManagement/Scenes/Scene1.h"
#include "SceneManagement/Scenes/Scene2.h"
#include "SceneManagement/Scenes/Scene3.h"
#include "SceneManagement/Scenes/Scene4.h"

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
			new Scene0(),
			new Scene1(),
			new Scene2(),
			new Scene3(),
			new Scene4(),
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
