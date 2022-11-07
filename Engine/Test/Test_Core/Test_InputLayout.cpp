/*
#include "../../engine/include/EngineMain/EngineMain.hpp"
#include "../../engine/lib/Dx12/include/PipelineState/InputLayout.hpp"

DXGI_FORMAT toFormat(engine::core::TextureFormat _format) {
	switch (_format) {
	case engine::core::TextureFormat::R32G32B32A32_FLOAT:
		return DXGI_FORMAT_R32G32B32A32_FLOAT;
	case engine::core::TextureFormat::R32G32B32_FLOAT:
		return DXGI_FORMAT_R32G32B32_FLOAT;
	case engine::core::TextureFormat::R32G32_FLOAT:
		return DXGI_FORMAT_R32G32_FLOAT;
	case engine::core::TextureFormat::R32_FLOAT:
		return DXGI_FORMAT_R32_FLOAT;
	default: return DXGI_FORMAT_UNKNOWN;
	}
}

D3D12_INPUT_ELEMENT_DESC toInputElementDesc(const engine::InputElement& _elem) {
	D3D12_INPUT_ELEMENT_DESC res{};
	res.SemanticName = _elem.semanticName.c_str();
	res.SemanticIndex = 0;
	res.Format = toFormat(_elem.format);  // å„Ç≈çlÇ¶ÇÈ
	res.InputSlot = 0;
	res.AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
	res.InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
	res.InstanceDataStepRate = 0;
	return res;
}

void gnMain() {
	using namespace engine;

	const InputLayout inputLayout{
		{"POSITION", core::TextureFormat::B8G8R8A8_UNORM},
		{"TEXCOORD", core::TextureFormat::B8G8R8A8_UNORM}
	};

	std::vector<D3D12_INPUT_ELEMENT_DESC> elements{};
	for (size_t i = 0; i < inputLayout.getSize(); ++i) {
		auto e = toInputElementDesc(inputLayout.getElement(i));
		elements.emplace_back(e);
	}

	return;
}
*/