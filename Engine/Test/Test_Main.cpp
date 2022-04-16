// 
// #include "EngineMain/EngineMain.hpp"
// #include "../engine/include/Window/Window.hpp"
// #include "../engine/include/EngineCore/EngineCore.hpp"
// #include "../engine/include/Graphics/Factory.hpp"
// #include "../engine/include/Graphics/Device.hpp"
// #include "../engine/include/Graphics/CommandList.hpp"
// 
// #include "../engine/include/Graphics/RenderingPipeline2D.hpp"
// #include "../engine/include/Input/Input.hpp"
// 
// #include "../engine/include/Graphics/InputLayout.hpp"
// #include "../engine/include/Graphics/RootSignature.hpp"
// #include "../engine/include/Graphics/PipelineState.hpp"
// 
// #include "../engine/include/Graphics/ConstantBuffer.hpp"
// 
// #include "../engine/include/Type/Type.hpp"
// 
// #include "../engine/include/Vertex/Vertex2D.hpp"
// 
// #include "../engine/include/Asset/AssetPath.hpp"
// 
// #include "../engine/include/Mesh/Mesh.hpp"
// 
// #include "../engine/include/Transform/Transform.hpp"
// #include "../engine/include/MatrixBuffer/MatrixBuffer.hpp"
// 
// #include <vector>
// 
// #include "../../../MathLib/MathLib/Math/include/Math.hpp"
// #pragma comment(lib, "C:/Users/USER/source/repos/MathLib/x64/Debug/MathLib.lib")
// using namespace gnLib;
//
//void gnMain() {
//	using namespace engine;
//
//	try {
//		Engine()->init();
//	}
//	catch (const std::exception&) {
//		return;
//	}
//
//	const float size = 1.0f;
//	std::vector<Vertex2D> vertex{
//		{ { -size, -size, 0.0f },{ 1.0f, 0.0f, 0.0f, 1.0f } },
//		{ { -size, size, 0.0f } ,{ 0.0f, 1.0f, 0.0f, 1.0f } },
//		{ { size, size, 0.0f }  ,{ 0.0f, 0.0f, 1.0f, 1.0f } },
//		{ { size, -size, 0.0f } ,{ 0.0f, 1.0f, 1.0f, 1.0f } },
//	};
//
//	std::vector<u32> indexes{ 0, 1, 2, 0, 2, 3 };
//	
//	Mesh mesh{};
//	mesh.setVertex(vertex.data(), sizeof(Vertex2D), vertex.size());
//	mesh.setIndex(indexes.data(), sizeof(u32), indexes.size());
//
//	MatrixBuffer matrix{};
//	{
//		matrix.world = Matrix4x4::identity();
//		const auto eye = Vector3{ 0.0f, 0.0f, -5.0f };
//		const auto target = Vector3{ 0.0f, 0.0f, 0.0f };
//		const auto up = Vector3{ 0.0f, 1.0f, 0.0f };
//		matrix.view = Matrix4x4::lookAtLH(eye, target, up);
//		// matrix.projection = Matrix4x4::orthographicLH(640.0f, 480.0f, 1.0f, 100.0f);
//		matrix.projection = Matrix4x4::perspectiveFovLH(
//			DirectX::XMConvertToRadians(45.0f), 640.0f / 480.0f, 0.5f, 100.0f
//		);
//	}
//
//	ConstantBuffer csBuffer{ sizeof(MatrixBuffer) };
//
//	float frame = 0.0f;
//	u32 frameInt = 0;
//
//	while (EngineWindow()->update()) {
//		Engine()->begin();
//		EnginePipeline2D()->setPipeline();
//
//		auto* commandList = EngineCommand()->get();
//		
//		{
//			Transform tf{};
//			tf.position = { 0.0f, 0.0f, 5.0f };
//			auto q = Quaternion::rotationAxis({ 0, 0, 1 }, frame);
//			auto p = Quaternion::rotationAxis({ 1, 0, 0 }, frame);
//			tf.rotation = p; // x -> z
//			// tf.rotation = Quaternion::identity(); // x -> z
//			auto a = Matrix4x4::scaling(tf.scale) * tf.rotation.toMatrix() * Matrix4x4::translation(tf.position);
//			matrix.world = a;
//			csBuffer.update(&matrix, sizeof(matrix));
//		}
//
//		commandList->SetGraphicsRootConstantBufferView(0, csBuffer.get()->GetGPUVirtualAddress());
//
//		commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//
//		mesh.draw(vertex.data(), (u32)indexes.size());
//		
//
//		frame += 0.02f;
//		// ++frameInt;
//
//		Engine()->end();
//		Sleep(1);
//	}
//
//}
