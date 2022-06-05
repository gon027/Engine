/*#include "../engine/include/EngineMain/EngineMain.hpp"
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
*/
/*
namespace engine {

	class Camera2D {
	public:
		Camera2D() 
			: eye({ 0.0f, 0.0f, -1.0f })
			, target({ 0.0f, 0.0f, 0.0f })
			, up({ 0.0f, 1.0f, 0.0f })
			, nearZ(1.0f)
			, farZ(100.0f)
			, viewWidth(640.0f)
			, viewHeight(480.0f)
			, view()
			, projection()
			, position(Vector3::Zero)
		{
			view = Matrix4x4::lookAtLH(eye, target, up);
			projection = Matrix4x4::orthographicLH(viewWidth, viewHeight, nearZ, farZ);
		}
		~Camera2D() = default;

		void setPosition(float _x, float _y) {
			position.set(_x, _y, 0.0f);

			eye += position;
			target += position;
		}

		Matrix4x4& getView() {
			view = Matrix4x4::lookAtLH(eye, target, up);
			return view;
		}

		Matrix4x4& getProjection() {
			return projection;
		}

	private:
		float nearZ;
		float farZ;

		float viewWidth;
		float viewHeight;

		Vector3 eye;
		Vector3 target;
		Vector3 up;

		Matrix4x4 view;
		Matrix4x4 projection;

		Vector3 position;
	};

}
*/



/*
void gnMain() {
	using namespace engine;

	try {
		Engine()->init();
	}
	catch (const std::exception&) {
		return;
	}

	auto tx = Texture::create(L"Test/char.png");
	auto w = Texture::create(L"Test/WaddleDee.PNG");
	Sprite sp{ tx }, sp1{ tx }, sp2{ w };
	sp.setPosition({ 100.0f, 1.0f, -1.0f });
	sp2.setPosition({ -50.f, 0, 1.0f });

	Camera2D cam{};
	cam.setPosition(50, 0);

	MatrixBuffer matrix{};
	matrix.view = cam.getView();
	matrix.projection = cam.getProjection();

	ConstantBuffer cBuffer{};
	cBuffer.init(&matrix, sizeof(MatrixBuffer));

	float z = 0.0f;

	float f = 0.0f;
	while (EngineWindow()->update()) {
		Engine()->begin();

		EnginePipeline2D()->setPipeline(0);

		auto commandList = EngineCommand()->get();

		matrix.view = cam.getView();
		matrix.projection = cam.getProjection();
		cBuffer.update(&matrix, sizeof(MatrixBuffer));
		commandList->SetGraphicsRootConstantBufferView(0, cBuffer.getGPUVirtualAddress());

		sp2.setPosition({ 0, 0, z });
		sp2.draw();

		sp.setRotation(Quaternion::rotationAxis({ 0, 0, 1 }, f));
		// sp.setScale({ 256, 256, 1 });
		sp.draw();

		if (Input::getKey(Key::W)) {
			cam.setPosition(0, -2);
		}

		if (Input::getKey(Key::S)) {
			cam.setPosition(0, 2);
		}

		if (Input::getKey(Key::A)) {
			cam.setPosition(2, 0);
		}

		if (Input::getKey(Key::D)) {
			cam.setPosition(-2, 0);
		}

		Engine()->end();
		Sleep(1);
		f += 0.02f;
	}
}
*/