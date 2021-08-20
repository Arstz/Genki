#pragma once
#include <string>
#include <vector>
#include <fstream>

class ShaderSource {
	std::string source;
public:
	ShaderSource(std::string source);
	std::string getSource(std::vector<std::string> replacable, std::vector<std::string> replacements);
	std::string getSource();
};

