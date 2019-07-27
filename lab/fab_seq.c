#include<stdio.h>
#include<time.h>

int main()
{
    int n;
    scanf("%d", &n);
    long long x0 = 0, x1 = 1;
    for (int i = 0; i < n; ++i)
    {
        long long tmp = x0;
        x0 = x1;
        x1 = tmp + x1;
        i != n - 1 ? printf("%lld ", x0) : printf("%lld\n", x0);
    }
    return 0;
}