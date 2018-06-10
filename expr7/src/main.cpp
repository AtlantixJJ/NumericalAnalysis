#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
using namespace std;

const double EPSILON = 0.00001;

struct linspace_t{
    double l, r;
    int len;
    linspace_t(double left, double right, int length) {
        l = left; r = right;
        len = length;
    }
    inline double get_step() const {return (r-l)/len;}
};

inline double get_f1(double x) {
    // 2𝑥3 − 𝑥2 + 3𝑥 − 1 
    double ans = 2 * x * x * x - x * x + 3 * x - 1;
    return ans;
}

inline double get_df1(double x) {
    // 6x2 - 2x + 3
    double ans = 6 * x * x - 2 * x + 3;
    return ans;
}

inline double get_f3(double x) {
    // 𝑥3 − 𝑥 − 1 = 0
    double ans = x * x * x - x - 1;
    return ans;
}

inline double get_df3(double x) {
    // 3x2 - 1
    double ans = 3 * x * x - 1;
    return ans;
}

inline double get_f2(double x) {
    // 2𝑥3 − 𝑥 − 1 
    double ans = 2 * x * x * x - x - 1;
    return ans;
}

inline double get_iter1_f2(double x) {
    double ans = pow((x + 1) / 2, 1.0 / 3.0);
    return ans;
}

inline double get_iter2_f2(double x) {
    double ans = 2 * x * x * x - 1;
    return ans;
}


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

double solve_binary_search(const linspace_t& b, double (*func)(double)) {
    double l = b.l, r = b.r;
    bool type;

    if(func(l) < 0 && func(r) > 0) {
        type = true;
    } else if(func(l) > 0 && func(r) < 0) {
        type = false;
    } else {
        printf("Impossible to solve: same sign at both end.\n");
        return 0;
    }

    double mid, res;
    int cnt = 0;
    printf("|Iteration|x\t|y\t|\n");
    printf("|:--|:--|:--|\n");
    while(true) {
        cnt += 1;
        mid = (l + r) / 2;
        res = func(mid);
        printf("|%d\t|%.5f\t|%.5f\t|\n", cnt, mid, res);
        if (abs(res) < EPSILON) {
            break;
        } else if (res > 0) {
            if(type) r = mid;
            else l = mid;
        } else {
            if(type) l = mid;
            else r = mid;
        }
    }
    printf("Error: %.10f\n", res);
    return mid;
}

double newton_method(double init_x, double (*f)(double), double (*df)(double), int max_iter=10) {
    int cnt = 0;
    double x = init_x;
    double y, dy;

    printf("|Iteration|x\t|y\t|\n");
    printf("|:--|:--|:--|\n");

    while(true) {
        y = f(x);
        dy = df(x);
        printf("|%d\t|%.5f\t|%.5f\t|\n", cnt, x, y);

        if(abs(y) < EPSILON) {
            break;
        } else {
            x -= y / dy;
            cnt += 1;
        }

        if(cnt >= max_iter) break;
    }
    printf("Total iter num: %d\n", cnt);
    printf("Error: %.10f\n", y);
    return x;
}

double iter_func(double init_x, double (*f_iter)(double), double (*f_full)(double), int max_iter) {
    int i;
    double res, x = init_x, tmp;

    printf("|Iteration|x\t|func\t|y\t|\n");
    printf("|:--|:--|:--|:--|\n");

    for(i = 0; i < max_iter; i ++) {
        res = f_full(x);
        tmp = f_iter(x);
        printf("|%d\t|%.5f|%.5f|%.5f|\n", i, x, tmp, res);
        x = tmp;
    }
    return x;
}

int main() {
    double x_bg = -3, x_ed = 3;
    int length = 600;
    linspace_t solve_block = linspace_t(x_bg, x_ed, length);

    // get the true y
    vector<double> f1_y;
    scan(f1_y, solve_block, get_f1);
    print2file("data/f1_y.txt", f1_y);

    printf("Solve problem 1.\n");

    printf("Binary search solution: \n");
    printf("Initial value: (%.5f, %.5f)\n", solve_block.l, solve_block.r);
    double res = solve_binary_search(solve_block, get_f1);
    printf("Solution: x=%.10f\n", res);
    printf("-----\n");

    printf("Newton method solution: (1)\n");
    printf("Init x: %.5f\n", 3.0);
    res = newton_method(3, get_f1, get_df1);
    printf("Solution: x=%.10f\n", res);
    printf("-----\n");

    printf("Solve problem 2.\n");

    printf("Stable point iteration: (1)\n");
    printf("Init x: %.5f\n", 0.0);
    res = iter_func(0.0, get_iter1_f2, get_f2, 10);
    printf("Solution: x=%.10f\n", res);
    printf("-----\n");

    printf("Stable point iteration: (2)\n");
    printf("Init x: %.5f\n", 0.0);
    res = iter_func(0.0, get_iter2_f2, get_f2, 3);
    printf("Solution: x=%.10f\n", res);
    printf("-----\n");

    vector<double> f3_y;
    scan(f3_y, solve_block, get_f3);
    print2file("data/f3_y.txt", f3_y);

    printf("Newton method solution: (2)/1\n");
    printf("Init x: %.5f\n", 1.5);
    res = newton_method(1.5, get_f3, get_df3);
    printf("Solution: x=%.10f\n", res);
    printf("-----\n");

    printf("Newton method solution: (2)/2\n");
    printf("Init x: %.5f\n", 0.0);
    res = newton_method(0.0, get_f3, get_df3, 30);
    printf("Solution: x=%.10f\n", res);
    printf("-----\n");

    /*
    printf("Newton method solution: (2)/2\n");
    printf("Init x: %.5f\n", 3.0);
    res = newton_method(3.0, get_f3, get_df3, 30);
    printf("Solution: x=%.10f\n", res);
    printf("-----\n");
    */
    return 0;
}