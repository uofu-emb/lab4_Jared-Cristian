#include <zephyr.h>
#include <stdio.h>

typedef struct request_msg {
    int32_t input;
    int32_t output;
    uint32_t handled_by;
}msg;

void fifo_worker_handler(struct k_msgq *requests, struct k_msgq *results, int id);

