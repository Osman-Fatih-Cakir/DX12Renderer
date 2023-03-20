#pragma once

#include <DirectXMath.h>

#include <string>

using int64   = long long;
using int32   = int;
using int16   = short;
using int8    = char;
using uint64  = unsigned long long;
using uint32  = unsigned;
using uint16  = unsigned short;
using uint8   = unsigned char;
using uint    = unsigned;
using fp32    = float;

using String  = std::string;
using WString = std::wstring;
using Mat     = DirectX::XMMATRIX; // 4x4 matrix aligned on a 16-byte boundary
using Vec     = DirectX::XMVECTOR; // 4 components, 32 bit floating point
using Mat4    = DirectX::XMFLOAT4X4;
using Mat3    = DirectX::XMFLOAT3X3;
using Vec4    = DirectX::XMFLOAT4;
using Vec3    = DirectX::XMFLOAT3;
using Vec2    = DirectX::XMFLOAT2;
using UVec2   = DirectX::XMUINT2;