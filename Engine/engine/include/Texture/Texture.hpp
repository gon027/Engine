#pragma once

#include <string>
#include <memory>

#include <include/Library/Librarys.hpp>
#include <include/Type/Type.hpp>
#include <include/DescriptorHeap/DescriptorHeap.h>

namespace engine {

	class Image;

	enum class TextureFormat {
		R8G8B8A8_UNORM,
		R8G8B8A8_UNORM_SRGB,
		B8G8R8A8_UNORM,
		B8G8R8A8_UNORM_SRGB
	};

	enum class ResourceDimension {
		Buffer,
		Texture1D,
		Texture2D,
		Texture3D,
		Unknown
	};

	class Texture;
	using TexturePtr = std::shared_ptr<Texture>;

	class Texture {
	public:
		static TexturePtr create(const std::wstring& _path);

		static TexturePtr create(const Image& _img);

	public:
		Texture();
		~Texture() = default;

		bool loadTexture(const std::wstring& _path);

		bool loadTexture(const u8* _data, u64 _width, u64 _height, u64 _stride);

		u64 getWidth() const {
			return width;
		}

		u64 getHeight() const {
			return height;
		}

		u16 getDepthOrArraySize() const {
			return depthOrArraySize;
		}

		u16 getMipLevels() const {
			return mipLevels;
		}

		// D3D12_RESOURCE_DIMENSION getDimension() const {
		// 	return dimension;
		// }

		// DXGI_FORMAT getFormat() const {
		// 	return format;
		// }
		
		D3D12_CPU_DESCRIPTOR_HANDLE getCPUHandle() const {
			return descriptorHeap.getCpuHandle();
		}

		D3D12_GPU_DESCRIPTOR_HANDLE getGPUHandle() const {
			return descriptorHeap.getGpuHandle();
		}

		ID3D12DescriptorHeap* getHeap() const {
			return descriptorHeap.getDescriptorHeap();
		}

		u32 getDescriptorSize() const {
			return descriptorHeap.getDescriptorSize();;
		}

	private:
		bool createResource();
		bool mapSubResource(const u8* _pixel, u64 _width, u64 _height, u64 _rowPitch, u64 _slicePitch);
		bool createDescriptorHeap();

	private:
		u64 width;
		u64 height;
		u16 depthOrArraySize;
		u16 mipLevels;

		TextureFormat textureFormat;
		ResourceDimension resourceDimention;

		DescriptorHeap descriptorHeap;

		D3D12Resource resource;
	};

}