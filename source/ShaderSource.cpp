#include "ShaderSource.h"

ShaderSource::ShaderSource(std::string source) {
	this->source = source;
}

std::string ShaderSource::getSource(std::vector<std::string> replacable, std::vector<std::string> replacements) {
	std::string newSource;

	for (int i = 0; i < replacable.size(); i++) {
		std::string temp(source);
		bool found = false;
		size_t needlePos = temp.find(replacable[i]);
		while(needlePos != std::numeric_limits<size_t>::max() && temp.size() > 0) {
			int currentIndex = 0;
			
			newSource += temp.substr(currentIndex, needlePos - currentIndex) + replacements[i];
			currentIndex += needlePos + replacable[i].size();
			temp = temp.substr(currentIndex, temp.size() - currentIndex);
			needlePos = temp.find(replacable[i]);
		}
		newSource += temp;
	}

	return newSource;
}

std::string ShaderSource::getSource() {
	return source;
}
