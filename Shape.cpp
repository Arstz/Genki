#include "Shape.h"

Shape::Shape() {}
Shape::Shape(
	uint vertexCount,
	float* vertexCoords,
	float* vertexColors,
	uint EBOsize,
	uint* vertexIDs,
	float positionX,
	float positionY,
	int layer
) {
	this->vertexCount = vertexCount;

	this->vertexCoords = new float[vertexCount * 2];
	this->vertexColors = new float[vertexCount * 4];

	for (uint i = 0; i < vertexCount * 2; i++) this->vertexCoords[i] = vertexCoords[i];
	for (uint i = 0; i < vertexCount * 4; i++) this->vertexColors[i] = vertexColors[i];

	this->EBOsize = EBOsize;

	this->vertexIDs = new uint[EBOsize];
	for (uint i = 0; i < EBOsize; i++) this->vertexIDs[i] = vertexIDs[i];

	this->positionX = positionX;
	this->positionY = positionY;

	this->layer = layer;
}

Shape::Shape(const Shape& shape) {
	this->vertexCount = shape.vertexCount;

	this->vertexCoords = new float[vertexCount * 2];
	this->vertexColors = new float[vertexCount * 4];

	for (uint i = 0; i < shape.vertexCount * 2; i++) this->vertexCoords[i] = shape.vertexCoords[i];
	for (uint i = 0; i < shape.vertexCount * 4; i++) this->vertexColors[i] = shape.vertexColors[i];

	this->EBOsize = shape.EBOsize;

	this->vertexIDs = new uint[shape.EBOsize];
	for (uint i = 0; i < EBOsize; i++) this->vertexIDs[i] = shape.vertexIDs[i];

	this->positionX = shape.positionX;
	this->positionY = shape.positionY;

	this->layer = shape.layer;
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

	this->vertexCoords = new float[vertexCount * 2];
	this->vertexColors = new float[vertexCount * 4];

	for (uint i = 0; i < shape.vertexCount * 2; i++) this->vertexCoords[i] = shape.vertexCoords[i];
	for (uint i = 0; i < shape.vertexCount * 4; i++) this->vertexColors[i] = shape.vertexColors[i];

	this->EBOsize = shape.EBOsize;

	this->vertexIDs = new uint[shape.EBOsize];
	for (uint i = 0; i < EBOsize; i++) this->vertexIDs[i] = shape.vertexIDs[i];

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

float* Shape::getPositionXpointer() {
	return &positionX;
}

float* Shape::getPositionYpointer() {
	return &positionY;
}

int Shape::getLayer() const {
	return layer;
}