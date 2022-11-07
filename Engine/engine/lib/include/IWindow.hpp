#pragma once

#include <string>
#include <memory>

namespace engine {

	namespace core {

		class IWindow {
		protected:
			using string = std::string;
			using const_string = const std::string;

		public:
			virtual ~IWindow() = default;

			virtual bool init(const_string& _title, int _width, int _height) = 0;

			virtual bool update() const = 0;

			virtual void setTitle(const_string& _title) = 0;

			virtual void resizeWindow(int _x, int _y) = 0;

			virtual void setWindowPosition(int _x, int _y) = 0;

			virtual bool isClose() const = 0;

			virtual int getWidth() const = 0;

			virtual int getHeight() const = 0;

			virtual string getTitle() const = 0;
		};

	}

	std::shared_ptr<core::IWindow> createWindow();

}