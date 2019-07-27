#include<stdio.h>
#include<pthread.h>
#include<math.h>
#include<stdlib.h>

long long a[100];

int n, i = 2;
int j = 1;
int func(void * t)
{
    while (i != n+1 || j != i)
    {
        if (j == n) 
            printf("%lld\n", a[j]);
        else 
            printf("%lld ", a[j]);
        j++;
    }
    return 0;
}

int main()
{
    pthread_t th;
    int ret;
    scanf("%d", &n);
    ret = pthread_create(&th, NULL, (void* (*)(void*))func, NULL);
    if (ret != 0){
        printf("Create thread error!");
        return -1;
    }
    a[0] = 0; a[1] = 1;
    for (i = 2; i <= n; ++i)
    {
        a[i] = a[i-1] + a[i-2];
    }

    pthread_join(th, NULL);
    return 0;
}