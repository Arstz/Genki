#pragma once

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
	void add(const char* value, unsigned int size);

	template<typename T>
	void add(const T& t) {add((char*)&t, sizeof(t));}

	template<typename T>
	void add(const T* t, unsigned int size) {add((char*)t, size);}

	void read(ByteArray& byteArray);
	void read(char* value, unsigned int size);

	template<typename T>
	void read(T& t) {read((char*)&t, sizeof(t));}

	template<typename T>
	void read(T* t, unsigned int size) {read((char*)t, size);}

	unsigned int getSize();
	char* getDataPointer();
	void setOffset(unsigned int offset);
};
