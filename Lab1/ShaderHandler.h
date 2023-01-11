#pragma once
#include <string>
#include <GL\glew.h>
#include "transform.h"
#include "WorldCamera.h"

class ShaderHandler
{
public:
	ShaderHandler();
	ShaderHandler(const std::string& fileName);

	void Use(); // Set gpu to use our shaders
	//void ParseShader(const std::string& filename); // Parse the shader files to seperate vert and frag shaders
	void Update(const Transform& transform, const WorldCamera& camera);
	void UpdateSky(const WorldCamera& camera);
	void UpdateLight(const Transform& transform, const WorldCamera& camera);
	
	void init(const std::string& filename);

	std::string ShaderHandler::LoadShader(const std::string& fileName);
	void ShaderHandler::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint ShaderHandler::CompileShader(const std::string& text, unsigned int type);

    ~ShaderHandler();


protected:
private:
	static const unsigned int NUM_SHADERS = 2; // number of shaders

	enum
	{
		TRANSFORM_U,
		MODEL,
		VIEW,
		PROJECTION,
		CAMERA_POS,
		LIGHT_POS,
		SKYBOX,
		LIGHT_COLOUR,
		DIFFUSE,
		NORMALMAP,
		SPECULAR,
		NUM_UNIFORMS
	};

	GLuint program; // Track the shader program
	GLuint shaders[NUM_SHADERS]; //array of shaders
	GLuint uniforms[NUM_UNIFORMS]; //no of uniform variables
};
