#pragma once

#include "CrossWindow/CrossWindow.h"

namespace WoohooDX12
{
  class AppWindow
  {
  public:
    int CreateAppWindow(int width, int height);
    void CloseAppWindow();

    xwin::WindowDesc GetDesc();

  public:
    int m_width = 640;
    int m_height = 640;

    xwin::Window* m_window = nullptr;
    xwin::EventQueue* m_eventQueue = nullptr;
  };
}
