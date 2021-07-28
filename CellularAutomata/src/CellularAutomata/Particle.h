#pragma once

#include <glm/glm.hpp>
#include <vector>


enum MaterialType
{
	SandMaterialType,
	NumMaterialTypes
};

struct Particle;
class Material
{
public:
	virtual ~Material() = default;
	virtual void Update(std::vector<Particle>& readBuffer, std::vector<Particle>& writeBuffer, uint32_t x, uint32_t y) = 0;
};


class SandMaterial : public Material
{
public:
	virtual void Update(std::vector<Particle>& readBuffer, std::vector<Particle>& writeBuffer, uint32_t x, uint32_t y) override;
};

struct Particle
{
	uint32_t  MaterialType = SandMaterialType;
	bool	  Active	   = false;
};