#define _POSIX_C_SOURCE 199309L

#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#include "matrix/matrix.h"

struct Ret_data {
    Matrix* left;
    Matrix* right;
} ret_data;

static int process(Matrix* left, Matrix* right, Matrix* res);
static void init_signals();
void signal_handler(int signal, siginfo_t* info, void* context);

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

    ret_data.left = left;
    ret_data.right = right;
    init_signals();

    MATRIX_ERROR_HANDLE(Matrix_multiply(res, left, right));

    return 0;
}

static void init_signals()
{
    struct sigaction sigact;
    sigact.sa_sigaction = signal_handler;
    sigemptyset(&sigact.sa_mask);
    sigact.sa_flags = SA_SIGINFO;

    if (sigaction(SIGINT, &sigact, NULL)) {
        perror("Setting alternative sigaction failed");
        return;
    }
}

void signal_handler(int signal, siginfo_t* info, void* context)
{
    assert(info);

    if (signal == SIGINT) {
        printf("Current indices for left matrix: %lu, %lu\n", ret_data.left->w_col, ret_data.left->w_row);
        printf("Current indices for right matrix: %lu, %lu\n", ret_data.right->w_col, ret_data.right->w_row);

        struct sigaction sigact;
        sigact.sa_handler = SIG_DFL;
        sigemptyset(&sigact.sa_mask);
        sigact.sa_flags = 0;
        if (sigaction(SIGINT, &sigact, NULL)) {
            perror("Setting alternative sigaction failed");
            return;
        }
    }
}
