#pragma once

#include "GLTexture.h"

#include <string>

namespace GameEngine3D {

	class ImageLoader{
	public:
		static GLTexture loadPNG(std::string filePath);
	};

}