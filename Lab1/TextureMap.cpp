#include "TextureMap.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

TextureMap::TextureMap()
{
	textureHandler[0] = 0;
	textureHandler[1] = 0;
	textureHandler[2] = 0;
	textureHandler[3] = 0;
	textureHandler[4] = 0;
	
}

 TextureMap::TextureMap(const std::string& fileName)
{
	 LoadTexture(fileName, 0);
}

TextureMap::~TextureMap()
{
	for (int i = 0; i < NUM_TYPES; i++)
	{
		glDeleteTextures(1, &textureHandler[i]);
	}
}

void TextureMap::LoadTexture(const std::string& fileName, GLuint unit)
{
	int width, height, numComponents; //width, height, and no of components of image
	unsigned char* imageData = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4); //load the image and store the data

	if (imageData == NULL)
	{
		std::cerr << "texture load failed" << fileName << std::endl;
	}

	glGenTextures(1, &textureHandler[unit]); // number of and address of textures
	glActiveTexture(GL_TEXTURE0 + unit); //set acitve texture unit 
	
	glBindTexture(GL_TEXTURE_2D, textureHandler[unit]); //bind texture - define type 

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // wrap texture outside width
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // wrap texture outside height

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // linear filtering for minification (texture is smaller than area)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // linear filtering for magnifcation (texture is larger)

	// Normal map
	switch (unit)
	{
	case 0:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData); //load image data into texture
		break;
	case 1:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData); //load image data into texture (normal map)
		break;
	case 2:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, imageData); //load image data into texture (specular map)
		break;
	}
		
	stbi_image_free(imageData);
	
	glBindTexture(GL_TEXTURE_2D, 0); //Unbind texture
}

void TextureMap::Bind(unsigned int unit)
{
	assert(unit >= 0 && unit <= 31); /// check we are working with one of the 32 textures
	assert(unit >= 0 && unit <= NUM_TYPES); 
	glActiveTexture(GL_TEXTURE0 + unit); //set acitve texture unit
	glBindTexture(GL_TEXTURE_2D, textureHandler[unit]); //type of and texture to bind to unit
	glActiveTexture(GL_TEXTURE0);
}


