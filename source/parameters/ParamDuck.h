#ifndef _PARAM_DUCK_H_
#define _PARAM_DUCK_H_

#include "ParamFloat.h"

class ParamDuck : public ParamFloat
{
public:
    ParamDuck();
    ~ParamDuck() = default;

    static double normalise(double percent);
    static double denormalise(double val_norm);
    static String string_from_value(float value, int max_string_len);
    static Optional<double> value_from_string(const String &string);
};

#endif // _PARAM_DUCK_H_