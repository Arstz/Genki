#pragma once
#include "Shape.h"
#include <list>
#include <vector>

class ShapeGroup {
	uint shapeCount;

	int layer;

	float alphaChannel;
	float positionX;
	float positionY;

	Shape* shapes;
	std::list<ShapeGroup> shapeGroups;
public:
	~ShapeGroup();
	ShapeGroup();
	ShapeGroup(const ShapeGroup& shapeGroup);
	ShapeGroup& operator=(const ShapeGroup& shapeGroup);
	ShapeGroup(ShapeGroup&& shapeGroup) noexcept;
	ShapeGroup& operator=(ShapeGroup&& shapeGroup) noexcept;

	ShapeGroup(
		uint shapeCount,
		Shape* shapes,
		float alphaChannel,
		float positionX,
		float positionY,
		int layer
	);
	ShapeGroup(const Shape& shape);
	ShapeGroup(ByteArray* byteArray);

	std::list<ShapeGroup>::iterator addShapeGroup(const ShapeGroup& shapeGroup);
	void removeShapeGroup(const std::list<ShapeGroup>::iterator& shapeGroupIterator);

	float* getAlphaChannelPointer();
	float* getPositionXpointer();
	float* getPositionYpointer();

	int getLayer() const;

	uint getEBOsize() const;
	uint getVertexCount() const;

	uint getShapeCount() const;

	Shape* getShapesPointer();
	std::list<ShapeGroup>* getShapeGroups();
	ByteArray getByteArray();
};