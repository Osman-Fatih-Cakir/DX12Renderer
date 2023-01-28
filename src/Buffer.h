#pragma once

#include <d3d12.h>

namespace WoohooDX12
{
  class UploadBuffer
  {
  public:
    void Create(ID3D12Device* device, UINT width, UINT height, const char* name);
    void Destroy();

    void AllocBuffer(void* bufferData, UINT size);
  public:
    ID3D12Resource* m_buffer = nullptr;
    char* m_data = nullptr;
  };
}