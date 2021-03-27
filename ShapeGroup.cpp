#include "ShapeGroup.h"

ShapeGroup::ShapeGroup() {}
ShapeGroup::ShapeGroup(
	uint shapeCount,
	uint shapeGroupCount,
	Shape* shapes,
	ShapeGroup* shapeGroups,
	float positionX,
	float positionY,
	int layer
) {
	this->shapeCount = shapeCount;
	this->shapeGroupCount = shapeGroupCount;
	this->shapes = shapes;
	this->shapeGroups = shapeGroups;
	this->positionX = positionX;
	this->positionY = positionY;
	this->layer = layer;
}

ShapeGroup::ShapeGroup(Shape* shape) {
	this->shapeCount = 1;
	this->shapeGroupCount = 0;

	this->layer = shape->layer;
	this->shapes = shape;
	this->shapeGroups = nullptr;

	this->positionX = 0.f;
	this->positionY = 0.f;
}

ShapeGroup::ShapeGroup(const ShapeGroup& shapeGroup) {
	this->layer = shapeGroup.layer;
	this->positionX = shapeGroup.positionX;
	this->positionY = shapeGroup.positionY;

	this->shapes = new Shape[shapeGroup.shapeCount];
	this->shapeGroups = new ShapeGroup[shapeGroup.shapeGroupCount];

	for (int i = 0; i < shapeGroup.shapeCount; i++) this->shapes[i] = shapeGroup.shapes[i];
	for (int i = 0; i < shapeGroup.shapeGroupCount; i++) this->shapeGroups[i] = shapeGroup.shapeGroups[i];
}

ShapeGroup::~ShapeGroup() {
	delete[] shapes;
	delete[] shapeGroups;
	shapes = nullptr;
	shapeGroups = nullptr;
}

uint ShapeGroup::getEBOsize() {
	uint size = 0;

	for (int i = 0; i < shapeCount; i++) size += shapes[i].getEBOsize();
	for (int i = 0; i < shapeGroupCount; i++) size += shapeGroups[i].getEBOsize();

	return size;
}

uint ShapeGroup::getVertexCount() {
	uint size = 0;

	for (int i = 0; i < shapeCount; i++) size += shapes[i].getVertexCount();
	for (int i = 0; i < shapeGroupCount; i++) size += shapeGroups[i].getVertexCount();

	return size;
}
