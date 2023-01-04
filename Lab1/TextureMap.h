#pragma once
#include <string>
#include <GL\glew.h>


class TextureMap
{
public:
	TextureMap(const std::string& fileName);

	void Bind(unsigned int unit); // bind upto 32 textures

	~TextureMap();

protected:
private:

	GLuint textureHandler;
};

