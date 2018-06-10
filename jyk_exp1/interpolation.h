#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <vector>

class LagrangeInterpolation;
class SplineInterpolation;

class Interpolation
{
public:
    enum InterpolationMethod
    {
        LAGRANGE,
        SPLINE,
    };

    typedef std::vector<std::pair<double, double>> PointList;

    Interpolation(const PointList& points, InterpolationMethod method);
    virtual ~Interpolation() {}

    int getN() const { return m_n; }

    InterpolationMethod getMethod() const { return m_method; }

    virtual const char* getMethodName() const = 0;

    virtual void doInterpolation() = 0;

    virtual double getPointValue(double x) const = 0;

    virtual void printPolynomial() const = 0;

    static Interpolation* newInterpolation(const PointList& points,
        InterpolationMethod method);

protected:
    int m_n;
    PointList m_points;

    std::string formatDouble(double v, const char* format = "%.9le") const;

private:
    InterpolationMethod m_method;
};

#endif // INTERPOLATION_H
