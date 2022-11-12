#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform int facingRight;

void main() {
	if (facingRight == 1)
		gl_Position = projection * view * model * vec4(pos, 1.0f);
	else
		gl_Position = projection * view * model * vec4(-pos.x, pos.y, pos.z, 1.0f);
		
	//gl_Position = projection * view * vec4(pos, 1.0f);
	TexCoord = texCoord;
}