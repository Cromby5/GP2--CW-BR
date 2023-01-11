#include "ObjectHandler.h"
#include <iostream>

ObjectHandler::ObjectHandler()
{
	
}


ObjectHandler::~ObjectHandler()
{
	
}

void ObjectHandler::initObjects()
{
	// Unsure whats going on that I can't use the constructor to load the objects directly into the vector of objects without the data being wrong in someway,
	// making a temp new object/texture/shader locally and then loading it into the vector works fine though from testing.
	// SHARED VAO ISSUE WHEN PASSING TEMP VARIABLES THAT GET DESTROYED WHEN WE ARE OUT OF SCOPE. YOU FORGOT ABOUT HOW DECONSTRUCTORS WORK FOR THE LAST 2 DAYS. DONT LET TEXTURES,SHADERS and MESHES GET DELETED THIS WAY.
	// WILL NOT RENDER DUE TO FACE COUNT BEING SOMEHOW LINKED TO MONKEY MODEL????
	
	initTextures();
	initShaders();
	
	objects.reserve(15); // reserve 15 objects to prevent reallocation of the vector in this example scene.

	tempObject.LoadObjectFILE("..\\res\\Models\\monkey3.obj", textures[0], shaders[0]);
	
	objects.emplace_back(tempObject);
	objects[0].SetObjectPos(glm::vec3(10.0, 1.5, 3.0));

	tempObject.LoadObjectFILE("..\\res\\Models\\monkey3.obj", textures[0], shaders[0]);
	objects.emplace_back(tempObject);
	objects[1].SetObjectPos(glm::vec3(5.0, 5, 3.0));
	
	
	
	tempObject.LoadObjectFILE("..\\res\\Models\\cube.obj", textures[0], shaders[0]);
	objects.emplace_back(tempObject);
	objects[2].SetObjectPos(glm::vec3(-5.0, 2.5, 3.0));

	tempObject.LoadObjectFILE("..\\res\\Models\\cart.obj", textures[0], shaders[0]);
	objects.emplace_back(tempObject);
	objects[3].SetObjectPos(glm::vec3(0.0, 1.5, 10.0));

	tempObject.LoadObjectFILE("..\\res\\Models\\MONARCH.obj", textures[2], shaders[0]);
	objects.emplace_back(tempObject);
	objects[4].SetObjectPos(glm::vec3(10.0, 3.5, 3.0));
	objects[4].SetObjectScale(glm::vec3(15.0, 15.0, 15.0));

	tempObject.LoadObjectFILE("..\\res\\Models\\canoe.obj", textures[0], shaders[0]);
	objects.emplace_back(tempObject);
	objects[5].SetObjectPos(glm::vec3(-5.0, -2.5, 3.0));

	tempObject.LoadObjectFILE("..\\res\\Models\\backpack.obj", textures[3], shaders[0]);
	objects.emplace_back(tempObject);
	objects[6].SetObjectPos(glm::vec3(5.0, -2.0, 0.0));
}

void ObjectHandler::initTextures()
{
	textures.reserve(10); // prevent reallocation of the vector in this example scene.

	tempTexture.LoadTexture("..\\res\\Textures\\bricks.jpg",0);
	tempTexture.LoadTexture("..\\res\\Textures\\bricksNormal.png", 1);
	tempTexture.LoadTexture("..\\res\\Textures\\BricksSpecularMap.png", 2);
	textures.emplace_back(tempTexture);
	
	tempTexture.LoadTexture("..\\res\\Textures\\water.jpg",0);
	textures.emplace_back(tempTexture);

	tempTexture.LoadTexture("..\\res\\Textures\\MONARCH.jpg", 0);
	textures.emplace_back(tempTexture);

	tempTexture.LoadTexture("..\\res\\Textures\\diffuse.jpg", 0);
	tempTexture.LoadTexture("..\\res\\Textures\\normal.png", 1);
	tempTexture.LoadTexture("..\\res\\Textures\\specular.jpg", 2);
	textures.emplace_back(tempTexture);
}

void ObjectHandler::initShaders()
{
	shaders.reserve(10); // prevent reallocation of the vector in this example scene.
	
	tempShader.init("..\\res\\shader");
	shaders.emplace_back(tempShader);
	
	tempShader.init("..\\res\\SkyboxShader");
	shaders.emplace_back(tempShader);
	
	tempShader.init("..\\res\\ReflectShader");
	shaders.emplace_back(tempShader);
	
	tempShader.init("..\\res\\RefractShader");
	shaders.emplace_back(tempShader);
	
	shaders.emplace_back("..\\res\\LightShader");
	shaders.emplace_back(tempShader);

}


void ObjectHandler::drawObjects(WorldCamera& myCamera , float counter)
{
	// for each object in the vector of objects, draw it with their own shader and textures set at their transform.
	for (unsigned int i = 0; i < objects.size(); i++)
	{
		objects[i]._shader.Use();
		objects[i]._shader.Update(objects[i]._transform, myCamera);
		objects[i]._texture.Bind(0);
		// Temp overrides, carried across from inital project state to test the new object handler.
		// for spec map testing
		if ( i == 3 || i == 6)
		{
			objects[i]._texture.Bind(1);
			objects[i]._texture.Bind(2);
		}
		if (i == 0)
		{
			objects[i].SetObjectPos(glm::vec3(sinf(counter),0.5f,0.0f));
		}
		if (i == 1)
		{
			objects[i].SetObjectPos(glm::vec3(-sinf(counter),-0.5f, 0.0f));
		}
		
		objects[i]._mesh.draw();
		objects[i]._mesh.updateSphereData(objects[i]._transform.GetPos(), 1.0f);
	}
}

// Limited to the first 2 objects created for demo purposes.
bool ObjectHandler::collision()
{
	glm::vec3 m1Pos = objects[0]._mesh.getSpherePos();
	float m1Rad = objects[0]._mesh.getSphereRadius();
	glm::vec3 m2Pos = objects[1]._mesh.getSpherePos();
	float m2Rad = objects[1]._mesh.getSphereRadius();
		
	float distance = ((m2Pos.x - m1Pos.x) * (m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y) * (m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z) * (m2Pos.z - m1Pos.z));

	if (distance * distance < (m1Rad + m2Rad))
	{
		//audioDevice.setlistener(myCamera.getPos(), m1Pos); //add bool to mesh
		std::cout << distance << '\n';
		return true;
	}
	else
	{
		return false;
	}
	
}



