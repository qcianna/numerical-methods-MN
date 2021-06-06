#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 5

void solve_x_GJ(double*, double*, double a[][N]);
void solve_c(double*, double*, double a[][N]);
void print_matrix(double a[][N]);

int main()
{
    double q;

    FILE* fp = fopen("lab2_x.txt", "w");
    for(double i_q=0.5; i_q<5; i_q+=0.111)
    {
        q = i_q;
        double x[N] = {0};
        double A[N][N] = {{2*q*pow(10, -4), 1, 6, 9, 10}, 
                        {2*pow(10,-4), 1, 6, 9, 10}, 
                        { 1, 6, 6, 8, 6}, 
                        {5, 9, 10, 7, 10}, 
                        { 3, 4, 9, 7, 9}};
        double b[N] = {10, 2, 9, 9, 3};
        double c[N] = {0};
        print_matrix(A);
        solve_x_GJ(x, b, A);
        double b_c[N] = {10, 2, 9, 9, 3};
        double A_c[N][N] = {{2*q*pow(10, -4), 1, 6, 9, 10}, 
                            {2*pow(10,-4), 1, 6, 9, 10}, 
                            { 1, 6, 6, 8, 6}, 
                            {5, 9, 10, 7, 10}, 
                            { 3, 4, 9, 7, 9}};
        solve_c(c, x, A_c);

        double s=0;
        for (int i=0; i<N; i++) 
        {
            s += pow(c[i]-b_c[i], 2);
            //fprintf(fp, "%f   %f\n", q, c[i]);
        }

        double o_q=0.2*sqrt(s);
        fprintf(fp, "%.13f     %.13f\n", q, o_q);
    }
    fclose(fp);
    
    return 0;
}

void solve_x_GJ(double* x, double* b, double a[][N]) 
{
    double w, w2;

    for (int i=0; i <N; i++) 
    {
        w = a[i][i];
        b[i] = b[i] / w;
        for (int j=0; j<N; j++) 
        {
            a[i][j] = a[i][j] / w;
        }

        for (int k=0; k<N; k++) 
        {
            w2 = a[k][i];
            if (k!=i) 
            {
                b[k] = b[k] - b[i] * w2;
                for (int j = 0; j<N; j++) 
                {
                    a[k][j] = a[k][j] - w2 * a[i][j];
                }
            }
        }
    }

    for (int i=0; i<N; i++) 
    {
        x[i] = b[i];
    }
}

void solve_c(double* c, double* x, double a[][N]) 
{
    for (int i=0; i<N; i++) 
    {
        double s=0;
        for(int j=0; j<N; j++)
        {
            s += a[i][j]*x[j];
        }
        c[i] = s;
    }
}

void print_matrix(double a[][N]) 
{
    for (int i = 0; i<N; i++) 
    {
        for (int j = 0; j<N; j++) 
        {
            printf("%9.5f ", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
