#include "Sprite.h"
#include "Vertex.h"
#include "ImageLoader.h"
#include "ResourceManager.h"

#include <cstddef>

namespace GameEngine3D {

	Sprite::Sprite() : _vboID(0), _x(0), _y(0), _width(0), _height(0)
	{
	}


	Sprite::~Sprite()
	{
		//If _vboID isn't 0 delete the buffer object
		if (_vboID)
			glDeleteBuffers(1, &_vboID);
	}

	void Sprite::initialize(float x, float y, float width, float height, std::string texturePath) {
		_x = x;
		_y = y;
		_width = width;
		_height = height;


		//Load the texture
		_texture = ResourceManager::getTexture(texturePath);

		//If vertex buffer object hasnt been generated
		if (!_vboID) {
			//Generate buffer and assign it to an id
			glGenBuffers(1, &_vboID);
		}

		Vertex vertexData[6];

		//Set vertex position and colour data 
		for (int i = 0; i < 6; i++) {
			//Set the position
			vertexData[i].position.x = x;
			if (i == 0 || i == 4 || i == 5)
				vertexData[i].position.x += width;

			vertexData[i].position.y = y;
			if (i == 0 || i == 1 || i == 5)
				vertexData[i].position.y += height;

			//Set the color
			vertexData[i].setColour(255, 255, 255, 255);

			//Set the UV data
			if (i == 0 || i == 5)
				vertexData[i].setUV(1.0f / 3.0f, 1.0f);

			else if (i == 2 || i == 3)
				vertexData[i].setUV(0.0f, 2.0f / 3.0f);

			else if (i == 1)
				vertexData[i].setUV(0.0f, 1.0f);

			else
				vertexData[i].setUV(1.0f / 3.0f, 2.0f / 3.0f);

		}

		//vertexData[1].setColour(0, 0, 255, 255);
		//vertexData[4].setColour(255, 0, 0, 255);

		//Bind the buffer object
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);

		//Upload the buffer
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

		//Unbind the buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}


	void Sprite::draw() {

		//Bind the texture
		glBindTexture(GL_TEXTURE_2D, _texture.id);

		//Bind the buffer object
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	
		//Draws array of verticies
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//Disable use of vertex arrays
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		//Unbind the buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}