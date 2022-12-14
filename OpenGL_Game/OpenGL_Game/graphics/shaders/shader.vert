#version 330 core
layout (location = 0) in vec3 aPos;			// position var has attribute position 0
layout (location = 2) in vec2 aTexCoord;	// texture coord

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	//gl_Position = vec4(aPos, 1.0f);
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	TexCoord = aTexCoord;
}
