#pragma once

#include <d3d12.h>
#include <exception>
#include "Types.h"

inline void ThrowIfFailed(HRESULT hr)
{
  if (FAILED(hr))
  {
    throw std::exception();
  }
}

// https://github.com/vilbeyli/VQEngine/blob/e309621b9b91622f06554324654c8a61f02c7c76/Source/Renderer/Common.h
inline void SetName(ID3D12Object* pObj, const char* format, const char* args, ...)
{
	char bufName[240];
	sprintf_s(bufName, format, args);
	std::string Name = bufName;
	std::wstring wName(Name.begin(), Name.end());
	pObj->SetName(wName.c_str());
}