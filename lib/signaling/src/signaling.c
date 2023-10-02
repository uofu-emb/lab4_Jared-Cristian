#include "signaling.h"

// producer: add 5 to the data and send data to output
void signal_handle_calculation(struct k_sem *request,
                               struct k_sem *response,
                               struct signal_data *data){
    while (1)
    {
        // Wait until the request is sent, this means data.input is ready
        // printf("+ Waiting for request\n");
        k_sem_take(request, K_MSEC(2000));
        // printf("+ Handling calculation, %d is input\n", data->input);
        data->output = data->input + 5;

        k_sleep(K_MSEC(1)); // wait to force a context switch to other thread

        // Output is set, so give up response flag to let other thread know
        // printf("+ Done with calculation\n");
        k_sem_give(response);
    }
}

// consumer: request data and return
int signal_request_calculate(struct k_sem *request,
                             struct k_sem *response,
                             struct signal_data *data){
    int err = 0;

    // send another request for data
    // printf("- Handoff to worker\n");
    k_sem_give(request);

    // wait for response data
    // printf("- Waiting for results\n");
    err += k_sem_take(response, K_MSEC(2000));
    // printf("- Result ready %d\n", data->output);

    return 0;
}