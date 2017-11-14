#include "Window.h"
#include "Errors.h"

namespace GameEngine3D {

	int Window::createWindow(std::string windowName, int windowWidth, int windowHeight, GLuint currentFlags) {
		//Flags to be passed to SDL window
		GLuint flags = SDL_WINDOW_OPENGL;

		//Add the flags contained in 'currentFlags' to 'flags'
		if (currentFlags & INVISIBLE)
			flags |= SDL_WINDOW_HIDDEN;

		//True fullscreen
		if (currentFlags & FULLSCREEN)
			flags |= SDL_WINDOW_FULLSCREEN; //SDL_WINDOW_FULLSCREEN_DESKTOP will take the size of the desktop(fake fullscreen)

		if (currentFlags & BORDERLESS)
			flags |= SDL_WINDOW_BORDERLESS;

		if (currentFlags & WINDOWED)
			flags |= SDL_WINDOW_SHOWN;

		//Create and open a SDL window
		_window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, flags);

		//Error checking on window
		if (_window == nullptr)
			fatalError("SDL Window could not be created!");

		//Creating a context 
		SDL_GLContext glContext = SDL_GL_CreateContext(_window);

		//Error checking on context
		if (glContext == nullptr)
			fatalError("SDL_GL context could not be created!");

		//Initialize glew 
		GLenum error = glewInit(); //glewInit() throws a GLenum

		//Error checking on glew
		if (error != GLEW_OK)
			fatalError("Could not initialize glew!");

		//Print out the OpenGL version
		printf("**** OpenGL Version: %s ****\n", glGetString(GL_VERSION));

		//Set background colour
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		//Turns off V-Sync
		SDL_GL_SetSwapInterval(0);

		//Enable alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//Return 0 if no errors
		return 0;
	}

	void Window::swapBuffer() {
		//Swap our buffer and push everything to the window
		SDL_GL_SwapWindow(_window);
	}

}