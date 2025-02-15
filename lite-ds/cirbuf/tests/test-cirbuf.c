#include <lite-ds/cirbuf.h>

#include <assert.h>
#include <stdio.h>

// Helper macros

#define ARRAY_LEN(arr) (sizeof(arr) / sizeof(arr[0]))

// Helper functions

// Test cases

void test_create_and_free(void)
{
    cirbuf_hdl_t hdl = cirbuf_init(10);
    assert(hdl != NULL);

    cirbuf_free(hdl);
}

void test_push_and_pop(void)
{
    cirbuf_hdl_t hdl = cirbuf_init(10);
    assert(hdl != NULL);

    uint8_t data[] = {1, 2, 3, 4, 5};
    for (size_t i = 0; i < ARRAY_LEN(data); i++) {
        cirbuf_push(hdl, data[i]);
    }

    for (size_t i = 0; i < ARRAY_LEN(data); i++) {
        uint8_t popped;
        cirbuf_pop(hdl, &popped);
        assert(popped == data[i]);
    }

    cirbuf_free(hdl);
}

void test_empty(void)
{
    cirbuf_hdl_t hdl = cirbuf_init(10);
    assert(hdl != NULL);

    assert(cirbuf_empty(hdl));

    cirbuf_push(hdl, 1U);

    assert(!cirbuf_empty(hdl));

    uint8_t popped;
    cirbuf_pop(hdl, &popped);

    assert(cirbuf_empty(hdl));

    cirbuf_free(hdl);
}

void test_full(void)
{
    cirbuf_hdl_t hdl = cirbuf_init(10);
    assert(hdl != NULL);

    for (size_t i = 0; i < 10; i++) {
        cirbuf_push(hdl, i);
        assert(cirbuf_size(hdl) == i + 1);
    }

    assert(cirbuf_full(hdl));

    uint8_t popped;
    cirbuf_pop(hdl, &popped);

    assert(!cirbuf_full(hdl));

    cirbuf_free(hdl);
}

void test_wrap(void)
{
    cirbuf_hdl_t hdl = cirbuf_init(3);
    assert(hdl != NULL);

    uint8_t data[] = {1, 2, 3, 4, 5, 6};
    for (size_t i = 0; i < ARRAY_LEN(data); i++) {
        cirbuf_push(hdl, data[i]);
    }

    uint8_t popped;
    for (size_t i = 0; i < 3; i++) {
        cirbuf_pop(hdl, &popped);
        assert(popped == data[i + 3]);
    }

    cirbuf_free(hdl);
}

void test_clear(void)
{
    cirbuf_hdl_t hdl = cirbuf_init(10);
    assert(hdl != NULL);

    uint8_t data[] = {1, 2, 3, 4, 5};
    for (size_t i = 0; i < ARRAY_LEN(data); i++) {
        cirbuf_push(hdl, data[i]);
    }

    cirbuf_clear(hdl);

    assert(cirbuf_empty(hdl));

    cirbuf_free(hdl);
}

void test_capacity(void)
{
    cirbuf_hdl_t hdl = cirbuf_init(10);
    assert(hdl != NULL);

    assert(cirbuf_capacity(hdl) == 10);

    cirbuf_free(hdl);
}

void test_size(void)
{
    cirbuf_hdl_t hdl = cirbuf_init(10);
    assert(hdl != NULL);

    assert(cirbuf_size(hdl) == 0);

    cirbuf_push(hdl, 1U);
    assert(cirbuf_size(hdl) == 1);

    uint8_t dummy;
    cirbuf_pop(hdl, &dummy);
    assert(cirbuf_size(hdl) == 0);

    cirbuf_free(hdl);
}

int main() {
    test_create_and_free();
    test_push_and_pop();
    test_empty();
    test_full();
    test_wrap();
    test_clear();
    test_capacity();
    test_size();

    return 0;
}
