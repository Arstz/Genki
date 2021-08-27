#include "Shape.h"
#include "ByteArray.h"
#include <initializer_list>
#include "crtdbg.h"
#include "..\include\CRTDBG\mydbgnew.h"
#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

Shape::Shape(
	uint	vertexCount,
	float*	vertexCoords,
	float*	vertexColors,
	uint	EBOsize,
	uint*	vertexIDs,
	float	alphaChannel = 0,
	float	positionX = 0,
	float	positionY = 0,
	int		layer = 0
) : vertexCount {vertexCount}, 
	vertexCoords {new float[static_cast<size_t>(vertexCount) * 2]}, 
	vertexColors {new float[static_cast<size_t>(vertexCount) * 4]},

	EBOsize			{EBOsize},
	vertexIDs		{new uint[EBOsize]},

	alphaChannel	{alphaChannel},
	positionX		{positionX},
	positionY		{positionY},
	layer			{layer}
{
	memcpy(this->vertexCoords, vertexCoords, vertexCount * sizeof(*vertexCoords) * 2);
	memcpy(this->vertexColors, vertexColors, vertexCount * sizeof(*vertexColors) * 4);

	memcpy(this->vertexIDs, vertexIDs, EBOsize * sizeof(*vertexIDs));
}

Shape::Shape(
	uint	vertexCount,
	float*	vertexCoords,
	Color	color,
	uint	EBOsize,
	uint*	vertexIDs,
	float	alphaChannel = 0,
	float	positionX = 0,
	float	positionY = 0,
	int		layer = 0
) : vertexCount		{vertexCount},
	vertexCoords	{new float[static_cast<size_t>(vertexCount) * 2]},
	vertexColors	{new float[static_cast<size_t>(vertexCount) * 4]},
	
	EBOsize			{EBOsize},
	vertexIDs		{new uint[EBOsize]},
	
	alphaChannel	{alphaChannel},
	positionX		{positionX},
	positionY		{positionY},
	layer			{layer}
{
	memcpy(this->vertexCoords, vertexCoords, vertexCount * sizeof(*vertexCoords) * 2);

	Color* tempColors = (Color*)this->vertexColors;

	for (int i = 0; i < vertexCount; i++) {
		tempColors[i] = color;
	}
	tempColors = nullptr;


	memcpy(this->vertexIDs, vertexIDs, EBOsize * sizeof(*vertexIDs));
}


Shape::Shape(const Shape& other) : 
	vertexCount		{other.vertexCount},
	vertexCoords	{new float[static_cast<size_t>(vertexCount) * 2]},
	vertexColors	{new float[static_cast<size_t>(vertexCount) * 4]},
					
	EBOsize			{other.EBOsize},
	vertexIDs		{new uint[EBOsize]},
				
	alphaChannel	{other.alphaChannel},
	positionX		{other.positionX},
	positionY		{other.positionY},
	layer			{other.layer} 
{
	memcpy(this->vertexCoords, other.vertexCoords, vertexCount * sizeof(*vertexCoords) * 2);
	memcpy(this->vertexColors, other.vertexColors, vertexCount * sizeof(*vertexColors) * 4);

	memcpy(this->vertexIDs, other.vertexIDs, EBOsize * sizeof(*vertexIDs));
}

Shape& Shape::operator=(const Shape& other) {
	vertexCount		= other.vertexCount;
	EBOsize			= other.EBOsize;

	alphaChannel	= other.alphaChannel;
	positionX		= other.positionX;
	positionY		= other.positionY;
	layer			= other.layer;

	float* newVertexCoords = new float[static_cast<size_t>(vertexCount) * 2];
	float* newVertexColors = new float[static_cast<size_t>(vertexCount) * 4];

	uint* newVertexIDs = new uint[EBOsize];

	delete[] vertexCoords;
	delete[] vertexColors;
	delete[] vertexIDs;

	memcpy(newVertexCoords, other.vertexCoords, vertexCount * sizeof(*vertexCoords) * 2);
	memcpy(newVertexColors, other.vertexColors, vertexCount * sizeof(*vertexColors) * 4);

	memcpy(newVertexIDs, other.vertexIDs, EBOsize * sizeof(*vertexIDs));

	vertexCoords	= newVertexCoords;
	vertexColors	= newVertexColors;
	vertexIDs		= newVertexIDs;

	newVertexCoords	= nullptr;
	newVertexColors	= nullptr;
	newVertexIDs	= nullptr;

	return *this;
}

Shape::Shape(Shape&& other) noexcept :
	vertexCount		{other.vertexCount},
	vertexCoords	{other.vertexCoords},
	vertexColors	{other.vertexColors},
					
	EBOsize			{other.EBOsize},
	vertexIDs		{other.vertexIDs},
				
	alphaChannel	{other.alphaChannel},
	positionX		{other.positionX},
	positionY		{other.positionY},
	layer			{other.layer} 
{

	other.vertexCoords = nullptr;
	other.vertexColors = nullptr;
	other.vertexIDs = nullptr;
}

Shape& Shape::operator=(Shape&& other) noexcept {
	delete[] vertexCoords;
	delete[] vertexColors;
	delete[] vertexIDs;

	vertexCount		= other.vertexCount;
	EBOsize			= other.EBOsize;

	alphaChannel	= other.alphaChannel;
	positionX		= other.positionX;
	positionY		= other.positionY;
	layer			= other.layer;

	vertexCoords	= other.vertexCoords;
	vertexColors	= other.vertexColors;
	vertexIDs		= other.vertexIDs;

	other.vertexCoords	= nullptr;
	other.vertexColors	= nullptr;
	other.vertexIDs		= nullptr;

	return *this;
}

