#version 330 core
out vec4 FragColor;
in vec4 vertexColor;
layout(std140) uniform Borders
{
	vec2 min;
	vec2 max;
};
void main()
{
	vec4 temp = vertexColor;
	if(gl_FragCoord.y > min.y) temp = vec4(0.f,0.f,0.f,0.f);
	if(gl_FragCoord.y < max.y) temp = vec4(0.f,0.f,0.f,0.f);
	if(gl_FragCoord.x < min.x) temp = vec4(0.f,0.f,0.f,0.f);
	if(gl_FragCoord.x > max.x) temp = vec4(0.f,0.f,0.f,0.f);
	FragColor = temp;
}
