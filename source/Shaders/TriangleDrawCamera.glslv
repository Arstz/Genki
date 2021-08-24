#version 330 core
layout (location = 0) in vec2 pos;
layout (location = 1) in vec4 color;

layout(std140) uniform Camera
{
	vec2 offset;
	vec2 scale;
};
out vec4 vertexColor;
void main()
{
   gl_Position = vec4((pos + offset) * scale, 0.f, 1.f);
   vertexColor = color;
}
