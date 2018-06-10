#ifndef MAIN_H_
#define MAIN_H_

#include <vector>
using namespace std;

struct linspace_t;

void print2file(const char *fname, const vector<double> &list);
void scan(vector<double> &list, const linspace_t& b, double (*func)(double));
inline double get_true_y(double x, double epsilon, double a);
inline double default_true_y(double x);
double compute_diff(vector<double> &true_y, vector<double> &est_y, vector<double> &diff);
#endif