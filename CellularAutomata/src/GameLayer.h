#pragma once

#include <XYZ.h>


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
	XYZ::OrthographicCameraController m_CameraController;
	XYZ::Renderer2DStats			  m_RendererStats;
	XYZ::Timestep					  m_Timestep;
	glm::vec2						  m_MousePosition;

	XYZ::Ref<XYZ::Texture2D>		  m_Texture;
	XYZ::Ref<XYZ::Shader>			  m_Shader;
};

