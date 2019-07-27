#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

int main()
{
    struct timespec start1, start2, end1, end2, interv;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start1);
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start2);
    printf("start time : %ld s + %ld ns\n", start1.tv_sec, start1.tv_nsec);
    printf("start time : %ld s + %ld ns\n", start2.tv_sec, start2.tv_nsec);
    #pragma omp parallel for
    for (int i = 0; i < 3; ++i)
    {
        int sum = 0;
        for (int j = 0; j < 1000000; ++j) sum++;
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end1);
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end2);
    printf("start time : %ld s + %ld ns\n", end1.tv_sec, end1.tv_nsec);
    printf("start time : %ld s + %ld ns\n", end2.tv_sec, end2.tv_nsec);

    return 0;
}