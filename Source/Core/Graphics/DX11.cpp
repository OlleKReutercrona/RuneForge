#include "stdafx.h"
#include "DX11.h"

#include <stdexcept>

using namespace Microsoft::WRL;

RF::DX11::~DX11() {
}

void RF::DX11::Init(const HWND hwnd, const uint32_t width, const uint32_t height) {
	mWidth = width;
	mHeight = height;

	CreateDeviceAndSwapChain(hwnd, width, height);
	CreateRenderTargetView();
	CreateViewport(width, height);

	mInitialized = true;
}

void RF::DX11::CreateDeviceAndSwapChain(const HWND hwnd, const uint32_t width, const uint32_t height) {
	DXGI_SWAP_CHAIN_DESC scd = {};
	scd.BufferDesc.Width = width;
	scd.BufferDesc.Height = height;
	scd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	scd.BufferDesc.RefreshRate.Numerator = 0u;
	scd.BufferDesc.RefreshRate.Denominator = 0u;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.SampleDesc.Count = 1u; // Anti-aliasing
	scd.SampleDesc.Quality = 0u; // Anti-aliasing
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferCount = 1u; // 1 back buffer and 1 front buffer
	scd.OutputWindow = hwnd;
	scd.Windowed = true;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Flags = 0u;

	UINT swapCreateFlags = 0u;
#ifndef NDEBUG
	swapCreateFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		swapCreateFlags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&scd,
		&pSwap,
		&pDevice,
		nullptr,
		&pContext
	);
}

void RF::DX11::CreateRenderTargetView() {
	// Gain access to texture subresource in swap chains (back buffer)
	Microsoft::WRL::ComPtr<ID3D11Resource> pBackBuffer;
	pSwap->GetBuffer(0u, __uuidof(ID3D11Resource), &pBackBuffer);
	pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &pDefaultTarget);
}

void RF::DX11::CreateViewport(const uint32_t width, const uint32_t height) {
	D3D11_VIEWPORT vp = {};
	vp.Width = static_cast<FLOAT>(width);
	vp.Height = static_cast<FLOAT>(height);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	pContext->RSSetViewports(1u, &vp);
}

void RF::DX11::Render(const FrameData& frameData) {
	frameData;

	if (!mInitialized) {
		throw std::runtime_error("Renderer not initialized");
	}

	// Clear the back buffer to a color (RGBA)
	const FLOAT clearColor[] = { 0.2f, 0.4f, 0.6f, 1.0f };
	pContext->ClearRenderTargetView(pDefaultTarget.Get(), clearColor);
	// Present the back buffer to the screen
	pSwap->Present(1u, 0u);
}
