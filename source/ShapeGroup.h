#pragma once
#include "Shape.h"
#include <list>
#include <vector>

class ShapeGroup {
	std::list<ShapeGroup> shapeGroups {};

	uint	shapeCount {0};
	Shape*	shapes {nullptr};

	float	positionX {0.f};
	float	positionY {0.f};

	float	alphaChannel {0.f};

	int		layer {0};
public:
	~ShapeGroup();
	ShapeGroup() = default;
	ShapeGroup(const ShapeGroup& other);
	ShapeGroup& operator=(const ShapeGroup& other);
	ShapeGroup(ShapeGroup&& other) noexcept;
	ShapeGroup& operator=(ShapeGroup&& other) noexcept;

	ShapeGroup(
		uint	shapeCount,
		Shape*	shapes,
		float	alphaChannel,
		float	positionX,
		float	positionY,
		int		layer
	);
	ShapeGroup(const Shape& shape);
	ShapeGroup(ByteArray* byteArray);

	std::list<ShapeGroup>::iterator addShapeGroup(const ShapeGroup& shapeGroup);
	void removeShapeGroup(const std::list<ShapeGroup>::iterator& shapeGroupIterator);

	uint getShapeCount() const noexcept;

	uint getEBOsize() const noexcept;
	uint getVertexCount() const noexcept;

	Shape* getShapesPointer() noexcept;

	std::list<ShapeGroup>& getShapeGroups() noexcept;

	float* getAlphaChannelPointer() noexcept;
	float* getPositionXpointer() noexcept;
	float* getPositionYpointer() noexcept;

	int getLayer() const noexcept;

	const Shape* getShapesPointer() const noexcept;

	const std::list<ShapeGroup>& getShapeGroups() const noexcept;

	const float* getAlphaChannelPointer() const noexcept;
	const float* getPositionXpointer() const noexcept;
	const float* getPositionYpointer() const noexcept;

	ByteArray getByteArray() const;
};