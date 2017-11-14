#pragma once

#include <GL/glew.h>

namespace GameEngine3D {

	struct Position {
		Position() : x(0), y(0){}
		
		Position(float a, float b) : x(a), y(b){}
		
		float x;
		float y;
	};

	//Represents rgba colour
	struct ColourRGBA8 {
		ColourRGBA8() : r(0), g(0), b(0), a(0){}

		ColourRGBA8(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha) 
			: r(red), g(green), b(blue), a(alpha) {}

		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	};

	struct UV {
		UV() : u(0), v(0){}

		UV(float U, float V) : u(U), v(V){}

		float u;
		float v;
	};

	struct Vertex {
		Position position;
		ColourRGBA8 colour;
		UV uv; ///< UV texture coordinates

		void setPosition(float xPos, float yPos) {
			position.x = xPos;
			position.y = yPos;
		}

		void setColour(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha) {
			colour.r = red;
			colour.g = green;
			colour.b = blue;
			colour.a = alpha;
		}

		void setUV(float u, float v) {
			uv.u = u;
			uv.v = v;
		}
	};

}