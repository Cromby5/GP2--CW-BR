#include "GameProcess.h"
#include <iostream>
#include <string>

Transform transform;

GameProcess::GameProcess()
{
	_gameState = GameState::PLAY;
	DisplayWindow* _gameDisplay = new DisplayWindow(); //new display
	SkyBox* sky = new SkyBox(); //new skybox
	ObjectHandler* objectHandler = new ObjectHandler(); //new object handler
	
	MeshHandler* mesh1 = new MeshHandler();
	MeshHandler* mesh2 = new MeshHandler();
}

GameProcess::~GameProcess()
{
}

void GameProcess::run()
{
	initSystems(); 
	gameProcessLoop();
}

void GameProcess::initSystems()
{
	_gameDisplay.initDisplay();
	sky.initSkyBox();
	objectHandler.initObjects();
	gameAudio.initAudio();
	
	myCamera.initWorldCamera(glm::vec3(0, 0, 5), 70.0f, (float)_gameDisplay.getScreenWidth()/_gameDisplay.getScreenHeight(), 0.01f, 1000.0f);

	counter = 1.0f;
}

void GameProcess::gameProcessLoop()
{
	while (_gameState != GameState::EXIT)
	{
		// deltatime
		lastTicks = currentTicks;
	    currentTicks = SDL_GetPerformanceCounter();
		deltatime = ((currentTicks - lastTicks) * 1 / (double)SDL_GetPerformanceFrequency());; // deltatime values are in ms
		
		gameAudio.playBackMusic();
		Input();
		drawGame();
		objectHandler.collision(deltatime,gameAudio);
	}
}

void GameProcess::Input()
{
	SDL_Event event;
	while(SDL_PollEvent(&event)) // Get and process events using the SDL event system 
	{
		switch (event.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
						while (deltatime > 0) // Key presses will still be registered from the keydown event, however they will only be processed if the deltatime is positive
						{
							case SDLK_w:
								myCamera.MoveForward(speed);
								break;
							case SDLK_s:
								myCamera.MoveForward(-speed);
								break;
							case SDLK_a:
								myCamera.MoveRight(-speed);
								break;
							case SDLK_d:
								myCamera.MoveRight(speed);
								break;
							case SDLK_ESCAPE:
								_gameState = GameState::EXIT;
								break;
						}
					}
				break;
			case SDL_MOUSEMOTION:
				SDL_SetRelativeMouseMode(SDL_TRUE); // Lock mouse to window and hide it from view 
				myCamera.RotateX((-event.motion.xrel / 1000.0f)); // Rotate camera on X axis (Remove the - on the xrel to invert the rotation)
				myCamera.RotateY((-event.motion.yrel / 1000.0f)); // Rotate camera on Y axis (Remove the - on the yrel to invert the rotation)
				break;
		}
	}
}

void GameProcess::drawGame()
{
	_gameDisplay.clearDisplayBuffer(0.0f, 0.0f, 0.0f, 1.0f);
	
	//drawFog();
	sky.drawSkyBox(myCamera);
	objectHandler.drawObjects(myCamera,counter);
	
	//glStencilFunc(GL_ALWAYS, 1, 0xFF);
	//glStencilMask(0xFF);
	
	transform.SetPos(glm::vec3(2.0, 1.5, 3.0));
	transform.SetRot(glm::vec3(0.0, 0.0, 0.0));
	transform.SetScale(glm::vec3(1.0, 1.0, 1.0));
	
	sky.drawCube(transform, myCamera);

	counter += deltatime * 1.0f;
	// Enable Writing to the Stencil Buffer?
	/*
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilMask(0x00);
	glDisable(GL_DEPTH_TEST);
	
	// Draw Outline

	
	// Disable Writing to the Stencil Buffer?
	glStencilMask(0xFF);
	glStencilFunc(GL_ALWAYS, 0, 0xFF);
	glEnable(GL_DEPTH_TEST);
	*/
	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();
	_gameDisplay.swapBuffer();
} 

void GameProcess::drawFog()
{
	// fog
	GLfloat fogColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glFogfv(GL_FOG_COLOR, fogColor);
	
	glFogi(GL_FOG_MODE, GL_EXP);
	glFogf(GL_FOG_DENSITY, 0.65f);
	float colour[] = {0.5,0.5,0.5,1.0};
	glFogfv(GL_FOG_COLOR, colour);
	float col[] = {1.0,1.0,1.0,1.0};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, col);
	//glFogf(GL_FOG_START, 1.0f);
	//glFogf(GL_FOG_END, 5.0f);
}








