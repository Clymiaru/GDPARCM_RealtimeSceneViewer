#include "pch.h"
#include "Core/App.h"

#include "SceneManagement/SceneManager.h"
#include "SceneManagement/Scenes/MainScene.h"
#include "SceneManagement/Scenes/Scene0.h"
#include "SceneManagement/Scenes/Scene1.h"
#include "SceneManagement/Scenes/Scene2.h"
#include "SceneManagement/Scenes/Scene3.h"
#include "SceneManagement/Scenes/Scene4.h"

#include "Threading/ThreadPoolManager.h"

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
	ThreadPoolManager::GetInstance().startScheduler("Scene0", 5);
	ThreadPoolManager::GetInstance().startScheduler("Scene1", 5);
	ThreadPoolManager::GetInstance().startScheduler("Scene2", 5);
	ThreadPoolManager::GetInstance().startScheduler("Scene3", 5);
	ThreadPoolManager::GetInstance().startScheduler("Scene4", 5);
	
	RealtimeSceneViewer app = RealtimeSceneViewer();
	app.Run();

	return 0;
}
