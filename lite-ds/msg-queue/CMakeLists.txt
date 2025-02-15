target_sources(lite-ds
    PRIVATE
        src/msg-queue.c
)

target_include_directories(lite-ds
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
)

lite_ds_add_test(test-msg-queue)
