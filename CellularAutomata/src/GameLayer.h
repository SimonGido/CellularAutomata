#pragma once

#include <XYZ.h>

class GameLayer : public XYZ::Layer
{
public:
	GameLayer();
	~GameLayer();

	virtual void OnAttach() override {};
	virtual void OnDetach() override {};
	virtual void OnUpdate(XYZ::Timestep ts) override {};
	virtual void OnEvent(XYZ::Event& event) override {};
	virtual void OnImGuiRender() override {};
};

