#pragma once

#include <XYZ.h>

struct Pixel
{
	uint8_t R, G, B, A;
};

class Chunk
{
public:
	static constexpr glm::ivec2 sc_ChunkSize = { 32, 32 };

public:
	Chunk(const glm::vec2& position);
	~Chunk();

	void Render();
	void SetPixel(uint32_t x, uint32_t y, Pixel pixel);
	void SetCircle(uint32_t x, uint32_t y, uint8_t radius, Pixel pixel);

	glm::vec2 GetPosition() const { return m_Position; }
private:
	XYZ::Ref<XYZ::Texture2D> m_Texture;
	glm::vec2				 m_Position;
	Pixel*					 m_Pixels;
	bool					 m_Dirty = false;
};