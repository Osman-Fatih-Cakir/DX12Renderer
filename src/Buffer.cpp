#include "Buffer.h"
#include "RendererUtils.h"
#include "d3dx12.h"
#include "Utils.h"

namespace WoohooDX12
{
  void StaticBufferHeap::Create(ID3D12Device* device, bool useVideoMem, BufferType type, uint32 memorySize, const char* name)
  {
    m_useVideoMem = useVideoMem;
    m_memorySize = memorySize;
    m_bufferType = type;
    m_memOffset = 0;

    if (useVideoMem)
    {
      ThrowIfFailed(device->CreateCommittedResource
      (
        &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
        D3D12_HEAP_FLAG_NONE,
        &CD3DX12_RESOURCE_DESC::Buffer(memorySize),
        GetResourceTransitionState(type),
        nullptr,
        IID_PPV_ARGS(&m_videoMemBuffer)
      ));
    }

    ThrowIfFailed(device->CreateCommittedResource
    (
      &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
      D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(memorySize),
      D3D12_RESOURCE_STATE_GENERIC_READ,
      nullptr,
      IID_PPV_ARGS(&m_uploadMemBuffer)
    ));

    SetName(m_uploadMemBuffer, "%s", name);

    // We do not intend to read from this resource on the CPU. (End is less than or equal to begin)
    D3D12_RANGE readRange = {};
    readRange.Begin = 0;
    readRange.End = 0;

    m_uploadMemBuffer->Map(0, &readRange, reinterpret_cast<void**>(&m_data));
  }

  const uint32* StaticBufferHeap::GetMemorySize()
  {
    return &m_memorySize;
  }

  void StaticBufferHeap::Destroy()
  {
    if (m_useVideoMem)
    {
      if (m_videoMemBuffer)
      {
        m_videoMemBuffer->Release();
        m_videoMemBuffer = nullptr;
      }
    }

    if (m_uploadMemBuffer)
    {
      m_uploadMemBuffer->Release();
      m_uploadMemBuffer = nullptr;
    }
  }

  bool StaticBufferHeap::AllocVertexBuffer(uint32 numOfVertices, uint32 strideInBytes, void* bufferData, D3D12_VERTEX_BUFFER_VIEW* vbv)
  {
    //OutputDebugString("VERTEX\n");
    assert(m_bufferType == BufferType::BT_VertexBuffer);

    bool success = AllocBuffer(numOfVertices, strideInBytes, bufferData, &vbv->BufferLocation, &vbv->SizeInBytes);
    vbv->StrideInBytes = success ? strideInBytes : 0;

    //OutputDebugString((std::to_string(success)+"\n").c_str());
    //OutputDebugString((std::to_string(vbv->StrideInBytes)+"\n").c_str());

    return success;
  }

  bool StaticBufferHeap::AllocIndexBuffer(uint32 numOfIndices, uint32 strideInBytes, void* bufferData, D3D12_INDEX_BUFFER_VIEW* ibv)
  {
    //OutputDebugString("INDEX\n");
    assert(m_bufferType == BufferType::BT_IndexBuffer);

    bool success = AllocBuffer(numOfIndices, strideInBytes, bufferData, &ibv->BufferLocation, &ibv->SizeInBytes);
    ibv->Format = success ? ((strideInBytes == 4) ? DXGI_FORMAT_R32_UINT : DXGI_FORMAT_R16_UINT) : DXGI_FORMAT_UNKNOWN;

    //OutputDebugString((std::to_string(success) + "\n").c_str());

    return success;
  }

  bool StaticBufferHeap::AllocConstantBuffer(uint32 numOfElements, uint32 strideInBytes, void* bufferData, D3D12_GPU_VIRTUAL_ADDRESS* bufferLocationOut, uint32* sizeOut)
  {
    //OutputDebugString("CONSTANT\n");
    assert(m_bufferType == BufferType::BT_ConstantBuffer);

    bool success = AllocBuffer(numOfElements, strideInBytes, bufferData, bufferLocationOut, sizeOut);

    //OutputDebugString((std::to_string(success) + "\n").c_str());

    return success;
  }

  bool StaticBufferHeap::AllocBuffer(uint32 numOfElements, uint32 stride, void* bufferData, D3D12_GPU_VIRTUAL_ADDRESS* bufferLocationOut, uint32* sizeOut)
  {
    uint32 alignedSize = AlignOffset(numOfElements * stride, MEMORY_ALIGNMENT);

    //OutputDebugString((std::to_string(alignedSize) + "\n").c_str());
    //OutputDebugString((std::to_string(m_memOffset) + "\n").c_str());
    //OutputDebugString((std::to_string(m_memorySize) + "\n").c_str());

    if (alignedSize + m_memOffset > m_memorySize)
    {
      Log("Static buffer heap out of memory", LogType::LT_ERROR);
      return false;
    }

    void* data = (void*)(m_data + m_memOffset);

    ID3D12Resource*& resource = m_useVideoMem ? m_videoMemBuffer : m_uploadMemBuffer;

    *bufferLocationOut = m_memOffset + resource->GetGPUVirtualAddress();

    *sizeOut = alignedSize;

    m_memOffset += alignedSize;

    memcpy(data, bufferData, static_cast<size_t>(numOfElements) * stride);

    return true;
  }

  void StaticBufferHeap::UploadData(ID3D12GraphicsCommandList* cmdList)
  {
    if (m_useVideoMem)
    {
      D3D12_RESOURCE_STATES state = GetResourceTransitionState(m_bufferType);
      cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(m_videoMemBuffer, state, D3D12_RESOURCE_STATE_COPY_DEST));

      cmdList->CopyBufferRegion(m_videoMemBuffer, m_memInit, m_uploadMemBuffer, m_memInit, m_memOffset - m_memInit);

      cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(m_videoMemBuffer, D3D12_RESOURCE_STATE_COPY_DEST, state));

      m_memInit = m_memOffset;
    }
  }
}