#pragma once
#include "Shape.h"

class ShapeGroup {
public: //peredelaem cheres 2 minuti bistraa bistraa

	uint shapeCount;
	uint shapeGroupCount;

	Shape* shapes;
	ShapeGroup* shapeGroups;

	float positionX;
	float positionY;

	int layer;
	
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
	ShapeGroup(Shape* shape);
	ShapeGroup(const ShapeGroup& shapeGroup);
	~ShapeGroup();

	uint getEBOsize();
	uint getVertexCount();
};

