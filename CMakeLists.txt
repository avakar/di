cmake_minimum_required(VERSION 3.1)
project(avakar_di)

include(deps.cmake OPTIONAL)

add_library(avakar_di INTERFACE)
target_include_directories(avakar_di INTERFACE include)
target_compile_features(avakar_di INTERFACE cxx_variadic_templates)

add_executable(avakar_di_test
    test/main.cpp
    include/avakar/di.h
    )
target_link_libraries(avakar_di_test avakar_di mutest)
