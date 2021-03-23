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

void EventController::loadLevel(std::string path) {
	level.clear();
	std::ifstream fin;
	fin.open("raid_na_derevene.lvl", std::ifstream::binary);
	size_t size;
	fin.read((char*)(&size), sizeof(size_t));
	level.resize(size);

	LevelEvent::dynamicShapes = new std::list<Shape*>::iterator[size];

	uint vertexCount;
	uint EBOsize;
	int shapeID;

	float* vertexCoords;
	float* vertexColors;
	uint* vertexIDs;

	int AnimatedValueID;
	int vertexNum;
	int channelNum;

	Animation* animation;
	AnimatedValueType animatedValueType;
	uint keyCount;
	float* timeKeys;
	float* stateKeys;

	uint valueNum;

	LevelEventType type;
	float initTime;

	for (int i = 0; i < size; i++) {
		fin.read((char*)(&type), sizeof(LevelEventType));
		fin.read((char*)(&initTime), sizeof(float));

		switch (type) {
		case LevelEventType::EMPTY:
			break;
		case LevelEventType::BACKGROUND_COLOR_ANIMATION:
			break;
		case LevelEventType::CAMERA_ANIMATION:
			fin.read((char*)(&valueNum), sizeof(uint));

			fin.read((char*)(&keyCount), sizeof(int));

			timeKeys = new float[keyCount];
			stateKeys = new float[keyCount];

			fin.read((char*)(timeKeys), sizeof(int) * keyCount);
			fin.read((char*)(stateKeys), sizeof(int) * keyCount);

			level[i] = new CameraAnimationEvent(
				new Animation(keyCount, timeKeys, stateKeys),
				valueNum,
				initTime
			);

			break;
		case LevelEventType::SHAPE_SPAWN:
			fin.read((char*)(&vertexCount), sizeof(uint));
			vertexCoords = new float[vertexCount * 2];
			vertexColors = new float[vertexCount * 4];

			fin.read((char*)(vertexCoords), sizeof(float) * vertexCount * 2);
			fin.read((char*)(vertexColors), sizeof(float) * vertexCount * 4);
			fin.read((char*)(&EBOsize), sizeof(uint));

			vertexIDs = new uint[EBOsize];
			fin.read((char*)(vertexIDs), sizeof(uint) * EBOsize);
			fin.read((char*)(&shapeID), sizeof(int));

			level[i] = new ShapeSpawnEvent(
				new Shape(
					vertexCount,
					vertexCoords,
					vertexColors,
					EBOsize,
					vertexIDs
				),
				shapeID,
				initTime
			);

			break;
		case LevelEventType::SHAPE_DESTRUCTION:
			fin.read((char*)(&shapeID), sizeof(int));
			level[i] = new ShapeDestructionEvent(shapeID, initTime);
			break;
		case LevelEventType::SHAPE_ANIMATION:
			fin.read((char*)(&shapeID), sizeof(int));
			fin.read((char*)(&AnimatedValueID), sizeof(int));
			fin.read((char*)(&vertexNum), sizeof(int));
			fin.read((char*)(&channelNum), sizeof(int));
			fin.read((char*)(&animatedValueType), sizeof(AnimatedValueType));

			fin.read((char*)(&keyCount), sizeof(int));

			timeKeys = new float[keyCount];
			stateKeys = new float[keyCount];

			fin.read((char*)(timeKeys), sizeof(int) * keyCount);
			fin.read((char*)(stateKeys), sizeof(int) * keyCount);

			level[i] = new ShapeAnimationEvent(
				new Animation(keyCount, timeKeys, stateKeys),
				animatedValueType,
				AnimatedValueID,
				shapeID,
				vertexNum,
				channelNum
			);

			break;
		case LevelEventType::PLAYER_BINDING:
			fin.read((char*)(&shapeID), sizeof(int));
			level[i] = new PlayerBindingEvent(shapeID, initTime);
			break;
		}
	}
	fin.close();
	vertexCoords = nullptr;
	vertexColors = nullptr;
	vertexIDs = nullptr;
	animation = nullptr;
	timeKeys = nullptr;
	stateKeys = nullptr;
}

void EventController::saveLevel(std::string path, std::vector<LevelEvent*>& level) {
	std::ofstream fout;
	fout.open("raid_na_derevene.lvl", std::ofstream::binary);
	size_t size = level.size();
	fout.write((char*)(&size), sizeof(size_t));
	for (int i = 0; i < size; i++) {
		LevelEventType type = level[i]->getType();
		float initTime = level[i]->getInitTime();
		fout.write((char*)(&type), sizeof(LevelEventType));
		fout.write((char*)(&initTime), sizeof(float));
		level[i]->write(fout);
	}
	fout.close();
}