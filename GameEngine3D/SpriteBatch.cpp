#include "SpriteBatch.h"

#include <algorithm>

namespace GameEngine3D {

	SpriteBatch::SpriteBatch() :_vboID(0), _vaoID(0)
	{
	}

	void SpriteBatch::initialise(){
		createVertexArray();
	}

	void SpriteBatch::begin(GlyphSortType sortType /*default = GlyphSortType::TEXTURE */){
		_sortType = sortType;

		//Reset the vector size
		_renderBatches.clear();
		
		//Delete all the glyphs
		for (Glyph* currentGlyph : _glyphs) 
			delete currentGlyph;
		
		_glyphs.clear();
	}

	void SpriteBatch::end(){
		sortGlyphs();
		createRenderBatches();
	}

	void SpriteBatch::draw(const glm::vec4& destinationRect, const glm::vec4& uvRect, GLuint textureID, float depth, const ColourRGBA8& colour){
		Glyph* newGlyph = new Glyph;
		newGlyph->textureID = textureID;
		newGlyph->depth = depth;

		newGlyph->topLeft.colour = colour;
		newGlyph->topLeft.setPosition(destinationRect.x, destinationRect.y + destinationRect.w);
		newGlyph->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		newGlyph->bottomLeft.colour = colour;
		newGlyph->bottomLeft.setPosition(destinationRect.x, destinationRect.y);
		newGlyph->bottomLeft.setUV(uvRect.x, uvRect.y);

		newGlyph->topRight.colour = colour;
		newGlyph->topRight.setPosition(destinationRect.x + destinationRect.z, destinationRect.y + destinationRect.w);
		newGlyph->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

		newGlyph->bottomRight.colour = colour;
		newGlyph->bottomRight.setPosition(destinationRect.x + destinationRect.z, destinationRect.y );
		newGlyph->bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

		_glyphs.push_back(newGlyph);

	}

	//Loop through the render batches and draw them all
	void SpriteBatch::renderBatch(){
		glBindVertexArray(_vboID);

		for (RenderBatch currentBatch : _renderBatches) {
			//Bind the texture
			glBindTexture(GL_TEXTURE_2D, currentBatch.texture);

			glDrawArrays(GL_TRIANGLES, currentBatch.offset, currentBatch.numVertices);
		}

		glBindVertexArray(0);
	}
	
	//Create separate render batches for glyphs with different textures
	void SpriteBatch::createRenderBatches(){
		//Create a render batch for the first glyph
		std::vector<Vertex> vertices;
		//Reserve the memory needed in one step to avoid resizing the vector constantly
		vertices.resize(_glyphs.size() * 6);

		if (_glyphs.empty())
			return;

		//Current vertex(can also be used as an offset)
		int currentVertex = 0;

		_renderBatches.emplace_back(currentVertex, 6, _glyphs[0]->textureID);
		vertices[currentVertex++] = _glyphs[0]->topLeft;
		vertices[currentVertex++] = _glyphs[0]->bottomLeft;
		vertices[currentVertex++] = _glyphs[0]->bottomRight;

		vertices[currentVertex++] = _glyphs[0]->bottomRight;
		vertices[currentVertex++] = _glyphs[0]->topRight;
		vertices[currentVertex++] = _glyphs[0]->topLeft;

		for (int currentGlyph = 1; currentGlyph < (int)_glyphs.size(); currentGlyph++) {
			//If different texture create a new render batch
			if (_glyphs[currentGlyph]->textureID != _glyphs[currentGlyph - 1]->textureID)
				_renderBatches.emplace_back(currentVertex, 6, _glyphs[currentGlyph]->textureID);
			else //Else add it to the same batch
				_renderBatches.back().numVertices += 6;

			vertices[currentVertex++] = _glyphs[currentGlyph]->topLeft;
			vertices[currentVertex++] = _glyphs[currentGlyph]->bottomLeft;
			vertices[currentVertex++] = _glyphs[currentGlyph]->bottomRight;

			vertices[currentVertex++] = _glyphs[currentGlyph]->bottomRight;
			vertices[currentVertex++] = _glyphs[currentGlyph]->topRight;
			vertices[currentVertex++] = _glyphs[currentGlyph]->topLeft;
		}

		//Bind the vertex data to the buffer
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);

		//Orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

		//Upload the data
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		//Unbind the buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	void SpriteBatch::createVertexArray(){
		if(_vaoID == 0)
			glGenVertexArrays(1, &_vaoID);

		glBindVertexArray(_vaoID);

		if (_vboID == 0)
			glGenBuffers(1, &_vboID);

		glBindBuffer(GL_ARRAY_BUFFER, _vboID);

		//Enable use of vertex arrays
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//Position attribute pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

		//Colour attribute pointer
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, colour));

		//UV attribute pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		glBindVertexArray(0);


	}

	void SpriteBatch::sortGlyphs(){
		switch(_sortType) {
			case GlyphSortType::BACK_TO_FRONT:
				std::stable_sort(_glyphs.begin(), _glyphs.end(), compareBackToFront);
				break;

			case GlyphSortType::FRONT_TO_BACK:
				std::stable_sort(_glyphs.begin(), _glyphs.end(), compareFrontToBack);
				break;

			case GlyphSortType::TEXTURE:
				std::stable_sort(_glyphs.begin(), _glyphs.end(), compareTexture);
				break;

		}
	}

	bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b){
		return (a->depth < b->depth);
	}

	bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b){
		return (a->depth > b->depth);
	}

	bool SpriteBatch::compareTexture(Glyph* a, Glyph* b){
		return (a->textureID < b->textureID);
	}


}