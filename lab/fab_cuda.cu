#include <stdio.h>
#include <math.h>

long long res[64];

__global__ void fib(long long *res)
{
    int idx = threadIdx.x;
    res[idx] = (long long)(1.0/sqrt(5.0)*(pow((1+sqrt(5.0))/2.0, idx+1) - pow((1-sqrt(5.0))/2.0, idx+1)) + 0.5);
    // printf("%d\n", res[idx]);
}

int main()
{
    int n;
    long long *gpures;
    scanf("%d", &n);
    cudaMalloc(&gpures, n*sizeof(long long));
    fib<<<1,n>>>(gpures);
    cudaMemcpy(res, gpures, n*sizeof(long long), cudaMemcpyDeviceToHost);
    cudaFree(gpures);
    for (int i = 0; i < n; ++i)
    {
        printf(i == n-1 ? "%lld\n" : "%lld ", res[i]);
    }
    return 0;
}