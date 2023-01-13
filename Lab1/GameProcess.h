#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include <SDL/SDL_mixer.h>
#include <vector>
#include "DisplayWindow.h" 
#include "transform.h"
#include "AudioHandler.h"
#include "WorldCamera.h"
#include "SkyBox.h"
#include "ObjectHandler.h"

enum class GameState{PLAY, EXIT};

class GameProcess
{
public:
	GameProcess();
	~GameProcess();

	void run();

private:

	void initSystems();
	void Input();
	void gameProcessLoop();
	void drawGame();
	void drawFog();

	DisplayWindow _gameDisplay;
	GameState _gameState;
	WorldCamera myCamera;
	
	AudioHandler gameAudio;
	
	SkyBox sky;
	ObjectHandler objectHandler;

	float counter = 0.0f;
	float speed = 0.5f;
	// deltatime variables, keeping track of time and keep it consitent between variable frame rates
	float deltatime = 0.0f;
	float lastTicks = 0.0f;
	float currentTicks = 0.0f;
};

