#pragma once

#include "CrossWindow/CrossWindow.h"

namespace WoohooDX12
{
  class AppWindow
  {
   public:
    int CreateAppWindow(int width, int height);
    void HandleEvents();
    bool ShouldRender();
    void CloseAppWindow();

    xwin::WindowDesc GetDesc();

   private:
    bool shouldRender = true;

   public:
    int m_width                    = 640;
    int m_height                   = 640;

    xwin::Window* m_window         = nullptr;
    xwin::EventQueue* m_eventQueue = nullptr;
  };

  enum class WhButtons : unsigned char
  {
    W       = 0,
    A       = 1,
    S       = 2,
    D       = 3,
    INVALID = 255
  };

  extern bool isRightClicked, buttonPressed[4];
  extern double frameDelta;
} // namespace WoohooDX12
