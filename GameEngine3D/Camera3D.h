#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> //Used to build orthographic projection matrix

//Include all the files in 3DGameEngine namespace
namespace GameEngine3D {

	class Camera3D
	{
	public:
		Camera3D();

		void initialise(glm::vec2 screenDimensions);

		void update();

		glm::vec2 convertScreentoWorldCoords(glm::vec2 screenCoords);

		bool isBoxInView(const glm::vec2& position, const glm::vec2& dimension);

		//Mutators(Setters)
		void setPosition(const glm::vec2& newPosition) { _position = newPosition; _updateMatrix = true; }
		void setScale(float newScale) { _scale = newScale; _updateMatrix = true; }

		//Accessors(Getters)
		glm::vec2 getPosition() const;
		float getScale() const;

		glm::mat4 getCameraMatrix() const { return _cameraMatrix; }

	private:
		glm::vec2 _screenDimensions;
		bool _updateMatrix;
		float _scale;

		glm::vec2 _position;
		glm::mat4 _cameraMatrix;
		glm::mat4 _orthoMatrix;

	};

	inline glm::vec2 Camera3D::getPosition() const { return _position; }
	inline float Camera3D::getScale() const { return _scale; }
}
