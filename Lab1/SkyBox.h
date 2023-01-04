#pragma once
#include <GL/glew.h>
#include <glm\glm.hpp>
#include "WorldCamera.h"
#include "ShaderHandler.h"

using namespace std;

class SkyBox
{
public:
	SkyBox();
	~SkyBox();
	
	unsigned int initSkyBox();

	void drawSkyBox(Transform transform, WorldCamera camera);
	
	unsigned int textureID;

private:
	GLuint vbo;
	GLuint vao;
	GLuint ebo;
	ShaderHandler shader;
};

