#pragma once

//Include files from our game engine
#include <GameEngine3D/GameEngine3D.h>
#include <GameEngine3D/Sprite.h>
#include <GameEngine3D/GLSLProgram.h>
#include <GameEngine3D/GLTexture.h>
#include <GameEngine3D/Window.h>
#include <GameEngine3D/Camera3D.h>
#include <GameEngine3D/SpriteBatch.h>
#include <GameEngine3D/InputManager.h>
#include <GameEngine3D/FPSLimiter.h>
#include <GameEngine3D/SpriteFont.h>

#include <glm\glm.hpp>

enum class GameState{PLAY, EXIT, PAUSED, WON, DIED};

class MainGame {
public:

	MainGame();
	~MainGame();
	
	void run(); ///< Function to run the program

private:
	void initialiseSystems();
	void initialiseShaders();
	void gameLoop();
	void processInput();
	void drawGame();

	glm::vec2 m_screenDimensions;

	float m_fps;
	float m_maxFPS;
	std::string m_title;

	GameState m_gameState; ///< Keep track of game state

	GameEngine3D::Window m_window; ///< Main window
	GameEngine3D::Camera3D m_camera; ///< Main camera
	GameEngine3D::Camera3D m_hudCamera; ///< HUD camera
	GameEngine3D::SpriteBatch m_spriteBatch;
	GameEngine3D::SpriteFont* m_spriteFont;
	GameEngine3D::SpriteBatch m_fontSpriteBatch;
	GameEngine3D::FPSLimiter m_fpsLimiter;
	GameEngine3D::InputManager m_inputManager;
	GameEngine3D::GLSLProgram m_sProgram;
	

};
