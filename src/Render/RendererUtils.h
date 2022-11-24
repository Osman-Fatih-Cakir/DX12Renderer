#pragma once

#include <d3d12.h>
#include <exception>

inline void ThrowIfFailed(HRESULT hr)
{
  if (FAILED(hr))
  {
    throw std::exception();
  }
}
