#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define NDEBUG
#include <assert.h>

#include "define_colors.h"

#ifdef NDEBUG
    #define MY_ASSERT(condition, message, ...) (void(0))
#else

    // Enter a.exe -DNDEBUG
    #define MY_ASSERT(condition, ...)                                         \
        {                                                                     \
        if (!(condition))                                                     \
            {                                                                 \
            fprintf(stderr, COLOR_RED "ASSERTION FAILED \n" COLOR_RESET);     \
            fprintf(stderr, "" __VA_ARGS__);                                  \
            fprintf(stderr, "Condition: %s\n", #condition);                   \
            fprintf(stderr, "File:      %s\n", __FILE__);                     \
            fprintf(stderr, "Line:      %d\n", __LINE__);                     \
            fprintf(stderr, "Function:  %s\n", __PRETTY_FUNCTION__);          \
            fprintf(stderr, COLOR_GREEN "Aborting program...\n" COLOR_RESET); \
            fflush (stderr);                                                  \
            abort();                                                          \
            }                                                                 \
    }
#endif // NDEBUG

int divide(int a, int b)
    {
    MY_ASSERT(b != 0, "b pointer is %d %d\n", a, b);
    return a / b;
    }

int main() {

    // Assert using
    int result = divide(10, 0);

    MY_ASSERT(0 == 1, "What is this???");

    result = divide(10, 2);
    printf("Result: %d\n", result);

    return 0;
}
