#include "ObjectHandler.h"

ObjectHandler::ObjectHandler()
{
	
}


ObjectHandler::~ObjectHandler()
{
	
}

void ObjectHandler::initObjects()
{
	textures.push_back(TextureMap("..\\res\\Textures\\bricks.jpg"));
	//textures[0].LoadTexture("..\\res\\Textures\\BricksNormal.png", 1);
	//textures[0].LoadTexture("..\\res\\Textures\\BricksSpecularMap.png", 2);
	
	textures.push_back(TextureMap("..\\res\\Textures\\water.jpg"));
	
	shaders.push_back(ShaderHandler("..\\res\\shader"));
	shaders.push_back(ShaderHandler("..\\res\\SkyboxShader"));
	shaders.push_back(ShaderHandler("..\\res\\ReflectShader"));
	shaders.push_back(ShaderHandler("..\\res\\LightShader")); 
	
	Object object1 = Object("..\\res\\Models\\monkey3.obj", textures[0], shaders[0]);
	objects.push_back(object1);
	objects[0].SetObjectPos(glm::vec3(10.0, 1.5, 3.0));
	
	Object object2 = Object("..\\res\\Models\\canoe.obj", textures[0], shaders[0]);
	objects.push_back(object2);
	objects[1].SetObjectPos(glm::vec3(5.0, 1.5, 3.0));
	
	// WILL NOT RENDER DUE TO FACE COUNT BEING SOMEHOW LINKED TO MONKEY MODEL????
	Object object3 = Object("..\\res\\Models\\cube.obj", textures[0], shaders[0]);
	objects.push_back(object3);
	objects[2].SetObjectPos(glm::vec3(10.0, 2.5, 3.0));

}

void ObjectHandler::drawObjects(WorldCamera& myCamera)
{
	// for each object
	for (unsigned int i = 0; i < objects.size(); i++)
	{
		objects[i]._shader.Use();
		objects[i]._shader.Update(objects[i]._transform, myCamera);
		objects[i]._texture.Bind(0);
		// override for spec map testing
		if (i == 0)
		{
			//objects[i]._texture.Bind(2);
		}
		objects[i]._mesh.draw();
		objects[i]._mesh.updateSphereData(objects[i]._transform.GetPos(), 1.0f);
	}
}


