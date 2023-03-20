#pragma once

#include "Types.h"

#include <DirectXMath.h>

constexpr Vec3 ZeroVector    = Vec3(0, 0, 0);
constexpr Vec3 UpVector      = Vec3(0, 1, 0);
constexpr Vec3 RightVector   = Vec3(1, 0, 0);
constexpr Vec3 ForwardVector = Vec3(0, 0, 1);
constexpr Vec3 LeftVector    = Vec3(-1, 0, 0);
constexpr Vec3 BackVector    = Vec3(0, 0, -1);
constexpr Vec3 DownVector    = Vec3(0, -1, 0);

inline void MakeIdentity(Mat4& mat)
{
  mat._11 = 1.0f;
  mat._12 = 0.0f;
  mat._13 = 0.0f;
  mat._14 = 0.0f;
  mat._21 = 0.0f;
  mat._22 = 1.0f;
  mat._23 = 0.0f;
  mat._24 = 0.0f;
  mat._31 = 0.0f;
  mat._33 = 1.0f;
  mat._32 = 0.0f;
  mat._34 = 0.0f;
  mat._41 = 0.0f;
  mat._42 = 0.0f;
  mat._43 = 0.0f;
  mat._44 = 1.0f;
}

inline void MakeIdentity(Mat& mat) { mat = DirectX::XMMatrixIdentity(); }