#include "Buffer.h"
#include "RendererUtils.h"

namespace WoohooDX12
{
  void UploadBuffer::Create(ID3D12Device* device, UINT width, UINT height, const char* name)
  {
    D3D12_HEAP_PROPERTIES heapProps = {};
    heapProps.Type = D3D12_HEAP_TYPE_UPLOAD;
    heapProps.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    heapProps.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    heapProps.CreationNodeMask = 1;
    heapProps.VisibleNodeMask = 1;

    D3D12_RESOURCE_DESC bufferResourceDesc = {};
    bufferResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    bufferResourceDesc.Alignment = 0;
    bufferResourceDesc.Width = width;
    bufferResourceDesc.Height = height;
    bufferResourceDesc.DepthOrArraySize = 1;
    bufferResourceDesc.MipLevels = 1;
    bufferResourceDesc.Format = DXGI_FORMAT_UNKNOWN;
    bufferResourceDesc.SampleDesc.Count = 1;
    bufferResourceDesc.SampleDesc.Quality = 0;
    bufferResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    bufferResourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

    ThrowIfFailed(device->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE, &bufferResourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&m_buffer)));

    SetName(m_buffer, "%s", name);

    // We do not intend to read from this resource on the CPU. (End is less than or equal to begin)
    D3D12_RANGE readRange = {};
    readRange.Begin = 0;
    readRange.End = 0;

    m_buffer->Map(0, &readRange, reinterpret_cast<void**>(&m_data));
  }

  void UploadBuffer::Destroy()
  {
    if (m_buffer)
    {
      m_buffer->Release();
      m_buffer = nullptr;
    }
  }

  void UploadBuffer::AllocBuffer(void* bufferData, UINT size)
  {
    D3D12_RANGE readRange = {};
    readRange.Begin = 0;
    readRange.End = 0;

    memcpy(m_data, bufferData, size);
    m_buffer->Unmap(0, &readRange);
  }
}