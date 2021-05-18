#include "pch.h"
#include "Core/App.h"

class RealtimeSceneViewer final : public App
{
public:
	RealtimeSceneViewer() :
		App()
	{
		// App specific initialization
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
