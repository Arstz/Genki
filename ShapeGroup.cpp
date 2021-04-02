#include "ShapeGroup.h"
#include "ByteArray.h"

ShapeGroup::ShapeGroup() {
	this->shapes = nullptr;
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

std::vector<char> ShapeGroup::getByteArray() {
	unsigned int shapeGroupCount = shapeGroups.size();
	std::vector<std::vector<char>> byteShapeGroups(shapeGroupCount);

	unsigned int byteArraySize =
		sizeof(shapeGroupCount) +
		sizeof(layer) +
		sizeof(alphaChannel) +
		sizeof(positionX) +
		sizeof(positionY);

	std::vector<std::vector<char>> byteShapes(shapeCount);
	for (int i = 0; i < shapeCount; i++) {
		byteShapes[i] = shapes[i].getByteArray();
		byteArraySize += byteShapes[i].size();
	}

	if (shapeGroupCount) {
		int i = 0;
		for (auto& shapeGroup : shapeGroups) {
			byteShapeGroups[i] = shapeGroup.getByteArray();
			byteArraySize += byteShapeGroups[i].size();
			i++;
		}
	}

	byteArraySize +=
		sizeof(shapeCount) +
		sizeof(shapeGroupCount) +
		sizeof(layer) +
		sizeof(alphaChannel) +
		sizeof(positionX) +
		sizeof(positionY);

	std::vector<char> byteArray(byteArraySize);
	unsigned int offset = 0;

	writeToByteArray(byteArray, (char*)&shapeCount, offset, sizeof(shapeCount));
	writeToByteArray(byteArray, (char*)&shapeGroupCount, offset, sizeof(shapeGroupCount));
	writeToByteArray(byteArray, (char*)&layer, offset, sizeof(layer));
	writeToByteArray(byteArray, (char*)&alphaChannel, offset, sizeof(alphaChannel));
	writeToByteArray(byteArray, (char*)&positionX, offset, sizeof(positionX));
	writeToByteArray(byteArray, (char*)&positionY, offset, sizeof(positionY));

	for (int i = 0; i < byteShapes.size(); i++)
		writeToByteArray(byteArray, byteShapes[i], offset);

	if (shapeGroupCount) 
		for (int i = 0; i < byteShapeGroups.size(); i++) 
			writeToByteArray(byteArray, byteShapeGroups[i], offset);

	return byteArray;
}