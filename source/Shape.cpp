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

Shape::Shape(ByteArray* byteArray) {
	*byteArray >> vertexCount >> EBOsize >> layer >> alphaChannel >> positionX >> positionY;
	vertexCoords = new float[static_cast<size_t>(vertexCount) * 2];
	vertexColors = new float[static_cast<size_t>(vertexCount) * 4];
	vertexIDs = new uint[EBOsize];
	byteArray->read(vertexCoords, sizeof(*vertexCoords) * vertexCount * 2);
	byteArray->read(vertexColors, sizeof(*vertexColors) * vertexCount * 4);
	byteArray->read(vertexIDs, sizeof(*vertexIDs) * EBOsize);
}

ByteArray Shape::getByteArray() {
	ByteArray byteArray(
		sizeof(vertexCount) +
		sizeof(EBOsize) +
		sizeof(layer) +
		sizeof(alphaChannel) +
		sizeof(positionX) +
		sizeof(positionY) +
		sizeof(*vertexIDs) * EBOsize +
		sizeof(*vertexCoords) * vertexCount * 2 +
		sizeof(*vertexColors) * vertexCount * 4
	);
	byteArray << vertexCount << EBOsize << layer << alphaChannel << positionX << positionY;
	byteArray.add(vertexCoords, sizeof(*vertexCoords) * vertexCount * 2);
	byteArray.add(vertexColors, sizeof(*vertexColors) * vertexCount * 4);
	byteArray.add(vertexIDs, sizeof(*vertexIDs) * EBOsize);

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

std::tuple<float, float, float, float> Shape::getBounds()
{
	float minX = std::numeric_limits<float>::max();
	float minY = std::numeric_limits<float>::max();
	float maxX = std::numeric_limits<float>::min();
	float maxY = std::numeric_limits<float>::min();

	for (int i = 0; i < vertexCount * 2; i += 2) {
		minX = std::min(minX, vertexCoords[i]);
		maxX = std::max(maxX, vertexCoords[i]);

		minY = std::min(minY, vertexCoords[i+1]);
		maxY = std::max(maxY, vertexCoords[i+1]);
	}
	return std::make_tuple(minX,minY,maxX,maxY);
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

