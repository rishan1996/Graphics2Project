#include "TextureCache.h"
#include "ImageLoader.h"

namespace GameEngine3D {

	GLTexture TextureCache::getTexture(std::string filePath) {

		//Search the map using binary search for the key with the same path
		auto textureIterator = _textureCache.find(filePath);

		//Check if texture was not in the map
		if (textureIterator == _textureCache.end()) {
			//If no texture then load it in
			GLTexture tempTexture = ImageLoader::loadPNG(filePath);

			//Insert the texture into the map
			_textureCache.emplace(filePath, tempTexture);

			//Return the texture
			return tempTexture;
		}

		//Texture is contained in the map
		return textureIterator->second; //Iterator contains a pair, return the value
	}

}