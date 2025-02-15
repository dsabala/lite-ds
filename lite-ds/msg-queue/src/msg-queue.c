#include <lite-ds/msg-queue.h>

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

/* Private types */

/** @brief Message queue structure */
struct msg_queue_hdl_s
{
	uint8_t* buf; /**< pointer to continous memory area */
	size_t head; /**< index of the head */
	size_t tail; /**< index of the tail */
	size_t size; /**< size of the buffer */
    size_t message_size; /**< size of the message */
	bool full; /**< flag indicating if the buffer is full */
};

/* Private functions */

/* Public functions */

msg_queue_hdl_t msg_queue_init(size_t size, size_t message_size)
{
    assert(size > 0);

    msg_queue_hdl_t hdl = malloc(sizeof(struct msg_queue_hdl_s));
    if (hdl == NULL) {
        return NULL;
    }

    hdl->size = size;
    hdl->message_size = message_size;
    hdl->buf = malloc(size * message_size);
    if (hdl->buf == NULL) {
        free(hdl);
        return NULL;
    }

    hdl->head = 0;
    hdl->tail = 0;
    hdl->full = false;

    return hdl;
}

void msg_queue_free(msg_queue_hdl_t hdl)
{
    assert(hdl != NULL);

    free(hdl->buf);
    free(hdl);
}

void msg_queue_clear(msg_queue_hdl_t hdl)
{
    assert(hdl != NULL);

    hdl->head = 0;
    hdl->tail = 0;
    hdl->full = false;
}

bool msg_queue_send(msg_queue_hdl_t hdl, void* data)
{
    assert(hdl != NULL);
    assert(data != NULL);

    if (hdl->full) {
        return false;
    }

    memcpy(&hdl->buf[hdl->head * hdl->message_size], data, hdl->message_size);

    hdl->head = (hdl->head + 1) % hdl->size;
    hdl->full = (hdl->head == hdl->tail);

    return true;
}

bool msg_queue_receive(msg_queue_hdl_t hdl, void* data)
{
    assert(hdl != NULL);
    assert(data != NULL);

    if (hdl->head == hdl->tail && !hdl->full) {
        return false;
    }

    memcpy(data, &hdl->buf[hdl->tail * hdl->message_size], hdl->message_size);

    hdl->tail = (hdl->tail + 1) % hdl->size;
    hdl->full = false;

    return true;
}

bool msg_queue_empty(msg_queue_hdl_t hdl)
{
    assert(hdl != NULL);

    return (hdl->head == hdl->tail && !hdl->full);
}

bool msg_queue_full(msg_queue_hdl_t hdl)
{
    assert(hdl != NULL);

    return hdl->full;
}

size_t msg_queue_capacity(msg_queue_hdl_t hdl)
{
    assert(hdl != NULL);

    return hdl->size;
}

size_t msg_queue_get_number_pending(msg_queue_hdl_t hdl)
{
    assert(hdl != NULL);

    if (hdl->full) {
        return hdl->size;
    }

    if (hdl->head >= hdl->tail) {
        return hdl->head - hdl->tail;
    }

    return hdl->size - hdl->tail + hdl->head;
}
