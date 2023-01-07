#pragma once
#include <string>
#include <GL\glew.h>
#include "transform.h"
#include "TextureMap.h"
#include "MeshHandler.h"
#include "ShaderHandler.h"
#include "WorldCamera.h"

class Object
{
public:
	
	Object(ShaderHandler shader, TextureMap texture, const std::string& modelName);
	~Object();
	void drawObject(WorldCamera& myCamera);

	
private:
	Transform objectTransform;
	TextureMap objectTexture;
	ShaderHandler objectShader;
	MeshHandler objectMesh;
	
};

