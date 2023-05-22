cmake_minimum_required(VERSION 3.25)
project(S28352_P01)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        fmt
        GIT_REPOSITORY  https://github.com/fmtlib/fmt
        GIT_TAG         a33701196adfad74917046096bf5a2aa0ab0bb50
)
FetchContent_MakeAvailable(fmt)

add_executable(S28352_P01
        main.cpp
        Cipher.cpp
        Cipher.hpp
        Operations.cpp
        Operations.hpp
        Login.cpp
        Login.hpp
        )
target_link_libraries(S28352_P01 fmt)

