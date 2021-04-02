#include "EventController.h"
#include "LevelEvent.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "ByteArray.h"

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
	level.clear();
	std::ifstream fin;
	fin.open("raid_na_derevene.lvl", std::ifstream::binary);
	size_t size;
	fin.read((char*)(&size), sizeof(size_t));
	level.resize(size);

}

void EventController::saveLevel(std::string path, std::vector<LevelEvent*>& level) {
	std::ofstream fout;
	fout.open("raid_na_derevene.lvl", std::ofstream::binary);
	unsigned int size = level.size();
	unsigned int checkSum = 0;

	std::vector<std::vector<char>> byteLevel(size);

	unsigned int byteLevelSize = sizeof(size) + sizeof(checkSum);

	for (int i = 0; i < size; i++) {
		std::vector<char> tempArray = level[i]->getByteArray();
		byteLevel[i] = std::vector<char>(tempArray.size() + sizeof(LevelEventType) + sizeof(float));
		LevelEventType type = level[i]->getType();
		float initTime = level[i]->getInitTime();
		unsigned int offset = 0;
		writeToByteArray(byteLevel[i], (char*)&type, offset, sizeof(LevelEventType));
		writeToByteArray(byteLevel[i], (char*)&initTime, offset, sizeof(float));
		byteLevelSize += byteLevel[i].size();
	}

	unsigned int offset = 0;

	char* fileData = new char[byteLevelSize];
	writeToByteArray(fileData, (char*)&size, offset, sizeof(size));
	writeToByteArray(fileData, (char*)&checkSum, offset, sizeof(checkSum));

	unsigned int tempOffset = offset;

	for (int i = 0; i < size; i++) writeToByteArray(fileData, byteLevel[i], offset);

	unsigned int* value = (unsigned int*)(fileData + offset);

	int valueCount = (byteLevelSize - offset) / 4;

	for (int i = 0; i < valueCount; i++) checkSum += *(value + i);

	writeToByteArray(fileData, (char*)&checkSum, tempOffset, sizeof(checkSum));

	fout.write((char*)fileData, byteLevelSize);
	fout.close();
	//		
}
