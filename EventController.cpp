#include "EventController.h"
#include "LevelEvent.h"
#include <iostream>
#include <fstream>

std::vector<LevelEvent*> EventController::level;
int EventController::currentEvent = 0;
float* EventController::currentTime = nullptr;

void EventController::update() 
{
	while (currentEvent < level.size() && level[currentEvent]->getInitTime() < *currentTime) {
		level[currentEvent]->start();
		currentEvent++;
	}
}

void EventController::generateObject(
	uint vertexCount,
	float* vertexCoords,
	float* vertexColors,
	uint EBOsize,
	uint* vertexIDs,
	int shapeId,
	float initTime
)
{
	Shape shape = Shape(vertexCount, vertexCoords, vertexColors, EBOsize, vertexIDs);

	level.push_back(&ShapeSpawnEvent(&shape, shapeId, initTime));
}

void EventController::loadLevel(std::string path) {
	std::ifstream fin;
	fin.open("raid_na_derevene.lvl", std::ifstream::binary);
	size_t size = 0;
	fin.read((char*)(&size), sizeof(size_t));
	for (int i = 0; i < size; i++)
	{
		size_t type = level[i]->getType();
		fin.read((char*)(&type), sizeof(LevelEventType));

		float initTime;
		fin.read((char*)(&initTime), sizeof(float));

		switch (type)
		{
		case LevelEventType::EMPTY:
			break;
		case LevelEventType::BACKGROUND_COLOR_ANIMATION:
			break;
		case LevelEventType::CAMERA_ANIMATION:
			break;
		case LevelEventType::SHAPE_SPAWN:

			uint vertexCount;
			uint EBOsize;
			int shapeId;

			fin.read((char*)(&vertexCount), sizeof(uint));
			float* vertexCoords = new float[vertexCount * 2];
			float* vertexColors = new float[vertexCount * 4];

			fin.read((char*)(&vertexCoords), sizeof(float) * vertexCount * 2);
			fin.read((char*)(&vertexCoords), sizeof(float) * vertexCount * 4);
			fin.read((char*)(&EBOsize), sizeof(uint));

			uint* vertexIDs = new uint[EBOsize];
			fin.read((char*)(&vertexIDs), sizeof(uint) * EBOsize);
			fin.read((char*)(&shapeId), sizeof(int));

			generateObject(vertexCount,
				vertexCoords,
				vertexColors,
				EBOsize,
				vertexIDs,
				shapeId,
				initTime
			)

			break;
		case LevelEventType::SHAPE_DESTRUCTION:
			break;
		case LevelEventType::SHAPE_ANIMATION:
			break;
		case LevelEventType::PLAYER_BINDING:
			break;
		}
		fin.close();
	}
	
}

void EventController::saveLevel(std::string path, std::vector<LevelEvent*> level) {
	std::ofstream fout;
	fout.open("raid_na_derevene.lvl", std::ofstream::binary);
	size_t size = level.size();
	fout.write((char*)(&size), sizeof(size_t));
	for (int i = 0; i < size; i++)
	{
		LevelEventType type = level[i]->getType();
		fout.write((char*)(&type), sizeof(LevelEventType));
		switch (type)
		{
		case LevelEventType::EMPTY:

			break;
		case LevelEventType::BACKGROUND_COLOR_ANIMATION:
			break;
		case LevelEventType::CAMERA_ANIMATION:
			break;
		case LevelEventType::SHAPE_SPAWN:
			break;
		case LevelEventType::SHAPE_DESTRUCTION:
			break;
		case LevelEventType::SHAPE_ANIMATION:
			break;
		case LevelEventType::PLAYER_BINDING:
			break;
		}
	}
}