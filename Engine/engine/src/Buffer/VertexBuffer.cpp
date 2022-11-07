#include "../../include/Buffer/VertexBuffer.hpp"
#include "../../lib/src/Dx12/Buffer/Dx12Resource.hpp"
#include "../../lib/src/Dx12/Device/Device.hpp"

namespace engine {

	VertexBuffer::VertexBuffer()
		: resource(new Dx12Resource{})
		, stride()
		, size()
		, bufferSize()
	{
	}

	VertexBuffer::~VertexBuffer()
	{
	}

	bool VertexBuffer::init(device_ptr _device, const void* _data, u64 _stride, size_t _size)
	{
		assert(_device != nullptr);
		
		auto* device = static_cast<Dx12Device*>(_device.get());

		stride = _stride;
		size = _size;
		bufferSize = stride * static_cast<u64>(size);

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

		auto* data = resource->map();
		{
			memcpy(data, _data, bufferSize);
		}
		resource->unMap();

		return true;
	}

	void VertexBuffer::update(const void* _data, u64 _stride, size_t _size)
	{
	}

	u64 VertexBuffer::getStride() const
	{
		return stride;
	}

	u64 VertexBuffer::getSize() const
	{
		return size;
	}

	u64 VertexBuffer::getBufferSize() const
	{
		return bufferSize;
	}

	resource_ptr VertexBuffer::get() const
	{
		return resource;
	}

}