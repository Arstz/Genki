#pragma once
#include "ByteArray.h"
#include <tuple>
#include <limits>
#include "Vector2f.h"
#include "Color.h"

typedef unsigned int uint;

class Shape {
	uint	vertexCount {0};
	float*	vertexCoords {nullptr};
	float*	vertexColors {nullptr};

	uint	EBOsize {0};
	uint*	vertexIDs {nullptr};

	float	positionX {0};
	float	positionY {0};

	float	alphaChannel {1.f};

	int		layer {0};
public:
	Shape() = default;
	Shape(
		uint	vertexCount,
		float*	vertexCoords,
		float*	vertexColors,
		uint	EBOsize,
		uint*	vertexIDs,
		float	alphaChannel,
		float	positionX,
		float	positionY,
		int		layer
	);
	Shape(
		uint vertexCount,
		float*	vertexCoords,
		Color	color,
		uint	EBOsize,
		uint*	vertexIDs,
		float	alphaChannel,
		float	positionX,
		float	positionY,
		int		layer
	);
	~Shape();
	Shape(const Shape& other);
	Shape& operator=(const Shape& other);
	Shape(Shape&& other) noexcept;
	Shape& operator=(Shape&& other) noexcept;
	Shape(ByteArray* byteArray);

	static Shape makeRectangle(
		Vector2f	point1,
		Vector2f	point2,
		Vector2f	pos = Vector2f(0, 0),
		Color		col = Color(1, 1, 1, 1),
		int			layer = 0
	);

	void setColor(const Color& color);

	uint getVertexCount() const noexcept;
	uint getEBOsize() const noexcept;

	float* getVertexCoordsPointer() noexcept;
	float* getVertexColorsPointer() noexcept;

	uint* getVertexIDsPointer() noexcept;
	
	float* getAlphaChannelPointer() noexcept;
	float* getPositionXpointer() noexcept;
	float* getPositionYpointer() noexcept;

	int getLayer() const noexcept;

	const float* getVertexCoordsPointer() const noexcept;
	const float* getVertexColorsPointer() const noexcept;

	const uint* getVertexIDsPointer() const noexcept;

	const float* getAlphaChannelPointer() const noexcept;
	const float* getPositionXpointer() const noexcept;
	const float* getPositionYpointer() const noexcept;

	std::tuple<float, float, float, float> getBounds();
	void scale(Vector2f multiplier);
	ByteArray getByteArray();
};
