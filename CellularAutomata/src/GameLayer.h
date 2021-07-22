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
	void putPixel(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	void putCircle(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t a, uint32_t radius);
	void updateTexture();

private:
	XYZ::OrthographicCameraController m_CameraController;
	XYZ::Renderer2DStats			  m_RendererStats;
	XYZ::Timestep					  m_Timestep;
	glm::vec2						  m_MousePosition;

	XYZ::Ref<XYZ::Texture2D>		  m_Texture;
	XYZ::Ref<XYZ::Shader>			  m_Shader;
	uint8_t*						  m_Pixels;
	bool							  m_PixelsDirty;
};

