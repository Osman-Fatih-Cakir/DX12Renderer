#include "Main.h"
#include <cassert>
#include "Utils.h"

#include <windows.h>
#include <memory>

WoohooDX12::Main* WoohooDX12::m_app = nullptr;

void WINAPI xmain(int argc, const char** argv)
{
  WoohooDX12::m_app = new WoohooDX12::Main;
  while (!WoohooDX12::m_app->m_quit)
  {
    WoohooDX12::m_app->Init();
    WoohooDX12::m_app->Run();
  }
}


namespace WoohooDX12
{
  Main::Main()
  {
    m_window = new AppWindow();
    m_renderer = new Renderer(m_window);

    system(" "); // Get the ascii color codes to work
  }

  Main::~Main()
  {
    SafeDel(m_renderer);
    SafeDel(m_window);
  }

  void Main::Init()
  {
    // Create window
    int check = m_window->CreateAppWindow(1280, 720);
    assert(check == 0 && "Window creation is failed.");

    m_renderer->Init();
  }

  void Main::Run()
  {
    while (!m_quit)
    {
      m_window->HandleEvents();

      if (m_window->ShouldRender())
      {
        m_renderer->Render();
      }
    }
  }
}
