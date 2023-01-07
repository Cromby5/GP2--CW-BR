#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include <SDL/SDL_mixer.h>
#include <vector>
#include "DisplayWindow.h" 
#include "ShaderHandler.h"
#include "MeshHandler.h"
#include "TextureMap.h"
#include "transform.h"
#include "AudioHandler.h"
#include "WorldCamera.h"
#include "SkyBox.h"
#include "Object.h"

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
	void gameLoop();
	void drawGame();
	void drawSphere(ShaderHandler& shader,MeshHandler& mesh, TextureMap& texture, float x, float y, float z);
	void drawFog();
	bool collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad);
	//void playAudio(unsigned int Source, glm::vec3 pos);

	DisplayWindow _gameDisplay;
	GameState _gameState;
	MeshHandler mesh1;
	MeshHandler mesh2;
	WorldCamera myCamera;
	ShaderHandler shader;
	ShaderHandler skyShader;
	ShaderHandler reflectShader;
		
	TextureMap texture;
	TextureMap texture1;
	
	AudioHandler gameAudio;
	SkyBox sky;

	vector<Object> objects;
	vector<TextureMap> textures;
		
	float counter = 0.0f;
	
	float deltatime = 0.0f;
	float lastTicks = 0.0f;
	float currentTicks = 0.0f;
	
	unsigned int whistle = 0;
	unsigned int backGroundMusic = 0;

	
};

