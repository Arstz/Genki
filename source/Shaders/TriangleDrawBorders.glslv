#version 330 core
layout (location = 0) in vec2 pos;
layout (location = 1) in vec4 color;

out vec4 vertexColor;
void main()
{
   gl_Position = vec4(pos.x * SCALE_X, pos.y, 0.f, 1.f);
   vertexColor = color;
}
