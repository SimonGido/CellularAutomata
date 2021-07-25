#include "Chunk.h"

Chunk::Chunk(const glm::vec2& position)
	:
	m_Position(position)
{
	m_Texture = XYZ::Texture2D::Create(sc_ChunkSize.X, sc_ChunkSize.Y, 4, {});

	m_Pixels = new Pixel[m_Texture->GetWidth() * m_Texture->GetHeight()];
	memset(m_Pixels, 255, m_Texture->GetWidth() * m_Texture->GetHeight() * sizeof(Pixel));
	m_Texture->SetData(m_Pixels, m_Texture->GetWidth() * m_Texture->GetHeight() * sizeof(Pixel));
}

Chunk::~Chunk()
{
	m_Texture.Reset();
}

void Chunk::Render()
{
	if (m_Dirty)
	{
		m_Texture->SetData(m_Pixels, m_Texture->GetWidth() * m_Texture->GetHeight() * sizeof(Pixel));
		m_Dirty = false;
	}
	XYZ::Renderer2D::SubmitQuad(
		glm::translate(glm::vec3(m_Position, 0.0f)), 
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		XYZ::Renderer2D::SetTexture(m_Texture),
		glm::vec4(1.0f)
	);
}

void Chunk::SetPixel(uint32_t x, uint32_t y, Pixel pixel)
{	
	static constexpr uint32_t channels = 4;
	if (x < m_Texture->GetWidth() && y < m_Texture->GetHeight())
	{
		uint32_t index = (y * m_Texture->GetWidth()) + x;
		m_Pixels[index] = pixel;
		m_Dirty = true;
	}
}

void Chunk::SetCircle(uint32_t x, uint32_t y, uint8_t radius, Pixel pixel)
{
	int32_t halfRadius = radius / 2;
	int32_t xMax = x + halfRadius;
	int32_t xMin = x - halfRadius;
	int32_t yMax = y + halfRadius;
	int32_t yMin = y - halfRadius;
	for (int32_t i = xMin; i < xMax; ++i)
	{
		for (int32_t j = yMin; j < yMax; ++j)
		{
			if (glm::distance(glm::vec2{ i, j }, glm::vec2{ x, y }) < (float)radius / 2.0f
			&& i >= 0 && j >= 0)
				SetPixel(i, j, pixel);
		}
	}
}
