#include "AppWindow.h"
#include "Utils.h"
#include "Main.h"
#include "Camera.h"

namespace WoohooDX12
{
  bool isRightClicked = false, buttonPressed[4] = {};
  double frameDelta = 0.0f;

  static std::chrono::high_resolution_clock::time_point lastTime;
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
    lastTime         = std::chrono::high_resolution_clock::now();

    if (!m_window->create(wdesc, *m_eventQueue))
    {
      Log("Window creation has failed.", LogType::LT_ERROR);
      return -1;
    };

    m_cam = new Camera;

    return 0;
  }

  void AppWindow::CloseAppWindow()
  {
    m_window->close();
  }

  void AppWindow::HandleEvents() {
    m_eventQueue->update();
    auto now = std::chrono::high_resolution_clock::now();
    frameDelta = ((now - lastTime).count()) / pow(10.0f, 6.0f);
    lastTime   = now;

    DirectX::XMVECTOR mouseOffset = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
    bool isFirstRight = false;
    while (!m_eventQueue->empty())
    {
      const xwin::Event& event = m_eventQueue->front();

      if (event.type == xwin::EventType::Resize)
      {
        const xwin::ResizeData data = event.data.resize;
        m_app->m_renderer->Resize(data.width, data.height);
        m_cam->SetProperties(45.0f,
                             data.width,
                             data.height,
                             CONST_MOUSESENSITIVITY);
        shouldRender = false;
      }
      else if (event.type == xwin::EventType::Close)
      {
        CloseAppWindow();
        shouldRender = false;
        m_app->m_quit = true;
      }
      else {
        shouldRender = true;
      }

      if (event.type == xwin::EventType::MouseInput && event.data.mouseInput.button == xwin::MouseInput::Right) {
        if (event.data.mouseInput.state == xwin::ButtonState::Pressed)
        {
          isRightClicked = true;
        }
        else
        {
          isRightClicked = false;
        }
      }
      if (event.type == xwin::EventType::MouseMove && isRightClicked) {
        mouseOffset = DirectX::XMVectorAdd(mouseOffset, DirectX::XMVectorSet(event.data.mouseMove.deltax, event.data.mouseMove.deltay, 0.0f, 0.0f));
      }
      if (event.type == xwin::EventType::Keyboard) {
        WhButtons key = WhButtons::INVALID;
        switch (event.data.keyboard.key)
        {
        case xwin::Key::W:
          key = WhButtons::W;
          break;
        case xwin::Key::A:
          key = WhButtons::A;
          break;
        case xwin::Key::S:
          key = WhButtons::S;
          break;
        case xwin::Key::D:
          key = WhButtons::D;
          break;
        }
        if (key == WhButtons::INVALID) {
          break;
        }

        if (event.data.keyboard.state == xwin::ButtonState::Pressed)
        {
          buttonPressed[(int) key] = true;
        }
        else
        {
          buttonPressed[(int) key] = false;
        }
      }

      m_eventQueue->pop();
    }

    if (isRightClicked) {
      DirectX::XMFLOAT2 offset2D;
      DirectX::XMStoreFloat2(&offset2D ,mouseOffset);
      m_cam->TakeInputs(offset2D.x, offset2D.y);
    }
  }
  bool AppWindow::ShouldRender() {
    return shouldRender;
  }
  xwin::WindowDesc AppWindow::GetDesc()
  {
    return m_window->getDesc();
  }
}
