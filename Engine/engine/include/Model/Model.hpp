#pragma once

#include <memory>
#include <unordered_map>
#include "../../lib/include/Fwd.hpp"

#include "../../lib/Math/MathLib.hpp"
#include "../Transform/Transform.hpp"
#include "../IndexData/IndexData.hpp"

#include "../Vertex/Vec.hpp"

#include "../Buffer/VertexBuffer.hpp"
#include "../Buffer/IndexBuffer.hpp"
#include "../Buffer/ConstantBuffer.hpp"

// 後で変える
#include "../../lib/src/Dx12/Texture/Dx12Texture.hpp"
#include "../../lib/src/Dx12/DescriptorHeap/DescriptorHeap.h"

#include "../../lib/include/ICommandList.hpp"

namespace model {
	struct ModelData;
}

using ModelDataPtr = std::shared_ptr<model::ModelData>;
using ModelList = std::unordered_map<std::string, ModelDataPtr>;

namespace engine {

	class Model {
	public:
		Model(device_ptr _device, ModelDataPtr _model);
		~Model();

		void update();

		void draw(commandList_ptr _cmdList);

		void setPosition(const Vector3& _pos);

	private:
		
	private:
		ModelDataPtr modelData;

		Transform transform;

		// モデルのメッシュ
		VertexBuffer vertexBuffer;
		IndexBuffer indexBuffer;
		ConstantBuffer constantBuffer;

		// モデルデータ
		std::unordered_map<std::wstring, Dx12Texture> textures;
		std::unordered_map<std::wstring, ConstantBuffer> materials;
	};

}