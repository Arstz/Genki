#pragma once
#include "ByteArray.h"
#include <tuple>
#include <limits>
#include "Vector2f.h"
#include "Color.h"

typedef unsigned int uint;

class Shape {
	uint vertexCount;
	uint EBOsize;

	uint* vertexIDs;

	int layer;	

	float alphaChannel;

	float positionX;
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
	Shape(
		uint vertexCount,
		float* vertexCoords,
		Color color,
		uint EBOsize,
		uint* vertexIDs,
		float alphaChannel,
		float positionX,
		float positionY,
		int layer
	);
	~Shape();
	Shape(const Shape& shape);
	Shape& operator=(const Shape& shape);
	Shape(Shape&& shape) noexcept;
	Shape& operator=(Shape&& shape) noexcept;
	Shape(ByteArray* byteArray);

	static Shape makeRectangle(
		Vector2f point1,
		Vector2f point2,
		Vector2f pos = Vector2f(0, 0),
		Color col = Color(1, 1, 1, 1),
		int layer = 0
	);

	void setColor(Color color);

	uint getVertexCount() const;
	uint getEBOsize() const;

	void scale(Vector2f multiplier);

	float* getVertexCoordsPointer();
	float* getVertexColorsPointer();

	uint* getVertexIDsPointer();

	std::tuple<float, float, float, float> getBounds();
	float* getAlphaChannelPointer();
	float* getPositionXpointer();
	float* getPositionYpointer();

	int getLayer() const;
	ByteArray getByteArray();
};
