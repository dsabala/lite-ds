#ifndef __LITE_DS_MEM_POOL_H__
#define __LITE_DS_MEM_POOL_H__

#include <stddef.h>

/** @brief Memory pool handler */
typedef struct mem_pool_s* mem_pool_t;

/**
 * @brief Create a memory pool
 *
 * @details Allocates memory for the memory pool and initializes it.
 *
 * @param[in] pool_size   size of the memory pool
 * @param[in] chunk_size  size of each chunk in the memory pool
 *
 * @return memory pool handler
 */
mem_pool_t mem_pool_create(size_t pool_size, size_t chunk_size);

/**
 * @brief Destroy a memory pool
 *
 * @param[in] mem_pool_hdl memory pool handler
 */
void mem_pool_destroy(mem_pool_t mem_pool_hdl);

/**
 * @brief Allocate a chunk from the memory pool
 *
 * @param[in] mem_pool_hdl memory pool handler
 *
 * @return pointer to the allocated chunk, NULL if no chunk is available
 */
void* mem_pool_alloc(mem_pool_t mem_pool_hdl);

/**
 * @brief Free a chunk back to the memory pool
 *
 * @param[in] mem_pool_hdl memory pool handler
 *
 * @param[in] ptr pointer to the chunk to free
 */
void mem_pool_free(mem_pool_t mem_pool_hdl, void* ptr);

#endif /* __LITE_DS_MEM_POOL_H__ */
