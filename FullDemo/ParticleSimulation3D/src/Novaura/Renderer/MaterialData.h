#pragma once
#include <glm/glm.hpp>

namespace Novaura {

	struct MaterialData
	{
		float roughness = 0.4f;
		float metallic = 0.4f;
		float ao = 0.0f;
		glm::vec3 albedo = glm::vec3(35.0f / 255.0f, 137.0f / 255.0f, 218.0f / 255.0f);
	};
}
