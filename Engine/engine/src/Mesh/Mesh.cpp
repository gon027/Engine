#include "../../include/Mesh/Mesh.hpp"
#include "../../include/EngineCore/EngineCore.hpp"
#include "../../include/Graphics/CommandList.hpp"

namespace engine {

	Mesh::Mesh()
		: vertex()
		, index()
		, vertexCount(0)
		, indexCount(0)
		, vertexBuffer()
		, indexBuffer()
	{
	}

	void Mesh::setVertex(const std::vector<Vertex2D>&_vertex) {
		vertex = _vertex;
		vertexCount = vertex.size();
		vertexBuffer.init(vertex.data(), sizeof(Vertex2D), vertexCount);
		// vertexBuffer.update(vertex.data());
	}

	void Mesh::setVertex(std::initializer_list<Vertex2D> _vertex) {
		vertex = _vertex;
		vertexCount = vertex.size();
		vertexBuffer.init(vertex.data(), sizeof(Vertex2D), vertexCount);
		// vertexBuffer.update(vertex.data());
	}

	void Mesh::setIndex(const std::vector<u32>&_index) {
		index = _index;
		indexCount = _index.size();
		indexBuffer.init(index.data(), sizeof(Vertex2D), indexCount);
	}

	void Mesh::setIndex(const std::initializer_list<u32> _index) {
		index = _index;
		indexCount = _index.size();
		indexBuffer.init(index.data(), sizeof(Vertex2D), indexCount);
	}

	void Mesh::draw() {
		if (getVertexCount() < 3) {
			return;
		}

		EngineCommand()->get()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		EngineCommand()->get()->IASetVertexBuffers(0, 1, &vertexBuffer.getView());
		EngineCommand()->get()->IASetIndexBuffer(&indexBuffer.getView());

		EngineCommand()->get()->DrawIndexedInstanced((u32)index.size(), 1, 0, 0, 0);
	}
}