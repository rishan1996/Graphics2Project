#include "InputManager.h"

namespace GameEngine3D {

	InputManager::InputManager() : _mouseCoordinates(0)
	{
	}

	void InputManager::pressKey(unsigned int keyID) {
		_keyMap[keyID] = true;
	}

	void InputManager::releaseKey(unsigned int keyID) {
		_keyMap[keyID] = false;
	}

	//Keeps track of mouse coordinates
	void InputManager::setMouseCoords(float x, float y){
		_mouseCoordinates.x = x;
		_mouseCoordinates.y = y;
	}

	bool InputManager::isKeyDown(unsigned int keyID) {
		auto it = _keyMap.find(keyID);
		if (it != _keyMap.end())
			return it->second;
		else
			return false;
	}

	bool InputManager::isKeyPressed(unsigned int keyID){
		if (isKeyDown(keyID) == true && wasKeyDown(keyID) == false)
			return true;
		else
			return false;
	}

	bool InputManager::isKeyReleased(unsigned int keyID) {
		if (isKeyDown(keyID) == false && wasKeyDown(keyID) == true)
			return true;
		else
			return false;
	}

	bool InputManager::isKeyHeld(unsigned int keyID) {
		if (isKeyDown(keyID) == true && wasKeyDown(keyID) == true)
			return true;
		else
			return false;
	}

	void InputManager::update(){
		for (auto& it : _keyMap) 
			_previousKeyMap[it.first] = it.second;
		

	}

	bool InputManager::wasKeyDown(unsigned int keyID) {
		auto it = _previousKeyMap.find(keyID);
		if (it != _previousKeyMap.end())
			return it->second;
		else
			return false;
	}

}