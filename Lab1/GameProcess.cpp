#include "GameProcess.h"
#include <iostream>
#include <string>


Transform transform;

GameProcess::GameProcess()
{
	_gameState = GameState::PLAY;
	DisplayWindow* _gameDisplay = new DisplayWindow(); //new display
	SkyBox* sky = new SkyBox(); //new skybox
	MeshHandler* mesh1();
	MeshHandler* mesh2();
	counter = 0;
	whistle = 0;
	backGroundMusic = 0;
	
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
	//whistle = audioDevice.loadSound("..\\res\\bang.wav");
	gameAudio.addAudioTrack("..\\res\\background.wav");

	mesh1.loadModel("..\\res\\monkey3.obj");
	mesh2.loadModel("..\\res\\monkey3.obj");
	
	myCamera.initWorldCamera(glm::vec3(0, 0, -5), 70.0f, (float)_gameDisplay.getWidth()/_gameDisplay.getHeight(), 0.01f, 1000.0f);

	shader.init("..\\res\\shader"); //new shader
	skyShader.init("..\\res\\SkyboxShader"); //new skybox shader

	counter = 1.0f;
}

void GameProcess::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		gameAudio.playAudioTrack();
		processInput();
		drawGame();
		collision(mesh1.getSpherePos(), mesh1.getSphereRadius(), mesh2.getSpherePos(), mesh2.getSphereRadius());
		//playAudio(backGroundMusic, glm::vec3(0.0f, 0.0f, 0.0f));
	}
}

void GameProcess::processInput()
{
	SDL_Event evnt;
	
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
						case SDLK_w:
							myCamera.MoveForward(1.0f);
						break;
						case SDLK_s:
							myCamera.MoveForward(-1.0f);
							break;
						case SDLK_a:
							myCamera.MoveRight(1.0f);
							break;
						case SDLK_d:
							myCamera.MoveRight(-1.0f);
							break;
						case SDLK_q:
							myCamera.Pitch(0.1f);
							break;
						case SDLK_e:
							myCamera.Pitch(-0.1f);
							break;
						case SDLK_x:
							myCamera.RotateY(0.1f);
							break;
						case SDLK_z:
							myCamera.RotateY(-0.1f);
							break;
					}
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
	_gameDisplay.clearDisplay(0.0f, 0.0f, 0.0f, 1.0f);

	glDepthMask(GL_FALSE);
	skyShader.Use();
	skyShader.Update(transform, myCamera);
	sky.drawSkyBox(transform, myCamera);

	transform.SetPos(glm::vec3(sinf(counter), 0.5, 0.0));
	transform.SetRot(glm::vec3(0.0, 0.0, counter * 5));
	transform.SetScale(glm::vec3(0.6, 0.6, 0.6));
	
	TextureMap texture("..\\res\\bricks.jpg"); //load texture
	TextureMap texture1("..\\res\\water.jpg"); //load texture

	shader.Use();
	shader.Update(transform, myCamera);
	texture.Bind(0);
	mesh1.draw();
	mesh1.updateSphereData(*transform.GetPos(), 0.6f);
	
	transform.SetPos(glm::vec3(-sinf(counter), -0.5, -sinf(counter)*5));
	transform.SetRot(glm::vec3(0.0, 0.0, counter * 5));
	transform.SetScale(glm::vec3(0.6, 0.6, 0.6));

	shader.Update(transform, myCamera);
	texture1.Bind(0);
	mesh2.draw();
	mesh2.updateSphereData(*transform.GetPos(), 0.6f);
	counter = counter + 0.05f;
	
	// ... draw rest of the scene
	//glm::mat4 view = glm::mat4(glm::mat3(myCamera.GetViewMatrix()));
	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();

	_gameDisplay.swapBuffer();
} 