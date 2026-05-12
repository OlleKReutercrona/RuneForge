#pragma once
#include "IRenderer.h"

#include <wrl.h>
#include <d3d11.h>

namespace RF {
	struct DX11CreationParams {
		HWND hwnd;
		uint32_t width;
		uint32_t height;
		//Colour clearColour = { 0.2f, 0.4f, 0.6f, 1.0f };
		bool startInFullScreen = false;
	};

	class DX11 : public IRenderer {
	public:
		DX11(const DX11CreationParams& params);
		~DX11();

		DX11() = delete;
		DX11(const DX11&) = delete;
		void operator=(const DX11&) = delete;

		virtual void Render(const FrameData& frameData);
	private:
		HRESULT CreateDeviceAndSwapChain(const HWND hwnd, const uint32_t width, const uint32_t height);
		HRESULT CreateRenderTargetView();
		void SetViewport(const uint32_t width, const uint32_t height);

		uint32_t mWidth;
		uint32_t mHeight;
		//Colour mClearColour;

		Microsoft::WRL::ComPtr<ID3D11Device> mDevice;
		Microsoft::WRL::ComPtr<IDXGISwapChain> mSwap;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> mContext;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mDefaultTarget;
	};
}
