#include <lite-ds/cirbuf.h>

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

/* Private types */

/** @brief Circular buffer structure */
struct cirbuf_hdl_s
{
	uint8_t* buf; /**< pointer to continous memory area */
	size_t head; /**< index of the head */
	size_t tail; /**< index of the tail */
	size_t size; /**< size of the buffer */
	bool full; /**< flag indicating if the buffer is full */
};

/* Private functions */

/* Public functions */

cirbuf_hdl_t cirbuf_init(size_t size)
{
    assert(size > 0);

    cirbuf_hdl_t hdl = malloc(sizeof(struct cirbuf_hdl_s));
    if (hdl == NULL) {
        return NULL;
    }

    hdl->size = size;
    hdl->buf = malloc(size);
    if (hdl->buf == NULL) {
        free(hdl);
        return NULL;
    }

    hdl->head = 0;
    hdl->tail = 0;
    hdl->full = false;

    return hdl;
}

void cirbuf_free(cirbuf_hdl_t hdl)
{
    assert(hdl != NULL);

    free(hdl->buf);
    free(hdl);
}

void cirbuf_clear(cirbuf_hdl_t hdl)
{
    assert(hdl != NULL);

    hdl->head = 0;
    hdl->tail = 0;
    hdl->full = false;
}

void cirbuf_push(cirbuf_hdl_t hdl, uint8_t data)
{
    assert(hdl != NULL);

    hdl->buf[hdl->head] = data;

    if (hdl->full) {
        hdl->tail = (hdl->tail + 1) % hdl->size;
    }
    hdl->head = (hdl->head + 1) % hdl->size;
    hdl->full = (hdl->head == hdl->tail);
}

bool cirbuf_pop(cirbuf_hdl_t hdl, uint8_t* data)
{
    assert(hdl != NULL);

    if (cirbuf_empty(hdl)) {
        return false;
    }

    *data = hdl->buf[hdl->tail];

    hdl->full = false;
    hdl->tail = (hdl->tail + 1) % hdl->size;

    return true;
}

bool cirbuf_empty(cirbuf_hdl_t hdl)
{
    assert(hdl != NULL);

    return (hdl->head == hdl->tail && !hdl->full);
}

bool cirbuf_full(cirbuf_hdl_t hdl)
{
    assert(hdl != NULL);

    return hdl->full;
}

size_t cirbuf_capacity(cirbuf_hdl_t hdl)
{
    assert(hdl != NULL);

    return hdl->size;
}

size_t cirbuf_size(cirbuf_hdl_t hdl)
{
    assert(hdl != NULL);

    if (hdl->full) {
        return hdl->size;
    } else if (hdl->head >= hdl->tail) {
        return hdl->head - hdl->tail;
    } else {
        return hdl->size + hdl->head - hdl->tail;
    }
}
