#include "stdafx.h"
#include "DX11.h"
#include <stdexcept>

using namespace Microsoft::WRL;

RF::DX11::DX11(const DX11CreationParams& params) :
	mWidth(params.width),
	mHeight(params.height) {
	//mClearColour(params.clearColour) {
	if (FAILED(CreateDeviceAndSwapChain(params.hwnd, params.width, params.height)))
		throw std::runtime_error("Failed to create Direct3D 11 device and swap chain.");

	if (FAILED(CreateRenderTargetView()))
		throw std::runtime_error("Failed to create Direct3D 11 render target view.");

	SetViewport(mWidth, mHeight);
}

RF::DX11::~DX11() {
}

HRESULT RF::DX11::CreateDeviceAndSwapChain(const HWND hwnd, const uint32_t width, const uint32_t height) {
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

	return D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		swapCreateFlags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&scd,
		&mSwap,
		&mDevice,
		nullptr,
		&mContext
	);
}

HRESULT RF::DX11::CreateRenderTargetView() {
	HRESULT hr = S_OK;

	Microsoft::WRL::ComPtr<ID3D11Resource> backBuffer;
	hr = mSwap->GetBuffer(0u, __uuidof(ID3D11Resource), &backBuffer);
	if (FAILED(hr))
		return hr;

	hr = mDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, &mDefaultTarget);
	return hr;
}

void RF::DX11::SetViewport(const uint32_t width, const uint32_t height) {
	D3D11_VIEWPORT vp = {};
	vp.Width = static_cast<FLOAT>(width);
	vp.Height = static_cast<FLOAT>(height);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	mContext->RSSetViewports(1u, &vp);
}

void RF::DX11::Render(const FrameData&) {
	const FLOAT clearColor[] = { 0.2f, 0.4f, 0.6f, 1.0f };
	mContext->ClearRenderTargetView(mDefaultTarget.Get(), clearColor);
	mSwap->Present(1u, 0u);
}
