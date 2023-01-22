#pragma once

#include <Windows.h>
#include <string>
#include "../../include/IWindow.hpp"

using std::string;

namespace engine {

	struct WindowPosition {
		int x;
		int y;
	};

	struct WindowSize {
		int width;
		int height;
	};

	class Window : public core::IWindow {
	public:
		Window();
		~Window();

		bool init(const string& _title, int _width, int _height) override;

		bool update() const override;

		void setTitle(const string& _title) override;

		void resizeWindow(int _x, int _y) override;

		void setWindowPosition(int _x, int _y) override;
		
		bool isClose() const override;

		int getWidth() const override {
			return windowSize.width;
		}

		int getHeight() const override {
			return windowSize.height;
		}

		string getTitle() const override {
			return title;
		}

		void* getInstance() const override {
			return hInstance;
		}

		void* getHandle() const override {
			return hwnd;
		} 

		/*
		inline const HINSTANCE getHInstance() const {
			return hInstance;
		}

		inline const HWND getHWnd() const {
			return hwnd;
		}
		*/

	protected:
		bool registerWindow();

		bool showWindow();

	private:
		WNDCLASSEX winc;
		HINSTANCE hInstance;
		HWND hwnd;

		WindowPosition windowPosition;
		WindowSize windowSize;

		string title;
	};

}