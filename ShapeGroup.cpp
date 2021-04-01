#include "ShapeGroup.h"

ShapeGroup::ShapeGroup() {
	this->shapes = nullptr;
	this->shapeGroups = nullptr;
}
ShapeGroup::ShapeGroup(
	uint shapeCount,
	uint shapeGroupCount,
	Shape* shapes,
	ShapeGroup* shapeGroups,
	float alphaChannel,
	float positionX,
	float positionY,
	int layer
) {
	this->shapeCount = shapeCount;
	this->shapeGroupCount = shapeGroupCount;

	this->shapes = new Shape[shapeCount];
	for (int i = 0; i < shapeCount; i++) this->shapes[i] = shapes[i];

	this->shapeGroups = new ShapeGroup[shapeGroupCount];
	for (int i = 0; i < shapeGroupCount; i++) this->shapeGroups[i] = shapeGroups[i];

	this->alphaChannel = alphaChannel;
	this->positionX = positionX;
	this->positionY = positionY;
	this->layer = layer;
}

ShapeGroup::ShapeGroup(const Shape &shape) {
	this->shapeCount = 1;
	this->shapeGroupCount = 0;

	this->layer = shape.getLayer();
	this->shapes = new Shape(shape);
	this->shapeGroups = nullptr;
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
	this->shapeGroupCount = shapeGroup.shapeGroupCount;

	this->shapes = new Shape[shapeGroup.shapeCount];
	this->shapeGroups = new ShapeGroup[shapeGroup.shapeGroupCount];

	for (int i = 0; i < shapeGroup.shapeCount; i++) this->shapes[i] = shapeGroup.shapes[i];
	for (int i = 0; i < shapeGroup.shapeGroupCount; i++) this->shapeGroups[i] = shapeGroup.shapeGroups[i];
}

ShapeGroup& ShapeGroup::operator=(const ShapeGroup& shapeGroup) {
	delete[] shapes;
	delete[] shapeGroups;

	this->layer = shapeGroup.layer;
	this->alphaChannel = shapeGroup.alphaChannel;
	this->positionX = shapeGroup.positionX;
	this->positionY = shapeGroup.positionY;

	this->shapeCount = shapeGroup.shapeCount;
	this->shapeGroupCount = shapeGroup.shapeGroupCount;

	this->shapes = new Shape[shapeGroup.shapeCount];
	this->shapeGroups = new ShapeGroup[shapeGroup.shapeGroupCount];

	for (int i = 0; i < shapeGroup.shapeCount; i++) this->shapes[i] = shapeGroup.shapes[i];
	for (int i = 0; i < shapeGroup.shapeGroupCount; i++) this->shapeGroups[i] = shapeGroup.shapeGroups[i];

	return *this;
}

ShapeGroup::~ShapeGroup() {
	delete[] shapes;
	delete[] shapeGroups;
	shapes = nullptr;
	shapeGroups = nullptr;
}

uint ShapeGroup::getEBOsize() const {
	uint size = 0;

	for (int i = 0; i < shapeCount; i++) size += shapes[i].getEBOsize();
	for (int i = 0; i < shapeGroupCount; i++) size += shapeGroups[i].getEBOsize();

	return size;
}

uint ShapeGroup::getVertexCount() const {
	uint size = 0;

	for (int i = 0; i < shapeCount; i++) size += shapes[i].getVertexCount();
	for (int i = 0; i < shapeGroupCount; i++) size += shapeGroups[i].getVertexCount();

	return size;
}

uint ShapeGroup::getShapeCount() const {
	return shapeCount;
}

uint ShapeGroup::getShapeGroupCount() const {
	return shapeGroupCount;
}

Shape* ShapeGroup::getShapesPointer() {
	return shapes;
}

ShapeGroup* ShapeGroup::getShapeGroupsPointer() {
	return shapeGroups;
}

float ShapeGroup::getAlphaChannel() const {
	return alphaChannel;
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