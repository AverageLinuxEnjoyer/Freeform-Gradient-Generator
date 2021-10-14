add_executable(gradient_exe 
    main.cpp
)

target_link_libraries(gradient_exe PRIVATE ImGui-SFML::ImGui-SFML)