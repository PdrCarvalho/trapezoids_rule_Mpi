#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "mpi.h"

MPI_Status status;

double f(double x)
{
    return 10 * ((x * x) - (10 * cos(2 * M_PI * x)));
}

int main(int argc, char **argv)
{
    time_t start_process = time(NULL);
    int numtasks, taskid;
    double a = 1;
    double b = 5;
    int N = atoi(argv[1]);
    int cores = atoi(argv[2]);
    double h = (b - a) / ((double)N);
    int local_n = N / cores;
    double total_area = 0.00;
    double local_a, local_b, x_i, local_total_area, result;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    local_a = a + taskid * local_n * h;
    local_b = local_a + local_n * h;
    local_total_area = (f(local_a) + f(local_b)) / 2;
    for (int i = 1; i < local_n; i++)
    {
        x_i = local_a + i * h;
        local_total_area += f(x_i);
    }
    MPI_Reduce(&local_total_area, &total_area, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if (taskid == 0)
    {
        result = h * total_area;
    }
    
    MPI_Finalize();
    if (taskid ==1){
        return 0;
    }
    time_t end_process = time(NULL);
    FILE *fp;
    char outputFilename[] = "parallel_time.txt";
    fp = fopen(outputFilename, "a");
    if (fp == NULL)
    {
        fprintf(stderr, "Can't open output file %s!\n", outputFilename);
        exit(1);
    }
    fprintf(fp, "\nProblem=%d result=%1.2f process time=%ld\n", N, result, (end_process - start_process));
    fclose(fp);
    return 0;
}
