/*
#include "EngineMain/EngineMain.hpp"
#include "../engine/include/EngineCore/EngineCore.hpp"
#include "../engine/include/Window/Window.hpp"
#include "../engine/include/Graphics/Device.hpp"
#include "../engine/include/Graphics/CommandList.hpp"
#include "../engine/include/Graphics/RenderingPipeline2D.hpp"
#include "../engine/include/MatrixBuffer/MatrixBuffer.hpp"
#include "../engine/include/Graphics/ConstantBuffer.hpp"
#include "../engine/include/Mesh/Mesh.hpp"
#include "../engine/include/Engine.hpp"
using namespace engine;
#include <vector>

namespace {

	class Camera3D {
	public:
		Camera3D()
			: eye({ 0.0f, 0.0f, -5.0f })
			, target({ 0.0f, 0.0f, 0.0f })
			, up({ 0.0f, 1.0f, 0.0f })
			, fovAngle(toRadian(45.0f))
			, viewWidth(640.0f)
			, viewHeight(480.0f)
			, view()
			, projection()
		{
			view = Matrix4x4::lookAtLH(eye, target, up);
			projection = Matrix4x4::perspectiveFovLH(
				fovAngle, (viewWidth / viewHeight), nearZ, farZ
			);
		}
		~Camera3D() = default;

		inline Matrix4x4& getView() noexcept {
			return view;
		}

		inline Matrix4x4& getProjection() noexcept {
			return projection;
		}

	// private:
		const float nearZ = 1.0f;
		const float farZ = 10.0f;

		const float fovAngle;

		float viewWidth;
		float viewHeight;

		Vector3 eye;
		Vector3 target;
		Vector3 up;

	private:
		Matrix4x4 view;
		Matrix4x4 projection;
	};

}
*/

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
//	// std::vector<Vertex2D> vertex{
//	// 	{ { -size, -size, 0.0f },{ 1.0f, 0.0f, 0.0f, 1.0f } },
//	// 	{ { -size, size, 0.0f } ,{ 0.0f, 1.0f, 0.0f, 1.0f } },
//	// 	{ { size, size, 0.0f }  ,{ 0.0f, 0.0f, 1.0f, 1.0f } },
//	// 	{ { size, -size, 0.0f } ,{ 0.0f, 1.0f, 1.0f, 1.0f } },
//	// };
//	// std::vector<u32> indexes{ 0, 1, 2, 0, 2, 3 };
//
//	const float size = 1.0f;
//	Mesh mesh{};
//	mesh.setVertex(
//		{
//			{ { -size, -size, 0.0f },{ 1.0f, 0.0f, 0.0f, 1.0f } },
//			{ { -size, size, 0.0f } ,{ 0.0f, 1.0f, 0.0f, 1.0f } },
//			{ { size, size, 0.0f }  ,{ 0.0f, 0.0f, 1.0f, 1.0f } },
//			{ { size, -size, 0.0f } ,{ 0.0f, 1.0f, 1.0f, 1.0f } },
//		}
//	);
//	mesh.setIndex({ 0, 1, 2, 0, 2, 3 });
//
//	Camera3D c2{};
//	MatrixBuffer matrix{};
//	{
//		matrix.world = Matrix4x4::identity();
//		matrix.view = c2.getView();
//		matrix.projection = c2.getProjection();
//	}
//
//	ConstantBuffer csBuffer{ sizeof(MatrixBuffer) };
//
//	float frame = 0.0f;
//	while (EngineWindow()->update()) {
//		Engine()->begin();
//		EnginePipeline2D()->setPipeline();
//
//		auto* commandList = EngineCommand()->get();
//
//		//{
//		//	Transform tf{};
//		//	tf.position = { 0.0f, 0.0f, 0.0f };
//		//	auto q = Quaternion::rotationAxis({ 0, 0, 1 }, frame);
//		//	auto p = Quaternion::rotationAxis({ 1, 0, 0 }, frame);
//		//	tf.rotation = q; // x -> z
//		//	// tf.rotation = Quaternion::identity(); // x -> z
//		//	auto a = Matrix4x4::scaling(tf.scale) * tf.rotation.toMatrix() * Matrix4x4::translation(tf.position);
//		//	// auto a = Matrix4x4::translation(tf.position);
//		//	//matrix.world = a;
//		//}
//
//		csBuffer.update(&matrix, sizeof(MatrixBuffer));
//		commandList->SetGraphicsRootConstantBufferView(0, csBuffer.get()->GetGPUVirtualAddress());
//
//		mesh.draw();
//
//		frame += 0.02f;
//		Engine()->end();
//		Sleep(1);
//	}
//
//}
