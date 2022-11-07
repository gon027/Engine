#include "Window.hpp"
#include "WinProc.hpp"
#include <memory>

namespace engine {

	namespace {

		struct ScreenSize {
			int width;
			int height;
		};

		// パソコンのスクリーンのサイズを取得
		ScreenSize getScreenSize() {
			RECT rc;
			SystemParametersInfo(SPI_GETWORKAREA, 0, &rc, 0);
			return {
				rc.right - rc.left,
				rc.bottom - rc.top
			};
		}

		WindowSize getWindowSize(int _width, int _height) {
			RECT rect{ 0, 0, (LONG)_width, (LONG)_height };
			AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

			return {
				rect.right - rect.left,
				rect.bottom - rect.top
			};
		}

	}

	Window::Window()
		: winc()
		, hInstance(GetModuleHandle(NULL))
		, hwnd(nullptr)
		, windowPosition({})
		, windowSize({})
		, title()
	{
	}

	Window::~Window()
	{
		//ウインドウクラス登録解除
		UnregisterClass(winc.lpszClassName, hInstance);
	}

	bool Window::init(const string& _title, int _width, int _height)
	{
		{
			title = _title;

			windowSize = getWindowSize(_width, _height);
		}

		registerWindow();		

		showWindow();

		return true;
	}

	bool Window::update() const
	{
		MSG msg{};
		while (true) {
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {

				if (msg.message == WM_QUIT) {
					return false;
				}

				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
			else {
				return true;
			}
		}
	}

	void Window::setTitle(const string& _title)
	{
		title = _title;
		SetWindowTextA(hwnd, _title.c_str());
	}

	void Window::resizeWindow(int _x, int _y)
	{
		windowSize = getWindowSize(_x, _y);
		SetWindowPos(hwnd, 0, 0, 0, windowSize.width, windowSize.height, SWP_NOMOVE);

		auto screenSize = getScreenSize();
		windowPosition.x = (screenSize.width - windowSize.width) / 2;
		windowPosition.y = (screenSize.height - windowSize.height) / 2;
		setWindowPosition(windowPosition.x, windowPosition.y);
	}

	void Window::setWindowPosition(int _x, int _y)
	{
		windowPosition.x = _x;
		windowPosition.y = _y;
		SetWindowPos(hwnd, 0, windowPosition.x, windowPosition.y, 0, 0, SWP_NOSIZE);
	}

	bool Window::isClose() const
	{
		return IsWindow(hwnd);
	}

	bool Window::registerWindow()
	{
		winc.cbSize = sizeof(WNDCLASSEX);
		winc.style = CS_HREDRAW | CS_VREDRAW;
		winc.lpfnWndProc = engine::WindowProc;
		winc.cbClsExtra = 0;
		winc.cbWndExtra = 0;
		winc.hInstance = hInstance;
		winc.hIcon = ((HICON)LoadImage(NULL, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED));
		winc.hCursor = (HCURSOR)LoadImage(NULL, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
		winc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		winc.lpszMenuName = NULL;
		winc.lpszClassName = title.c_str();
		winc.hIconSm = NULL;

		return RegisterClassEx(&winc);
	}

	bool Window::showWindow()
	{
		hwnd = CreateWindow(
			title.c_str(),
			title.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			windowSize.width,
			windowSize.height,
			nullptr,
			nullptr,
			hInstance,
			nullptr
		);

		{
			auto screenSize = getScreenSize();
			windowPosition.x = (screenSize.width - windowSize.width) / 2;
			windowPosition.y = (screenSize.height - windowSize.height) / 2;
			setWindowPosition(windowPosition.x, windowPosition.y);
		}

		return ShowWindow(hwnd, SW_SHOW);
	}

	std::shared_ptr<core::IWindow> createWindow() {
		return std::shared_ptr<Window> {
			new Window{}
		};
	}
}