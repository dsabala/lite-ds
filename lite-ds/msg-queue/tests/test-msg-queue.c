#include <lite-ds/msg-queue.h>

#include <assert.h>
#include <stdio.h>

// Helper macros

#define ARRAY_LEN(arr) (sizeof(arr) / sizeof(arr[0]))

// Helper functions

// Test cases

void test_create_and_free(void)
{
    msg_queue_hdl_t hdl = msg_queue_init(10, 4);
    assert(hdl != NULL);

    msg_queue_free(hdl);
}

void test_push_and_pop(void)
{
    msg_queue_hdl_t hdl = msg_queue_init(10, sizeof(uint32_t));
    assert(hdl != NULL);

    uint32_t data_in[] = {0x11223344, 0x55667788, 0x99AABBCC, 0xDDEEFF00};
    for (size_t i = 0; i < ARRAY_LEN(data_in); i++) {
        assert(msg_queue_send(hdl, &data_in[i]));
    }

    uint32_t data_out[4];
    for(size_t i = 0; i < ARRAY_LEN(data_out); i++) {
        assert(msg_queue_receive(hdl, &data_out[i]));
    }

    assert(data_in[0] == data_out[0]);
    assert(data_in[1] == data_out[1]);
    assert(data_in[2] == data_out[2]);
    assert(data_in[3] == data_out[3]);

    msg_queue_free(hdl);
}

void test_empty(void)
{
    msg_queue_hdl_t hdl = msg_queue_init(10, sizeof(uint32_t));
    assert(hdl != NULL);

    assert(msg_queue_empty(hdl));

    uint32_t data = 0x11223344;
    assert(msg_queue_send(hdl, &data));

    assert(!msg_queue_empty(hdl));

    uint32_t popped;
    assert(msg_queue_receive(hdl, &popped));

    assert(msg_queue_empty(hdl));

    msg_queue_free(hdl);
}

void test_full(void)
{
    msg_queue_hdl_t hdl = msg_queue_init(10, sizeof(uint32_t));
    assert(hdl != NULL);

    uint32_t data = 0x11223344;
    for (size_t i = 0; i < 10; i++) {
        assert(msg_queue_send(hdl, &data));
    }

    assert(msg_queue_full(hdl));

    msg_queue_free(hdl);
}

void test_not_wrap(void)
{
    msg_queue_hdl_t hdl = msg_queue_init(3, sizeof(uint32_t));
    assert(hdl != NULL);

    uint32_t data[] = {0x11223344, 0x55667788, 0x99AABBCC, 0xDDEEFF00};
    for (size_t i = 0; i < ARRAY_LEN(data); i++) {
        msg_queue_send(hdl, &data[i]);
    }

    uint32_t popped;
    for (size_t i = 0; i < 3; i++) {
        assert(msg_queue_receive(hdl, &popped));
        assert(popped == data[i]);
    }

    msg_queue_free(hdl);
}

void test_clear(void)
{
    msg_queue_hdl_t hdl = msg_queue_init(10, sizeof(uint32_t));
    assert(hdl != NULL);

    uint32_t data[] = {0x11223344, 0x55667788, 0x99AABBCC, 0xDDEEFF00};
    for (size_t i = 0; i < ARRAY_LEN(data); i++) {
        assert(msg_queue_send(hdl, &data[i]));
    }

    msg_queue_clear(hdl);

    assert(msg_queue_empty(hdl));

    msg_queue_free(hdl);
}

void test_capacity(void)
{
    msg_queue_hdl_t hdl = msg_queue_init(10, sizeof(uint32_t));
    assert(hdl != NULL);

    assert(msg_queue_capacity(hdl) == 10);

    msg_queue_free(hdl);
}

void test_pending(void)
{
    msg_queue_hdl_t hdl = msg_queue_init(10, sizeof(uint32_t));
    assert(hdl != NULL);

    assert(msg_queue_get_number_pending(hdl) == 0);

    uint32_t data = 0x11223344;
    assert(msg_queue_send(hdl, &data));

    assert(msg_queue_get_number_pending(hdl) == 1);

    uint32_t popped;
    assert(msg_queue_receive(hdl, &popped));

    assert(msg_queue_get_number_pending(hdl) == 0);

    msg_queue_free(hdl);
}

int main() {
    test_create_and_free();
    test_push_and_pop();
    test_empty();
    test_full();
    test_not_wrap();
    test_clear();
    test_capacity();
    test_pending();

    return 0;
}
