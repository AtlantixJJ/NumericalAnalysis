#include "interpolation.h"
#include "lagrangeinterpolation.h"
#include "splineinterpolation.h"

#include <cmath>
#include <string>

Interpolation* Interpolation::newInterpolation(const PointList& points,
    InterpolationMethod method)
{
    switch (method)
    {
    case LAGRANGE:
        return new LagrangeInterpolation(points);
    case SPLINE:
        return new SplineInterpolation(points);
    default:
        return nullptr;
    }
}

Interpolation::Interpolation(const PointList& points, InterpolationMethod method)
    : m_n(points.size() - 1), m_points(points), m_method(method)
{

}

std::string Interpolation::formatDouble(double v, const char* format) const
{
    char* s = new char[256];
    sprintf(s, format, abs(v));
    std::string str = v < 0 ? "- " : "+ ";
    str += s;
    delete[] s;
    return str;
}
