#pragma once
#include <vector>
typedef unsigned int uint;

class Shape {
	uint vertexCount;
	uint EBOsize;

	uint* vertexIDs;

	int layer;	

	float alphaChannel;

	float positionX; //peredelaem primerno nikogda
	float positionY;

	float* vertexCoords;
	float* vertexColors;	
public:
	Shape();
	Shape(
		uint vertexCount,
		float* vertexCoords,
		float* vertexColors,
		uint EBOsize,
		uint* vertexIDs,
		float alphaChannel,
		float positionX,
		float positionY,
		int layer
	);

	Shape(const Shape& shape);
	Shape(char* byteArray, unsigned int& offset);
	~Shape();

	Shape& operator=(const Shape& shape);

	uint getVertexCount() const;
	uint getEBOsize() const;

	float* getVertexCoordsPointer();
	float* getVertexColorsPointer();

	uint* getVertexIDsPointer();

	float* getAlphaChannelPointer();
	float* getPositionXpointer();
	float* getPositionYpointer();

	int getLayer() const;
	std::vector<char> getByteArray();
};