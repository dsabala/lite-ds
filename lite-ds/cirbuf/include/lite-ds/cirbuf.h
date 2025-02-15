#ifndef __LITE_DS_CIRBUF_H__
#define __LITE_DS_CIRBUF_H__

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/** @brief Circular buffer handler */
typedef struct cirbuf_hdl_s* cirbuf_hdl_t;

/**
 * @brief Initialize a circular buffer
 *
 * @param[in] size Size of the circular buffer
 *
 * @return Circular buffer handler
 */
cirbuf_hdl_t cirbuf_init(size_t size);

/**
 * @brief Free a circular buffer
 *
 * @param[in] hdl Circular buffer handler
 */
void cirbuf_free(cirbuf_hdl_t hdl);

/**
 * @brief Clear a circular buffer
 *
 * @param[in] hdl Circular buffer handler
 */
void cirbuf_clear(cirbuf_hdl_t hdl);

/**
 * @brief Push data into a circular buffer
 *
 * @param[in] hdl   Circular buffer handler
 * @param[in] data  Data to push
 */
void cirbuf_push(cirbuf_hdl_t hdl, uint8_t data);

/**
 * @brief Pop data from a circular buffer
 *
 * @param[in] hdl   Circular buffer handler
 * @param[out] data Data popped
 *
 * @return true if successful, false if buffer is empty
 */
bool cirbuf_pop(cirbuf_hdl_t hdl, uint8_t* data);

/**
 * @brief Check if a circular buffer is empty
 *
 * @param[in] hdl Circular buffer handler
 *
 * @return true     If the buffer is empty
 * @return false    If the buffer is not empty
 */
bool cirbuf_empty(cirbuf_hdl_t hdl);

/**
 * @brief Check if a circular buffer is full
 *
 * @param[in] hdl Circular buffer handler
 *
 * @return true     If the buffer is full
 * @return false    If the buffer is not full
 */
bool cirbuf_full(cirbuf_hdl_t hdl);

/**
 * @brief Get the size of a circular buffer
 *
 * @param[in] hdl Circular buffer handler
 *
 * @return Size of the circular buffer
 */
size_t cirbuf_capacity(cirbuf_hdl_t hdl);

/**
 * @brief Get the number of elements in a circular buffer
 *
 * @param[in] hdl Circular buffer handler
 *
 * @return Number of elements in the circular buffer
 */
size_t cirbuf_size(cirbuf_hdl_t hdl);

#endif /* __LITE_DS_CIRBUF_H__ */
