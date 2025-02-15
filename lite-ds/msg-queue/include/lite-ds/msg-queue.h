#ifndef __LITE_DS_MSG_QUEUE_H__
#define __LITE_DS_MSG_QUEUE_H__

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/** @brief queue handler */
typedef struct msg_queue_hdl_s* msg_queue_hdl_t;

/**
 * @brief Initialize a message queue
 *
 * @param[in] count maximum count of pending messages
 * @param[in] message_size size of message
 *
 * @return queue handler
 */
msg_queue_hdl_t msg_queue_init(size_t size, size_t message_size);

/**
 * @brief Free a message queue
 *
 * @param[in] hdl queue handler
 */
void msg_queue_free(msg_queue_hdl_t hdl);

/**
 * @brief Clear a message queue
 *
 * @param[in] hdl queue handler
 */
void msg_queue_clear(msg_queue_hdl_t hdl);

/**
 * @brief Send a message to a message queue
 *
 * @param[in] hdl   queue handler
 * @param[in] data  message to push
 *
 * @return true if successful, false if buffer is full
 */
bool msg_queue_send(msg_queue_hdl_t hdl, void* data);

/**
 * @brief Receive data from a message queue
 *
 * @param[in] hdl    queue handler
 * @param[out] data  buffer to store message
 *
 * @return true if successful, false if buffer is empty
 */
bool msg_queue_receive(msg_queue_hdl_t hdl, void* data);

/**
 * @brief Check if a message queue is empty
 *
 * @param[in] hdl queue handler
 *
 * @return true     If the message queue is empty
 * @return false    If the message queue is not emptycircular buffer
 */
bool msg_queue_empty(msg_queue_hdl_t hdl);

/**
 * @brief Check if a message queue is full
 *
 * @param[in] hdl queue handler
 *
 * @return true     If the buffer is full
 * @return false    If the buffer is not full
 */
bool msg_queue_full(msg_queue_hdl_t hdl);

/**
 * @brief Get the size of a message queue
 *
 * @param[in] hdl queue handler
 *
 * @return size of the queue
 */
size_t msg_queue_capacity(msg_queue_hdl_t hdl);

/**
 * @brief Get the number of pending messages in a message queue
 *
 * @param[in] hdl queue handler
 *
 * @return number of messages in the queue
 */
size_t msg_queue_get_number_pending(msg_queue_hdl_t hdl);

#endif /* __LITE_DS_MSG_QUEUE_H__ */
