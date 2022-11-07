#pragma once

#include "../Library/Librarys.hpp"
#include "../../../engine/include/Core/ResourceOption.hpp"

namespace engine {

	inline DXGI_FORMAT toFormat(TextureFormat _format) {
		switch (_format) {
		case TextureFormat::R32G32B32A32_FLOAT:
			return DXGI_FORMAT_R32G32B32A32_FLOAT;
		case TextureFormat::R32G32B32_FLOAT:
			return DXGI_FORMAT_R32G32B32_FLOAT;
		case TextureFormat::R32G32_FLOAT:
			return DXGI_FORMAT_R32G32_FLOAT;
		case TextureFormat::R32_FLOAT:
			return DXGI_FORMAT_R32_FLOAT;
		default: return DXGI_FORMAT_UNKNOWN;
		}
	}

	inline D3D12_HEAP_TYPE toHeapType(const HeapType& _type) {
		switch (_type)
		{
		case HeapType::Custom:
			return D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_CUSTOM;
		case HeapType::Default:
			return D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_DEFAULT;
		case HeapType::ReadBack:
			return D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_READBACK;
		case HeapType::Upload:
			return D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_UPLOAD;
		default:
			return D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_DEFAULT;
		}
	}

	inline DXGI_FORMAT toFORMAT(TextureFormat _format) {
		switch (_format)
		{
		case TextureFormat::R8G8B8A8_UNORM:
			return DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
		case TextureFormat::R8G8B8A8_UNORM_SRGB:
			return DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		case TextureFormat::B8G8R8A8_UNORM:
			return DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_UNORM;
		case TextureFormat::B8G8R8A8_UNORM_SRGB:
			return DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
		default:
			return DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
		}
	}

	inline D3D12_RESOURCE_DIMENSION toResourceDimension(ResourceDimension _dimension) {
		switch (_dimension)
		{
		case ResourceDimension::Buffer:
			return D3D12_RESOURCE_DIMENSION_BUFFER;
		case ResourceDimension::Texture1D:
			return D3D12_RESOURCE_DIMENSION_TEXTURE1D;
		case ResourceDimension::Texture2D:
			return D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		case ResourceDimension::Texture3D:
			return D3D12_RESOURCE_DIMENSION_TEXTURE3D;
		case ResourceDimension::Unknown:
			return D3D12_RESOURCE_DIMENSION_UNKNOWN;
		default:
			return D3D12_RESOURCE_DIMENSION_UNKNOWN;
		}
	}

	inline D3D12_TEXTURE_LAYOUT toLayout(TextureLayout _layout) {
		switch (_layout)
		{
		case engine::TextureLayout::Unknown:
			return D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_UNKNOWN;
		case engine::TextureLayout::RowMajor:
			return D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
		default:
			return D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_UNKNOWN;
		}
	}

	inline D3D12_RESOURCE_STATES toResourceStates(ResouceStates _status) {
		switch (_status)
		{
		case engine::ResouceStates::GenericRead:
			return D3D12_RESOURCE_STATE_GENERIC_READ;
		case engine::ResouceStates::DepthWrite:
			return D3D12_RESOURCE_STATE_DEPTH_WRITE;
		case engine::ResouceStates::PixelShaderResouce:
			return D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
		case engine::ResouceStates::RenderTarget:
			return D3D12_RESOURCE_STATE_RENDER_TARGET;
		case engine::ResouceStates::Present:
			return D3D12_RESOURCE_STATE_PRESENT;
		default:
			return D3D12_RESOURCE_STATE_GENERIC_READ;
		}
	}

}