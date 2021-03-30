#pragma once
#include "Shape.h"

class ShapeGroup {
	uint shapeCount;
	uint shapeGroupCount;

	float positionX;
	float positionY;

	Shape* shapes;
	ShapeGroup* shapeGroups;

	int layer;
public:
	ShapeGroup();
	ShapeGroup(
		uint shapeCount,
		uint shapeGroupCount,
		Shape* shapes,
		ShapeGroup* shapeGroups,
		float positionX,
		float positionY,
		int layer
	);
	ShapeGroup(const Shape& shape);
	ShapeGroup(const ShapeGroup& shapeGroup);
	~ShapeGroup();

	float* getPositionXpointer();
	float* getPositionYpointer();

	int getLayer() const;

	uint getEBOsize() const;
	uint getVertexCount() const;

	uint getShapeCount() const;
	uint getShapeGroupCount() const;

	Shape* getShapesPointer();
	ShapeGroup* getShapeGroupsPointer();
};