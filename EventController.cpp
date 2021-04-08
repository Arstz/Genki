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

#define CREATE_EVENT create(byteLevel + offset, initTime)

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

void EventController::destroy()
{
	for (auto a : level) {
		delete a;
	}
	level.~vector();
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
	for (unsigned int i = 0; i < size; i++) {
		LevelEventType type = LevelEventType::EMPTY;
		float initTime;
		unsigned int blockSize;

		writeFromByteArray((char*)&type, byteLevel, offset, sizeof(type));
		writeFromByteArray((char*)&initTime, byteLevel, offset, sizeof(initTime));
		writeFromByteArray((char*)&blockSize, byteLevel, offset, sizeof(blockSize));

		switch (type) {
		case LevelEventType::EMPTY:
			break;
		case LevelEventType::BACKGROUND_COLOR_ANIMATION:
			level[i] = BackgroundColorAnimationEvent::CREATE_EVENT;
			break;
		case LevelEventType::CAMERA_ANIMATION:
			level[i] = CameraAnimationEvent::CREATE_EVENT;
			break;
		case LevelEventType::SHAPE_SPAWN:
			level[i] = ShapeSpawnEvent::CREATE_EVENT;
			break;
		case LevelEventType::SHAPE_GROUP_SPAWN:
			level[i] = ShapeGroupSpawnEvent::CREATE_EVENT;
			break;
		case LevelEventType::SHAPE_GROUP_DESTRUCTION:
			level[i] = ShapeGroupDestructionEvent::CREATE_EVENT;
			break;
		case LevelEventType::SHAPE_ANIMATION:
			level[i] = ShapeAnimationEvent::CREATE_EVENT;
			break;
		case LevelEventType::SHAPE_GROUP_ANIMATION:
			level[i] = ShapeGroupAnimationEvent::CREATE_EVENT;
			break;
		case LevelEventType::PLAYER_BINDING:
			level[i] = PlayerBindingEvent::CREATE_EVENT;
			break;
		default:
			break;
		}
		offset += blockSize;
	}


	delete[] byteLevel;
	byteLevel = nullptr;
}

void EventController::saveLevel(std::string path, std::vector<LevelEvent*>& level) {
	unsigned int size = level.size();
	unsigned int checkSum = 0;

	std::vector<std::vector<char>> byteLevel(size);

	unsigned int byteLevelSize = 0;

	for (unsigned int i = 0; i < size; i++) {
		LevelEventType type = level[i]->getType();
		float initTime = level[i]->getInitTime();
		std::vector<char> tempArray = level[i]->getByteArray();
		unsigned int blockSize = tempArray.size();
		byteLevel[i] = std::vector<char>(tempArray.size() + sizeof(type) + sizeof(initTime) + sizeof(blockSize));

		unsigned int offset = 0;
		writeToByteArray(byteLevel[i], (char*)&type, offset, sizeof(type));
		writeToByteArray(byteLevel[i], (char*)&initTime, offset, sizeof(initTime));
		writeToByteArray(byteLevel[i], (char*)&blockSize, offset, sizeof(initTime));
		writeToByteArray(byteLevel[i], tempArray, offset);

		byteLevelSize += static_cast<unsigned int>(byteLevel[i].size());
	}

	unsigned int offset = 0;

	char* fileData = new char[byteLevelSize + sizeof(byteLevelSize) + sizeof(size) + sizeof(checkSum)];
	writeToByteArray(fileData, (char*)&byteLevelSize, offset, sizeof(byteLevelSize));
	writeToByteArray(fileData, (char*)&size, offset, sizeof(size));
	writeToByteArray(fileData, (char*)&checkSum, offset, sizeof(checkSum));

//	unsigned int tempOffset = offset;
//	unsigned int* value = (unsigned int*)(fileData + offset);

	for (unsigned int i = 0; i < size; i++) writeToByteArray(fileData, byteLevel[i], offset);

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
