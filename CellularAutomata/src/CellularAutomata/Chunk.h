#pragma once

#include <XYZ.h>

struct IVec2
{
	uint32_t X, Y;
};

class Chunk
{
public:
	static constexpr IVec2 sc_ChunkSize = { 512, 512 };

public:
	Chunk(const glm::vec2& position);


private:
	XYZ::Ref<XYZ::Texture2D> m_Texture;
	glm::vec2				 m_Position;
};