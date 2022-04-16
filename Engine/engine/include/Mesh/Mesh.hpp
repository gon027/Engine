#pragma once

#include <vector>
#include "../Library/Librarys.hpp"
#include "../Graphics/VertexBuffer.hpp"
#include "../Graphics/IndexBuffer.hpp"
#include "../Vertex/Vertex2D.hpp"
#include "../Type/Type.hpp"

namespace engine {

	class Mesh {
	public:
		Mesh();
		~Mesh() = default;

		void setVertex(const std::vector<Vertex2D>& _vertex);
		void setVertex(std::initializer_list<Vertex2D> _vertex);

		void setIndex(const std::vector<u32>& _index);
		void setIndex(std::initializer_list<u32> _index);

		void draw();

		inline u64 getVertexCount() const {
			return vertexCount;
		}

		inline u64 getIndexCount() const {
			return indexCount;
		}

	public:
		std::vector<Vertex2D> vertex;
		std::vector<u32> index;

		u64 vertexCount;
		u64 indexCount;

	private:
		VertexBuffer vertexBuffer;
		IndexBuffer indexBuffer;
	};

}