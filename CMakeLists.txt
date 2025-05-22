cmake_minimum_required(VERSION 3.31)
project(Converter___Basic_Ops)

set(CMAKE_CXX_STANDARD 20)

# For Windows (MSVC) - static runtime to avoid MSVC DLL dependencies
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

# For MinGW - static link GCC, stdc++, and pthread libs to avoid DLLs
if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
endif()

# For Linux - static linking attempt (optional, might cause issues)
if(UNIX AND NOT APPLE)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
endif()

# For macOS - generally avoid static linking, leave default
if(APPLE)
    message(STATUS "Static linking on macOS is not fully supported; using default linking")
endif()

add_executable(Converter___Basic_Ops main.cpp)
