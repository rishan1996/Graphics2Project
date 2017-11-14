#pragma once

#include <glm/glm.hpp>

#include "GLTexture.h"

namespace GameEngine3D{

	class SpriteSheet{
	public:
		SpriteSheet();
		~SpriteSheet();

		void initialise(const GLTexture& texture, const glm::ivec2& dimensions);

		glm::vec4 getUV(int index);

		GLTexture texture;
		glm::ivec2 dimensions;
	};

}