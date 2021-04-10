#include "ByteArray.h"

#include "crtdbg.h"
#include "..\include\CRTDBG\mydbgnew.h"
#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

void writeToByteArray(
	std::vector<char>& byteVector,
	char* byteArray, 
	unsigned int &offset, 
	unsigned int size
) {
	for (int i = 0; i < size; i++) byteVector[i + offset] = byteArray[i];
	offset += size;
}

void writeToByteArray(
	std::vector<char>& byteVector, 
	const std::vector<char>& byteArray, 
	unsigned int& offset
) {
	for (int i = 0; i < byteArray.size(); i++) byteVector[i + offset] = byteArray[i];
	offset += byteArray.size();
}

void writeToByteArray(
	char* byteVector, 
	char* byteArray, 
	unsigned int& offset, 
	unsigned int size
) {
	for (int i = 0; i < size; i++) byteVector[i + offset] = byteArray[i];
	offset += size;
}

void writeFromByteArray(
	char* byteVector,
	char* byteArray,
	unsigned int& offset, 
	unsigned int size
) {
	for (int i = 0; i < size; i++) byteVector[i] = byteArray[i + offset];
	offset += size;
}

void writeToByteArray(
	char* byteVector, 
	const std::vector<char>& byteArray, 
	unsigned int& offset
) {
	for (int i = 0; i < byteArray.size(); i++) byteVector[i + offset] = byteArray[i];
	offset += byteArray.size();
}
