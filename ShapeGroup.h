#pragma once
#include "Shape.h"
#include <list>

class ShapeGroup {
	uint shapeCount;

	int layer;

	float alphaChannel;
	float positionX;
	float positionY;

	Shape* shapes;
	std::list<ShapeGroup> shapeGroups;
public:
	ShapeGroup();
	ShapeGroup(
		uint shapeCount,
		Shape* shapes,
		float alphaChannel,
		float positionX,
		float positionY,
		int layer
	);
	ShapeGroup(Shape shape);
	ShapeGroup(const ShapeGroup& shapeGroup);
	~ShapeGroup();
	ShapeGroup& operator=(const ShapeGroup& shapeGroup);

	std::list<ShapeGroup>::iterator addShapeGroup(ShapeGroup shapeGroup);
	void removeShapeGroup(std::list<ShapeGroup>::iterator shapeGroupIterator);

	float* getAlphaChannelPointer();
	float* getPositionXpointer();
	float* getPositionYpointer();

	int getLayer() const;

	uint getEBOsize() const;
	uint getVertexCount() const;

	uint getShapeCount() const;

	Shape* getShapesPointer();
	std::list<ShapeGroup> getShapeGroups();
};