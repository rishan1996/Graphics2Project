#pragma once

#include <map>
#include <string>

#include "GLTexture.h"

namespace GameEngine3D {

	class TextureCache{
	public:
		//Return texture if found in map(textureCache), if not found then load texture and add to cache
		GLTexture getTexture(std::string filePath);

	private:
		//Key is file path, value is texture
		std::map<std::string, GLTexture> _textureCache;
	};

}