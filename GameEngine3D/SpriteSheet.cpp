#include "SpriteSheet.h"

namespace GameEngine3D {

	void SpriteSheet::initialise(const GLTexture& texture, const glm::ivec2& dimensions){
		this->texture = texture;
		this->dimensions = dimensions;
	}

	glm::vec4 SpriteSheet::getUV(int index){
		int x, y;
		glm::vec4 uv;

		if (index != 0) {
			x = index % dimensions.x;
			y = index / dimensions.x;

			uv.x = x / (float)dimensions.x;
			uv.y = y / (float)dimensions.y;
			
		}
		else {
			x = 0;
			y = 0;

			uv.x = (float)x;
			uv.y = (float)y;
		}

		uv.z = 1.0f / dimensions.x;
		uv.w = 1.0f / dimensions.y;

		return uv;
	}

}