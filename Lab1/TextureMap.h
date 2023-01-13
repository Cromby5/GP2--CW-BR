#pragma once
#include <string>
#include <GL\glew.h>


class TextureMap
{
public:
	
	TextureMap();
	
    TextureMap(const std::string& fileName);

	void LoadTexture(const std::string& fileName, GLuint unit);

	void Bind(unsigned int unit); // bind upto 32 textures

	~TextureMap();

protected:
private:
	enum
	{
		DEFAULT,
		NORMAL,
		SPECULAR,
		NUM_TYPES
	};
	
	GLuint textureID[NUM_TYPES];
	
	
};

