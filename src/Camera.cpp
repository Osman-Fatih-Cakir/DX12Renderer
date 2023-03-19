#include "Camera.h"

#include "RendererUtils.h"
#include "Utils.h"
#include "d3dx12.h"
#include "AppWindow.h"

using namespace DirectX;

namespace WoohooDX12
{
  Camera* m_cam = nullptr;

  Vec3 worldUp(0, 1, 0), reverse(-1.0f, -1.0f, -1.0f);

  Camera::Camera(Vec3 i_target)
  {
    target = XMLoadFloat3(&i_target);
    XMFLOAT3 initPos = XMFLOAT3(0.0, 0.0, 10.0f);
    pos = XMLoadFloat3(&initPos);
    rot    = XMVECTOR();
    scal   = XMVECTOR();
    fov    = 45.0f;
  }

  // Getters
  Mat Camera::CalculateProjMat()
  {
    projMat = XMMatrixPerspectiveFovLH(XMConvertToRadians(float(fov)),
                                       float(viewWidth / viewHeight),
                                       nearPlane,
                                       farPlane);
    return projMat;
  }

  Mat Camera::CalculateViewMat()
  {
    XMVECTOR frontVec = XMVectorMultiply(target, XMLoadFloat3(&reverse));

    viewMat           = XMMatrixLookAtLH(pos,
                               XMVectorAdd(frontVec, pos),
                               XMLoadFloat3(&worldUp));
    return viewMat;
  }

  // Setters
  void Camera::SetProperties(unsigned short fov_in_Angle,
                             float aspect_Width,
                             float aspect_Height,
                             float sensitivity)
  {
    fov              = fov_in_Angle;
    viewWidth        = aspect_Width;
    viewHeight       = aspect_Height;
    nearPlane        = CONST_CAMNEAR;
    farPlane         = CONST_CAMFAR;
    mouseSensitivity = sensitivity;
  }

  void Camera::TakeInputs(float mouseOffsetX, float mouseOffsetY)
  {
    float multiplier = mouseSensitivity * frameDelta;
    mouseYaw   += mouseOffsetX * -multiplier;
    mousePitch       += mouseOffsetY * multiplier;

    // Limit Pitch direction to 90 degrees, because we don't want our camera to
    // upside-down!
    if (mousePitch > 89.0f)
    {
      mousePitch = 89.0f;
    }
    else if (mousePitch < -89.0f)
    {
      mousePitch = -89.0f;
    }

    // Set target direction
    double radPitch = XMConvertToRadians(mousePitch);
    double radYaw   = XMConvertToRadians(mouseYaw);
    target          = XMVectorSet(cos(radPitch) * cos(radYaw),
                         sin(radPitch),
                         cos(radPitch) * sin(radYaw),
                         0.0f);

    XMVECTOR front, right, up;
    front = XMVector3Normalize(target);
    right = XMVector3Cross(XMVector3Normalize(target), XMLoadFloat3(&worldUp));
    up    = XMVectorNegate(XMVector3Normalize(XMVector3Cross(front, right)));

    if (buttonPressed[(int)WhButtons::W]) {
      pos -= front * multiplier;
    }
    if (buttonPressed[(int)WhButtons::S]) {
      pos += front * multiplier;
    }
    if (buttonPressed[(int)WhButtons::D]) {
      pos += right * multiplier;
    }
    if (buttonPressed[(int)WhButtons::A]) {
      pos -= right * multiplier;
    }
    XMFLOAT3 fPos;
    XMStoreFloat3(&fPos, pos);


    CalculateViewMat();
  }
} // namespace WoohooDX12