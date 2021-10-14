cmake_minimum_required(VERSION 3.15)
project(gradient
    LANGUAGES CXX
    VERSION 1.0
)

add_subdirectory(dependencies)
add_subdirectory(src)

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
endif(CCACHE_FOUND)