#ifndef _PARAM_VOLUME_H_
#define _PARAM_VOLUME_H_

#include "ParamFloat.h"

constexpr double VOLUME_MIN = -66.1;
constexpr double VOLUME_MAX = 35.0;
constexpr double VOLUME_OFF_THRESHOLD = VOLUME_MIN + 0.1;

class ParamVolume : public ParamFloat
{
public:
    ParamVolume();
    ~ParamVolume() = default;

    static double normalise(double gain);
    static double normalise_db(double db);
    static double denormalise(double val_norm);
    static double denormalise_db(double val_norm);
    static double skew(double val_norm);
    static double unskew(double val_skewed);
    static String string_from_value(float value, int max_string_len);
    static Optional<double> value_from_string(const String &string);
};

#endif // _PARAM_VOLUME_H_