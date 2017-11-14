#pragma once

#include "TextureCache.h"
#include "UniformLocationCache.h"

namespace GameEngine3D {

	//Static class
	class ResourceManager{
	public:
		static GLTexture getTexture(std::string filePath);
		static GLuint getLocation(std::string locationOf, GLSLProgram* currentProgram);

	private:
		static TextureCache _textureCache;
		static UniformLocationCache _locationCache;
	};

}