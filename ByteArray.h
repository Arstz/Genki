#pragma once
#include <vector>

void writeToByteArray(
	std::vector<char>& byteVector, 
	char* byteArray,
	unsigned int &offset, 
	unsigned int size
);

void writeToByteArray(
	std::vector<char>& byteVector,
	const std::vector<char>& byteArray,
	unsigned int& offset
);

void writeToByteArray(
	char* byteVector,
	char* byteArray,
	unsigned int& offset,
	unsigned int size
);

void writeToByteArray(
	char* byteVector,
	const std::vector<char>& byteArray,
	unsigned int& offset
);