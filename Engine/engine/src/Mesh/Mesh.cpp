#include "../../include/Mesh/Mesh.hpp"
// #include <include/EngineCore/EngineCore.hpp>
// #include <include/CommandList/CommandList.hpp>

namespace engine {
	void Mesh::setVertexBuffer(const void* _data, UINT _strideInBytes, size_t _dataSize)
	{
		// vertexBuffer.copyBuffer(_data);
	}

	void Mesh::setIndexBuffer(IndexData& _indexData)
	{
		// indexBuffer.copyBuffer(_indexData.getData());
	}

	void Mesh::draw()
	{
		// auto commandList = EngineCommand()->get();
		// 
		// commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		// 
		// commandList->IASetVertexBuffers(0, 1, &vertexBuffer.getView());
		// commandList->IASetIndexBuffer(&indexBuffer.getView());
		// 
		// commandList->DrawIndexedInstanced(indexSize, 1, 0, 0, 0);
	}
}