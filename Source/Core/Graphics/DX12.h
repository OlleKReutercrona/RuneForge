#pragma once
#include <wrl.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include "IRenderer.h"

namespace RF {
	class DX12 : public IRenderer {
	public:
		DX12(const HWND hwnd, const uint32_t width, const uint32_t height);
		~DX12();

		// Render one frame (clear the screen and present)
		virtual void Render(const FrameData& frameData);

	private:
		// Create GPU command objects (queue, allocator, list)
		void CreateCommandObjects();

		// Create swap chain (back buffers tied to HWND)
		void CreateSwapChain(HWND hwnd, uint32_t width, uint32_t height);

		// Create Render Target Views for swap chain back buffers
		void CreateRTV();

	private:
		static constexpr uint32_t FRAME_COUNT = 2; // double buffering

		// Core D3D12 objects
		Microsoft::WRL::ComPtr<ID3D12Device> mDevice;
		Microsoft::WRL::ComPtr<IDXGISwapChain3> mSwapChain;
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> mCommandQueue;
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> mCommandAllocator;
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> mCommandList;

		// Render target descriptor heap + back buffer resources
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mRtvHeap;
		Microsoft::WRL::ComPtr<ID3D12Resource> mRenderTargets[FRAME_COUNT];

		// Fence for CPU/GPU synchronization
		Microsoft::WRL::ComPtr<ID3D12Fence> mFence;

		// RTV size increment (used for descriptor heap offsets)
		UINT mRtvDescriptorSize = 0;

		// Current back buffer index
		UINT mFrameIndex = 0;

		// Sync objects
		HANDLE mFenceEvent = 0;
		UINT64 mFenceValue = 0;
	};
}
