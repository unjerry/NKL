#ifndef QUAT_H
#define QUAT_H
#include "math_template/matrix_over_field.h"
class quat
{
public:
    matrix_over_field<long double> M;
    quat(/* args */);
    ~quat();
};

quat::quat(/* args */)
{
}

quat::~quat()
{
}

#endif
