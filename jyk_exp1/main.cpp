#include "interpolation.h"
#include "splineinterpolation.h"

#include <cmath>
#include <cstdio>

inline double func(double x)
{
    return 1 / (1 + 16 * x * x);
}

inline double dfunc(double x)
{
    double deno = 1 + 16 * x * x;
    return -32 * x / (deno * deno);
}

void doInterpolation(int n, double x, Interpolation::InterpolationMethod method)
{
    printf("n = %d, x = %lf:\n", n, x);

    Interpolation* interpolation;
    Interpolation::PointList points;
    double h = 10.0 / n;
    for (int i = 0; i <= n; i++)
    {
        double x = -5 + i * h, y = func(x);
        points.push_back(std::make_pair(x, y));
    }

    interpolation = Interpolation::newInterpolation(points, method);
    printf("%s interpolation:\n", interpolation->getMethodName());

    if (interpolation->getMethod() == Interpolation::SPLINE)
    {
        SplineInterpolation* p = (SplineInterpolation*)interpolation;
        p->setBoundary(dfunc(points.front().first), dfunc(points.back().first));
    }

    interpolation->doInterpolation();
    interpolation->printPolynomial();

    double result = interpolation->getPointValue(x);
    double real = func(x);
    printf("real = %.9lf, result = %.9lf, error = %.9lf\n", real, result, abs(real - result));
    delete interpolation;
}

int main()
{
    double x = 4.8;

    doInterpolation(10, x, Interpolation::LAGRANGE);
    doInterpolation(20, x, Interpolation::LAGRANGE);

    doInterpolation(10, x, Interpolation::SPLINE);
    doInterpolation(20, x, Interpolation::SPLINE);

    return 0;
}
