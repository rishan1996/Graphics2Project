#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>

namespace GameEngine3D {

	//Enum for creating window flags 
	//Assign the flags to separate bits so we can combine flags
	enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 , WINDOWED = 0x8};

	class Window{
	public:
		int createWindow(std::string windowName, int windowWidth, int windowHeight, GLuint currentFlags);

		void swapBuffer();

		int getWindowWidth() { return _windowWidth; }

		int getWindowHeight() { return _windowHeight; }

	private:
		SDL_Window* _window;

		int _windowWidth, _windowHeight;
	};

}