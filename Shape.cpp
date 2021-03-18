#include "Shape.h"

Shape::Shape() {}

Shape::Shape(
	uint vertexCount,
	float* vertexCoords,
	float* vertexColors,
	uint EBOsize,
	uint* vertexIDs
) {
	this->vertexCount = vertexCount;
	this->vertexCoords = vertexCoords;
	this->vertexColors = vertexColors;
	this->EBOsize = EBOsize;
	this->vertexIDs = vertexIDs;
}

Shape::Shape(const Shape& shape) {
	this->vertexCount = shape.vertexCount;
	this->vertexCoords = new float[this->vertexCount * 2];
	for (int i = 0; i < vertexCount * 2; i++) this->vertexCoords[i] = shape.vertexCoords[i];
	this->vertexColors = new float[this->vertexCount * 4];
	for (int i = 0; i < vertexCount * 4; i++) this->vertexColors[i] = shape.vertexColors[i];
	this->EBOsize = shape.EBOsize;
	this->vertexIDs = new uint[this->EBOsize];
	for (int i = 0; i < this->EBOsize; i++) this->vertexIDs[i] = shape.vertexIDs[i];
}

Shape::~Shape() {
//	delete[] vertexCoords;
//	delete[] vertexColors;
//	delete[] vertexIDs;
}

uint Shape::getVertexCount() {
	return vertexCount;
}

uint Shape::getEBOsize() {
	return EBOsize;
}

float* Shape::getColorPointer(uint vertexNum, uint channelNum) {
	return &vertexColors[vertexNum * 4 + channelNum];
}

float* Shape::getPositionPointer(uint vertexNum, uint channelNum) {
	return &vertexColors[vertexNum * 2 + channelNum];
}