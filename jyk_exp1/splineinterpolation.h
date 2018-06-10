#ifndef SPLINE_INTERPOLATION_H
#define SPLINE_INTERPOLATION_H

#include "interpolation.h"

class SplineInterpolation : public Interpolation
{
public:
    SplineInterpolation(const PointList& points);
    virtual ~SplineInterpolation();

    void setBoundary(double df0, double dfn) { m_df0 = df0, m_dfn = dfn; }

    virtual const char* getMethodName() const override { return "Spline"; }

    virtual void doInterpolation() override;

    virtual double getPointValue(double x) const override;

    virtual void printPolynomial() const override;

private:
    double m_df0, m_dfn;
    double *m_h, *m_M;

    double xxx(double x) const { return x * x * x; }

    double differences(int i) const
    {
        return (m_points[i + 1].second - m_points[i].second) / m_h[i];
    }
};

#endif // SPLINE_INTERPOLATION_H
