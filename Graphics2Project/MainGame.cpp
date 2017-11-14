#include "MainGame.h"

#include <GameEngine3D/Errors.h>
#include <GameEngine3D/ResourceManager.h>

//Constructor used to initialize variables
MainGame::MainGame() : m_screenDimensions(1280.0f, 720.0f), m_fps(0.0f), m_maxFPS(60.0f), m_title("Graphics 2 Project"), m_gameState(GameState::PLAY){
}

MainGame::~MainGame() {
	delete m_spriteFont;
}

void MainGame::run() {
	initialiseSystems();
	gameLoop();
}

void MainGame::initialiseSystems() {
	GameEngine3D::initialise();

	m_window.createWindow(m_title, (int)m_screenDimensions.x, (int)m_screenDimensions.y, GameEngine3D::WINDOWED); ///< Use our window class to create an SDL Window with the given properties

	initialiseShaders();

	m_camera.initialise(m_screenDimensions);
	m_hudCamera.initialise(m_screenDimensions);
	m_hudCamera.setPosition(glm::vec2(m_screenDimensions.x / 2, m_screenDimensions.y / 2)); ///< Set the position of the hud


	m_spriteBatch.initialise(); ///< Initialise our spritebatch variable

	m_fontSpriteBatch.initialise();

	m_spriteFont = new GameEngine3D::SpriteFont("Fonts/arialbold.ttf", 32);

	m_fpsLimiter.initialise(m_maxFPS); ///< Initialise out fps limiter to max fps(60)
}

void MainGame::initialiseShaders() {
	m_sProgram.compileShaders("Shaders/basic.shader");
	m_sProgram.addAttribute("vertexPosition");
	m_sProgram.addAttribute("vertexColour");
	m_sProgram.addAttribute("vertexUV");
	m_sProgram.linkShaders();
}


void MainGame::gameLoop() {
	//Used to get delta time
	float prevTime = 0;
	float currentTime = (float)SDL_GetTicks();

	while (m_gameState == GameState::PLAY) {
		//Used for frame time measuring 
		prevTime = currentTime;
		currentTime = m_fpsLimiter.begin();

		float deltaTime = currentTime - prevTime;

		//If deltaTime grows too large, lock it down
		if (deltaTime > 0.15f)
			deltaTime = 0.15f;

		m_inputManager.update();

		processInput();

	//	setCameraPosition();
		m_camera.update();
		m_hudCamera.update();

		drawGame();

		m_fpsLimiter.end();

		m_fps = m_fpsLimiter.getFPS();

		//Static variable to tell us when to print fps
		static int counter = 0;

		//Print out the fps
	//	if (counter++ % 500 == 0)
	//		std::cout << _fps << std::endl;
	}

	while (m_gameState == GameState::WON) {
		if (m_inputManager.isKeyPressed(SDLK_SPACE))
			m_gameState = GameState::EXIT;
	}
}

void MainGame::processInput() {
	SDL_Event events;

	//Check if there is an event
	while (SDL_PollEvent(&events)) {
		//Process the event
		switch (events.type) {
			//If the 'X' button is pressed
		case SDL_QUIT:
			m_gameState = GameState::EXIT;
			break;

		case SDL_KEYDOWN:
			m_inputManager.pressKey(events.key.keysym.sym);
			break;

		case SDL_KEYUP:
			m_inputManager.releaseKey(events.key.keysym.sym);
			break;

		case SDL_MOUSEBUTTONDOWN:
			m_inputManager.pressKey(events.button.button);
			break;

		case SDL_MOUSEBUTTONUP:
			m_inputManager.releaseKey(events.button.button);
			break;

			//Track mouse motion 
		case SDL_MOUSEMOTION:
			m_inputManager.setMouseCoords((float)events.motion.x, (float)events.motion.y);
			break;
		}
	}
}

void MainGame::drawGame() {

	//Set the depth to 1.0
	glClearDepth(1.0);

	//Clears the colour buffer and depth buffer with bitwise or
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Enable the shader
	m_sProgram.useProgram();

	//Get the first texture
	glActiveTexture(GL_TEXTURE0);

	//Get the uniform location for texture
	GLuint textureLocation = GameEngine3D::ResourceManager::getLocation("myTexture", &m_sProgram);

	//Send 1 integer to gpu 
	glUniform1i(textureLocation, 0);

	//Get the uniform location for the projection matrix
	GLuint projMatrixLocation = GameEngine3D::ResourceManager::getLocation("projMatrix", &m_sProgram);

	//Set the camera matrix
	glm::mat4 cameraMatrix = m_camera.getCameraMatrix();

	//Send a mat4 to the gpu
	glUniformMatrix4fv(projMatrixLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	//Begin drawing to the sprite batch
	m_spriteBatch.begin();


	//Finish drawing to the sprite batch
	m_spriteBatch.end();

	//Render the batches
	m_spriteBatch.renderBatch();

/*	if (m_gameState == GameState::PLAY)
		drawHud();
	else if (m_gameState == GameState::WON)
		drawEnd();*/

	//Unbind the player texture before finishing drawing
	glBindTexture(GL_TEXTURE_2D, 0);

	//Disable the shader
	m_sProgram.unuseProgram();

	//Swap the buffers
	m_window.swapBuffer();

}

