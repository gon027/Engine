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

// Œã‚Å•Ï‚¦‚é
#include "../../lib/src/Dx12/DescriptorHeap/DescriptorHeap.h"

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

	private:
		struct Vertex {
			Vec3 position;
			Vec3 normal;
			Vec2 uv;
		};

		ModelDataPtr modelData;

		Transform transform;

		std::vector<Vertex> vertex;
		std::vector<unsigned int> index;

		VertexBuffer vertexBuffer;
		IndexBuffer indexBuffer;

		std::vector<size_t> offsets;

		D3D12DescriptorHeap srvDescHeap;
		unsigned int incrimentSize;
	};

}