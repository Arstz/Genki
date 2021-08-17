#include "Shader.h"
#include <iostream>

std::vector<int> Shader::shaderIDs(0);
int Shader::lastShaderVariableID = 1;

void log(int shaderID, int statusType) {
	int success;
	char infoLog[512];
	glGetShaderiv(shaderID, statusType, &success);
	if (!success) {
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		std::cout << "ERROR::KAKOITO_SHADER_OBOSRALSIA\n" << infoLog << std::endl;
	}
}

Shader::Shader() {
	glShaderID = 0;
	bufferProperties = std::vector<BufferProperties>(0);
}

Shader::Shader(Shader&& other) noexcept {
	glShaderID = other.glShaderID;
	other.glShaderID = 0; //does opengl create shader with id zero if(glShaderID != 0) {glDeleteShader(glShaderID);}
	bufferProperties = other.bufferProperties;
}

Shader& Shader::operator=(Shader&& other) noexcept {
	glShaderID = other.glShaderID;
	other.glShaderID = 0; //does opengl create shader with id zero if(glShaderID != 0) {glDeleteShader(glShaderID);}
	bufferProperties = other.bufferProperties;
	return *this;
}

Shader::Shader(
	int* types, 
	char** const* sources,
	int count, 
	const std::vector<BufferProperties>& bufferProperties
) {
	this->bufferProperties = bufferProperties;
	int* shaders = new int[count];

	glShaderID = glCreateProgram();
	shaderIDs.push_back(glShaderID);

	for (int i = 0; i < count; i++) {
		shaders[i] = glCreateShader(types[i]);

		glShaderSource(shaders[i], 1, sources[i], NULL);
		glCompileShader(shaders[i]);

		log(shaders[i], GL_COMPILE_STATUS);

		glAttachShader(glShaderID, shaders[i]);
	}

	glLinkProgram(glShaderID);

	log(glShaderID, GL_LINK_STATUS);

	for (int i = 0; i < bufferProperties.size(); i++) {
		this->bufferProperties[i].shaderVariableID = lastShaderVariableID;
		glUniformBlockBinding(
			glShaderID,
			glGetUniformBlockIndex(glShaderID, bufferProperties[i].variableName),
			lastShaderVariableID++
		);
	}

	for (int i = 0; i < count; i++) {
		glDeleteShader(shaders[i]);
	}

}

Shader::~Shader() { //does opengl create shader with id zero if(glShaderID != 0) {glDeleteShader(glShaderID);}
	glDeleteShader(glShaderID);
}

const std::vector<BufferProperties>& Shader::getBufferProperties() {
	return bufferProperties;
}
