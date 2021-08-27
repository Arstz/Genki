#include "ShapeGroup.h"
#include "ByteArray.h"

#include "crtdbg.h"
#include "..\include\CRTDBG\mydbgnew.h"
#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

ShapeGroup::ShapeGroup(
	uint	shapeCount,
	Shape*	shapes,
	float	alphaChannel,
	float	positionX,
	float	positionY,
	int		layer
) :
	shapeCount		{shapeCount},
	shapes			{new Shape[shapeCount]},
	positionX		{positionX},
	positionY		{positionY},
	alphaChannel	{alphaChannel},
	layer			{layer}
{
	for (uint i = 0; i < shapeCount; i++) {
		this->shapes[i] = shapes[i];
	}
}

ShapeGroup::ShapeGroup(const Shape& shape) :
	shapeCount {1},
	shapes {new Shape[1] {shape}}
{}

ShapeGroup::ShapeGroup(const ShapeGroup& other) :
	shapeGroups		{other.shapeGroups},
	shapeCount		{other.shapeCount},
	shapes			{new Shape[shapeCount]},
	positionX		{other.positionX},
	positionY		{other.positionY},
	alphaChannel	{other.alphaChannel},
	layer			{other.layer}
{
	for (uint i = 0; i < other.shapeCount; i++) {
		this->shapes[i] = other.shapes[i];
	}
}

ShapeGroup& ShapeGroup::operator=(const ShapeGroup& other) {
	shapeGroups		= other.shapeGroups;
	shapeCount		= other.shapeCount;
	positionX		= other.positionX;
	positionY		= other.positionY;
	alphaChannel	= other.alphaChannel;
	layer			= other.layer;

	Shape* newShapes = new Shape[shapeCount];

	for (uint i = 0; i < shapeCount; i++) {
		newShapes[i] = other.shapes[i];
	}

	delete[] shapes;

	shapes = newShapes;
	newShapes = nullptr;

	return *this;
}

ShapeGroup::ShapeGroup(ShapeGroup&& other) noexcept :
	shapeGroups		{other.shapeGroups},
	shapeCount		{other.shapeCount},
	shapes			{other.shapes},
	positionX		{other.positionX},
	positionY		{other.positionY},
	alphaChannel	{other.alphaChannel},
	layer			{other.layer}
{
	other.shapes = nullptr;
}

ShapeGroup& ShapeGroup::operator=(ShapeGroup&& other) noexcept {
	delete[] shapes;

	shapeGroups		= other.shapeGroups;
	shapeCount		= other.shapeCount;
	shapes			= other.shapes;
	positionX		= other.positionX;
	positionY		= other.positionY;
	alphaChannel	= other.alphaChannel;
	layer			= other.layer;

	other.shapes	= nullptr;

	return *this;
}

ShapeGroup::ShapeGroup(ByteArray* byteArray) {
	unsigned int shapeGroupCount;
	shapeGroups = std::list<ShapeGroup>();
	*byteArray >> shapeCount >> shapeGroupCount >> layer >> alphaChannel >> positionX >> positionY;
	shapes = new Shape[shapeCount];
	for (uint i = 0; i < shapeCount; i++)
		shapes[i] = Shape(byteArray);
	for (uint i = 0; i < shapeGroupCount; i++)
		shapeGroups.push_back(ShapeGroup(byteArray));
}

ByteArray ShapeGroup::getByteArray() const {
	unsigned int shapeGroupCount = shapeGroups.size();
	std::vector<ByteArray> byteShapes(shapeCount);
	std::vector<ByteArray> byteShapeGroups(shapeGroupCount);
	unsigned int byteArraySize =
		sizeof(shapeCount) +
		sizeof(shapeGroupCount) +
		sizeof(layer) +
		sizeof(alphaChannel) +
		sizeof(positionX) +
		sizeof(positionY);

	for (uint i = 0; i < shapeCount; i++) {
		byteShapes[i] = shapes[i].getByteArray();
		byteArraySize += byteShapes[i].getSize();
	}
	if (shapeGroupCount) {
		uint i = 0;
		for (auto& shapeGroup : shapeGroups) {
			byteShapeGroups[i] = shapeGroup.getByteArray();
			byteArraySize += byteShapeGroups[i].getSize();
			i++;
		}
	}
	ByteArray byteArray(byteArraySize);
	byteArray << shapeCount << shapeGroupCount << layer << alphaChannel << positionX << positionY;
	for (uint i = 0; i < byteShapes.size(); i++)
		byteArray.add(byteShapes[i]);
	if (shapeGroupCount)
		for (uint i = 0; i < byteShapeGroups.size(); i++)
			byteArray.add(byteShapeGroups[i]);
	return byteArray;
}



std::list<ShapeGroup>::iterator ShapeGroup::addShapeGroup(const ShapeGroup &shapeGroup) {
	std::list<ShapeGroup>::iterator i = shapeGroups.begin();
	while (i != shapeGroups.end() && (*i).layer < shapeGroup.layer) i++;
	return shapeGroups.insert(i, shapeGroup); 
}

void ShapeGroup::removeShapeGroup(const std::list<ShapeGroup>::iterator &shapeGroupIterator) {
	shapeGroups.erase(shapeGroupIterator);
}

ShapeGroup::~ShapeGroup() {
	delete[] shapes;
	shapes = nullptr;
}

uint ShapeGroup::getShapeCount() const noexcept {
	return shapeCount;
}

uint ShapeGroup::getEBOsize() const noexcept {
	uint size = 0;

	for (uint i = 0; i < shapeCount; i++) size += shapes[i].getEBOsize();
	for (auto &shapeGroup : shapeGroups) size += shapeGroup.getEBOsize();

	return size;
}

uint ShapeGroup::getVertexCount() const noexcept {
	uint size = 0;

	for (uint i = 0; i < shapeCount; i++) size += shapes[i].getVertexCount();
	for (auto &shapeGroup : shapeGroups) size += shapeGroup.getVertexCount();

	return size;
}

Shape* ShapeGroup::getShapesPointer() noexcept {
	return shapes;
}

std::list<ShapeGroup>& ShapeGroup::getShapeGroups() noexcept {
	return shapeGroups;
}

float* ShapeGroup::getAlphaChannelPointer() noexcept {
	return &alphaChannel;
}

float* ShapeGroup::getPositionXpointer() noexcept {
	return &positionX;
}

float* ShapeGroup::getPositionYpointer() noexcept {
	return &positionY;
}

int ShapeGroup::getLayer() const noexcept {
	return layer;
}

const Shape* ShapeGroup::getShapesPointer() const noexcept {
	return shapes;
}

const std::list<ShapeGroup>& ShapeGroup::getShapeGroups() const noexcept {
	return shapeGroups;
}

const float* ShapeGroup::getAlphaChannelPointer() const noexcept {
	return &alphaChannel;
}

const float* ShapeGroup::getPositionXpointer() const noexcept {
	return &positionX;
}

const float* ShapeGroup::getPositionYpointer() const noexcept {
	return &positionY;
}
