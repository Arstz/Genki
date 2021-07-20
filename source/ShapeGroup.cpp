#include "ShapeGroup.h"
#include "ByteArray.h"

#include "crtdbg.h"
#include "..\include\CRTDBG\mydbgnew.h"
#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

ShapeGroup::ShapeGroup() {
	this->shapeCount = 0;
	this->shapes = nullptr;
	this->alphaChannel = 1.f;
	this->positionX = 0.f;
	this->positionY = 0.f;
	this->layer = 0;
}
ShapeGroup::ShapeGroup(
	uint shapeCount,
	Shape* shapes,
	float alphaChannel,
	float positionX,
	float positionY,
	int layer
) {
	this->shapeCount = shapeCount;

	this->shapes = new Shape[shapeCount];
	for (int i = 0; i < shapeCount; i++) this->shapes[i] = shapes[i];

	this->shapeGroups = shapeGroups;

	this->alphaChannel = alphaChannel;
	this->positionX = positionX;
	this->positionY = positionY;
	this->layer = layer;
}

ShapeGroup::ShapeGroup(const Shape& shape) {
	this->shapeCount = 1;

	this->layer = shape.getLayer();
	this->shapes = new Shape[1] {shape};
	this->shapeGroups = std::list<ShapeGroup>();
	this->alphaChannel = 1.f;
	this->positionX = 0.f;
	this->positionY = 0.f;
}

ShapeGroup::ShapeGroup(const ShapeGroup& shapeGroup) {
	this->layer = shapeGroup.layer;
	this->alphaChannel = shapeGroup.alphaChannel;
	this->positionX = shapeGroup.positionX;
	this->positionY = shapeGroup.positionY;

	this->shapeCount = shapeGroup.shapeCount;

	this->shapes = new Shape[shapeGroup.shapeCount];
	this->shapeGroups = shapeGroups;

	for (int i = 0; i < shapeGroup.shapeCount; i++) this->shapes[i] = shapeGroup.shapes[i];
}

ShapeGroup::ShapeGroup(ByteArray* byteArray) {
	unsigned int shapeGroupCount;
	shapeGroups = std::list<ShapeGroup>();
	*byteArray >> shapeCount >> shapeGroupCount >> layer >> alphaChannel >> positionX >> positionY;
	shapes = new Shape[shapeCount];
	for (int i = 0; i < shapeCount; i++)
		shapes[i] = Shape(byteArray);
	for (int i = 0; i < shapeGroupCount; i++)
		shapeGroups.push_back(ShapeGroup(byteArray));
}

ByteArray ShapeGroup::getByteArray() {
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

	for (int i = 0; i < shapeCount; i++) {
		byteShapes[i] = shapes[i].getByteArray();
		byteArraySize += byteShapes[i].getSize();
	}
	if (shapeGroupCount) {
		int i = 0;
		for (auto& shapeGroup : shapeGroups) {
			byteShapeGroups[i] = shapeGroup.getByteArray();
			byteArraySize += byteShapeGroups[i].getSize();
			i++;
		}
	}
	ByteArray byteArray(byteArraySize);
	byteArray << shapeCount << shapeGroupCount << layer << alphaChannel << positionX << positionY;
	for (int i = 0; i < byteShapes.size(); i++)
		byteArray.add(byteShapes[i]);
	if (shapeGroupCount)
		for (int i = 0; i < byteShapeGroups.size(); i++)
			byteArray.add(byteShapeGroups[i]);
	return byteArray;
}

ShapeGroup& ShapeGroup::operator=(const ShapeGroup& shapeGroup) {
	delete[] shapes;

	this->layer = shapeGroup.layer;
	this->alphaChannel = shapeGroup.alphaChannel;
	this->positionX = shapeGroup.positionX;
	this->positionY = shapeGroup.positionY;

	this->shapeCount = shapeGroup.shapeCount;

	this->shapes = new Shape[shapeGroup.shapeCount];
	this->shapeGroups = shapeGroups;

	for (int i = 0; i < shapeGroup.shapeCount; i++) this->shapes[i] = shapeGroup.shapes[i];

	return *this;
}

ShapeGroup::ShapeGroup(ShapeGroup&& shapeGroup) noexcept {
	this->shapes = shapeGroup.shapes;
	this->layer = shapeGroup.layer;
	this->alphaChannel = shapeGroup.alphaChannel;
	this->positionX = shapeGroup.positionX;
	this->positionY = shapeGroup.positionY;
	this->shapeCount = shapeGroup.shapeCount;
	shapeGroup.shapes = nullptr;
}

ShapeGroup& ShapeGroup::operator=(ShapeGroup&& shapeGroup) noexcept {
	delete[] shapes;
	this->shapes = shapeGroup.shapes;
	this->layer = shapeGroup.layer;
	this->alphaChannel = shapeGroup.alphaChannel;
	this->positionX = shapeGroup.positionX;
	this->positionY = shapeGroup.positionY;
	this->shapeCount = shapeGroup.shapeCount;
	shapeGroup.shapes = nullptr;
	return *this;
}

std::list<ShapeGroup>::iterator ShapeGroup::addShapeGroup(const ShapeGroup &shapeGroup) {
	std::list<ShapeGroup>::iterator i = shapeGroups.begin();
	while (i != shapeGroups.end() && (*i).layer < shapeGroup.layer) i++;
	return shapeGroups.insert(i, shapeGroup); 
}

void ShapeGroup::removeShapeGroup(const std::list<ShapeGroup>::iterator &shapeGroupIterator) {
	shapeGroups.erase(shapeGroupIterator);
	delete[] (*shapeGroupIterator).shapes;
	(*shapeGroupIterator).shapes = nullptr;
}

ShapeGroup::~ShapeGroup() {
	delete[] shapes;
	shapes = nullptr;
}

uint ShapeGroup::getEBOsize() const {
	uint size = 0;

	for (int i = 0; i < shapeCount; i++) size += shapes[i].getEBOsize();
	for (auto &shapeGroup : shapeGroups) size += shapeGroup.getEBOsize();

	return size;
}

uint ShapeGroup::getVertexCount() const {
	uint size = 0;

	for (int i = 0; i < shapeCount; i++) size += shapes[i].getVertexCount();
	for (auto &shapeGroup : shapeGroups) size += shapeGroup.getVertexCount();

	return size;
}

uint ShapeGroup::getShapeCount() const {
	return shapeCount;
}

Shape* ShapeGroup::getShapesPointer() {
	return shapes;
}

std::list<ShapeGroup> ShapeGroup::getShapeGroups() {
	return shapeGroups;
}

float* ShapeGroup::getAlphaChannelPointer() {
	return &alphaChannel;
}

float* ShapeGroup::getPositionXpointer() {
	return &positionX;
}

float* ShapeGroup::getPositionYpointer() {
	return &positionY;
}

int ShapeGroup::getLayer() const {
	return layer;
}

