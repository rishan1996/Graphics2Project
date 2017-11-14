#include "ImageLoader.h"
#include "picoPNG.h"
#include "IOManager.h"
#include "Errors.h"

namespace GameEngine3D {

	GLTexture ImageLoader::loadPNG(std::string filePath) {
		GLTexture texture = {};

		std::vector<unsigned char> in;
		std::vector<unsigned char> out;
		unsigned long width, height;

		//Error check when reading file to buffer
		if (IOManager::readFileToBuffer(filePath, in) == false)
			fatalError("Failed to load the PNG file to the buffer!");

		//Catch the error code returned by this function
		int errorCode = decodePNG(out, width, height, &(in[0]), in.size()); //Fills out variable with the binary data to use for texture

		//Error check the decode PNG function
		if (errorCode != 0)
			fatalError("decodePNG failed with error code: " + errorCode);

		//Generate the OpenGL texture object
		glGenTextures(1, &(texture.id)); //Generate 1 texture and store the id in texture.id

		//Bind the 2D texture
		glBindTexture(GL_TEXTURE_2D, texture.id);

		//Upload image data to the texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		//Set up simple mipmapping
		glGenerateMipmap(GL_TEXTURE_2D);

		//Unbind texture
		glBindTexture(GL_TEXTURE_2D, 0);

		//Set texture width and height
		texture.width = width;
		texture.height = height;

		return texture;
	}

}