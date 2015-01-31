project("OpenGL1")

add_subdirectory(./glfw-3.0.4/)
include_directories(./glfw-3.0.4/include/)

add_executable(OpenGL1 main.cpp)

target_link_libraries(OpenGL1 glfw ${GLFW_LIBRARIES})