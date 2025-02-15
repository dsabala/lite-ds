cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(lite-ds VERSION 1.0)

if (LITEDS_BUILD_TESTS)
    include(CTest)
    enable_testing()
endif()

add_library(lite-ds STATIC)

target_compile_options(lite-ds
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Werror
)

if (LITEDS_BUILD_TESTS)
    target_compile_options(lite-ds
        PRIVATE
            -g2
            -Og
    )
endif()

if (LITEDS_BUILD_TESTS)
    function(lite_ds_add_test name)
        add_executable(${name} ${CMAKE_CURRENT_LIST_DIR}/tests/${name}.c)
        target_link_libraries(${name} lite-ds)
        add_test(NAME ${name} COMMAND ${name})
    endfunction()
else()
    function(lite_ds_add_test name)
    endfunction()
endif()

add_subdirectory(lite-ds)
