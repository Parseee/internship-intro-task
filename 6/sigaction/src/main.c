#define _POSIX_C_SOURCE 199309L

#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#include "matrix/matrix.h"

typedef struct Ret_data {
    Matrix* left;
    Matrix* right;
} Ret_data;

static int process(Matrix* left, Matrix* right, Matrix* res);
static void init_signals(Ret_data ret_data);
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

    Ret_data ret_data = { left, right};
    init_signals(ret_data);

    MATRIX_ERROR_HANDLE(Matrix_multiply(res, left, right));

    return 0;
}

static void init_signals(Ret_data ret_data)
{
    struct sigaction sigact;
    sigact.sa_sigaction = signal_handler;
    sigemptyset(&sigact.sa_mask);
    sigact.sa_flags = SA_SIGINFO;
<<<<<<< HEAD
<<<<<<< HEAD
    union sigval sv;
    sv.sival_ptr = (void*)&ret_data;
=======
>>>>>>> 79afa59 (sigaction buggs)
=======
>>>>>>> 79afa59 (sigaction buggs)
    if (sigaction(SIGINT, &sigact, NULL)) {
        perror("Setting alternative sigaction failed");
        return;
    }

<<<<<<< HEAD
<<<<<<< HEAD
    // if (sigqueue(getpid(), SIGINT, (union sigval) { .sival_ptr = (void*)&ret_data })) {
    //     perror("Pushing signal handler argument failed");
    //     return;
    // }
=======
=======
>>>>>>> 79afa59 (sigaction buggs)
    if (sigqueue(getpid(), SIGINT, (union sigval) { .sival_ptr = (void*)&ret_data })) {
        perror("Pushing signal handler argument failed");
        return;
    }
<<<<<<< HEAD
>>>>>>> 79afa59 (sigaction buggs)
=======
>>>>>>> 79afa59 (sigaction buggs)
}

void signal_handler(int signal, siginfo_t* info, void* context)
{
    assert(info);

    Ret_data* ret_data = info->si_ptr;
    if (signal == SIGINT) {
        printf("Current indices for left matrix: %lu, %lu\n", ret_data->left->w_col, ret_data->left->w_row);
        printf("Current indices for right matrix: %lu, %lu\n", ret_data->right->w_col, ret_data->right->w_row);

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
