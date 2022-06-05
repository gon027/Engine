#pragma once

#include <string>
#include <memory>
#include <include/Common/Common.hpp>

#define Engine()             EngineCore::get()
#define EngineWindow()       EngineCore::get()->getWindow()
#define EngineFactory()      EngineCore::get()->getFactory()
#define EngineDevice()       EngineCore::get()->getDevice()
#define EngineCommand()      EngineCore::get()->getCommandList()
#define EngineCommandQueue() EngineCore::get()->getCommandQueue()
#define EngineRenderTarget() EngineCore::get()->getRenderTarget()
#define EnginePipeline2D()   EngineCore::get()->getRenderingPipeline2D()
#define EngineKeyBoard()     EngineCore::get()->getKeyBoard()
#define EngineMouse()        EngineCore::get()->getMouse()
#define EngineCamera2D()     EngineCore::get()->getCamera2D()

namespace engine {

	class Window;
	class Factory;
	class Device;
	class CommandList;
	class CommandQueue;
	class RenderTarget;
	class RenderingPipeline2D;
	class KeyBoard;
	class Mouse;
	class Camera2D;

	class EngineCore : public Singleton<EngineCore> {
        friend Singleton<EngineCore>;

	public:
		void init(const std::string& _title, int _width, int _height);

		void begin();

		void end();

		Window* getWindow() const;
		Factory* getFactory() const;
		Device* getDevice() const;
		CommandList* getCommandList() const;
		CommandQueue* getCommandQueue() const;
		RenderTarget* getRenderTarget() const;
		RenderingPipeline2D* getRenderingPipeline2D() const;
		KeyBoard* getKeyBoard() const;
		Mouse* getMouse() const;
		Camera2D* getCamera2D() const;

	protected:
		EngineCore();
		~EngineCore();

	private:
		EngineCore(const EngineCore&);
		EngineCore(EngineCore&&);

	private:
		std::unique_ptr<Window>              window;
		std::unique_ptr<Factory>             factory;
		std::unique_ptr<Device>              device;
		std::unique_ptr<CommandList>         commandList;
		std::unique_ptr<CommandQueue>        commandQueue;
		std::unique_ptr<RenderTarget>        renderTarget;
		std::unique_ptr<RenderingPipeline2D> renderingPipeline2d;
		std::unique_ptr<KeyBoard>            keyBoard;
		std::unique_ptr<Mouse>               mouse;
		std::unique_ptr<Camera2D>            camera;
	};

}