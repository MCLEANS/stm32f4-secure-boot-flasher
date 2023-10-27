cmake_minimum_required(VERSION 3.0.12)

project(SecureBootFlasher)

add_executable(${PROJECT_NAME}
        src/main.cpp
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        includes
        )