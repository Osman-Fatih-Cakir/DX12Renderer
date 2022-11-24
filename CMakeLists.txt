cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_FLAGS_DEBUG /MDd)

file(GLOB_RECURSE dx12SourceFiles "src/*.cpp" "src/*.h" "src/*.c")
add_subdirectory(Dependency/crosswindow)

project(DX12Renderer)
xwin_add_executable(
    DX12Renderer
    "${dx12SourceFiles}"
)
set(XGFX_API "DIRECTX12")
set_property(TARGET DX12Renderer PROPERTY C_STANDARD 17)
set_property(TARGET DX12Renderer PROPERTY CXX_STANDARD 17)
target_include_directories(DX12Renderer PUBLIC "${CMAKE_SOURCE_DIR}/Dependency/crosswindow/src")


target_link_libraries(
    DX12Renderer
    CrossWindow
)

add_subdirectory(Dependency/crosswindow-graphics)

target_link_libraries(
    DX12Renderer
    CrossWindowGraphics
)
target_include_directories(DX12Renderer PUBLIC "${CMAKE_SOURCE_DIR}/Dependency/crosswindow-graphics/src")