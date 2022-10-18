#include "Main.h"
#include <cassert>
#include "Utils.h"

extern bool g_windowShouldClose;

namespace WoohooDX12
{
  Main::Main()
  {
    m_window = new AppWindow();
    m_renderer = new Renderer(m_window);
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
    m_quit = false;
    while (!m_quit)
    {
      bool shouldRender = true;

      m_window->m_eventQueue->update();

      while (!m_window->m_eventQueue->empty())
      {
        const xwin::Event& event = m_window->m_eventQueue->front();

        if (event.type == xwin::EventType::Resize)
        {
          const xwin::ResizeData data = event.data.resize;
          m_renderer->Resize(data.width, data.height);
          shouldRender = false;
        }

        if (event.type == xwin::EventType::Close)
        {
          m_window->CloseAppWindow();
          shouldRender = false;
          m_quit = true;
          g_windowShouldClose = true;
        }

        m_window->m_eventQueue->pop();
      }

      if (shouldRender)
      {
        m_renderer->Render();
      }
    }
  }
}
