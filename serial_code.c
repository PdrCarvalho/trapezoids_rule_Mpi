#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
// #include <sys/time.h>

double f(double x){
    return 10 * ( (x * x) - (10 * cos(2 * M_PI * x)));
}

int main(int argc, char const *argv[])
{
    time_t start_process = time(NULL);
    double a = 1;
    double b = 5;
    int N = atoi(argv[1]);
    double h = (b-a)/((double)N);
    double total_area = (f(a)+f(b))/2;
    double x_i;
    for (int i=1;i< N;i++){
        x_i = a+i*h;
        total_area+= f(x_i);
    }
    double Result= h*total_area;
    time_t end_process = time(NULL);
    FILE *fp;
    char outputFilename[] = "serial_time.txt";
    fp = fopen(outputFilename, "a");
    if (fp == NULL) {
        fprintf(stderr, "Can't open output file %s!\n", outputFilename);
        exit(1);
    }
    fprintf(fp,"\nProblem=%d Result=%1.2f process time=%ld\n", N,Result,(end_process - start_process));
    fclose(fp);
    return 0;
}
