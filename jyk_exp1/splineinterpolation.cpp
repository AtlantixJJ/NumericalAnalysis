#include "splineinterpolation.h"

#include <cmath>
#include <cstdio>
#include <string>

SplineInterpolation::SplineInterpolation(const PointList& points)
    : Interpolation(points, SPLINE), m_df0(0), m_dfn(0)
{

}

SplineInterpolation::~SplineInterpolation()
{
    delete[] m_h;
    delete[] m_M;
}

void SplineInterpolation::doInterpolation()
{
    double *u, *v, *d, *b, *y;
    u = new double[m_n + 1];
    v = new double[m_n + 1];
    d = new double[m_n + 1];
    b = new double[m_n + 1];
    y = new double[m_n + 1];
    m_h = new double[m_n + 1];

    for (int i = 0; i < m_n; i++)
    {
        m_h[i] = m_points[i + 1].first - m_points[i].first;
        if (i > 0)
        {
            u[i] = m_h[i - 1] / (m_h[i - 1] + m_h[i]);
            v[i] = m_h[i] / (m_h[i - 1] + m_h[i]);
            d[i] = 6 * (differences(i) - differences(i - 1)) / (m_h[i - 1] + m_h[i]);
        }
    }
    v[0] = u[m_n] = 1, v[m_n] = u[0] = 0;
    d[0] = 6 * (differences(0) - m_df0) / m_h[0];
    d[m_n] = 6 * (m_dfn - differences(m_n - 1)) / m_h[m_n - 1];

    b[0] = v[0] / 2, y[0] = d[0] / 2;
    for (int i = 1; i <= m_n; i++)
    {
        double tmp = 2 - u[i] * b[i - 1];
        b[i] = v[i] / tmp;
        y[i] = (d[i] - u[i] * y[i - 1]) / tmp;
    }
    for (int i = m_n - 1; i >= 0; i--)
        y[i] -= b[i] * y[i + 1];
    m_M = y;
}

double SplineInterpolation::getPointValue(double x) const
{
    for (int i = 0; i < m_n; i++)
    {
        double x0 = m_points[i].first, x1 = m_points[i + 1].first;
        if (x0 <= x && x <= x1)
        {
            double a = m_M[i] / 6,
                   b = m_M[i + 1] / 6,
                   c = m_points[i].second - m_M[i] * m_h[i] * m_h[i] / 6,
                   d = m_points[i + 1].second - m_M[i + 1] * m_h[i] * m_h[i] / 6;
            return (a * xxx(x1 - x) + b * xxx(x - x0) + c * (x1 - x) + d * (x - x0)) / m_h[i];
        }
    }
    return 0;
}

void SplineInterpolation::printPolynomial() const
{
    printf("f = ");
    for (int i = 0; i < m_n; i++)
    {
        double x0 = m_points[i].first, x1 = m_points[i + 1].first;
        double a = m_M[i] / 6 / m_h[i],
               b = m_M[i + 1] / 6 / m_h[i],
               c = (m_points[i].second - m_M[i] * m_h[i] * m_h[i] / 6) / m_h[i],
               d = (m_points[i + 1].second - m_M[i + 1] * m_h[i] * m_h[i] / 6) / m_h[i];

        if (i > 0) printf("    ");
        printf("(%.9le .* (%.2lf - x) .^ 3 %s .* (x %s) .^ 3 %s .* (%.2lf - x) %s .* (x %s)) .* (%.2lf <= x & x < %.2lf)%s\n",
            a, x1,
            formatDouble(b).c_str(), formatDouble(-x0, "%.2lf").c_str(),
            formatDouble(c).c_str(), x1,
            formatDouble(d).c_str(), formatDouble(-x0, "%.2lf").c_str(),
            x0, x1,
            i == m_n - 1 ? ";" : " + ..."
        );
    }
}
