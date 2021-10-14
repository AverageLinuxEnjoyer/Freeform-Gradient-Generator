add_executable(gradient_exe)

add_subdirectory(gui)
target_sources(gradient_exe PUBLIC main.cpp)
target_sources(gradient_exe PUBLIC application.cpp)
target_sources(gradient_exe PUBLIC gradient.cpp)

target_link_libraries(gradient_exe PRIVATE ImGui-SFML::ImGui-SFML)