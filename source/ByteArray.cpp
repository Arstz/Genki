#include "ByteArray.h"

#include "crtdbg.h"
#include "..\include\CRTDBG\mydbgnew.h"
#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

ByteArray::~ByteArray() {
	delete[] data;
	data = nullptr;
}

ByteArray::ByteArray() {
	data = nullptr;
	size = 0;
	offset = 0;
}

ByteArray::ByteArray(const ByteArray& byteArray) {
	size = byteArray.size;
	offset = byteArray.offset;
	data = new char[size];
	for (unsigned int i = 0; i < size; i++) data[i] = byteArray.data[i];
}

ByteArray::ByteArray(unsigned int size) {
	this->size = size;
	this->offset = 0;
	this->data = new char[size];
}

ByteArray& ByteArray::operator=(const ByteArray& byteArray) {
	delete[] data;
	size = byteArray.size;
	offset = byteArray.offset;
	data = new char[size];
	for (unsigned int i = 0; i < size; i++) data[i] = byteArray.data[i];
	return *this;
}

void ByteArray::add(const ByteArray& byteArray) {
	for (unsigned int i = 0; i < byteArray.size; i++) data[offset + i] = byteArray.data[i];
	offset += byteArray.size;
}

void ByteArray::add(const char* value, unsigned int size) {
	for (int i = 0; i < size; i++) data[offset + i] = value[i];
	offset += size;
}

void ByteArray::read(ByteArray& byteArray) {
	for (unsigned int i = 0; i < byteArray.size; i++) byteArray.data[i] = data[offset + i];
	offset += byteArray.size;
}

ByteArray& ByteArray::operator << (const ByteArray& byteArray) {
	this->add(byteArray);
	return *this;
}

ByteArray& ByteArray::operator >> (const ByteArray& byteArray) {
	this->read(byteArray);
	return *this;
}

void ByteArray::read(char* value, unsigned int size) {
	for (int i = 0; i < size; i++) value[i] = data[offset + i];
	offset += size;
}

unsigned int ByteArray::getSize() {
	return size;
}

char* ByteArray::getDataPointer() {
	return data;
}

void ByteArray::setOffset(unsigned int offset) {
	this->offset = offset;
}
