#include <lite-ds/mem-pool.h>

#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

/* Private types */

/** @brief Memory pool chunk structure */
typedef struct mem_pool_chunk_s {
    struct mem_pool_chunk_s* next; /**< pointer to the next chunk */
    uint8_t data[]; /**< data */
} mem_pool_chunk_t;

/** @brief Memory pool structure */
struct mem_pool_s {
    uint8_t* chunk_arr; /**< array of chunks */
    size_t chunk_arr_size; /**< size of the chunk array */
    mem_pool_chunk_t* free_chunk; /**< pointer to the first free chunk */
};

/* Public functions */

mem_pool_t mem_pool_create(size_t pool_size, size_t chunk_size)
{
    assert(pool_size > 0);
    assert(chunk_size >= sizeof(void*));

    /* Allocate pool handler structure */
    mem_pool_t mem_pool = (struct mem_pool_s*)malloc(sizeof(struct mem_pool_s));
    if (NULL == mem_pool) {
        return NULL;
    }

    /* Allocate pool memory */
    mem_pool->chunk_arr_size = pool_size * chunk_size;
    mem_pool->chunk_arr = (uint8_t*)malloc(mem_pool->chunk_arr_size);
    mem_pool->free_chunk = (mem_pool_chunk_t*)mem_pool->chunk_arr;
    if (NULL == mem_pool->chunk_arr) {
        free(mem_pool);
        return NULL;
    }

    /* Initialise the memory pool */
    for (size_t i = 0; i < pool_size - 1; i++) {
        mem_pool_chunk_t* chunk = (mem_pool_chunk_t*)(mem_pool->chunk_arr + i * chunk_size);
        chunk->next = (mem_pool_chunk_t*)(mem_pool->chunk_arr + (i + 1) * chunk_size);
    }
    ((mem_pool_chunk_t*)(mem_pool->chunk_arr + (pool_size - 1) * chunk_size))->next = NULL;

    return mem_pool;
}

void mem_pool_destroy(mem_pool_t mem_pool_hdl)
{
    assert(NULL != mem_pool_hdl);

    free(mem_pool_hdl->chunk_arr);
    free(mem_pool_hdl);
}

void* mem_pool_alloc(mem_pool_t mem_pool_hdl)
{
    assert(NULL != mem_pool_hdl);

    /* Return NULL if there is no free chunks */
    if (mem_pool_hdl->free_chunk == NULL) {
        return NULL;
    }

    /* Take first free chunk */
    void* allocated_chunk = mem_pool_hdl->free_chunk;

    /* Update free chunk list */
    mem_pool_hdl->free_chunk = mem_pool_hdl->free_chunk->next;

    return allocated_chunk;
}

void mem_pool_free(mem_pool_t mem_pool_hdl, void* ptr)
{
    assert(NULL != mem_pool_hdl);
    assert(NULL != ptr);

    /* Check if ptr is within the range of the allocated pool */
    if (ptr < (void*)mem_pool_hdl->chunk_arr ||
        ptr >= (void*)(mem_pool_hdl->chunk_arr + mem_pool_hdl->chunk_arr_size))
    {
        return;
    }

    /* Cast ptr to interprete it as chunk */
    mem_pool_chunk_t* freed_chunk = (mem_pool_chunk_t*)ptr;

    /* Put freed chunk in front of free chunks list */
    freed_chunk->next = mem_pool_hdl->free_chunk;
    mem_pool_hdl->free_chunk = freed_chunk;
}
