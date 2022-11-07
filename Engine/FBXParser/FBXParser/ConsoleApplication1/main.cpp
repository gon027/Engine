#include <iostream>
#include <fstream>
#include <string>

struct FBXHeader {
	
};

struct FBXNode {
	long long endPosition;           // 終端距離
	long long attributeCount;        // 属性
	long long allAttributeByteSize;  // 全属性のバイト長
	char nodeNameSize;               // ノード名のバイト長
	char nodeName[256];              // ノード名
	FBXNode* next;
};

int main()
{
	using std::cout;
	using std::endl;

	std::ifstream ifs{ "FBXModel/FBXTestObject.fbx", std::ios::in | std::ios::binary };
	if (!ifs) {
		std::cout << "Not Read." << std::endl;
	}

	// std::cout << "Clear" << std::endl;

	// マジックナンバー
	char magicNumber[32];
	ifs.read(magicNumber, sizeof(char) * 23);
	std::cout << "マジックナンバー : " << magicNumber << std::endl;

	// バージョン
	int version{ 0 };
	ifs.read((char*)&version, sizeof(char) * 4);
	std::cout << "バージョン : " << version << std::endl;

	// std::cout << sizeof(long long) << std::endl;

	// --------
	// 終端距離
	long long endPosition{};
	ifs.read((char*)&endPosition, sizeof(char) * 4);
	std::cout << endPosition << std::endl;

	// 属性
	long long attributeCount{};
	ifs.read((char*)&attributeCount, sizeof(char) * 4);
	std::cout << attributeCount << std::endl;

	// 全属性のバイト長
	long long allAttributeByteSize{};
	ifs.read((char*)&allAttributeByteSize, sizeof(char) * 4);
	std::cout << allAttributeByteSize << std::endl;

	// ノード名のバイト長
	char nodeNameSize{};
	ifs.read(&nodeNameSize, sizeof(char));
	std::cout << (int)nodeNameSize << std::endl;

	// ノード名
	char nodeName[256]{};
	ifs.read(nodeName, sizeof(char) * nodeNameSize);
	std::cout << nodeName << std::endl;

	// Headerここまで

	// ノード名のバイト長
	long long aa{};
	ifs.read((char*)&aa, sizeof(char) * 4);
	std::cout << aa << std::endl;

	long long bb{};
	ifs.read((char*)&bb, sizeof(char) * 4);
	std::cout << bb << std::endl;

	long long cc{};
	ifs.read((char*)&cc, sizeof(char) * 4);
	std::cout << cc << std::endl;

	char dd{};
	ifs.read(&dd, sizeof(char));
	std::cout << (int)dd << std::endl;

	char ee[64]{};
	ifs.read(ee, sizeof(char) * dd);
	std::cout << ee << std::endl;

	// 属性
	char atr{};
	ifs.read(&atr, sizeof(char));
	std::cout << atr << std::endl;

	// バージョン
	int ver{};
	ifs.read((char*)&ver, sizeof(char) * 4);
	cout << ver << endl;
}