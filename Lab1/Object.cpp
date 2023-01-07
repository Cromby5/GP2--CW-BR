#include "Object.h"

Object::Object(ShaderHandler shader, TextureMap texture, const std::string& modelName)
{
	objectTransform.SetPos(glm::vec3(0.0, 0.0, 0.0));
	objectTransform.SetRot(glm::vec3(0.0, 0.0, 0.0));
	objectTransform.SetScale(glm::vec3(1.0, 1.0, 1.0));

	objectTexture = texture;
	objectShader = shader;
	objectMesh.loadModel(modelName);
}

Object::~Object()
{
	
}

void Object::drawObject(WorldCamera& myCamera)
{
	objectShader.Use();
	objectShader.Update(objectTransform, myCamera);
	objectTexture.Bind(0);
	objectMesh.draw();
	objectMesh.updateSphereData(*objectTransform.GetPos(), 0.6f);
}


