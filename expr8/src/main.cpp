#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

const int N = 100;
const double EPSILON = 1e-5;

double mat[N][N], vec_c[N], vec_v[N], vec_u[N];

int read_matrix_from_file(const char *fname) {
    int n, i, j;
    FILE *f = fopen(fname, "r");
    fscanf(f, "%d", &n);
    for(i = 0; i < n; i ++) {
        for(j = 0; j < n; j ++) {
            fscanf(f, "%lf", &mat[i][j]);
        }
    }
    fclose(f);
    return n;
}

void print_matrix(int n) {
    int i, j;
    for(i = 0; i < n; i ++) {
        printf("[");
        for(j = 0; j < n; j ++) {
            printf("%.3lf, ", mat[i][j]);
        }
        printf("],\n");
    }
}

void init_vector(int n) {
    int i;
    for(i = 0; i < n; i ++)
        vec_v[i] = 1.0;
}

void matrix_vector_v(int n) {
    int i, j;
    for(i = 0; i < n; i++) {
        vec_c[i] = 0;
        for(j = 0; j < n; j ++) {
            vec_c[i] += mat[i][j] * vec_v[j];
        }
    }

    for(i = 0; i < n; i++)
        vec_v[i] = vec_c[i];
}

double normalize_u(int n) {
    double maxi = -0xffff;
    int i;
    for(i = 0; i < n; i++) {
        if(vec_v[i] > maxi) maxi = vec_v[i];
    }
    for(i = 0; i < n; i++) {
        vec_v[i] = vec_v[i] / maxi;
    }
    return maxi;  
}

void output_log(int n, int iter, double maxi, FILE *log_file) {
    fprintf(log_file, "Iter %d,Maximum %.10lf", iter, maxi);
    int i;
    for(i = 0; i < n; i ++)
        fprintf(log_file, ",%.10lf", vec_v[i]);
    fprintf(log_file, "\n");
}

void print_log(int n, int iter, double maxi) {
    printf("|Iter %d\t|Maximum %.10lf\t", iter, maxi);
    int i;
    for(i = 0; i < n; i ++)
        printf("|%.10lf\t", vec_v[i]);
    printf("|\n");
}

void power_vector(int n, FILE *log_file) {
    double maxi_v = 1.0, last_maxi = 0xffffff;
    int iter = 0;
    while(true) {
        print_log(n, iter, maxi_v);
        output_log(n, iter, maxi_v, log_file);
        // multiply A and v to get new v
        matrix_vector_v(n);

        // get the maximum of v and normalize u
        maxi_v = normalize_u(n);

        if(abs(last_maxi - maxi_v) < EPSILON) {
            break;
        }

        last_maxi = maxi_v;
        iter += 1;
    }
    print_log(n, iter, maxi_v);
    output_log(n, iter, maxi_v, log_file);
}

int main() {    
    int n;
    // problem1
    n = read_matrix_from_file("data/mat1.txt");
    FILE *log1 = fopen("data/log1.txt", "w");
    fprintf(log1, "%d\n", n);
    print_matrix(n);
    init_vector(n);
    power_vector(n, log1);
    fclose(log1);

    // problem2
    n = read_matrix_from_file("data/mat2.txt");
    FILE *log2 = fopen("data/log2.txt", "w");
    fprintf(log2, "%d\n", n);
    print_matrix(n);
    init_vector(n);
    power_vector(n, log2);
    fclose(log2);


    return 0;
}