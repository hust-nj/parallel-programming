#include<stdio.h>
#include<math.h>

#include<mpi.h>
long long a[100];
int main(int argc, char *argv[])
{
    int n;
	int myrank, nporcs;
    double x0 = (1 - sqrt(5)) / 2, x1 = (1 + sqrt(5)) / 2;
	double x03 = x0 * x0 * x0, x13 = x1 * x1 * x1;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nporcs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	if (myrank != 0){
		MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		double ans0 = 1, ans1 = 1;
		for (int i = 0; i < myrank; ++i)
		{
			ans0 *= x0;
			ans1 *= x1;
		}
		for (int i = myrank; i <= n; i += 3)
		{
			a[i] = (long long)((ans1 - ans0) / sqrt(5) + 0.5);
			MPI_Send(&a[i], 1, MPI_LONG_LONG_INT, 0, i, MPI_COMM_WORLD);
			ans0 *= x03;
			ans1 *= x13;
		}
	} else {
		scanf("%d", &n);
		// n = 23;
		// change to n = xx is ok!
		for (int i = 1; i <= 3; ++i)
		{
			MPI_Send(&n, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
		}
		for (int i = 1; i <= n; ++i)
		{
			MPI_Recv(&a[i], 1, MPI_LONG_LONG_INT, i % 3 ? i % 3 : 3, i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			i == n ? printf("%lld\n", a[i]) : printf("%lld ", a[i]);
		}
	}
	MPI_Finalize();
    return 0;
}