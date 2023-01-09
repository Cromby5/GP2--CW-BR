#pragma once
#include <string>
#include <vector>
#include <GL\glew.h>
#include "transform.h"
#include "TextureMap.h"
#include "MeshHandler.h"
#include "ShaderHandler.h"
#include "WorldCamera.h"

// Each indivdual object that will be stored by the handler
struct Object
{
public:
	Object()
	{

	};
	
	Object(const std::string& meshName, TextureMap& texture, ShaderHandler& shader)
	{
		_texture = texture;
		_shader = shader;
		_mesh.loadModel(meshName);
		_transform.SetPos(glm::vec3(0.0, 0.0, 0.0));
		_transform.SetRot(glm::vec3(0.0, 0.0, 0.0));
		_transform.SetScale(glm::vec3(1.0, 1.0, 1.0));
	};
	
	inline void SetObjectPos(glm::vec3& pos) {_transform.SetPos(pos);}
	inline void SetObjectRot(glm::vec3& rot) { _transform.SetRot(rot);}
	inline void SetObjectScale(glm::vec3& scale) { _transform.SetScale(scale);}
	
	Transform _transform;
	TextureMap _texture;
	ShaderHandler _shader;
	MeshHandler _mesh;
	
private:
	
};

class ObjectHandler
{
public:
	
	ObjectHandler();

	~ObjectHandler();
	void initObjects();
	void drawObjects(WorldCamera& myCamera);

	
private:
	// TESTING
	//Object a;

	Transform _transform;
	// objects
	std::vector<Object> objects;
	// Arrays of all possible tex/shaders/meshes an object can have
	std::vector<TextureMap> textures;
	std::vector<ShaderHandler> shaders;
	std::vector<MeshHandler> meshs;
	
};

