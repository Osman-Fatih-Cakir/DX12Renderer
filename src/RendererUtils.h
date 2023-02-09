#pragma once

#include <d3d12.h>
#include <exception>
#include "Types.h"

namespace WoohooDX12
{
	enum class BufferType
	{
		BT_VertexBuffer = 0,
		BT_IndexBuffer = 1,
		BT_ConstantBuffer = 2,
	};

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

	inline D3D12_RESOURCE_STATES GetResourceTransitionState(BufferType bufferType)
	{
		D3D12_RESOURCE_STATES s;
		switch (bufferType)
		{
		case BufferType::BT_ConstantBuffer:
			s = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
			break;
		case BufferType::BT_VertexBuffer:
			s = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
			break;
		case BufferType::BT_IndexBuffer:
			s = D3D12_RESOURCE_STATE_INDEX_BUFFER;
			break;
		default:
			assert(false);
			break;
		}
		return s;
	}

	// https://github.com/vilbeyli/VQEngine/blob/e309621b9b91622f06554324654c8a61f02c7c76/Source/Renderer/Common.h
	template<class T>
	T AlignOffset(const T& uOffset, const T& uAlign) { return ((uOffset + (uAlign - 1)) & ~(uAlign - 1)); }
}