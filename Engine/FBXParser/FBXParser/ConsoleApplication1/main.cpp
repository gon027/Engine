#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct FBXHeader {
	char magicNumber[32];  // マジックナンバー
	int version{ 0 };      // バージョン
};

struct FBXNode {
	long long endPosition;           // 終端距離
	long long attributeCount;        // 属性
	long long allAttributeByteSize;  // 全属性のバイト長
	char nodeNameSize;               // ノード名のバイト長
	char nodeName[256];              // ノード名
	std::vector<FBXNode> node;       // 子ノード
};

int main()
{
	using std::cout;
	using std::endl;

	const std::string FBXFileName1{
		"FBX/Shachiku_chan_Ver2.0.fbx"
	};
	const std::string FBXFileName2{
		"FBXModel/FBXTestObject.fbx"
	};
	std::ifstream ifs{ FBXFileName2, std::ios::in | std::ios::binary };
	if (!ifs) {
		std::cout << "Not Read." << std::endl;
	}

	// std::cout << "Clear" << std::endl;

	std::cout << "-------------------------" << std::endl;
	{
		// マジックナンバー
		char magicNumber[32];
		ifs.read(magicNumber, sizeof(char) * 23);
		std::cout << "マジックナンバー : " << magicNumber << std::endl;

		// バージョン
		int version{ 0 };
		ifs.read((char*)&version, sizeof(char) * 4);
		std::cout << "バージョン : " << version << std::endl; }

	// std::cout << sizeof(long long) << std::endl;

	std::cout << "----- Top Lebel Node -----" << std::endl;
	{
		{
			// --------
			// 終端距離
			long long endPosition{};
			ifs.read((char*)&endPosition, sizeof(char) * 4);
			std::cout << "終端距離 = " << endPosition << std::endl;

			// 属性
			long long attributeCount{};
			ifs.read((char*)&attributeCount, sizeof(char) * 4);
			std::cout << "属性数 = " << attributeCount << std::endl;

			// 全属性のバイト長
			long long allAttributeByteSize{};
			ifs.read((char*)&allAttributeByteSize, sizeof(char) * 4);
			std::cout << "全属性の合計バイト = " << allAttributeByteSize << std::endl;

			// ノード名のバイト長
			char nodeNameSize{};
			ifs.read(&nodeNameSize, sizeof(char));
			std::cout << "ノード名のバイト長 = " << (int)nodeNameSize << std::endl;

			// ノード名
			char nodeName[256]{};
			ifs.read(nodeName, sizeof(char) * nodeNameSize);
			std::cout << "ノード名 = " << nodeName << std::endl;

			std::cout << "属性 = ." << std::endl;

			std::cout << std::endl; 
		}
		// 属性は省略

				// ヘッダー部
		struct A {
			;
			struct {
				std::string nodeName;
			};
			// 属性部
			struct {
				std::string attribute;
				void* a;

				// bool 
				struct B { bool value; };
				// i32
				struct i32 { unsigned int value; };
			};

			std::vector<A> children;

		};

		// ノード名のバイト長
		{
			long long aa{};
			ifs.read((char*)&aa, sizeof(char) * 4);
			std::cout << "終端距離 = " << aa << std::endl;

			long long bb{};
			ifs.read((char*)&bb, sizeof(char) * 4);
			std::cout << "属性数 = " << bb << std::endl;

			long long cc{};
			ifs.read((char*)&cc, sizeof(char) * 4);
			std::cout << "全属性の合計バイト = " << cc << std::endl;

			char dd{};
			ifs.read(&dd, sizeof(char));
			std::cout << "全属性の合計バイト = " << (int)dd << std::endl;

			char ee[64]{};
			ifs.read(ee, sizeof(char) * dd);
			std::cout << "ノード名 = " << ee << std::endl;

			// 属性
			char atr{};
			ifs.read(&atr, sizeof(char));
			std::cout << "属性 = " << atr << std::endl;

			// バージョン
			int ver{};
			ifs.read((char*)&ver, sizeof(char) * 4);
			cout << "バージョン = " << ver << endl;

			std::cout << std::endl;
		}

		{
			long long aa{};
			ifs.read((char*)&aa, sizeof(char) * 4);
			std::cout << "終端距離 = " << aa << std::endl;

			long long bb{};
			ifs.read((char*)&bb, sizeof(char) * 4);
			std::cout << "属性数 = " << bb << std::endl;

			long long cc{};
			ifs.read((char*)&cc, sizeof(char) * 4);
			std::cout << "全属性の合計バイト = " << cc << std::endl;

			char dd{};
			ifs.read(&dd, sizeof(char));
			std::cout << "全属性の合計バイト = " << (int)dd << std::endl;

			char ee[64]{};
			ifs.read(ee, sizeof(char) * dd);
			std::cout << "ノード名 = " << ee << std::endl;

			// 属性
			char atr{};
			ifs.read(&atr, sizeof(char));
			std::cout << "属性 = " << atr << std::endl;

			// バージョン
			int ver{};
			ifs.read((char*)&ver, sizeof(char) * 4);
			cout << "バージョン = " << ver << endl;

			std::cout << std::endl;
		}

		{
			long long aa{};
			ifs.read((char*)&aa, sizeof(char) * 4);
			std::cout << "終端距離 = " << aa << std::endl;

			long long bb{};
			ifs.read((char*)&bb, sizeof(char) * 4);
			std::cout << "属性数 = " << bb << std::endl;

			long long cc{};
			ifs.read((char*)&cc, sizeof(char) * 4);
			std::cout << "全属性の合計バイト = " << cc << std::endl;

			char dd{};
			ifs.read(&dd, sizeof(char));
			std::cout << "全属性の合計バイト = " << (int)dd << std::endl;

			char ee[64]{};
			ifs.read(ee, sizeof(char) * dd);
			std::cout << "ノード名 = " << ee << std::endl;

			// 属性
			char atr{};
			ifs.read(&atr, sizeof(char));
			std::cout << "属性 = " << atr << std::endl;

			// バージョン
			int ver{};
			ifs.read((char*)&ver, sizeof(char) * 4);
			cout << "バージョン = " << ver << endl;

			std::cout << std::endl;
		}

		{
			long long aa{};
			ifs.read((char*)&aa, sizeof(char) * 4);
			std::cout << "終端距離 = " << aa << std::endl;

			long long bb{};
			ifs.read((char*)&bb, sizeof(char) * 4);
			std::cout << "属性数 = " << bb << std::endl;

			long long cc{};
			ifs.read((char*)&cc, sizeof(char) * 4);
			std::cout << "全属性の合計バイト = " << cc << std::endl;

			char dd{};
			ifs.read(&dd, sizeof(char));
			std::cout << "全属性の合計バイト = " << (int)dd << std::endl;

			char ee[64]{};
			ifs.read(ee, sizeof(char) * dd);
			std::cout << "ノード名 = " << ee << std::endl;

			// 属性
			char atr{};
			std::cout << "属性 = " << atr << std::endl;

			std::cout << std::endl;
		}

		{
			long long aa{};
			ifs.read((char*)&aa, sizeof(char) * 4);
			std::cout << "終端距離 = " << aa << std::endl;

			long long bb{};
			ifs.read((char*)&bb, sizeof(char) * 4);
			std::cout << "属性数 = " << bb << std::endl;

			long long cc{};
			ifs.read((char*)&cc, sizeof(char) * 4);
			std::cout << "全属性の合計バイト = " << cc << std::endl;

			char dd{};
			ifs.read(&dd, sizeof(char));
			std::cout << "全属性の合計バイト = " << (int)dd << std::endl;

			char ee[64]{};
			ifs.read(ee, sizeof(char) * dd);
			std::cout << "ノード名 = " << ee << std::endl;

			// 属性
			char atr{};
			ifs.read(&atr, sizeof(char));
			std::cout << "属性 = " << atr << std::endl;

			// バージョン
			int ver{};
			ifs.read((char*)&ver, sizeof(char) * 4);
			cout << "バージョン = " << ver << endl;

			std::cout << std::endl;
		}

		{
			long long aa{};
			ifs.read((char*)&aa, sizeof(char) * 4);
			std::cout << "終端距離 = " << aa << std::endl;

			long long bb{};
			ifs.read((char*)&bb, sizeof(char) * 4);
			std::cout << "属性数 = " << bb << std::endl;

			long long cc{};
			ifs.read((char*)&cc, sizeof(char) * 4);
			std::cout << "全属性の合計バイト = " << cc << std::endl;

			char dd{};
			ifs.read(&dd, sizeof(char));
			std::cout << "全属性の合計バイト = " << (int)dd << std::endl;

			char ee[64]{};
			ifs.read(ee, sizeof(char) * dd);
			std::cout << "ノード名 = " << ee << std::endl;

			// 属性
			char atr{};
			ifs.read(&atr, sizeof(char));
			std::cout << "属性 = " << atr << std::endl;

			// バージョン
			int ver{};
			ifs.read((char*)&ver, sizeof(char) * 4);
			cout << "バージョン = " << ver << endl;

			std::cout << std::endl;
		}

		{
			long long aa{};
			ifs.read((char*)&aa, sizeof(char) * 4);
			std::cout << "終端距離 = " << aa << std::endl;

			long long bb{};
			ifs.read((char*)&bb, sizeof(char) * 4);
			std::cout << "属性数 = " << bb << std::endl;

			long long cc{};
			ifs.read((char*)&cc, sizeof(char) * 4);
			std::cout << "全属性の合計バイト = " << cc << std::endl;

			char dd{};
			ifs.read(&dd, sizeof(char));
			std::cout << "全属性の合計バイト = " << (int)dd << std::endl;

			char ee[64]{};
			ifs.read(ee, sizeof(char) * dd);
			std::cout << "ノード名 = " << ee << std::endl;

			// 属性
			char atr{};
			ifs.read(&atr, sizeof(char));
			std::cout << "属性 = " << atr << std::endl;

			// バージョン
			int ver{};
			ifs.read((char*)&ver, sizeof(char) * 4);
			cout << "バージョン = " << ver << endl;

			std::cout << std::endl;
		}

		{
			long long aa{};
			ifs.read((char*)&aa, sizeof(char) * 4);
			std::cout << "終端距離 = " << aa << std::endl;

			long long bb{};
			ifs.read((char*)&bb, sizeof(char) * 4);
			std::cout << "属性数 = " << bb << std::endl;

			long long cc{};
			ifs.read((char*)&cc, sizeof(char) * 4);
			std::cout << "全属性の合計バイト = " << cc << std::endl;

			char dd{};
			ifs.read(&dd, sizeof(char));
			std::cout << "全属性の合計バイト = " << (int)dd << std::endl;

			char ee[64]{};
			ifs.read(ee, sizeof(char) * dd);
			std::cout << "ノード名 = " << ee << std::endl;

			// 属性
			char atr{};
			ifs.read(&atr, sizeof(char));
			std::cout << "属性 = " << atr << std::endl;

			// バージョン
			int ver{};
			ifs.read((char*)&ver, sizeof(char) * 4);
			cout << "バージョン = " << ver << endl;

			std::cout << std::endl;
		}

		{
			long long aa{};
			ifs.read((char*)&aa, sizeof(char) * 4);
			std::cout << "終端距離 = " << aa << std::endl;

			long long bb{};
			ifs.read((char*)&bb, sizeof(char) * 4);
			std::cout << "属性数 = " << bb << std::endl;

			long long cc{};
			ifs.read((char*)&cc, sizeof(char) * 4);
			std::cout << "全属性の合計バイト = " << cc << std::endl;

			char dd{};
			ifs.read(&dd, sizeof(char));
			std::cout << "全属性の合計バイト = " << (int)dd << std::endl;

			char ee[64]{};
			ifs.read(ee, sizeof(char) * dd);
			std::cout << "ノード名 = " << ee << std::endl;

			// 属性
			char atr{};
			ifs.read(&atr, sizeof(char));
			std::cout << "属性 = " << atr << std::endl;

			// バージョン
			int ver{};
			ifs.read((char*)&ver, sizeof(char) * 4);
			cout << "バージョン = " << ver << endl;

			std::cout << std::endl;
		}

		{
			long long aa{};
			ifs.read((char*)&aa, sizeof(char) * 4);
			std::cout << "終端距離 = " << aa << std::endl;

			long long bb{};
			ifs.read((char*)&bb, sizeof(char) * 4);
			std::cout << "属性数 = " << bb << std::endl;

			long long cc{};
			ifs.read((char*)&cc, sizeof(char) * 4);
			std::cout << "全属性の合計バイト = " << cc << std::endl;

			char dd{};
			ifs.read(&dd, sizeof(char));
			std::cout << "全属性の合計バイト = " << (int)dd << std::endl;

			char ee[64]{};
			ifs.read(ee, sizeof(char) * dd);
			std::cout << "ノード名 = " << ee << std::endl;

			// 属性
			char atr{};
			ifs.read(&atr, sizeof(char));
			std::cout << "属性 = " << atr << std::endl;

			// バージョン
			int ver{};
			ifs.read((char*)&ver, sizeof(char) * 4);
			cout << "バージョン = " << ver << endl;

			std::cout << std::endl;
		}

		{
			long long aa{};
			ifs.read((char*)&aa, sizeof(char) * 4);
			std::cout << "終端距離 = " << aa << std::endl;

			long long bb{};
			ifs.read((char*)&bb, sizeof(char) * 4);
			std::cout << "属性数 = " << bb << std::endl;

			long long cc{};
			ifs.read((char*)&cc, sizeof(char) * 4);
			std::cout << "全属性の合計バイト = " << cc << std::endl;

			char dd{};
			ifs.read(&dd, sizeof(char));
			std::cout << "全属性の合計バイト = " << (int)dd << std::endl;

			char ee[64]{};
			ifs.read(ee, sizeof(char) * dd);
			std::cout << "ノード名 = " << ee << std::endl;

			// 属性
			char atr{};
			ifs.read(&atr, sizeof(char));
			std::cout << "属性 = " << atr << std::endl;

			// バージョン
			int ver{};
			ifs.read((char*)&ver, sizeof(char) * 4);
			cout << "バージョン = " << ver << endl;

			std::cout << std::endl;
		}

		{
			long long aa{};
			ifs.read((char*)&aa, sizeof(char) * 4);
			std::cout << "終端距離 = " << aa << std::endl;

			long long bb{};
			ifs.read((char*)&bb, sizeof(char) * 4);
			std::cout << "属性数 = " << bb << std::endl;

			long long cc{};
			ifs.read((char*)&cc, sizeof(char) * 4);
			std::cout << "全属性の合計バイト = " << cc << std::endl;

			char dd{};
			ifs.read(&dd, sizeof(char));
			std::cout << "全属性の合計バイト = " << (int)dd << std::endl;

			char ee[64]{};
			ifs.read(ee, sizeof(char) * dd);
			std::cout << "ノード名 = " << ee << std::endl;

			// 属性
			char atr{};
			ifs.read(&atr, sizeof(char));
			std::cout << "属性 = " << atr << std::endl;

			// バージョン
			int ver{};
			ifs.read((char*)&ver, sizeof(char) * 4);
			cout << "バージョン = " << ver << endl;

			std::cout << std::endl;
		}

		// 13バイトスキップ
		{
			long long aa{};
			ifs.read((char*)&aa, sizeof(char) * 4);
			std::cout << "終端距離 = " << aa << std::endl;
		}
		{
			long long aa{};
			ifs.read((char*)&aa, sizeof(char) * 4);
			std::cout << "終端距離 = " << aa << std::endl;
		}
		{
			long long aa{};
			ifs.read((char*)&aa, sizeof(char) * 4);
			std::cout << "終端距離 = " << aa << std::endl;
		}
		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << (char)aa << std::endl;
		}

		{
			long long aa{};
			ifs.read((char*)&aa, sizeof(char) * 4);
			std::cout << "終端距離 = " << aa << std::endl;

			long long bb{};
			ifs.read((char*)&bb, sizeof(char) * 4);
			std::cout << "属性数 = " << bb << std::endl;

			long long cc{};
			ifs.read((char*)&cc, sizeof(char) * 4);
			std::cout << "全属性の合計バイト = " << cc << std::endl;

			char dd{};
			ifs.read(&dd, sizeof(char));
			std::cout << "全属性の合計バイト = " << (int)dd << std::endl;

			char ee[64]{};
			ifs.read(ee, sizeof(char) * dd);
			std::cout << "ノード名 = " << ee << std::endl;

			// 属性
			char atr{};
			ifs.read(&atr, sizeof(char));
			std::cout << "属性 = " << atr << std::endl;

			// バージョン
			int len{};
			ifs.read((char*)&len, sizeof(char) * 4);
			cout << "文字列 = " << len << endl;

			char st[64]{};
			ifs.read(st, sizeof(char) * len);
			std::cout << "ノード名 = " << st << std::endl;

			std::cout << std::endl;
		}

		{
			// --------
			// 終端距離
			long long endPosition{};
			ifs.read((char*)&endPosition, sizeof(char) * 4);
			std::cout << "終端距離 = " << endPosition << std::endl;

			// 属性
			long long attributeCount{};
			ifs.read((char*)&attributeCount, sizeof(char) * 4);
			std::cout << "属性数 = " << attributeCount << std::endl;

			// 全属性のバイト長
			long long allAttributeByteSize{};
			ifs.read((char*)&allAttributeByteSize, sizeof(char) * 4);
			std::cout << "全属性の合計バイト = " << allAttributeByteSize << std::endl;

			// ノード名のバイト長
			char nodeNameSize{};
			ifs.read(&nodeNameSize, sizeof(char));
			std::cout << "ノード名のバイト長 = " << (int)nodeNameSize << std::endl;

			// ノード名
			char nodeName[256]{};
			ifs.read(nodeName, sizeof(char) * nodeNameSize);
			std::cout << "ノード名 = " << nodeName << std::endl;

			std::cout << std::endl;
		}

		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;
		
			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}

		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}

		// ノード名のバイト長
		{
			long long aa{};
			ifs.read((char*)&aa, sizeof(char) * 4);
			std::cout << "終端距離 = " << aa << std::endl;

			long long bb{};
			ifs.read((char*)&bb, sizeof(char) * 4);
			std::cout << "属性数 = " << bb << std::endl;

			long long cc{};
			ifs.read((char*)&cc, sizeof(char) * 4);
			std::cout << "全属性の合計バイト = " << cc << std::endl;

			char dd{};
			ifs.read(&dd, sizeof(char));
			std::cout << "全属性の合計バイト = " << (int)dd << std::endl;

			char ee[64]{};
			ifs.read(ee, sizeof(char) * dd);
			std::cout << "ノード名 = " << ee << std::endl;

			std::cout << std::endl;
		}

		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}


		{
			long long aa{};
			ifs.read((char*)&aa, sizeof(char) * 4);
			std::cout << "終端距離 = " << aa << std::endl;

			long long bb{};
			ifs.read((char*)&bb, sizeof(char) * 4);
			std::cout << "属性数 = " << bb << std::endl;

			long long cc{};
			ifs.read((char*)&cc, sizeof(char) * 4);
			std::cout << "全属性の合計バイト = " << cc << std::endl;

			char dd{};
			ifs.read(&dd, sizeof(char));
			std::cout << "全属性の合計バイト = " << (int)dd << std::endl;

			char ee[64]{};
			ifs.read(ee, sizeof(char) * dd);
			std::cout << "ノード名 = " << ee << std::endl;

			// 属性
			char atr{};
			ifs.read(&atr, sizeof(char));
			std::cout << "属性 = " << atr << std::endl;

			// バージョン
			int ver{};
			ifs.read((char*)&ver, sizeof(char) * 4);
			cout << "バージョン = " << ver << endl;

			std::cout << std::endl;
		}

		{
			long long aa{};
			ifs.read((char*)&aa, sizeof(char) * 4);
			std::cout << "終端距離 = " << aa << std::endl;

			long long bb{};
			ifs.read((char*)&bb, sizeof(char) * 4);
			std::cout << "属性数 = " << bb << std::endl;

			long long cc{};
			ifs.read((char*)&cc, sizeof(char) * 4);
			std::cout << "全属性の合計バイト = " << cc << std::endl;

			char dd{};
			ifs.read(&dd, sizeof(char));
			std::cout << "全属性の合計バイト = " << (int)dd << std::endl;

			char ee[64]{};
			ifs.read(ee, sizeof(char) * dd);
			std::cout << "ノード名 = " << ee << std::endl;

			// 属性
			std::cout << "属性 = ."<< std::endl;

			std::cout << std::endl;
		}

		// ノード名のバイト長
		{
			long long aa{};
			ifs.read((char*)&aa, sizeof(char) * 4);
			std::cout << "終端距離 = " << aa << std::endl;

			long long bb{};
			ifs.read((char*)&bb, sizeof(char) * 4);
			std::cout << "属性数 = " << bb << std::endl;

			long long cc{};
			ifs.read((char*)&cc, sizeof(char) * 4);
			std::cout << "全属性の合計バイト = " << cc << std::endl;

			char dd{};
			ifs.read(&dd, sizeof(char));
			std::cout << "全属性の合計バイト = " << (int)dd << std::endl;

			char ee[64]{};
			ifs.read(ee, sizeof(char) * dd);
			std::cout << "ノード名 = " << ee << std::endl;

			// 属性
			char atr{};
			ifs.read(&atr, sizeof(char));
			std::cout << "属性 = " << atr << std::endl;

			// バージョン
			int ver{};
			ifs.read((char*)&ver, sizeof(char) * 4);
			cout << "バージョン = " << ver << endl;

			std::cout << std::endl;
		}

		// ノード名のバイト長
		{
			long long aa{};
			ifs.read((char*)&aa, sizeof(char) * 4);
			std::cout << "終端距離 = " << aa << std::endl;

			long long bb{};
			ifs.read((char*)&bb, sizeof(char) * 4);
			std::cout << "属性数 = " << bb << std::endl;

			long long cc{};
			ifs.read((char*)&cc, sizeof(char) * 4);
			std::cout << "全属性の合計バイト = " << cc << std::endl;

			char dd{};
			ifs.read(&dd, sizeof(char));
			std::cout << "全属性の合計バイト = " << (int)dd << std::endl;

			char ee[64]{};
			ifs.read(ee, sizeof(char) * dd);
			std::cout << "ノード名 = " << ee << std::endl;

			// 属性
			char atr{};
			ifs.read(&atr, sizeof(char));
			std::cout << "属性 = " << atr << std::endl;

			// 文字数
			int ver{};
			ifs.read((char*)&ver, sizeof(char) * 4);
			cout << "文字数 = " << ver << endl;

			char str[256]{};
			ifs.read((char*)&ver, sizeof(char) * ver);
			cout << "文字列 = " << ver << endl;

			std::cout << std::endl;
		}

		// ノード名のバイト長
		{
			long long aa{};
			ifs.read((char*)&aa, sizeof(char) * 4);
			std::cout << "終端距離 = " << aa << std::endl;

			long long bb{};
			ifs.read((char*)&bb, sizeof(char) * 4);
			std::cout << "属性数 = " << bb << std::endl;

			long long cc{};
			ifs.read((char*)&cc, sizeof(char) * 4);
			std::cout << "全属性の合計バイト = " << cc << std::endl;

			char dd{};
			ifs.read(&dd, sizeof(char));
			std::cout << "全属性の合計バイト = " << (int)dd << std::endl;

			char ee[64]{};
			ifs.read(ee, sizeof(char) * dd);
			std::cout << "ノード名 = " << ee << std::endl;

			// 属性
			char atr{};
			ifs.read(&atr, sizeof(char));
			std::cout << "属性 = " << atr << std::endl;

			// 文字数
			int ver{};
			ifs.read((char*)&ver, sizeof(char) * 4);
			cout << "文字数 = " << ver << endl;

			char str[256]{};
			ifs.read((char*)&ver, sizeof(char) * ver);
			cout << "文字列 = " << ver << endl;

			std::cout << std::endl;
		}

		// ノード名のバイト長
		{
			long long aa{};
			ifs.read((char*)&aa, sizeof(char) * 4);
			std::cout << "終端距離 = " << aa << std::endl;

			long long bb{};
			ifs.read((char*)&bb, sizeof(char) * 4);
			std::cout << "属性数 = " << bb << std::endl;

			long long cc{};
			ifs.read((char*)&cc, sizeof(char) * 4);
			std::cout << "全属性の合計バイト = " << cc << std::endl;

			char dd{};
			ifs.read(&dd, sizeof(char));
			std::cout << "全属性の合計バイト = " << (int)dd << std::endl;

			char ee[64]{};
			ifs.read(ee, sizeof(char) * dd);
			std::cout << "ノード名 = " << ee << std::endl;

			// 属性
			char atr{};
			ifs.read(&atr, sizeof(char));
			std::cout << "属性 = " << atr << std::endl;

			// 文字数
			int ver{};
			ifs.read((char*)&ver, sizeof(char) * 4);
			cout << "文字数 = " << ver << endl;

			char str[256]{};
			ifs.read((char*)&ver, sizeof(char) * ver);
			cout << "文字列 = " << ver << endl;

			std::cout << std::endl;
		}

		// ノード名のバイト長
		{
			long long aa{};
			ifs.read((char*)&aa, sizeof(char) * 4);
			std::cout << "終端距離 = " << aa << std::endl;

			long long bb{};
			ifs.read((char*)&bb, sizeof(char) * 4);
			std::cout << "属性数 = " << bb << std::endl;

			long long cc{};
			ifs.read((char*)&cc, sizeof(char) * 4);
			std::cout << "全属性の合計バイト = " << cc << std::endl;

			char dd{};
			ifs.read(&dd, sizeof(char));
			std::cout << "全属性の合計バイト = " << (int)dd << std::endl;

			char ee[64]{};
			ifs.read(ee, sizeof(char) * dd);
			std::cout << "ノード名 = " << ee << std::endl;

			// 属性
			char atr{};
			ifs.read(&atr, sizeof(char));
			std::cout << "属性 = " << atr << std::endl;

			// 文字数
			int ver{};
			ifs.read((char*)&ver, sizeof(char) * 4);
			cout << "文字数 = " << ver << endl;

			char str[256]{};
			ifs.read((char*)&ver, sizeof(char) * ver);
			cout << "文字列 = " << ver << endl;

			std::cout << std::endl;
		}

		// ノード名のバイト長
		{
			long long aa{};
			ifs.read((char*)&aa, sizeof(char) * 4);
			std::cout << "終端距離 = " << aa << std::endl;

			long long bb{};
			ifs.read((char*)&bb, sizeof(char) * 4);
			std::cout << "属性数 = " << bb << std::endl;

			long long cc{};
			ifs.read((char*)&cc, sizeof(char) * 4);
			std::cout << "全属性の合計バイト = " << cc << std::endl;

			char dd{};
			ifs.read(&dd, sizeof(char));
			std::cout << "全属性の合計バイト = " << (int)dd << std::endl;

			char ee[64]{};
			ifs.read(ee, sizeof(char) * dd);
			std::cout << "ノード名 = " << ee << std::endl;

			// 属性
			char atr{};
			ifs.read(&atr, sizeof(char));
			std::cout << "属性 = " << atr << std::endl;

			// 文字数
			int ver{};
			ifs.read((char*)&ver, sizeof(char) * 4);
			cout << "文字数 = " << ver << endl;

			char str[256]{};
			ifs.read((char*)&ver, sizeof(char) * ver);
			cout << "文字列 = " << ver << endl;

			std::cout << std::endl;
		}
		// ノード名のバイト長
		{
			long long aa{};
			ifs.read((char*)&aa, sizeof(char) * 4);
			std::cout << "終端距離 = " << aa << std::endl;

			long long bb{};
			ifs.read((char*)&bb, sizeof(char) * 4);
			std::cout << "属性数 = " << bb << std::endl;

			long long cc{};
			ifs.read((char*)&cc, sizeof(char) * 4);
			std::cout << "全属性の合計バイト = " << cc << std::endl;

			char dd{};
			ifs.read(&dd, sizeof(char));
			std::cout << "全属性の合計バイト = " << (int)dd << std::endl;

			char ee[64]{};
			ifs.read(ee, sizeof(char) * dd);
			std::cout << "ノード名 = " << ee << std::endl;

			// 属性
			char atr{};
			ifs.read(&atr, sizeof(char));
			std::cout << "属性 = " << atr << std::endl;

			// 文字数
			int ver{};
			ifs.read((char*)&ver, sizeof(char) * 4);
			cout << "文字数 = " << ver << endl;

			char str[256]{};
			ifs.read((char*)&ver, sizeof(char) * ver);
			cout << "文字列 = " << ver << endl;

			std::cout << std::endl;
		}
		
		// 13バイトスキップ
		{
			long long aa{};
			ifs.read((char*)&aa, sizeof(char) * 4);
			std::cout << "終端距離 = " << aa << std::endl;
		}
		{
			long long aa{};
			ifs.read((char*)&aa, sizeof(char) * 4);
			std::cout << "終端距離 = " << aa << std::endl;
		}
		{
			long long aa{};
			ifs.read((char*)&aa, sizeof(char) * 4);
			std::cout << "終端距離 = " << aa << std::endl;
		}
		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << (char)aa << std::endl;
		}
		{
			long long aa{};
			ifs.read((char*)&aa, sizeof(char) * 4);
			std::cout << "終端距離 = " << aa << std::endl;

			long long bb{};
			ifs.read((char*)&bb, sizeof(char) * 4);
			std::cout << "属性数 = " << bb << std::endl;

			long long cc{};
			ifs.read((char*)&cc, sizeof(char) * 4);
			std::cout << "全属性の合計バイト = " << cc << std::endl;

			char dd{};
			ifs.read(&dd, sizeof(char));
			std::cout << "全属性の合計バイト = " << (int)dd << std::endl;

			char ee[64]{};
			ifs.read(ee, sizeof(char) * dd);
			std::cout << "ノード名 = " << ee << std::endl;

			// 属性
			std::cout << "属性 = ." << std::endl;

			std::cout << std::endl;
		}

		// ノード名のバイト長
		{
			long long aa{};
			ifs.read((char*)&aa, sizeof(char) * 4);
			std::cout << "終端距離 = " << aa << std::endl;

			long long bb{};
			ifs.read((char*)&bb, sizeof(char) * 4);
			std::cout << "属性数 = " << bb << std::endl;

			long long cc{};
			ifs.read((char*)&cc, sizeof(char) * 4);
			std::cout << "全属性の合計バイト = " << cc << std::endl;

			char dd{};
			ifs.read(&dd, sizeof(char));
			std::cout << "全属性の合計バイト = " << (int)dd << std::endl;

			char ee[64]{};
			ifs.read(ee, sizeof(char) * dd);
			std::cout << "ノード名 = " << ee << std::endl;

			std::cout << std::endl;
		}

		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}

		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}

		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}

		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}

		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}

		{
			long long aa{};
			ifs.read((char*)&aa, sizeof(char) * 4);
			std::cout << "終端距離 = " << aa << std::endl;

			long long bb{};
			ifs.read((char*)&bb, sizeof(char) * 4);
			std::cout << "属性数 = " << bb << std::endl;

			long long cc{};
			ifs.read((char*)&cc, sizeof(char) * 4);
			std::cout << "全属性の合計バイト = " << cc << std::endl;

			char dd{};
			ifs.read(&dd, sizeof(char));
			std::cout << "全属性の合計バイト = " << (int)dd << std::endl;

			char ee[64]{};
			ifs.read(ee, sizeof(char) * dd);
			std::cout << "ノード名 = " << ee << std::endl;

			std::cout << std::endl;
		}

		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}

		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}

		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}

		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}

		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}
		// プロパティがなかったらその下に子ノード

		{
			long long aa{};
			ifs.read((char*)&aa, sizeof(char) * 4);
			std::cout << "終端距離 = " << aa << std::endl;

			long long bb{};
			ifs.read((char*)&bb, sizeof(char) * 4);
			std::cout << "属性数 = " << bb << std::endl;

			long long cc{};
			ifs.read((char*)&cc, sizeof(char) * 4);
			std::cout << "全属性の合計バイト = " << cc << std::endl;

			char dd{};
			ifs.read(&dd, sizeof(char));
			std::cout << "全属性の合計バイト = " << (int)dd << std::endl;

			char ee[64]{};
			ifs.read(ee, sizeof(char) * dd);
			std::cout << "ノード名 = " << ee << std::endl;

			std::cout << std::endl;
		}
		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}
		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}
		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}
		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}

		{
			long long aa{};
			ifs.read((char*)&aa, sizeof(char) * 4);
			std::cout << "終端距離 = " << aa << std::endl;

			long long bb{};
			ifs.read((char*)&bb, sizeof(char) * 4);
			std::cout << "属性数 = " << bb << std::endl;

			long long cc{};
			ifs.read((char*)&cc, sizeof(char) * 4);
			std::cout << "全属性の合計バイト = " << cc << std::endl;

			char dd{};
			ifs.read(&dd, sizeof(char));
			std::cout << "全属性の合計バイト = " << (int)dd << std::endl;

			char ee[64]{};
			ifs.read(ee, sizeof(char) * dd);
			std::cout << "ノード名 = " << ee << std::endl;

			std::cout << std::endl;
		}

		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}

		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}

		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}

		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}

		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}

		{
			long long aa{};
			ifs.read((char*)&aa, sizeof(char) * 4);
			std::cout << "終端距離 = " << aa << std::endl;

			long long bb{};
			ifs.read((char*)&bb, sizeof(char) * 4);
			std::cout << "属性数 = " << bb << std::endl;

			long long cc{};
			ifs.read((char*)&cc, sizeof(char) * 4);
			std::cout << "全属性の合計バイト = " << cc << std::endl;

			char dd{};
			ifs.read(&dd, sizeof(char));
			std::cout << "全属性の合計バイト = " << (int)dd << std::endl;

			char ee[64]{};
			ifs.read(ee, sizeof(char) * dd);
			std::cout << "ノード名 = " << ee << std::endl;

			std::cout << std::endl;
		}
		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}
		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}
		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}
		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}
		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}

		{
			long long aa{};
			ifs.read((char*)&aa, sizeof(char) * 4);
			std::cout << "終端距離 = " << aa << std::endl;

			long long bb{};
			ifs.read((char*)&bb, sizeof(char) * 4);
			std::cout << "属性数 = " << bb << std::endl;

			long long cc{};
			ifs.read((char*)&cc, sizeof(char) * 4);
			std::cout << "全属性の合計バイト = " << cc << std::endl;

			char dd{};
			ifs.read(&dd, sizeof(char));
			std::cout << "全属性の合計バイト = " << (int)dd << std::endl;

			char ee[64]{};
			ifs.read(ee, sizeof(char) * dd);
			std::cout << "ノード名 = " << ee << std::endl;

			std::cout << std::endl;
		}

		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}

		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}
		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}
		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}
		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}

		{
			long long aa{};
			ifs.read((char*)&aa, sizeof(char) * 4);
			std::cout << "終端距離 = " << aa << std::endl;

			long long bb{};
			ifs.read((char*)&bb, sizeof(char) * 4);
			std::cout << "属性数 = " << bb << std::endl;

			long long cc{};
			ifs.read((char*)&cc, sizeof(char) * 4);
			std::cout << "全属性の合計バイト = " << cc << std::endl;

			char dd{};
			ifs.read(&dd, sizeof(char));
			std::cout << "全属性の合計バイト = " << (int)dd << std::endl;

			char ee[64]{};
			ifs.read(ee, sizeof(char) * dd);
			std::cout << "ノード名 = " << ee << std::endl;

			std::cout << std::endl;
		}
		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}
		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}
		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}
		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}
		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}



		{
			long long aa{};
			ifs.read((char*)&aa, sizeof(char) * 4);
			std::cout << "終端距離 = " << aa << std::endl;

			long long bb{};
			ifs.read((char*)&bb, sizeof(char) * 4);
			std::cout << "属性数 = " << bb << std::endl;

			long long cc{};
			ifs.read((char*)&cc, sizeof(char) * 4);
			std::cout << "全属性の合計バイト = " << cc << std::endl;

			char dd{};
			ifs.read(&dd, sizeof(char));
			std::cout << "全属性の合計バイト = " << (int)dd << std::endl;

			char ee[64]{};
			ifs.read(ee, sizeof(char) * dd);
			std::cout << "ノード名 = " << ee << std::endl;

			std::cout << std::endl;
		}
		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}
		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}
		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}
		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}
		{
			char aa{};
			ifs.read((char*)&aa, sizeof(char));
			std::cout << "終端距離 = " << aa << std::endl;

			// ノード名のバイト長
			long long nodeNameSize{};
			ifs.read((char*)&nodeNameSize, sizeof(char) * 4);
			std::cout << "ノード名のバイト長 = " << nodeNameSize << std::endl;

			char str[64]{};
			ifs.read(str, sizeof(char) * nodeNameSize);
			std::cout << "名前 = " << str << std::endl;

			std::cout << std::endl;
		}
	}
}