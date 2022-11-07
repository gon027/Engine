#pragma once

#include <iosfwd>
#include <fstream>
#include <string>

class BinaryFile {
public:
	BinaryFile(const std::string& _fileName)
		: ifs{ _fileName, std::ios::in | std::ios::binary }
	{}
	~BinaryFile() = default;

	bool isOpen() const {
		return ifs.is_open();
	}

	template<class T>
	void read(T* _str, size_t _size) {
		ifs.read((char*)_str, _size);
	}

	void read8(char* _value) {
		read(_value, sizeof(char));
	}

	void read16(short* _value) {
		read(_value, sizeof(char) * 2);
	}

	void read32(int* _value) {
		read(_value, sizeof(char) * 4);
	}

	void read64(long long* _value) {
		read(_value, sizeof(char) * 8);
	}

private:
	BinaryFile(const BinaryFile&);
	BinaryFile& operator= (const BinaryFile&);

private:
	std::ifstream ifs;
};