cmake_minimum_required (VERSION 3.0.2)
project(AutoMUSic)

SET(EXECUTABLE_OUTPUT_PATH "./bin")
SET(LIBRARY_OUTPUT_PATH "./lib")
SET(SDL2_COMPILE_FLAGS "-I/usr/local/include/SDL2 -D_THREAD_SAFE -L/usr/local/lib -lSDL2")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SDL2_COMPILE_FLAGS}")
add_executable(audio_io ./src/impl/AMUS_audio_io.cpp)