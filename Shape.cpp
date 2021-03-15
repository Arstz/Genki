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

Shape::~Shape() {
	delete[] vertexCoords;
	delete[] vertexColors;
	delete[] vertexIDs;
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