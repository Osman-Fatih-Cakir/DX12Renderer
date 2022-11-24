#include "AppWindow.h"
#include "Utils.h"

namespace WoohooDX12
{
  int AppWindow::CreateAppWindow(int width, int height)
  {
    m_width = width;
    m_height = height;

    // Create Window
    xwin::WindowDesc wdesc;
    wdesc.title = "WoohooDX12Renderer";
    wdesc.name = "AppWindow";
    wdesc.visible = true;
    wdesc.width = width;
    wdesc.height = height;
    wdesc.fullscreen = false;

    m_eventQueue = new xwin::EventQueue();
    m_window = new xwin::Window();

    if (!m_window->create(wdesc, *m_eventQueue))
    {
      Log("Window creation has failed.", LogType::LT_ERROR);
      return -1;
    };

    return 0;
  }

  void AppWindow::CloseAppWindow()
  {
    m_window->close();
  }
  xwin::WindowDesc AppWindow::GetDesc()
  {
    return m_window->getDesc();
  }
}
