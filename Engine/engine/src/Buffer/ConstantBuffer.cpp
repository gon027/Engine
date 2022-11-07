#include "../../include/Buffer/ConstantBuffer.hpp"
#include "../../lib/src/Dx12/Buffer/Dx12Resource.hpp"
#include "../../lib/src/Dx12/Device/Device.hpp"

namespace engine {

	namespace {
		u32 calcBufferSize(size_t _size) {
			return (_size + 255) & ~255;
		};
	}

	ConstantBuffer::ConstantBuffer()
		: resource(new Dx12Resource{})
		, pData(nullptr)
		, bufferSize()
	{
	}

	ConstantBuffer::~ConstantBuffer()
	{
		if (resource) {
			resource->unMap();
		}
	}

	bool ConstantBuffer::init(device_ptr _device, const void* _data, size_t _size)
	{
		assert(_device != nullptr);

		auto* device = static_cast<Dx12Device*>(_device.get());

		bufferSize = calcBufferSize(_size);

		ResourceDesc desc{};
		desc.dimension = ResourceDimension::Buffer;
		desc.width = bufferSize;
		desc.height = 1;
		desc.depthOrArraySize = 1;
		desc.mipLevels = 1;
		desc.format = TextureFormat::UNKNOWN;
		desc.layout = TextureLayout::RowMajor;
		desc.flags = ResourceFlags::None;

		if (!resource->init(_device, ResourceType::Upload, desc, ResouceStates::GenericRead)) {
			return false;
		}

		pData = resource->map();
		memcpy(pData, _data, bufferSize);

		return true;
	}

	void ConstantBuffer::update(const void* _data, size_t _size)
	{
		bufferSize = calcBufferSize(_size);
		memcpy(pData, _data, bufferSize);
	}

	u64 ConstantBuffer::getBufferSize() const
	{
		return bufferSize;
	}

	resource_ptr ConstantBuffer::get() const
	{
		return resource;
	}

}