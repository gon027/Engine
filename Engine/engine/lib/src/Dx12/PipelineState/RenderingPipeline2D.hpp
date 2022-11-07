#pragma once

#include <vector>
#include "../RootSignature/RootSignature.hpp"
#include "../PipelineState/PipelineState.hpp"
#include "../../../engine/include/Type/Type.hpp"

namespace engine {

	class RootSignature;
	class PipelineState;

	enum class RenderState : u64 {
		Default = 0,
		Texture = 1,
	};

	class RenderingPipeline2D {
	public:
		RenderingPipeline2D();
		~RenderingPipeline2D();

		void init();

		void setPipeline(RenderState _state);

	private:
		void createColorPipeline();

		void createTexturePipeline();

	private:
		std::vector<RootSignature> rootSignatureList;
		std::vector<PipelineState> pipelineStateList;
	};

}