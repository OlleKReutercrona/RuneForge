#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <dxgi1_6.h>
#include "IRenderer.h"

namespace RF {
	class DX11 : public IRenderer {
	public:
		DX11(const HWND hwnd, const uint32_t width, const uint32_t height);
		~DX11();

		virtual void Render(const FrameData& frameData);
	private:
		void CreateDeviceAndSwapChain(const HWND hwnd, const uint32_t width, const uint32_t height);
		void CreateRenderTargetView();
		void CreateViewport(const uint32_t width, const uint32_t height);

		uint32_t mWidth;
		uint32_t mHeight;

		Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
		Microsoft::WRL::ComPtr<IDXGISwapChain> pSwap;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pDefaultTarget;
	};
}
