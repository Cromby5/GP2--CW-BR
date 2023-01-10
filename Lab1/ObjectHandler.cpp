#include "ObjectHandler.h"

ObjectHandler::ObjectHandler()
{
	
}


ObjectHandler::~ObjectHandler()
{
	
}

void ObjectHandler::initObjects()
{
	// Unsure whats going on that I can't use the constructor to load the objects directly into the vector of objects without the data being wrong in someway, making a temp new object/texture/shader locally and then loading it into the vector works fine though from testing.
	initTextures();
	initShaders();
	
	MeshHandler monkeymesh = MeshHandler("..\\res\\Models\\monkey3.obj");
	MeshHandler canoemesh = MeshHandler("..\\res\\Models\\canoe.obj");
	MeshHandler cubemesh = MeshHandler("..\\res\\Models\\cube.obj");
	MeshHandler carmesh = MeshHandler("..\\res\\Models\\350z.obj");
	
	Object monkey = Object(monkeymesh, textures[0], shaders[0]);
	objects.push_back(Object(monkey));
	objects[0].SetObjectPos(glm::vec3(10.0, 1.5, 3.0));

	Object canoe = Object(canoemesh, textures[1], shaders[0]);
	objects.push_back(Object(canoe));
	objects[1].SetObjectPos(glm::vec3(5.0, 5, 3.0));
	
	// WILL NOT RENDER DUE TO FACE COUNT BEING SOMEHOW LINKED TO MONKEY MODEL????
	
	Object cube = Object(cubemesh, textures[0], shaders[0]);
	
	objects.push_back(Object(cube));
	objects[2].SetObjectPos(glm::vec3(-5.0, 2.5, 3.0));
	
}

void ObjectHandler::initTextures()
{
	TextureMap Brick = TextureMap("..\\res\\Textures\\bricks.jpg");
	//TextureMap BrickN = TextureMap("..\\res\\Textures\\bricksNormal.jpg");
	//TextureMap BrickS = TextureMap("..\\res\\Textures\\bricksSpecular.jpg");

	TextureMap Water = TextureMap("..\\res\\Textures\\water.jpg");

	textures.push_back(TextureMap(Brick));
	textures.push_back(TextureMap(Water));
}

void ObjectHandler::initShaders()
{
	ShaderHandler shader = ShaderHandler("..\\res\\shader");
	ShaderHandler skyShader = ShaderHandler("..\\res\\SkyboxShader");
	ShaderHandler reflectShader = ShaderHandler("..\\res\\ReflectShader");
	ShaderHandler refractShader = ShaderHandler("..\\res\\RefractShader");
	ShaderHandler lightShader = ShaderHandler("..\\res\\LightShader");

	shaders.push_back(ShaderHandler(shader));
	shaders.push_back(ShaderHandler(skyShader));
	shaders.push_back(ShaderHandler(reflectShader));
	shaders.push_back(ShaderHandler(refractShader));
	shaders.push_back(ShaderHandler(lightShader));
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


