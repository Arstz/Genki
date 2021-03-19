#pragma once
typedef unsigned int uint;

class Shape {
public:
	uint vertexCount;
	float* vertexCoords;
	float* vertexColors;

	uint EBOsize;
	uint* vertexIDs;


	Shape();
	Shape(
		uint vertexCount,
		float* vertexCoords,
		float* vertexColors,
		uint EBOsize,
		uint* vertexIDs
	);
	Shape(const Shape& shape);
	~Shape();

	uint getVertexCount();
	uint getEBOsize();

	float* getColorPointer(uint vertexNum, uint channelNum);
	float* getPositionPointer(uint vertexNum, uint channelNum);
};