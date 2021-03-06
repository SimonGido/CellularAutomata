#include <XYZ.h>
#include <XYZ/Core/EntryPoint.h>

#include "GameLayer.h"


class Game : public XYZ::Application
{
public:
	Game()
	{
		PushLayer(new GameLayer());
	}

	~Game()
	{

	}
};

XYZ::Application* CreateApplication()
{
	return new Game();
}
