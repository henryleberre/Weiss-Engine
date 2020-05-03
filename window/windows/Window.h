#pragma once

#include "Peripheral.h"
#include "../common/Include.h"
#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS {

	namespace WIN {

		LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lparam);

		class WindowsWindow : public Window {
			friend LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lparam);

		private:
			HWND m_handle = 0;

		public:
			WindowsWindow(const WindowDescriptor& descriptor);

			[[nodiscard]] HWND GetHandle()              const noexcept;
			[[nodiscard]] HDC  GetDeviceContextHandle() const noexcept;

			[[nodiscard]] virtual Rect GetWindowRectangle() const override;
			[[nodiscard]] virtual Rect GetClientRectangle() const override;

			[[nodiscard]] LRESULT HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam);

			virtual void SetWindowSize(const uint16_t width, const uint16_t height) override;

			virtual void SetClientSize(const uint16_t width, const uint16_t height) override;

			virtual void SetTitle(const char* title) const noexcept override;

			virtual void SetIcon(const char* pathname) override;

			virtual void Update() override;

			void Destroy() noexcept;

			~WindowsWindow();
		};

	}; // WIN

}; // WS

#endif // __WEISS__OS_WINDOWS