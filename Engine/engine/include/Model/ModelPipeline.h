#pragma once

#include "../../lib/include/IDevice.hpp"
#include "../../lib/src/Dx12/RootSignature/RootSignature.hpp"
#include "../../lib/src/Dx12/PipelineState/PipelineState.hpp"

namespace engine {

	class ModelPipeline {
	public:
		ModelPipeline(device_ptr _device);
		~ModelPipeline() = default;

		RootSignature& getRootSignature() {
			return rootSignature;
		}

		std::shared_ptr<core::Pipeline>& getPipelineState() {
			return pipelineState;
		}

	private:
		RootSignature rootSignature;
		std::shared_ptr<core::Pipeline> pipelineState;
	};

}