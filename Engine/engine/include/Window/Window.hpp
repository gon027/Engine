#pragma once

#include <Windows.h>
#include <string>

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

	class Window {
	public:
		Window();
		~Window();

		bool init(const string& _title, int _width, int _height);

		bool update();

		void setTitle(const string& _title);

		void resizeWindow(int _x, int _y);

		void setWindowPosition(int _x, int _y);
		
		bool isClose() const;

		inline const int getWidth() const {
			return windowSize.width;
		}

		inline const int getHeight() const {
			return windowSize.height;
		}

		inline const string getTitle() const {
			return title;
		}

		inline const HINSTANCE getHInstance() const {
			return hInstance;
		}

		inline const HWND getHWnd() const {
			return hwnd;
		}

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