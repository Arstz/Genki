#include <string>


extern std::string TriangleDraw_glslf = ""
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 vertexColor;\n"
"\n"
"void main()\n"
"{\n"
"	FragColor = vertexColor;\n"
"}\n\0";


extern std::string TriangleDraw_glslv = ""
"#version 330 core\n"
"layout (location = 0) in vec2 pos;\n"
"layout (location = 1) in vec4 color;\n"
"\n"
"out vec4 vertexColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(pos.x * SCALE_X, pos.y, 0.f, 1.f);\n"
"   vertexColor = color;\n"
"}\n\0";


extern std::string TriangleDrawBorders_glslf = ""
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 vertexColor;\n"
"layout(std140) uniform Borders\n"
"{\n"
"	vec2 min;\n"
"	vec2 max;\n"
"};\n"
"void main()\n"
"{\n"
"	vec4 temp = vertexColor;\n"
"	if(gl_FragCoord.y > min.y) temp = vec4(0.f,0.f,0.f,0.f);\n"
"	if(gl_FragCoord.y < max.y) temp = vec4(0.f,0.f,0.f,0.f);\n"
"	if(gl_FragCoord.x < min.x) temp = vec4(0.f,0.f,0.f,0.f);\n"
"	if(gl_FragCoord.x > max.x) temp = vec4(0.f,0.f,0.f,0.f);\n"
"	FragColor = temp;\n"
"}\n\0";


extern std::string TriangleDrawBorders_glslv = ""
"#version 330 core\n"
"layout (location = 0) in vec2 pos;\n"
"layout (location = 1) in vec4 color;\n"
"\n"
"out vec4 vertexColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(pos.x * SCALE_X, pos.y, 0.f, 1.f);\n"
"   vertexColor = color;\n"
"}\n\0";


extern std::string TriangleDrawCamera_glslf = ""
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 vertexColor;\n"
"void main()\n"
"{\n"
"	FragColor = vertexColor;\n"
"}\n\0";


extern std::string TriangleDrawCamera_glslv = ""
"#version 330 core\n"
"layout (location = 0) in vec2 pos;\n"
"layout (location = 1) in vec4 color;\n"
"\n"
"layout(std140) uniform Camera\n"
"{\n"
"	vec2 offset;\n"
"	vec2 scale;\n"
"};\n"
"out vec4 vertexColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4((pos + offset) * scale, 0.f, 1.f);\n"
"   vertexColor = color;\n"
"}\n\0";


