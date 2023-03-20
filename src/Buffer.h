#pragma once

#include "RendererUtils.h"

#include <d3d12.h>

namespace WoohooDX12
{
  constexpr static uint32 MEMORY_ALIGNMENT = 256;

  class StaticBufferHeap
  {
   public:
    void Create(ID3D12Device* device, bool useUploadHeap, BufferType type, uint32 memorySize, const char* name);
    void Destroy();

    bool AllocVertexBuffer(uint32 numOfVertices, uint32 strideInBytes, void* bufferData, D3D12_VERTEX_BUFFER_VIEW* vbv);
    bool AllocIndexBuffer(uint32 numOfIndices, uint32 strideInBytes, void* bufferData, D3D12_INDEX_BUFFER_VIEW* ibv);
    bool AllocConstantBuffer(uint32 numOfElements,
                             uint32 strideInBytes,
                             void* bufferData,
                             D3D12_GPU_VIRTUAL_ADDRESS* bufferLocationOut,
                             uint32* sizeOut);

    void UploadData(ID3D12GraphicsCommandList* cmdList);

    void UpdateBuffer(void* buffer, size_t sizeOfBuffer);

    const uint32* GetMemorySize();

   private:
    bool AllocBuffer(uint32 numOfElements,
                     uint32 stride,
                     void* bufferData,
                     D3D12_GPU_VIRTUAL_ADDRESS* bufferLocationOut,
                     uint32* sizeOut);

   public:
    ID3D12Resource* m_videoMemBuffer  = nullptr;
    ID3D12Resource* m_uploadMemBuffer = nullptr;
    char* m_data                      = nullptr;

   private:
    bool m_useVideoMem      = true;
    BufferType m_bufferType = BufferType::BT_VertexBuffer;

    uint32 m_memorySize     = 0;
    uint32 m_memOffset      = 0;
    uint32 m_memInit        = 0;
  };
} // namespace WoohooDX12