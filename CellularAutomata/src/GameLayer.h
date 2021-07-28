#pragma once

#include <XYZ.h>

#include "CellularAutomata/World.h"


class GameLayer : public XYZ::Layer
{
public:
	GameLayer();
	~GameLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(XYZ::Timestep ts) override;
	virtual void OnEvent(XYZ::Event& event) override;
	virtual void OnImGuiRender() override;

private:
	void displayStats();

private:
	XYZ::OrthographicCameraController m_CameraController;
	glm::vec2						  m_MousePosition;
	World							  m_World;
};

