#pragma once

#include "../Type/Type.hpp"

namespace engine {

	enum class HeapType {
		Default,
		Upload,
		ReadBack,
		Custom
	};

	enum class ResourceDimension {
		Buffer,
		Texture1D,
		Texture2D,
		Texture3D,
		Unknown
	};

	enum class TextureFormat {
		UNKNOWN,
		R8G8B8A8_UNORM,
		R8G8B8A8_UNORM_SRGB,
		B8G8R8A8_UNORM,
		B8G8R8A8_UNORM_SRGB,
		R32G32B32A32_FLOAT,
		R32G32B32_FLOAT,
		R32G32_FLOAT,
		R32_FLOAT,
	};

	enum class TextureLayout {
		Unknown,
		RowMajor,
	};

	enum class ResourceFlags {
		None,
		RenderTarget,
		DepthStencil,
		UnorderedAccess,
		ShaderResource
	};

	struct ResourceDesc {
		ResourceDimension dimension = ResourceDimension::Unknown;
		u64 width = 1;
		u64 height = 0;
		u16 depthOrArraySize = 0;
		u16 mipLevels = 0;
		TextureFormat format = TextureFormat::UNKNOWN;
		TextureLayout layout = TextureLayout::Unknown;
		ResourceFlags flags = ResourceFlags::None;
	};

	enum class HeapFlag {
		None = 0,
	};

	enum class ResouceStates {
		GenericRead,
		DepthWrite,
		PixelShaderResouce,
		RenderTarget,
		Present
	};

	struct ClearValue {
		int a = 0;

		ClearValue() = default;
	};

}