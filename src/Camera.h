#pragma once

#include "RendererUtils.h"

#include <d3d12.h>

namespace WoohooDX12
{
  static constexpr double CONST_CAMNEAR = 0.001, CONST_CAMFAR = 10000.0, CONST_MOUSESENSITIVITY = 0.1f;

  class Camera
  {
    DirectX::XMVECTOR pos, rot, scal, target;
    Mat viewMat, projMat;
    // Fov is in angle
    unsigned short fov = 45.0f, viewWidth = 1920.0f, viewHeight = 1080.0f;
    float nearPlane = CONST_CAMNEAR, farPlane = CONST_CAMFAR,
          mouseSensitivity = 0.001f, mouseYaw = 90.0f, mousePitch = 0.0f;

   public:
    Camera(Vec3 target = Vec3(0, 0, 1));

    // Getters
    Mat CalculateProjMat();
    Mat CalculateViewMat();

    // Setters
    void SetProperties(unsigned short fov_in_Angle,
                       float aspect_Width,
                       float aspect_Height,
                       float sensitivity);
    void TakeInputs(float mouseOffsetX, float mouseOffsetY);
  };

  extern Camera* m_cam;
} // namespace WoohooDX12