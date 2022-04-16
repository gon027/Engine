/*

#include "EngineMain/EngineMain.hpp"
#include "../engine/include/Window/Window.hpp"
#include "../engine/include/Graphics/Device.hpp"
#include "../engine/include/EngineCore/EngineCore.hpp"
#include "../engine/include/Graphics/CommandList.hpp"
#include "../engine/include/Type/Type.hpp"
#include "../engine/include/Vertex/Vertex2D.hpp"
#include "../engine/include/Mesh/Mesh.hpp"
#include "../engine/include/MatrixBuffer/MatrixBuffer.hpp"
#include "../engine/include/Graphics/RenderingPipeline2D.hpp"
#include "../engine/include/Graphics/ConstantBuffer.hpp"
#include "../engine/include/Transform/Transform.hpp"
#include "../engine/include/Input/Input.hpp"
#include <vector>
#include "../engine/include/Asset/AssetPath.hpp"
#include "../engine/include/Graphics/PixelShader.hpp"

#include "../../../MathLib/MathLib/Math/include/Math.hpp"
#pragma comment(lib, "C:/Users/USER/source/repos/MathLib/x64/Debug/MathLib.lib")
using namespace gnLib;
using namespace engine;

#include "../../Engine/engine/Lib/DirectXTex/DirectXTex.h"
#pragma comment(lib, "C:/Users/USER/source/repos/Engine/Engine/engine/Lib/DirectXTex/x64/Debug/DirectXTex.lib")

#include "../engine/include/Texture/Texture.hpp"
#include "../engine/include/Sprite/Sprite.hpp"

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

	MatrixBuffer matrix{};
	{
		matrix.view = Matrix4x4::lookAtLH(
			{ 0, 0, -10 }, { 0, 0, 0 }, { 0, 1, 0 }
		);
		matrix.projection = Matrix4x4::orthographicLH(
			640.0f, 480.0f, 1.0f, 100.0f
		);
	}
	
	ConstantBuffer cBuffer{};
	cBuffer.init(&matrix, sizeof(MatrixBuffer));

	float z = 0.0f;

	float f = 0.0f;
	while (EngineWindow()->update()) {
		Engine()->begin();

		EnginePipeline2D()->setPipeline(0);

		auto commandList = EngineCommand()->get();

		cBuffer.update(&matrix, sizeof(MatrixBuffer));
		commandList->SetGraphicsRootConstantBufferView(0, cBuffer.getGPUVirtualAddress());

		sp.setRotation(Quaternion::rotationAxis({ 0, 0, 1 }, f));
		// sp.setScale({ 256, 256, 1 });
		sp.draw();

		if (Input::getKey(Key::W)) {
			z += 1.0f;
		}

		if (Input::getKey(Key::S)) {
			z -= 1.0f;
		}

		sp2.setPosition({ 0, 0, z });
		sp2.draw();



		Engine()->end();
		Sleep(1);
		f += 0.02f;
	}
}
*/