#include "Buffer.h"
#include "RendererUtils.h"

namespace WoohooDX12
{
  void Buffer::Create(ID3D12Device* device, UINT width, UINT height, const char* name)
  {
    D3D12_HEAP_PROPERTIES heapProps = {};
    heapProps.Type = D3D12_HEAP_TYPE_UPLOAD;
    heapProps.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    heapProps.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    heapProps.CreationNodeMask = 1;
    heapProps.VisibleNodeMask = 1;

    D3D12_RESOURCE_DESC vertexBufferResourceDesc = {};
    vertexBufferResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    vertexBufferResourceDesc.Alignment = 0;
    vertexBufferResourceDesc.Width = width;
    vertexBufferResourceDesc.Height = height;
    vertexBufferResourceDesc.DepthOrArraySize = 1;
    vertexBufferResourceDesc.MipLevels = 1;
    vertexBufferResourceDesc.Format = DXGI_FORMAT_UNKNOWN;
    vertexBufferResourceDesc.SampleDesc.Count = 1;
    vertexBufferResourceDesc.SampleDesc.Quality = 0;
    vertexBufferResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    vertexBufferResourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

    ThrowIfFailed(device->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE, &vertexBufferResourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&m_resource)));

    SetName(m_resource, "%s", name);

    m_resource->Map(0, NULL, reinterpret_cast<void**>(&m_data));
  }

  void Buffer::Destroy()
  {
    if (m_resource)
    {
      m_resource->Release();
      m_resource = nullptr;
    }
  }

  void Buffer::AllocBuffer(void* bufferData, UINT size)
  {
    memcpy(m_data, bufferData, size);
    m_resource->Unmap(0, nullptr);
  }
}