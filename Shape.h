#pragma once
typedef unsigned int uint;

class Graphics;

class Shape {
	friend Graphics;
	uint vertexCount;
	float* vertexCoords;
	float* vertexColors;

	uint EBOsize;
	uint* vertexIDs;
public:

	Shape();
	Shape(
		unsigned int vertexCount,
		float* vertexCoords,
		float* vertexColors,
		unsigned int EBOsize,
		unsigned int* vertexIDs
	);
	~Shape();

	uint getVertexCount();
	uint getEBOsize();

	float* getColorPointer(uint vertexNum, uint channelNum);
	float* getPositionPointer(uint vertexNum, uint channelNum);
};