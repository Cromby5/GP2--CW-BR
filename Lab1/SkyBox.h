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
	
	void initSkyBox();
	void loadCubeMap();

	void drawSkyBox();
	
	unsigned int textureID;
	
private:
	GLuint vbo;
	GLuint vao;
	GLuint ebo;
	ShaderHandler shader;
};

