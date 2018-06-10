#include "main.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;

struct linspace_t{
    double l, r;
    int len;
    linspace_t(double left, double right, int length) {
        l = left; r = right;
        len = length;
    }
    inline double get_step() const {return (r-l)/len;}
};

void print2file(const char *fname, const vector<double> &list) {
    FILE *out = fopen(fname, "w");
    for(int j = 0; j < list.size(); j ++)
        fprintf(out, "%10lf\n", list[j]);
    fclose(out);
}

void scan(vector<double> &list, const linspace_t& b, double (*func)(double)) {
    double x;
    double step = b.get_step();

    for(int i = 0; i <= b.len; i++) {
        x = i * step + b.l;
        list.push_back(func(x));
    }
}

inline double get_true_y(double x, double epsilon=1, double a=0.5) {
    double ans = (1 - a) / (1 - exp(-1/epsilon));
    ans *= 1 - exp(-x/epsilon);
    ans += a * x;
    return ans;
}

inline double default_true_y(double x) {
    return get_true_y(x, 1, 0.5);
}

void init_identity(vector<double> &est_y, const linspace_t& b) {
    double step = b.get_step();
    for(int i = 0; i <= b.len; i++) 
        est_y.push_back(i * step + b.l); 
}

double compute_diff(vector<double> &true_y, vector<double> &est_y, vector<double> &diff) {
    
    double res = 0, maxi = -10;
    for(int i = 0; i < true_y.size(); i++) {
        double tmp = abs(true_y[i] - est_y[i]);
        res += tmp;
        if(tmp > maxi) maxi = tmp;
        diff.push_back(tmp);
    }

    print2file("diff_y.txt", diff);

    printf("Sum abs diff: %f\n", res);
    printf("Max diff: %f\n", maxi);
    return res;
}

void JacobIter(vector<double> &est_y, const linspace_t& b) {
    init_identity(est_y, b);

    double epsilon = 1, a = 0.5;
    double h = b.get_step();

    double a_ii = -(2 * epsilon + h);
    double left_coef = epsilon / (-a_ii);
    double right_coef = (epsilon + h) / (-a_ii);
    double bf = a * h * h / a_ii;
    double old_x, tmp;
    int N = 20000, iter, i;

    for(iter = 0; iter < N; iter ++) {
        //est_y[0] = est_y[1] * right_coef + bf;
        old_x = 0;
        for(i = 1; i < b.len; i++) {
            tmp = est_y[i];
            est_y[i] = left_coef * old_x + right_coef * est_y[i+1] + bf;
            old_x = tmp;
        }
        //est_y[b.len] = left_coef * est_y[b.len - 1] + bf;
    }
}

void GSIter(vector<double> &est_y, const linspace_t& b) {
    init_identity(est_y, b);

    double epsilon = 1, a = 0.5;
    double h = b.get_step();

    double a_ii = -(2 * epsilon + h);
    double left_coef = epsilon / (-a_ii);
    double right_coef = (epsilon + h) / (-a_ii);
    double bf = a * h * h / a_ii;
    int N = 10000, iter, i;

    for(iter = 0; iter < N; iter ++) {
        //est_y[0] = est_y[1] * right_coef + bf;
        for(i = 1; i < b.len; i++) {
            est_y[i] = left_coef * est_y[i-1] + right_coef * est_y[i+1] + bf;
        }
        //est_y[b.len] = left_coef * est_y[b.len - 1] + bf;
    }
}

void SORIter(vector<double> &est_y, const linspace_t& b) {
    init_identity(est_y, b);

    double epsilon = 1, a = 0.5;
    double h = b.get_step();

    double a_ii = -(2 * epsilon + h);
    double omega = 1.3;
    double left_coef = omega * epsilon / (-a_ii);
    double right_coef = omega * (epsilon + h) / (-a_ii);
    double bf = omega * a * h * h / a_ii;
    int N = 5000, iter, i;

    for(iter = 0; iter < N; iter ++) {
        //est_y[0] = est_y[1] * right_coef + bf;
        for(i = 1; i < b.len; i++) {
            est_y[i] += -omega * est_y[i] + left_coef * est_y[i-1] + right_coef * est_y[i+1] + bf;
        }
        //est_y[b.len] = left_coef * est_y[b.len - 1] + bf;
    }
}

int main() {
    double x_bg = 0, x_ed = 1;
    int length = 100;
    linspace_t solve_block = linspace_t(x_bg, x_ed, length);

    // get the true y
    vector<double> true_y;
    scan(true_y, solve_block, default_true_y);
    print2file("true_y.txt", true_y);

    // init est y
    vector<double> est_y, diff_y;

    JacobIter(est_y, solve_block);
    compute_diff(true_y, est_y, diff_y);
    print2file("Jacob_diff.txt", diff_y);
    est_y.clear(); diff_y.clear();

    GSIter(est_y, solve_block);
    compute_diff(true_y, est_y, diff_y);
    print2file("GS_diff.txt", diff_y);
    est_y.clear(); diff_y.clear();

    SORIter(est_y, solve_block);
    compute_diff(true_y, est_y, diff_y);
    print2file("SOR_diff.txt", diff_y);
    est_y.clear(); diff_y.clear();

    return 0;
}