#pragma once

#include "../../../include/ITexture.hpp"

#include "../Library/Librarys.hpp"
#include "../DescriptorHeap/DescriptorHeap.h"

namespace engine {

	class Dx12Texture : public core::ITexture {
	public:
		Dx12Texture();
		~Dx12Texture();

		bool load(device_ptr _device, const std::wstring& _fileName) override;

		bool load(device_ptr _device, const Image& _image) override;

		unsigned int getWidth() override;

		unsigned int getHeight() override;

		ID3D12Resource* getResource() const;

		ID3D12DescriptorHeap* getHeap() const;

	private:
		unsigned int width;
		unsigned int height;

		D3D12Resource resource;
		DescriptorHeap descriptorHeap;
	};

}