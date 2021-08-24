#include "EventController.h"
#include "LevelEvent\LevelEvent.h"

#include <iostream>
#include <fstream>
#include <vector>
#include "ByteArray.h"

#include "crtdbg.h"
#include "..\include\CRTDBG\mydbgnew.h"
#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

#define CREATE_EVENT create(byteLevel, initTime)

std::vector<LevelEvent*> EventController::level;
int EventController::currentEvent = 0;

void EventController::update(float currentTime)
{
	while (currentEvent < level.size() && level[currentEvent]->getInitTime() < currentTime) {
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

	ByteArray* byteLevel = new ByteArray(byteLevelSize);

	fin.read(byteLevel->getDataPointer(), byteLevelSize);

	fin.close();
	level.resize(size);
	for (unsigned int i = 0; i < size; i++) {
		LevelEventType type = LevelEventType::NONE;
		float initTime;
		unsigned int blockSize;

		*byteLevel >> type >> initTime >> blockSize;

		switch (type) {
		case LevelEventType::NONE:
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

	delete byteLevel;
	byteLevel = nullptr;
}

void EventController::saveLevel(std::string path, std::vector<LevelEvent*>& level) {
	unsigned int size = level.size();
	unsigned int checkSum = 0;

	std::vector<ByteArray> byteLevel(size);

	unsigned int byteLevelSize = 0;

	for (unsigned int i = 0; i < size; i++) {
		LevelEventType type		= level[i]->getType();
		float initTime			= level[i]->getInitTime();
		ByteArray tempArray		= level[i]->getByteArray();
		unsigned int blockSize	= tempArray.getSize();
		byteLevel[i] = ByteArray(tempArray.getSize() + sizeof(type) + sizeof(initTime) + sizeof(blockSize));

		unsigned int offset = 0;
		byteLevel[i].add(type);
		byteLevel[i].add(initTime);
		byteLevel[i].add(blockSize);
		byteLevel[i].add(tempArray);

		byteLevelSize += static_cast<unsigned int>(byteLevel[i].getSize());
	}

	unsigned int offset = 0;

	ByteArray fileData(byteLevelSize + sizeof(byteLevelSize) + sizeof(size) + sizeof(checkSum));
	fileData.add(byteLevelSize);
	fileData.add(size);
	fileData.add(checkSum);

//	unsigned int tempOffset = offset;
//	unsigned int* value = (unsigned int*)(fileData + offset);

	for (unsigned int i = 0; i < size; i++) fileData.add(byteLevel[i]);

//	int valueCount = (byteLevelSize - offset) / 4;
//	for (int i = 0; i < valueCount; i++) checkSum += *(value + i);
//	writeToByteArray(fileData, (char*)&checkSum, tempOffset, sizeof(checkSum));

	std::ofstream fout;
	fout.open("raid_na_derevene.lvl", std::ofstream::binary);
	fout.write(fileData.getDataPointer(), byteLevelSize + sizeof(byteLevelSize) + sizeof(size) + sizeof(checkSum));
	fout.close();

	byteLevel.clear();
}
