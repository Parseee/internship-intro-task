#include <assert.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

// #include "error/error.h"
#include "matrix/matrix.h"

typedef struct Ret_data {
    Matrix* left;
    Matrix* right;
} Ret_data;

static int process(Matrix* left, Matrix* right, Matrix* res);
static void init_signals(struct sigaction* sigact, Ret_data ret_data);
void signal_handler(int signal, siginfo_t* info, void* ucontext);

int main(void)
{
    Matrix left;
    Matrix right;
    MATRIX_ERROR_HANDLE(Matrix_ctor(&left));
    MATRIX_ERROR_HANDLE(Matrix_ctor(&right));
    Matrix res;
    MATRIX_ERROR_HANDLE(Matrix_ctor(&res));

    MATRIX_ERROR error = process(&left, &right, &res);

    MATRIX_ERROR_HANDLE(Matrix_dtor(&left));
    MATRIX_ERROR_HANDLE(Matrix_dtor(&right));
    MATRIX_ERROR_HANDLE(Matrix_dtor(&res));

    return 0;
}

static int process(Matrix* left, Matrix* right, Matrix* res)
{
    assert(left);
    assert(right);
    assert(res);

    MATRIX_ERROR_HANDLE(Matrix_random_fill(left));
    MATRIX_ERROR_HANDLE(Matrix_random_fill(right));

    struct sigaction sigact;
    Ret_data ret_data = { left, right };
    init_signals(&sigact, ret_data);

    // MATRIX_ERROR_HANDLE(Matrix_multiply(res, left, right));

    return 0;
}

static void init_signals(struct sigaction* sigact, Ret_data ret_data)
{
    assert(sigact);

    sigact->sa_sigaction = signal_handler;
    sigemptyset(&sigact->sa_mask);
    sigact->sa_flags = SA_SIGINFO;
    sigaction(SIGINT, sigact, NULL);

    sigqueue(getpid(), SIGUSR1, (union sigval){ .sival_ptr = (void *)msg });

}

void signal_handler(int signal, siginfo_t* info, void* ucontext)
{
    assert(info);
    assert(ucontext);

    Ret_data* ret_data = (Ret_data*)ucontext;

    if (signal == SIGINT) {
        printf("Current indices for left matrix: %ld, %ld\n", ret_data->left->w_col, ret_data->left->w_row);
        printf("Current indices for right matrix: %ld, %ld\n", ret_data->right->w_col, ret_data->right->w_row);


    }
}