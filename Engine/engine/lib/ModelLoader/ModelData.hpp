#pragma once

#include <string>
#include <vector>
#include <variant>

namespace model {

	namespace pmx {
		enum class SphereMode : unsigned char;
	}

	using VString = std::variant<std::string, std::wstring>;

	// ���f����ǂݎ������̍ŏI�`��
	struct ModelData {
	public:
		struct ModelVertex {
			float position[3];
			float normal[3];
			float uv[2];
		};

		struct MaterialForHlsl {
			float diffuse[4];
			float specular[3];           // �X�y�L����
			float specularCoefficient;
			float ambient[3];            // �A���r�G���g
		};

		struct Material {
			VString textureName;
			pmx::SphereMode sphereMode;
			VString sphereName;
			VString toonName;
			unsigned long vertCount;
			MaterialForHlsl material;
		};

	public:
		VString extension;
		VString modelName;
		std::vector<ModelVertex> vertexes;
		std::vector<unsigned int> indexes;
		std::vector<Material> materials;
	};

}