#include "../../include/Texture/Texture.hpp"
#include "../../include/Image/Image.hpp"

namespace engine {

	/*
	TexturePtr Texture::create(const std::wstring& _path)
	{
		TexturePtr result{ new Texture{} };
		if (!result->loadTexture(_path)) {
			return nullptr;
		}

		return result;
	}

	TexturePtr Texture::create(const Image& _img)
	{
		TexturePtr result{ new Texture };
		if (!result->loadTexture(_img.getData(), _img.getWidth(), _img.getHeight(), _img.getStride())) {
			return nullptr;
		}

		return result;
	}

	Texture::Texture()
		: width(0)
		, height(0)
		, depthOrArraySize(0)
		, mipLevels(0)
		, resourceDimention()
		, textureFormat()
		, resource(nullptr)
		, descriptorHeap()
	{
	}

	bool Texture::loadTexture(const std::wstring& _path)
	{

		DirectX::ScratchImage image{};

		{
			using namespace DirectX;
			DirectX::TexMetadata metaData{};

			HRESULT hr{};
			hr = LoadFromWICFile(
				_path.c_str(), WIC_FLAGS::WIC_FLAGS_NONE, &metaData, image
			);
			if (FAILED(hr)) {
				return false;
			}

			const auto toD3D12ResourceDimension = [](DirectX::TEX_DIMENSION _dimension) {
				return static_cast<D3D12_RESOURCE_DIMENSION>(_dimension);
			};

			auto dimension = toD3D12ResourceDimension(metaData.dimension);
			auto format = metaData.format;


			width = static_cast<UINT64>(metaData.width);
			height = static_cast<UINT>(metaData.height);
			depthOrArraySize = static_cast<UINT16>(metaData.arraySize);
			mipLevels = static_cast<UINT16>(metaData.mipLevels);
			textureFormat = convertToTextureFormat(metaData.format);
			resourceDimention = convertResourceDimention(dimension);
		}

		if (!createResource()) {
			return false;
		}

		{
			const auto pixel = image.GetImage(0, 0, 0);
			const auto w = getWidth();
			const auto h = getHeight();

			if (!mapSubResource(pixel->pixels, w, h, pixel->rowPitch, pixel->slicePitch)) {
				return false;
			}
		}

		if (!createDescriptorHeap()) {
			return false;
		}

		return true;
	}

	bool Texture::loadTexture(const u8* _data, u64 _width, u64 _height, u64 _stride)
	{
		width = static_cast<UINT64>(_width);
		height = static_cast<UINT>(_height);
		depthOrArraySize = static_cast<UINT16>(1);
		mipLevels = static_cast<UINT16>(1);
		textureFormat = core::TextureFormat::R8G8B8A8_UNORM;
		resourceDimention = core::ResourceDimension::Texture2D;
		
		if (!createResource()) {
			return false;
		}

		{
			const auto pixel = _data;
			const auto w = getWidth();
			const auto h = getHeight();
			const auto rowPitch = _width * _stride;
			const auto slicePitch = _width * _stride * _height;

			if (!mapSubResource(_data, w, h, rowPitch, slicePitch)) {
				return false;
			}
		}

		if (!createDescriptorHeap()) {
			return false;
		}

		return true;
	}

	bool Texture::createResource()
	{
		D3D12_RESOURCE_DESC desc{};
		desc.Dimension = convertD3D12ResourceDimension(resourceDimention);
		desc.Alignment = 0;
		desc.Width     = getWidth();
		desc.Height    = (UINT)getHeight();
		desc.DepthOrArraySize = getDepthOrArraySize();
		desc.MipLevels       = getMipLevels();
		desc.Format = convertToDXGI_FORMAT(textureFormat);
		desc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
		desc.SampleDesc.Quality = 0;
		desc.SampleDesc.Count = 1;

		D3D12_HEAP_PROPERTIES prop{};
		prop.Type                 = D3D12_HEAP_TYPE_CUSTOM;
		prop.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
		prop.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
		prop.CreationNodeMask     = 0;
		prop.VisibleNodeMask      = 0;

		
		HRESULT hr = EngineDevice()->get()->CreateCommittedResource(
			&prop,
			D3D12_HEAP_FLAG_NONE,
			&desc,
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
			nullptr,
			IID_PPV_ARGS(resource.GetAddressOf())
		);
		// return SUCCEEDED(hr);
	}

	bool Texture::mapSubResource(const u8* _pixel, u64 _width, u64 _height, u64 _rowPitch, u64 _slicePitch)
	{
		u8* pDetaBegin{ nullptr };
		D3D12_BOX box{ 0, 0, 0, (u32)_width, (u32)_height, 1 };
		D3D12_RANGE range{ 0, 0 };

		HRESULT hr = resource->Map(0, &range, reinterpret_cast<void**>(pDetaBegin));
		if (FAILED(hr)) {
			return false;
		}

		hr = resource->WriteToSubresource(
			0,
			&box,
			_pixel,
			static_cast<UINT>(_rowPitch),
			static_cast<UINT>(_slicePitch)
		);

		if (FAILED(hr)) {
			return false;
		}
		resource->Unmap(0, nullptr);

		return true;
	}

	bool Texture::createDescriptorHeap()
	{
		if (!descriptorHeap.init(1, DescriptorType::CSV_SRV_UAV, DescriptorFlag::Visibe)) {
			return false;
		}

		{
			D3D12_SHADER_RESOURCE_VIEW_DESC desc{};
			desc.Format = resource->GetDesc().Format;
			desc.Texture2D.MipLevels = resource->GetDesc().MipLevels;
			desc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
			desc.Texture2D.MostDetailedMip = 0;
			desc.Texture2D.PlaneSlice = 0;
			desc.Texture2D.ResourceMinLODClamp = 0.0f;
			desc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;

			// D3D12_CPU_DESCRIPTOR_HANDLE handleSRV = { descriptor->GetCPUDescriptorHandleForHeapStart() };
			// auto s = "Shader Resource View Handle = " + std::to_string(handleSRV.ptr) + "\n";
			// OutputDebugString(s.c_str());

			auto handle = descriptorHeap.getCpuHandle();
			//EngineDevice()->get()->CreateShaderResourceView(resource.Get(), &desc, handle);
		}

		return true;
	}
	*/
}