#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include <SDL/SDL_mixer.h>
#include "DisplayWindow.h" 
#include "ShaderHandler.h"
#include "MeshHandler.h"
#include "TextureMap.h"
#include "transform.h"
#include "AudioHandler.h"
#include "WorldCamera.h"
#include "SkyBox.h"

enum class GameState{PLAY, EXIT};

class GameProcess
{
public:
	GameProcess();
	~GameProcess();

	void run();

private:

	void initSystems();
	void processInput();
	void gameLoop();
	void drawGame();
	bool collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad);
	//void playAudio(unsigned int Source, glm::vec3 pos);

	DisplayWindow _gameDisplay;
	GameState _gameState;
	MeshHandler mesh1;
	MeshHandler mesh2;
	WorldCamera myCamera;
	ShaderHandler shader;
	ShaderHandler skyShader;
	
	AudioHandler gameAudio;
	SkyBox sky;

	float counter;
	unsigned int whistle;
	unsigned int backGroundMusic;
};

