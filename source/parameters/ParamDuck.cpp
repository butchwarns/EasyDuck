#include "ParamDuck.h"
#include <bdsp/utility.h>
#include <bdsp/mappings.h>
#include <bdsp/decibel.h>

ParamDuck::ParamDuck() : ParamFloat("DUCK",
                                    1,
                                    (float)normalise(0.0),
                                    string_from_value)
{
}

double ParamDuck::normalise(double percent)
{
    const auto val_norm = percent / 100.0;

    return val_norm;
}

double ParamDuck::denormalise(double val_norm)
{
    const double percent = val_norm * 100.0;

    return percent;
}

String ParamDuck::string_from_value(float value, int max_string_len)
{
    const double val_denorm = denormalise(value);

    std::stringstream val_formatted;
    // Format value string to the correct number of decimal places
    const int num_decimal_places = 1;
    const String value_suffix = "%";
    val_formatted << std::fixed << std::setprecision(num_decimal_places);
    val_formatted << val_denorm << value_suffix;

    String val_formatted_str = val_formatted.str();

    constrain_string_length(val_formatted_str, max_string_len);

    return val_formatted_str;
}

Optional<double> ParamDuck::value_from_string(const String &string)
{
    if (string.endsWithIgnoreCase("%"))
    {
        string.dropLastCharacters(1);
    }

    try
    {
        double value = 0.0;
        value = std::stod(string.toStdString());
        value = normalise(value);

        return value;
    }
    catch (const std::invalid_argument &e)
    {
    }
    catch (const std::out_of_range &e)
    {
    }

    return std::nullopt;
}