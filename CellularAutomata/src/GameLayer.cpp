#include "GameLayer.h"


GameLayer::GameLayer()
{
	XYZ::Application::Get().GetImGuiLayer()->EnableDockspace(false);
}

GameLayer::~GameLayer()
{

}