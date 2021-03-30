#pragma once
typedef unsigned int uint;

class Shape {
	uint vertexCount;
	float* vertexCoords;
	float* vertexColors;

	uint EBOsize;
	uint* vertexIDs;

	float positionX; //peredelaem primerno nikogda
	float positionY;

	int layer;
public:
	Shape();
	Shape(
		uint vertexCount,
		float* vertexCoords,
		float* vertexColors,
		uint EBOsize,
		uint* vertexIDs,
		float positionX,
		float positionY,
		int layer
	);

	Shape(const Shape& shape);
	~Shape();

	Shape& operator=(const Shape& shape);

	uint getVertexCount() const;
	uint getEBOsize() const;

	float* getVertexCoordsPointer();
	float* getVertexColorsPointer();

	uint* getVertexIDsPointer();

	float* getPositionXpointer();
	float* getPositionYpointer();

	int getLayer() const;
};