Shape::Shape(ByteArray* byteArray) {
	*byteArray >> vertexCount >> EBOsize >> layer >> alphaChannel >> positionX >> positionY;
	vertexCoords = new float[static_cast<size_t>(vertexCount) * 2];
	vertexColors = new float[static_cast<size_t>(vertexCount) * 4];
	vertexIDs = new uint[EBOsize];
	byteArray->read(vertexCoords, sizeof(*vertexCoords) * vertexCount * 2);
	byteArray->read(vertexColors, sizeof(*vertexColors) * vertexCount * 4);
	byteArray->read(vertexIDs, sizeof(*vertexIDs) * EBOsize);
}

Shape Shape::makeRectangle(
	Vector2f	point1,
	Vector2f	point2,
	Vector2f	pos, 
	Color		col, 
	int			layer
) {
	return	Shape(
		4,
		(float*)std::begin(std::initializer_list<float> {point1.x, point1.y, point1.x, point2.y, point2.x, point1.y, point2.x, point2.y}),
		(float*)std::begin(std::initializer_list<float> {col.r, col.g, col.b, col.a, col.r, col.g, col.b, col.a, col.r, col.g, col.b, col.a, col.r, col.g, col.b, col.a}),
		6,
		(uint*)std::begin(std::initializer_list<uint> {0, 1, 2, 1, 2, 3}),
		1.f,
		pos.x, 
		pos.y, 
		layer
	);
}

void Shape::setColor(const Color& color) {
	for (int i = 0; i < vertexCount; i++) {
		vertexColors[i * 4 + 0] = color.r;
		vertexColors[i * 4 + 1] = color.g;
		vertexColors[i * 4 + 2] = color.b;
		vertexColors[i * 4 + 3] = color.a;
	}
}

ByteArray Shape::getByteArray() {
	ByteArray byteArray(
		sizeof(vertexCount) +
		sizeof(EBOsize) +
		sizeof(layer) +
		sizeof(alphaChannel) +
		sizeof(positionX) +
		sizeof(positionY) +
		sizeof(*vertexIDs) * EBOsize +
		sizeof(*vertexCoords) * vertexCount * 2 +
		sizeof(*vertexColors) * vertexCount * 4
	);
	byteArray << vertexCount << EBOsize << layer << alphaChannel << positionX << positionY;
	byteArray.add(vertexCoords, sizeof(*vertexCoords) * vertexCount * 2);
	byteArray.add(vertexColors, sizeof(*vertexColors) * vertexCount * 4);
	byteArray.add(vertexIDs, sizeof(*vertexIDs) * EBOsize);

	return byteArray;
}

Shape::~Shape() {
	delete[] vertexCoords;	
	delete[] vertexColors;
	delete[] vertexIDs;
	vertexColors = nullptr;
	vertexCoords = nullptr;
	vertexIDs = nullptr;
}

uint Shape::getVertexCount() const noexcept {
	return vertexCount;
}

uint Shape::getEBOsize() const noexcept {
	return EBOsize;
}

float* Shape::getVertexCoordsPointer() noexcept {
	return vertexCoords;
}

float* Shape::getVertexColorsPointer() noexcept {
	return vertexColors;
}

uint* Shape::getVertexIDsPointer() noexcept {
	return vertexIDs;
}


float* Shape::getAlphaChannelPointer() noexcept {
	return &alphaChannel;
}

float* Shape::getPositionXpointer() noexcept {
	return &positionX;
}

float* Shape::getPositionYpointer() noexcept {
	return &positionY;
}

int Shape::getLayer() const noexcept {
	return layer;
}

const float* Shape::getVertexCoordsPointer() const noexcept {
	return vertexCoords;
}

const float* Shape::getVertexColorsPointer() const noexcept {
	return vertexColors;
}

const uint* Shape::getVertexIDsPointer() const noexcept {
	return vertexIDs;
}

const float* Shape::getAlphaChannelPointer() const noexcept {
	return &alphaChannel;
}

const float* Shape::getPositionXpointer() const noexcept {
	return &positionX;
}

const float* Shape::getPositionYpointer() const noexcept {
	return &positionY;
}

std::tuple<float, float, float, float> Shape::getBounds() {
	float minX = std::numeric_limits<float>::max();
	float minY = std::numeric_limits<float>::max();
	float maxX = std::numeric_limits<float>::min();
	float maxY = std::numeric_limits<float>::min();

	for (int i = 0; i < vertexCount * 2; i += 2) {
		minX = std::min(minX, vertexCoords[i]);
		maxX = std::max(maxX, vertexCoords[i]);

		minY = std::min(minY, vertexCoords[i+1]);
		maxY = std::max(maxY, vertexCoords[i+1]);
	}
	return std::make_tuple(minX, minY, maxX, maxY);
}


void Shape::scale(Vector2f multiplier) {
	for (int i = 0; i < vertexCount; i++) {
		vertexCoords[i * 2 + 0] *= multiplier.x;
		vertexCoords[i * 2 + 1] *= multiplier.y;
	}
}
