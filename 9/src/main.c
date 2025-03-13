#include <stdint.h>
#include <stdio.h>

// #include "error/error.h"
#include "vector/vector.h"

#define MAX(a, b) a < b ? b : a

typedef struct Sub_arr {
    size_t left;
    size_t right;
    int64_t sum;
} Sub_arr;

static Sub_arr process(Vector* vector);
static size_t read_size(void);

int main(void)
{
    size_t vector_size = read_size();

    Vector vector;
    VECTOR_ERROR_HANDLE(Vector_ctor(&vector, vector_size));

    VECTOR_ERROR_HANDLE(Vector_print(&vector));

    Sub_arr res = process(&vector);

    printf("left: %lu, right: %lu, max sum: %lli", res.left, res.right, res.sum);

    VECTOR_ERROR_HANDLE(Vector_dtor(&vector));
    return 0;
}

typedef struct Sub {
    int64_t val;
    size_t l_idx;
} Sub;

static Sub_arr process(Vector* vector)
{
    Sub_arr res = { .left = 0ull, .right = 0ull, .sum = 0ll };

    if (vector->size == 0) {
        return res;
    }



    int max_sum = vector->data[0];          // Максимальная сумма
    int current_sum = vector->data[0];      // Сумма текущей последовательности
    int max_length = 1;            // Длина самой длинной последовательности
    int current_length = 1;        // Длина текущей последовательности
    int start = 0;                 // Начало текущей последовательности
    int max_start = 0;             // Начало последовательности с максимальной суммой
    int max_end = 0;               // Конец последовательности с максимальной суммой

    for (int i = 1; i < vector->size; i++) {
        if (vector->data[i] > vector->data[i - 1]) {
            current_sum += vector->data[i]; // Добавляем элемент к текущей сумме
            current_length++;      // Увеличиваем длину текущей последовательности
        } else {
            // Сравниваем текущую последовательность с максимальной
            if (current_sum > max_sum || (current_sum == max_sum && current_length > max_length)) {
                max_sum = current_sum;
                max_length = current_length;
                max_start = start;
                max_end = i - 1;
            }
            // Сбрасываем текущую последовательность
            current_sum = vector->data[i];
            current_length = 1;
            start = i;
        }
    }

    // Проверяем последнюю последовательность
    if (current_sum > max_sum || (current_sum == max_sum && current_length > max_length)) {
        max_sum = current_sum;
        max_length = current_length;
        max_start = start;
        max_end = vector->size - 1;
    }

    // Выводим результат
    printf("Индексы последовательности: [%d, %d]\n", max_start, max_end);
    printf("Максимальная сумма: %d\n", max_sum);

    return res;
}

static size_t read_size(void)
{
    int64_t read_size = 0ll;
    scanf("%lld", &read_size);
    return read_size > 0ll ? (size_t)read_size : 0ull;
}