#include <windows.h>
#include <memory>
#include "Engine/Main.h"

bool g_windowShouldClose = false;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
  while (!g_windowShouldClose)
  {
    WoohooDX12::Main main;
    main.Init();
    main.Run();
  }
  
  return 0;
}
