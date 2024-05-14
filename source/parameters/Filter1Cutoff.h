#ifndef _PARAM_CUTOFF_H_
#define _PARAM_CUTOFF_H_

#include <JuceHeader.h>
#include "ParamFloat.h"
#include <bdsp/cv/VoltPerOctave.h>

const double FREQ_ZERO_VOLT = bdsp::constants::MIN_FILTER_FREQ * pow(2.0, 5.0);
constexpr double CV_MIN = -5.0;
constexpr double CV_MAX = 5.0;

class Filter1Cutoff : public ParamFloat
{
public:
    Filter1Cutoff();
    ~Filter1Cutoff() = default;

    static double normalise(double gain);
    static double denormalise(double val_norm);
    static String string_from_value(float value, int len_string_max);
    static Optional<double> value_from_string(const String &string);
};
#endif // _PARAM_CUTOFF_H_