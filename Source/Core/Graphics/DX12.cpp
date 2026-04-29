#include "stdafx.h"
#include "DX12.h"
#include "d3dx12.h" // helper classes for barriers, handles, etc.

#include <stdexcept>

using namespace Microsoft::WRL;

RF::DX12::~DX12() {
    // Ensure GPU is finished before destroying resources
    mFenceValue++;
    HRESULT hr = mCommandQueue->Signal(mFence.Get(), mFenceValue);

    if (mFence->GetCompletedValue() < mFenceValue) {
        hr = mFence->SetEventOnCompletion(mFenceValue, mFenceEvent);
        WaitForSingleObject(mFenceEvent, INFINITE);
    }
    CloseHandle(mFenceEvent);
}

void RF::DX12::Init(const HWND hwnd, const uint32_t width, const uint32_t height) {
    UINT dxgiFactoryFlags = 0;

#if defined(_DEBUG)
    // Enable debug layer in debug builds (gives better validation messages)
    {
        ComPtr<ID3D12Debug> debugController;
        if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
            debugController->EnableDebugLayer();
            dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
        }
    }
#endif

    // Create DXGI factory (manages adapters, swap chains)
    ComPtr<IDXGIFactory4> factory;
    if (FAILED(CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&factory))))
        throw std::runtime_error("Failed to create DXGI Factory");

    // Create the D3D12 device (nullptr = default hardware adapter)
    if (FAILED(D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&mDevice))))
        throw std::runtime_error("Failed to create D3D12 device");

    // Setup command queue/allocator/list
    CreateCommandObjects();

    // Create swap chain tied to window
    CreateSwapChain(hwnd, width, height);

    // Create render target views for each back buffer
    CreateRTV();

    // Fence for GPU/CPU synchronization
    if (FAILED(mDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&mFence))))
        throw std::runtime_error("Failed to create fence");

    mFenceValue = 0;
    mFenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
    if (!mFenceEvent)
        throw std::runtime_error("Failed to create fence event");

    // Get the current back buffer index
    mFrameIndex = mSwapChain->GetCurrentBackBufferIndex();
}

void RF::DX12::Render(const FrameData& frameData)
{
    frameData;

    // Reset allocator and command list each frame
    HRESULT hr = mCommandAllocator->Reset();
    hr = mCommandList->Reset(mCommandAllocator.Get(), nullptr);

    // Transition back buffer from "present" to "render target"
    CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
        mRenderTargets[mFrameIndex].Get(),
        D3D12_RESOURCE_STATE_PRESENT,
        D3D12_RESOURCE_STATE_RENDER_TARGET);
    mCommandList->ResourceBarrier(1, &barrier);

    // Get the RTV for the current back buffer
    const CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(
        mRtvHeap->GetCPUDescriptorHandleForHeapStart(),
        static_cast<int>(mFrameIndex),
        mRtvDescriptorSize);

    // Clear screen to a color (similar to ClearRenderTargetView in DX11)
    constexpr FLOAT clearColor[] = { 0.2f, 0.4f, 0.6f, 1.0f };
    mCommandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);

    // Transition back buffer back to "present" state
    barrier = CD3DX12_RESOURCE_BARRIER::Transition(
        mRenderTargets[mFrameIndex].Get(),
        D3D12_RESOURCE_STATE_RENDER_TARGET,
        D3D12_RESOURCE_STATE_PRESENT);
    mCommandList->ResourceBarrier(1, &barrier);

    // Close and execute command list
    hr = mCommandList->Close();
    ID3D12CommandList* ppCommandLists[] = { mCommandList.Get() };
    mCommandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

    // Present back buffer to screen (vsync = 1)
    hr = mSwapChain->Present(1, 0);
    mFrameIndex = mSwapChain->GetCurrentBackBufferIndex();

    // Fence synchronization: ensure CPU doesn't get too far ahead of GPU
    mFenceValue++;
    hr = mCommandQueue->Signal(mFence.Get(), mFenceValue);

    if (mFence->GetCompletedValue() < mFenceValue)
    {
        hr = mFence->SetEventOnCompletion(mFenceValue, mFenceEvent);
        WaitForSingleObject(mFenceEvent, INFINITE);
    }
}

void RF::DX12::CreateCommandObjects() {
    // Describe command queue (like immediate context in DX11)
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT; // direct = can do all ops

    // Create the GPU command queue
    if (FAILED(mDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&mCommandQueue))))
        throw std::runtime_error("Failed to create command queue");

    // Command allocator (reusable memory for command lists)
    if (FAILED(mDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&mCommandAllocator))))
        throw std::runtime_error("Failed to create command allocator");

    // Command list (records commands, submitted to GPU)
    if (FAILED(mDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, mCommandAllocator.Get(), nullptr, IID_PPV_ARGS(&mCommandList))))
        throw std::runtime_error("Failed to create command list");

    // Close immediately; we only open it per-frame
    HRESULT hr = mCommandList->Close();
    if (FAILED(hr))
		throw std::runtime_error("Failed to close command list");
}

void RF::DX12::CreateSwapChain(const HWND hwnd, const uint32_t width, const uint32_t height) {
    ComPtr<IDXGIFactory4> factory;
    HRESULT hr = CreateDXGIFactory1(IID_PPV_ARGS(&factory));
    if (FAILED(hr))
		throw std::runtime_error("Failed to create DXGI Factory");

    // Swap chain description (like DXGI_SWAP_CHAIN_DESC in DX11 but v1.6+)
    DXGI_SWAP_CHAIN_DESC1 swapDesc = {};
    swapDesc.BufferCount = FRAME_COUNT;
    swapDesc.Width = width;
    swapDesc.Height = height;
    swapDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 32-bit color
    swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // modern, efficient
    swapDesc.SampleDesc.Count = 1; // no MSAA

    // Create swap chain for HWND
    ComPtr<IDXGISwapChain1> swapChain1;
    if (FAILED(factory->CreateSwapChainForHwnd(mCommandQueue.Get(), hwnd, &swapDesc, nullptr, nullptr, &swapChain1)))
        throw std::runtime_error("Failed to create swap chain");

    // Upgrade to IDXGISwapChain3 for modern features
    if (FAILED(swapChain1.As(&mSwapChain)))
        throw std::runtime_error("Failed to cast swap chain");

    mFrameIndex = mSwapChain->GetCurrentBackBufferIndex();
}

void RF::DX12::CreateRTV() {
    // Create descriptor heap for render target views (like RTV array in DX11)
    D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
    rtvHeapDesc.NumDescriptors = FRAME_COUNT;
    rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

    if (FAILED(mDevice->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&mRtvHeap))))
        throw std::runtime_error("Failed to create RTV heap");

    // RTV handle size (increment for each back buffer)
    mRtvDescriptorSize = mDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

    // First RTV handle in heap
    CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(mRtvHeap->GetCPUDescriptorHandleForHeapStart());

    // Create RTV for each swap chain buffer
    for (UINT i = 0; i < FRAME_COUNT; i++) {
        if (FAILED(mSwapChain->GetBuffer(i, IID_PPV_ARGS(&mRenderTargets[i]))))
            throw std::runtime_error("Failed to get swap chain buffer");

        mDevice->CreateRenderTargetView(mRenderTargets[i].Get(), nullptr, rtvHandle);

        // Move handle to next descriptor slot
        rtvHandle.Offset(1, mRtvDescriptorSize);
    }
}
