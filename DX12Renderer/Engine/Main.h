#pragma once

#include "AppWindow.h"
#include "Render/Renderer.h"

namespace WoohooDX12
{
  class Main
  {
  public:
    Main();
    ~Main();
    void Init();
    void Run();

  public:
    AppWindow* m_window = nullptr;
    Renderer* m_renderer = nullptr;
    bool m_quit = false;
  };
}
