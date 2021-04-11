#pragma once
#include <vector>

class ByteArray {
	char* data;
	unsigned int size;
	unsigned int offset;
public:
	~ByteArray();
	ByteArray();
	ByteArray(const ByteArray& byteArray);
	ByteArray(unsigned int size);
	ByteArray& operator = (const ByteArray& byteArray);
	void add(const ByteArray& byteArray);

	template<class T>
	void add(const T& t) {
		char* value = (char*)&t;
		for (int i = 0; i < sizeof(t); i++) data[offset + i] = value[i];
		offset += sizeof(t);
	}

	template<class T>
	void add(const T* t, unsigned int size) {
		char* value = (char*)t;
		for (int i = 0; i < size; i++) data[offset + i] = value[i];
		offset += size;
	}

	template<class T>
	void read(T& t) {
		char* value = (char*)&t;
		for (int i = 0; i < sizeof(t); i++) value[i] = data[offset + i];
		offset += sizeof(t);
	}

	template<class T>
	void read(T* t, unsigned int size) {
		char* value = (char*)t;
		for (int i = 0; i < size; i++) value[i] = data[offset + i];
		offset += size;
	}

	void read(ByteArray& byteArray);
	unsigned int getSize();
	char* getDataPointer();
	void setOffset(unsigned int offset);
};

void writeToByteArray(
	std::vector<char>& byteVector, 
	char* byteArray,
	unsigned int &offset, 
	unsigned int size
);

void writeToByteArray(
	std::vector<char>& byteVector,
	const std::vector<char>& byteArray,
	unsigned int& offset
);

void writeToByteArray(
	char* byteVector,
	char* byteArray,
	unsigned int& offset,
	unsigned int size
);

void writeFromByteArray(
	char* byteVector,
	char* byteArray,
	unsigned int& offset,
	unsigned int size
);

void writeToByteArray(
	char* byteVector,
	const std::vector<char>& byteArray,
	unsigned int& offset
);
