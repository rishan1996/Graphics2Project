#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "Vertex.h"

namespace GameEngine3D {

	enum class GlyphSortType {
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};

	struct Glyph {
		GLuint textureID;

		float depth;

		Vertex topLeft;
		Vertex bottomLeft;
		Vertex topRight;
		Vertex bottomRight;

	};

	class RenderBatch {
		public:

			RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) : offset(Offset), numVertices(NumVertices), texture(Texture){}

			GLuint offset;
			GLuint numVertices;
			GLuint texture;
	};

	class SpriteBatch {
	public:
		SpriteBatch();

		void initialise();

		//Get SpriteBatch ready for rendering
		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
		//Does some postprocessing such as sorting the glyphs
		void end();

		//This will add what you want to draw to the renderBatch
		//The z and w component of destinationRect and uvRect represent width and height respectively 
		void draw(const glm::vec4& destinationRect, const glm::vec4& uvRect, GLuint textureID, float depth, const ColourRGBA8& colour);

		//This will render all the sprites to the screen
		void renderBatch();

	private:

		void createRenderBatches();
		void createVertexArray();
		void sortGlyphs();

		static bool compareFrontToBack(Glyph* a, Glyph*b);
		static bool compareBackToFront(Glyph* a, Glyph*b);
		static bool compareTexture(Glyph* a, Glyph*b);

		//Vertex buffer object id
		GLuint _vboID;

		//Vertex array object id
		GLuint _vaoID;

		GlyphSortType _sortType;

		//Store our glyphs
		std::vector<Glyph*> _glyphs;

		//Store out render batches
		std::vector<RenderBatch> _renderBatches;

	};

}