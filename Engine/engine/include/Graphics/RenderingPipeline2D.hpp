#pragma once

#include <vector>
#include "../Graphics/RootSignature.hpp"
#include "../Graphics/PipelineState.hpp"

namespace engine {

	class RootSignature;
	class PipelineState;

	class RenderingPipeline2D {
	public:
		RenderingPipeline2D();
		~RenderingPipeline2D();

		void init();

		void setPipeline(size_t _index);

	private:
		void createColorPipeline();

		void createTexturePipeline();

	private:
		std::vector<RootSignature> rootSignatureList;
		std::vector<PipelineState> pipelineStateList;
	};

}