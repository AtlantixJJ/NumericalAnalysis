#include "lagrangeinterpolation.h"

#include <cmath>
#include <cstdio>
#include <string>

LagrangeInterpolation::LagrangeInterpolation(const PointList& points)
    : Interpolation(points, LAGRANGE)
{

}

void LagrangeInterpolation::doInterpolation()
{

}

double LagrangeInterpolation::getPointValue(double x) const
{
    double res = 0;
    for (int i = 0; i <= m_n; i++)
    {
        double s = 1;
        for (int j = 0; j <= m_n; j++)
            if (j != i) s *= (x - m_points[j].first) / (m_points[i].first - m_points[j].first);
        res += s * m_points[i].second;
    }
    return res;
}

void LagrangeInterpolation::printPolynomial() const
{
    printf("f = ");
    for (int i = 0; i <= m_n; i++)
    {
        double s = 1;
        for (int j = 0; j <= m_n; j++)
            if (j != i) s *= m_points[i].first - m_points[j].first;
        s = m_points[i].second / s;

        if (i > 0) printf("  %s", formatDouble(s).c_str());
        else printf("%.9le", s);

        for (int j = 0; j <= m_n; j++)
            if (j != i) printf(" .* (x %s)", formatDouble(-m_points[j].first, "%.2lf").c_str());

        printf("%s\n", i == m_n ? ";" : " ...");
    }
}
