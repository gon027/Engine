#include <iostream>
#include "BinaryFile.hpp"

/*
int main() {
	BinaryFile bf{ "FBXModel/FBXTestObject.fbx" };
	if (!bf.isOpen()) {
		std::cout << "no" << std::endl;
	}

	std::cout << 1 << std::endl;

	char str;
	bf.read(&str, 1);
	std::cout << str << std::endl;

	int v;
	bf.read32(&v);
	std::cout << v << std::endl;

}
*/