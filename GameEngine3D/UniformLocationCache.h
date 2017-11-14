#pragma once

#include <GL/glew.h>
#include <string>
#include <map>

#include "GLSLProgram.h"

namespace GameEngine3D {

	class UniformLocationCache{
	public:
		//Return the uniform location if found in map, if not found then load location and add to cache
		GLuint getUniformLocation(std::string locationOf, GLSLProgram* currentProgram);

	private:
		//Key is variable name, value is locationID
		std::map<std::string, GLuint> _uniformLocationCache;

	};

}