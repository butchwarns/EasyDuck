#ifndef _PARAM_GAIN_H_
#define _PARAM_GAIN_H_

#include "ParamFloat.h"

constexpr double GAIN_MIN = -24.0;
constexpr double GAIN_MAX = 48.0;

class ParamGain : public ParamFloat
{
public:
    ParamGain();
    ~ParamGain() = default;

    static double normalise(double gain);
    static double normalise_db(double db);
    static double denormalise(double val_norm);
    static double denormalise_db(double val_norm);
    static double skew(double val_norm);
    static double unskew(double val_skewed);
    static String string_from_value(float value, int max_string_len);
    static Optional<double> value_from_string(const String &string);
};

#endif // _PARAM_GAIN_H_