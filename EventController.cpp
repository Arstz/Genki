#include "EventController.h"
#include "LevelEvent.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "ByteArray.h"

#include "crtdbg.h"
#include "mydbgnew.h"
#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

#define CREATE_EVENT create(byteLevel, offset, initTime)

std::vector<LevelEvent*> EventController::level;
int EventController::currentEvent = 0;
float* EventController::currentTime = nullptr;

void EventController::update() 
{
	while (currentEvent < level.size() && level[currentEvent]->getInitTime() < *currentTime) {
		level[currentEvent]->start();
//		delete level[currentEvent];
		currentEvent++;
	}
}


void EventController::loadLevel(std::string path) {
	for (int i = 0; i < level.size(); i++) delete level[i];
	level.clear();

	std::ifstream fin;
	fin.open("raid_na_derevene.lvl", std::ifstream::binary);
	unsigned int byteLevelSize;
	unsigned int size;
	unsigned int checkSum;

	unsigned int offset = 0;

	fin.read((char*)(&byteLevelSize), sizeof(byteLevelSize));
	fin.read((char*)(&size), sizeof(size));
	fin.read((char*)(&checkSum), sizeof(checkSum));

	char* byteLevel = new char[byteLevelSize];

	fin.read((char*)byteLevel, byteLevelSize);

	fin.close();
	level.resize(size);
	for (int i = 0; i < size; i++) {
		LevelEventType type;
		float initTime;

		writeFromByteArray((char*)&type, byteLevel, offset, sizeof(type));
		writeFromByteArray((char*)&initTime, byteLevel, offset, sizeof(initTime));

		switch (type) {
		case EMPTY:
			break;
		case BACKGROUND_COLOR_ANIMATION:
			level[i] = BackgroundColorAnimationEvent::CREATE_EVENT;
			break;
		case CAMERA_ANIMATION:
			level[i] = CameraAnimationEvent::CREATE_EVENT;
			break;
		case SHAPE_SPAWN:
			level[i] = ShapeSpawnEvent::CREATE_EVENT;
			break;
		case SHAPE_GROUP_SPAWN:
			level[i] = ShapeGroupSpawnEvent::CREATE_EVENT;
			break;
		case SHAPE_GROUP_DESTRUCTION:
			level[i] = ShapeGroupDestructionEvent::CREATE_EVENT;
			break;
		case SHAPE_ANIMATION:
			level[i] = ShapeAnimationEvent::CREATE_EVENT;
			break;
		case SHAPE_GROUP_ANIMATION:
			level[i] = ShapeGroupAnimationEvent::CREATE_EVENT;
			break;
		case PLAYER_BINDING:
			level[i] = PlayerBindingEvent::CREATE_EVENT;
			break;
		default:
			break;
		}
	}

	delete[] byteLevel;
	byteLevel = nullptr;
}

void EventController::saveLevel(std::string path, std::vector<LevelEvent*>& level) {
	unsigned int size = level.size();
	unsigned int checkSum = 0;

	std::vector<std::vector<char>> byteLevel(size);

	unsigned int byteLevelSize = 0;

	for (int i = 0; i < size; i++) {
		LevelEventType type = level[i]->getType();
		float initTime = level[i]->getInitTime();
		std::vector<char> tempArray = level[i]->getByteArray();
		byteLevel[i] = std::vector<char>(tempArray.size() + sizeof(type) + sizeof(initTime));

		unsigned int offset = 0;
		writeToByteArray(byteLevel[i], (char*)&type, offset, sizeof(type));
		writeToByteArray(byteLevel[i], (char*)&initTime, offset, sizeof(initTime));
		writeToByteArray(byteLevel[i], tempArray, offset);

		byteLevelSize += byteLevel[i].size();
	}

	unsigned int offset = 0;

	char* fileData = new char[byteLevelSize + sizeof(byteLevelSize) + sizeof(size) + sizeof(checkSum)];
	writeToByteArray(fileData, (char*)&byteLevelSize, offset, sizeof(byteLevelSize));
	writeToByteArray(fileData, (char*)&size, offset, sizeof(size));
	writeToByteArray(fileData, (char*)&checkSum, offset, sizeof(checkSum));

//	unsigned int tempOffset = offset;
//	unsigned int* value = (unsigned int*)(fileData + offset);

	for (int i = 0; i < size; i++) writeToByteArray(fileData, byteLevel[i], offset);

//	int valueCount = (byteLevelSize - offset) / 4;
//	for (int i = 0; i < valueCount; i++) checkSum += *(value + i);
//	writeToByteArray(fileData, (char*)&checkSum, tempOffset, sizeof(checkSum));

	std::ofstream fout;
	fout.open("raid_na_derevene.lvl", std::ofstream::binary);
	fout.write((char*)fileData, byteLevelSize + sizeof(byteLevelSize) + sizeof(size) + sizeof(checkSum));
	fout.close();

	byteLevel.clear();

	delete[] fileData;
	fileData = nullptr;
}
