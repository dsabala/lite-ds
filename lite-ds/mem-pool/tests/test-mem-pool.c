#include <lite-ds/mem-pool.h>

#include <assert.h>
#include <stdint.h>
#include <stdio.h>

// Helper macros

#define ARRAY_LEN(arr) (sizeof(arr) / sizeof(arr[0]))

// Helper functions

// Test cases

void test_mem_pool_create_destroy() {
    mem_pool_t mem_pool = mem_pool_create(10, 16);
    assert(NULL != mem_pool);
    mem_pool_destroy(mem_pool);
}

void test_mem_pool_alloc_free() {
    mem_pool_t mem_pool = mem_pool_create(10, 16);
    assert(NULL != mem_pool);

    uint8_t* ptrs[10];
    for (size_t i = 0; i < ARRAY_LEN(ptrs); i++) {
        ptrs[i] = mem_pool_alloc(mem_pool);
        assert(NULL != ptrs[i]);
        assert(ptrs[i] == (ptrs[0] + (i * 16)));
    }

    assert(NULL == mem_pool_alloc(mem_pool));

    for (size_t i = 0; i < ARRAY_LEN(ptrs); i++) {
        mem_pool_free(mem_pool, ptrs[i]);
    }

    mem_pool_destroy(mem_pool);
}

void test_mem_pool_alloc_free_alloc_free() {
    mem_pool_t mem_pool = mem_pool_create(10, 16);
    assert(NULL != mem_pool);

    uint8_t* ptrs[10];
    for (size_t i = 0; i < ARRAY_LEN(ptrs); i++) {
        ptrs[i] = mem_pool_alloc(mem_pool);
        assert(NULL != ptrs[i]);
    }

    for (size_t i = 0; i < ARRAY_LEN(ptrs); i++) {
        mem_pool_free(mem_pool, ptrs[i]);
    }

    for (size_t i = 0; i < ARRAY_LEN(ptrs); i++) {
        ptrs[i] = mem_pool_alloc(mem_pool);
        assert(NULL != ptrs[i]);
    }

    for (size_t i = 0; i < ARRAY_LEN(ptrs); i++) {
        mem_pool_free(mem_pool, ptrs[i]);
    }

    mem_pool_destroy(mem_pool);
}

// Main function

int main() {
    test_mem_pool_create_destroy();
    test_mem_pool_alloc_free();
    test_mem_pool_alloc_free_alloc_free();

    return 0;
}
