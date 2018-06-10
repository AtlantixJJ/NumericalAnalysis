#ifndef LAGRANGE_INTERPOLATION_H
#define LAGRANGE_INTERPOLATION_H

#include "interpolation.h"

class LagrangeInterpolation : public Interpolation
{
public:
    LagrangeInterpolation(const PointList& points);
    virtual ~LagrangeInterpolation() {}

    virtual const char* getMethodName() const override { return "Lagrange"; }

    virtual void doInterpolation() override;

    virtual double getPointValue(double x) const override;

    virtual void printPolynomial() const override;

private:
};

#endif // LAGRANGE_INTERPOLATION_H
