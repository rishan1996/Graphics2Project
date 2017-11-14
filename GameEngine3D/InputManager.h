#pragma once

#include <unordered_map>
#include <glm/glm.hpp>

namespace GameEngine3D {

	class InputManager{
	public:
		InputManager();

		void pressKey(unsigned int keyID);
		void releaseKey(unsigned int keyID);

		void setMouseCoords(float x, float y); ///< Set the mouse coordinates

		bool isKeyDown(unsigned int keyID); ///< Returns true if key is held down

		bool isKeyPressed(unsigned int keyID); ///< Returns true if the key was just been pressed

		bool isKeyReleased(unsigned int keyID); ///< Returns true if the key was just released

		bool isKeyHeld(unsigned int keyID); ///< Returns true if the key is still down

		void update(); ///< Keeps track of previous key state

		//Accessors
		glm::vec2 getMouseCoords() const;

	private:
		bool wasKeyDown(unsigned int keyID); ///< Checks if key was down last frame

		std::unordered_map<unsigned int, bool> _keyMap; ///< Stores a map of keys
		std::unordered_map<unsigned int, bool> _previousKeyMap; ///< Used for isKeyPressed function

		glm::vec2 _mouseCoordinates;

	};

	inline glm::vec2 InputManager::getMouseCoords() const { return _mouseCoordinates; }

}

