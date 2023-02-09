#pragma once

#define DX12DEBUG

#include <d3d12.h>
#include <dxgi1_3.h>
#include <dxgi1_4.h>
#include <d3dcompiler.h>
#include <chrono>
#include "Utils.h"
#include "AppWindow.h"
#include "Types.h"
#include "Buffer.h"

namespace WoohooDX12
{
  struct Vertex
  {
    float position[3];
    float color[3];
  };

  // TODO Use MVP matrix (calculate matrix on CPU instead of every vertex)
  // Uniform data
  struct uboVS
  {
    Mat projectionMatrix;
    Mat viewMatrix;
    Mat modelMatrix;
  };

  class Renderer
  {
  public:
    Renderer(AppWindow* window);
    ~Renderer();

    void Init();
    void UnInit();

    void Resize(UINT width, UINT height);

    void Render();

  protected:
    void InitAPI();
    void InitResources();
    void SetupRenderCommands();
    void InitFrameBuffer();
    void CompileShaders(ID3DBlob** vertexShader, ID3DBlob** fragmentShader);
    void CreateCommands();

    void UploadResourcesToGPU();
    void SetupSwapchain(UINT width, UINT height);

    void DestroyAPI();
    void DestroyResources();
    void DestroyCommands();
    void DestroyFrameBuffer();

  public:
    constexpr static Vertex m_vertexBufferData[3] =
    {
      {{0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
      {{0.5f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
      {{-0.5f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}}
    };

    constexpr static UINT m_indexBufferData[3] = { 0, 1, 2 };
    static const UINT m_backbufferCount = 2;

    AppWindow* m_window = nullptr;

    std::chrono::time_point<std::chrono::steady_clock> m_timeStart, m_timeEnd;
    float m_elapsedTime = 0.0f;
    uboVS m_ubo;

    // Graphics API structures
    IDXGIFactory4* m_factory = nullptr;
    IDXGIAdapter1* m_adapter = nullptr;
#ifdef DX12DEBUG
    ID3D12Debug1* m_debugController = nullptr;
    ID3D12DebugDevice* m_debugDevice = nullptr;
#endif

    ID3D12Device* m_device = nullptr;
    ID3D12CommandQueue* m_commandQueue = nullptr;
    ID3D12CommandAllocator* m_commandAllocator = nullptr;
    ID3D12GraphicsCommandList* m_commandList = nullptr;

    // Current Frame
    UINT m_currentBuffer = 0;
    ID3D12DescriptorHeap* m_rtvHeap = nullptr;
    ID3D12Resource* m_renderTargets[m_backbufferCount];
    IDXGISwapChain3* m_swapchain = nullptr;

    UINT m_width = 640;
    UINT m_height = 480;

    // Resources
    D3D12_VIEWPORT m_viewport;
    D3D12_RECT m_surfaceSize;

    StaticBufferHeap* m_vertexBuffer = nullptr;
    StaticBufferHeap* m_indexBuffer = nullptr;

    StaticBufferHeap* m_uniformBuffer = nullptr;
    ID3D12DescriptorHeap* m_uniformBufferHeap = nullptr;
    UINT8* m_mappedUniformBuffer = nullptr;

    D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;
    D3D12_INDEX_BUFFER_VIEW m_indexBufferView;

    UINT m_rtvDescriptorSize;
    ID3D12RootSignature* m_rootSignature = nullptr;
    ID3D12PipelineState* m_pipelineState = nullptr;

    // Sync
    UINT m_frameIndex;
    HANDLE m_fenceEvent;
    ID3D12Fence* m_fence = nullptr;
    UINT64 m_fenceValue;
  };
} // namespace WoohooDX12
