#include "Shape.h"
#include "ByteArray.h"

#include "crtdbg.h"
#include "..\include\CRTDBG\mydbgnew.h"
#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

Shape::Shape() {
	this->EBOsize = 0;
	this->alphaChannel = 0.f;
	this->layer = 0;
	this->positionX = 0.f;
	this->positionY = 0.f;
	this->vertexCount = 0;
	this->vertexCoords = nullptr;
	this->vertexColors = nullptr;
	this->vertexIDs = nullptr;
}
Shape::Shape(
	uint vertexCount,
	float* vertexCoords,
	float* vertexColors,
	uint EBOsize,
	uint* vertexIDs,
	float alphaChannel,
	float positionX,
	float positionY,
	int layer
) {
	this->vertexCount = vertexCount;

	this->vertexCoords = new float[static_cast<long long>(vertexCount) * 2];
	this->vertexColors = new float[static_cast<long long>(vertexCount) * 4];

	for (uint i = 0; i < vertexCount * 2; i++) this->vertexCoords[i] = vertexCoords[i];
	for (uint i = 0; i < vertexCount * 4; i++) this->vertexColors[i] = vertexColors[i];

	this->EBOsize = EBOsize;

	this->vertexIDs = new uint[EBOsize];
	for (uint i = 0; i < EBOsize; i++) this->vertexIDs[i] = vertexIDs[i];

	this->alphaChannel = alphaChannel;
	this->positionX = positionX;
	this->positionY = positionY;

	this->layer = layer;
}

Shape::Shape(const Shape& shape) {
	this->vertexCount = shape.vertexCount;

	this->vertexCoords = new float[static_cast<size_t>(vertexCount) * 2];
	this->vertexColors = new float[static_cast<size_t>(vertexCount) * 4];

	for (uint i = 0; i < shape.vertexCount * 2; i++) this->vertexCoords[i] = shape.vertexCoords[i];
	for (uint i = 0; i < shape.vertexCount * 4; i++) this->vertexColors[i] = shape.vertexColors[i];

	this->EBOsize = shape.EBOsize;

	this->vertexIDs = new uint[shape.EBOsize];
	for (uint i = 0; i < EBOsize; i++) this->vertexIDs[i] = shape.vertexIDs[i];

	this->alphaChannel = shape.alphaChannel;
	this->positionX = shape.positionX;
	this->positionY = shape.positionY;

	this->layer = shape.layer;
}

Shape::Shape(char* byteArray, unsigned int& offset) {
	writeFromByteArray((char*)&vertexCount, byteArray, offset, sizeof(vertexCount));
	writeFromByteArray((char*)&EBOsize, byteArray, offset, sizeof(EBOsize));
	writeFromByteArray((char*)&layer, byteArray, offset, sizeof(layer));
	writeFromByteArray((char*)&alphaChannel, byteArray, offset, sizeof(alphaChannel));
	writeFromByteArray((char*)&positionX, byteArray, offset, sizeof(positionX));
	writeFromByteArray((char*)&positionY, byteArray, offset, sizeof(positionY));
	vertexCoords = new float[static_cast<size_t>(vertexCount) * 2];
	vertexColors = new float[static_cast<size_t>(vertexCount) * 4];
	vertexIDs = new uint[EBOsize];
	writeFromByteArray((char*)vertexCoords, byteArray, offset, sizeof(*vertexCoords) * vertexCount * 2);
	writeFromByteArray((char*)vertexColors, byteArray, offset, sizeof(*vertexColors) * vertexCount * 4);
	writeFromByteArray((char*)vertexIDs, byteArray, offset, sizeof(*vertexIDs) * EBOsize);
}

std::vector<char> Shape::getByteArray() {
	unsigned int byteArraySize =
		sizeof(vertexCount) +
		sizeof(EBOsize) +
		sizeof(layer) +
		sizeof(alphaChannel) +
		sizeof(positionX) +
		sizeof(positionY) +
		sizeof(*vertexIDs) * EBOsize +
		sizeof(*vertexCoords) * vertexCount * 2 +
		sizeof(*vertexColors) * vertexCount * 4;

	std::vector<char> byteArray(byteArraySize);
	unsigned int offset = 0;

	writeToByteArray(byteArray, (char*)&vertexCount, offset, sizeof(vertexCount));
	writeToByteArray(byteArray, (char*)&EBOsize, offset, sizeof(EBOsize));
	writeToByteArray(byteArray, (char*)&layer, offset, sizeof(layer));
	writeToByteArray(byteArray, (char*)&alphaChannel, offset, sizeof(alphaChannel));
	writeToByteArray(byteArray, (char*)&positionX, offset, sizeof(positionX));
	writeToByteArray(byteArray, (char*)&positionY, offset, sizeof(positionY));
	writeToByteArray(byteArray, (char*)vertexCoords, offset, sizeof(*vertexCoords) * vertexCount * 2);
	writeToByteArray(byteArray, (char*)vertexColors, offset, sizeof(*vertexColors) * vertexCount * 4);
	writeToByteArray(byteArray, (char*)vertexIDs, offset, sizeof(*vertexIDs) * EBOsize);

	return byteArray;
}

Shape::~Shape() {
	delete[] vertexCoords;	
	delete[] vertexColors;
	delete[] vertexIDs;
	vertexColors = nullptr;
	vertexCoords = nullptr;
	vertexIDs = nullptr;
}

Shape& Shape::operator=(const Shape& shape) {
	delete[] vertexCoords;
	delete[] vertexColors;
	delete[] vertexIDs;

	this->vertexCount = shape.vertexCount;

	this->vertexCoords = new float[static_cast<size_t>(vertexCount) * 2];
	this->vertexColors = new float[static_cast<size_t>(vertexCount) * 4];

	for (uint i = 0; i < shape.vertexCount * 2; i++) this->vertexCoords[i] = shape.vertexCoords[i];
	for (uint i = 0; i < shape.vertexCount * 4; i++) this->vertexColors[i] = shape.vertexColors[i];

	this->EBOsize = shape.EBOsize;

	this->vertexIDs = new uint[shape.EBOsize];
	for (uint i = 0; i < EBOsize; i++) this->vertexIDs[i] = shape.vertexIDs[i];

	this->alphaChannel = shape.alphaChannel;
	this->positionX = shape.positionX;
	this->positionY = shape.positionY;

	this->layer = shape.layer;

	return *this;
}

uint Shape::getVertexCount() const {
	return vertexCount;
}

uint Shape::getEBOsize() const {
	return EBOsize;
}

float* Shape::getVertexCoordsPointer() {
	return vertexCoords;
}

float* Shape::getVertexColorsPointer() {
	return vertexColors;
}

uint* Shape::getVertexIDsPointer() {
	return vertexIDs;
}

float* Shape::getAlphaChannelPointer() {
	return &alphaChannel;
}

float* Shape::getPositionXpointer() {
	return &positionX;
}

float* Shape::getPositionYpointer() {
	return &positionY;
}

int Shape::getLayer() const {
	return layer;
}

