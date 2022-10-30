cmake_minimum_required(VERSION 3.7)
project(Tofu3Dcpp)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/App.cpp src/GLSLProgram.cpp external/imgui/imgui_impl_glfw.cpp external/imgui/imgui_impl_glfw.h external/imgui/imgui.cpp external/imgui/imgui.h external/imgui/imconfig.h external/imgui/imgui_demo.cpp external/imgui/imgui_draw.cpp external/imgui/imgui_tables.cpp external/imgui/imgui_widgets.cpp external/imgui/imgui_impl_opengl3_loader.h external/imgui/imgui_impl_opengl3.cpp external/imgui/imgui_impl_opengl3.h)
include_directories("include")

find_package(OpenGL REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(glm REQUIRED)

add_executable(Tofu3Dcpp ${SOURCE_FILES} ${SOURCES})

target_link_libraries(Tofu3Dcpp ${OPENGL_LIBRARIES} glfw)
