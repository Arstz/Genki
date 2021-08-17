#pragma once
#define GLEW_STATIC

#include "..\include\GL\glew.h"
#include "..\include\GLFW\glfw3.h"
#include <string>
#include <vector>

enum class ShaderType {
	VERTEX_SHADER,
	FRAGMENT_SHADER,
};

struct BufferProperties {
	int type;
	int shaderVariableID;
	size_t bufferSize;
	const char* variableName;
};

void log(int shaderID, int statusType);

class Shader {
	static std::vector<int> shaderIDs; //da sviazhed on shaider_program ee controller sheipov
	static int lastShaderVariableID;

	std::vector<BufferProperties> bufferProperties;

	int glShaderID;

public:
	Shader();
	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;

	Shader(Shader&& other) noexcept;
	Shader& operator=(Shader&& other) noexcept;

	Shader(
		int* types, 
		char** const * sources,
		int count, 
		const std::vector<BufferProperties>& bufferProperties
	);
	~Shader();

	const std::vector<BufferProperties>& getBufferProperties();
};

