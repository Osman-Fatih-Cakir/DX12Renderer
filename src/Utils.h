#pragma once

#include <string>
#include <iostream>
#include <filesystem>
#include "Types.h"

namespace fs = std::filesystem;

#define SafeDel(ptr) { delete ptr; ptr = nullptr; }

enum class LogType
{
  LT_TEXT = 0,
  LT_LOG = 1,
  LT_WARNING = 2,
  LT_ERROR = 3,
  LT_INFO = 4
};

enum class ColorCode
{
  CC_Reset = 0,
  CC_Blue = 1,
  CC_Yellow = 2,
  CC_Red = 3,
  CC_Green = 4,
  CC_Purple = 5
};

// NOTE: Order matters
const static std::string colorCodes[6] =
{
  "\x1B[0m",  // Reset
  "\x1B[32m", // Green
  "\x1B[33m", // Yellow
  "\x1B[31m", // Red
  "\x1B[36m", // Blue
  "\x1B[35m"  // Purple
};

inline void Log(const String& str, LogType logType = LogType::LT_LOG)
{
  std::cout << colorCodes[(int)logType] << str << colorCodes[0] << std::endl;
}

inline std::wstring GetWorkspacePath()
{
  return fs::current_path().wstring() + L"\\..\\Workspace\\";
}

inline std::wstring GetShaderPath(bool isBinary)
{
  return GetWorkspacePath() + L"Shaders\\" + (isBinary ? (L"DXBC\\") : (L"HLSL\\"));
}
