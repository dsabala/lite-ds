target_sources(lite-ds
    PRIVATE
        src/mem-pool.c
)

target_include_directories(lite-ds
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
)

lite_ds_add_test(test-mem-pool)
