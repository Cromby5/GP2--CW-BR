#version 330 core

layout (location = 0) in vec3 aPos;

layout (location = 1) in vec2 texCoord;

layout (location = 2) in vec3 aNormal;

out vec3 currentPos;

out vec2 texCoord0;

out vec3 Normal;


uniform mat4 transform;
uniform mat4 model;

void main()
{
	//currentPos = vec3(model * vec4(aPos,1.0));
	gl_Position = transform * vec4(aPos, 1.0);
	texCoord0 = texCoord;
	Normal = aNormal;
}