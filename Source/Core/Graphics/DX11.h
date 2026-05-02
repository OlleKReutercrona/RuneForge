#pragma once
#include "IRenderer.h"

#include <wrl.h>
#include <d3d11.h>
#include <dxgi1_6.h>

namespace RF {
	class DX11 : public IRenderer {
	public:
		DX11(const HWND hwnd, const uint32_t width, const uint32_t height);
		~DX11();

		virtual void Render(const FrameData& frameData);
	private:
		HRESULT CreateDeviceAndSwapChain(const HWND hwnd, const uint32_t width, const uint32_t height);
		HRESULT CreateRenderTargetView();
		void SetViewport(const uint32_t width, const uint32_t height);

		uint32_t mWidth;
		uint32_t mHeight;

		Microsoft::WRL::ComPtr<ID3D11Device> mDevice;
		Microsoft::WRL::ComPtr<IDXGISwapChain> mSwap;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> mContext;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mDefaultTarget;
	};
}
