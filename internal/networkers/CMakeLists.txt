cmake_minimum_required(VERSION 3.16)

add_executable(LumawaveRGB
    Main.cpp

    LumawaveRGB.hpp
    LumawaveRGB.cpp

    shader_system/Shader.hpp
    shader_system/Shader.cpp
)

FIND_PACKAGE(Boost 1.42.0 REQUIRED COMPONENTS system thread regex)
IF(Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ENDIF(Boost_FOUND)

target_link_libraries(LumawaveRGB PRIVATE ${Boost_SYSTEM_LIBRARY} fftw3)
target_compile_features(LumawaveRGB PRIVATE cxx_std_20)

add_executable(LumawaveRGB)
