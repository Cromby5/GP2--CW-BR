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
	
	MeshHandler* mesh1 = nullptr;
	MeshHandler* mesh2 = nullptr;

	//Audio* audioDevice();
}

GameProcess::~GameProcess()
{
}

void GameProcess::run()
{
	initSystems(); 
	gameLoop();
}

void GameProcess::initSystems()
{
	_gameDisplay.initDisplay();
	sky.initSkyBox();
	objectHandler.initObjects();
	//whistle = audioDevice.loadSound("..\\res\\bang.wav");
	gameAudio.addAudioTrack("..\\res\\Audio\\background.wav");

	mesh1.loadModel("..\\res\\Models\\monkey3.obj");
	mesh2.loadModel("..\\res\\Models\\canoe.obj");
	lightCube.loadModel("..\\res\\Models\\cube.obj");

	texture.LoadTexture("..\\res\\Textures\\bricks.jpg", 0);
	texture1.LoadTexture("..\\res\\Textures\\water.jpg", 0);
	
	myCamera.initWorldCamera(glm::vec3(0, 0, 5), 70.0f, (float)_gameDisplay.getScreenWidth()/_gameDisplay.getScreenHeight(), 0.01f, 1000.0f);

	shader.init("..\\res\\shader"); //new shader
	skyShader.init("..\\res\\SkyboxShader"); //new skybox shader
	reflectShader.init("..\\res\\ReflectShader"); //new reflection shader
	refractShader.init("..\\res\\RefractShader"); //new refraction shader
	lightShader.init("..\\res\\LightShader"); //new light shader

	counter = 1.0f;
}

void GameProcess::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		// deltatime
		lastTicks = currentTicks;
	    currentTicks = SDL_GetPerformanceCounter();
		deltatime = ((currentTicks - lastTicks) * 1000 / (double)SDL_GetPerformanceFrequency());;
		
		gameAudio.playAudioTrack();
		Input();
		drawGame();
		collision(mesh1.getSpherePos(), mesh1.getSphereRadius(), mesh2.getSpherePos(), mesh2.getSphereRadius());

		//playAudio(backGroundMusic, glm::vec3(0.0f, 0.0f, 0.0f));	
	}
}

void GameProcess::Input()
{
	SDL_Event evnt;
	float speed = 0.5f;
	while(SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			case SDL_KEYDOWN:
				std::cout << "Key Pressed Down" << std::endl;
					switch (evnt.key.keysym.sym)
					{
						while (deltatime > 0)
						{
							case SDLK_w:
								myCamera.MoveForward(speed);
								break;
							case SDLK_s:
								myCamera.MoveForward(-speed);
								break;
							case SDLK_a:
								myCamera.MoveRight(speed);
								break;
							case SDLK_d:
								myCamera.MoveRight(-speed);
								break;
							case SDLK_ESCAPE:
								_gameState = GameState::EXIT;
								break;
						}
					}
				break;
			case SDL_MOUSEMOTION:
				SDL_SetRelativeMouseMode(SDL_TRUE); // Lock mouse to window and hide it from view 
				myCamera.RotateX((-evnt.motion.xrel / 1000.0f)); // Rotate camera on X axis
				myCamera.RotateY((evnt.motion.yrel / 1000.0f )); // Rotate camera on Y axis
				break;
		}
	}
}

bool GameProcess::collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad)
{
	float distance = ((m2Pos.x - m1Pos.x)*(m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y)*(m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z)*(m2Pos.z - m1Pos.z));
	
	if (distance*distance < (m1Rad + m2Rad))
	{
		//audioDevice.setlistener(myCamera.getPos(), m1Pos); //add bool to mesh
		cout << distance << '\n';
		return true;
	}
	else
	{
		return false;
	}
}

void GameProcess::drawGame()
{
	_gameDisplay.clearDisplayBuffer(0.0f, 0.0f, 0.0f, 1.0f);
	
	//drawFog();
	
	skyShader.Use();
	skyShader.UpdateSky(transform, myCamera);
	sky.drawSkyBox();
	
	objectHandler.drawObjects(myCamera);
	
	//glStencilFunc(GL_ALWAYS, 1, 0xFF);
	//glStencilMask(0xFF);
	drawSphere(shader,mesh1, texture, sinf(counter), 0.5, 0.0);
	
	drawSphere(shader,mesh2, texture1, -sinf(counter), -0.5, -sinf(counter) * 5);
	
	drawSphere(lightShader, lightCube, texture, 5.0, 1.5, 0.0);
	
	transform.SetPos(glm::vec3(2.0, 1.5, 3.0));
	transform.SetRot(glm::vec3(0.0, 0.0, 0.0));
	transform.SetScale(glm::vec3(1.0, 1.0, 1.0));
	
	reflectShader.Use();
	reflectShader.Update(transform, myCamera);
	sky.drawCube();

	counter += deltatime * 0.001f;
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

void GameProcess::drawSphere(ShaderHandler& shader,MeshHandler& mesh, TextureMap& texture,float x,float y,float z)
{
	transform.SetPos(glm::vec3(x, y, z));
	transform.SetRot(glm::vec3(0.0, 0.0, 0.0));
	transform.SetScale(glm::vec3(0.6, 0.6, 0.6));
	shader.Use();
	shader.Update(transform, myCamera);
	texture.Bind(0);
	mesh.draw();
	mesh.updateSphereData(transform.GetPos(), 0.6f);
}

void GameProcess::drawFog()
{
	// fog
	GLfloat fogColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glFogfv(GL_FOG_COLOR, fogColor);
	
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_START, 1.0f);
	glFogf(GL_FOG_END, 5.0f);
	glFogf(GL_FOG_DENSITY, 0.35f);
}








