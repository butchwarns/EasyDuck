#include "Filter1Cutoff.h"
#include <bdsp/cv/VoltPerOctave.h>
#include <bdsp/mappings.h>

Filter1Cutoff::Filter1Cutoff() : ParamFloat("CUTOFF",
                                            1,
                                            (float)normalise(FREQ_ZERO_VOLT),
                                            string_from_value)
{
}

double Filter1Cutoff::normalise(double frequency)
{
    const double cv = bdsp::cv::VoltPerOctave<double>::freq_to_volt(frequency, FREQ_ZERO_VOLT);
    const auto val_norm = bdsp::mappings::normalise<double>(cv, CV_MIN, CV_MAX);

    return val_norm;
}

double Filter1Cutoff::denormalise(double val_norm)
{
    const auto cv = bdsp::mappings::linear_norm<double>(val_norm, CV_MIN, CV_MAX);
    const double frequency = bdsp::cv::VoltPerOctave<double>::volt_to_freq(cv, FREQ_ZERO_VOLT);

    return frequency;
}

String Filter1Cutoff::string_from_value(float value, int len_string_max)
{
    const double val_denorm = denormalise(value);

    const int num_decimal_places = 0;
    const String value_suffix = "Hz";

    std::stringstream val_formatted;
    val_formatted << std::fixed << std::setprecision(num_decimal_places);
    val_formatted << val_denorm << value_suffix.toStdString();
    String string = val_formatted.str();

    constrain_string_length(string, len_string_max);

    return string;
}

Optional<double> Filter1Cutoff::value_from_string(const String &string)
{
    if (string.endsWithIgnoreCase("Hz"))
    {
        string.dropLastCharacters(2);
    }

    try
    {
        double value = 0.0;
        value = std::stod(string.toStdString());
        value = normalise(value);

        return value;
    }
    catch (...)
    {
    }

    return std::nullopt;
}