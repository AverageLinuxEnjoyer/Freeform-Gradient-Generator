add_executable(gradient_exe)

add_subdirectory(gui)
add_subdirectory(gradient)
target_sources(gradient_exe PUBLIC main.cpp)
target_sources(gradient_exe PUBLIC application.cpp)

target_link_libraries(gradient_exe PRIVATE ImGui-SFML::ImGui-SFML)