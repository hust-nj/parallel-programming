#include<stdio.h>
#include<math.h>

long long a[100];
int main()
{
    int n;
    scanf("%d", &n);
    double x0 = (1 - sqrt(5)) / 2, x1 = (1 + sqrt(5)) / 2;
    #pragma omp parallel for
    for (int i = 0; i < n; ++i)
    {
        int j = i + 1;
        double m = x0, n = x1, mulm = 1, muln = 1;
        while (j)
        {
            if (j % 2){
                mulm *= m;
                muln *= n;
            }
            m = m * m;
            n = n * n;
            j /= 2;
        }
        a[i] = (long long)((muln - mulm) / sqrt(5) + 0.5);
    }
    for (int i = 0; i < n; ++i)
    {
        i == n-1 ? printf("%lld\n", a[i]) : printf("%lld ", a[i]);
    }
    return 0;
}