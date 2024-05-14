#include "ParamGain.h"
#include <bdsp/utility.h>
#include <bdsp/mappings.h>
#include <bdsp/decibel.h>

ParamGain::ParamGain() : ParamFloat("GAIN",
                                    1,
                                    (float)normalise_db(0.0),
                                    string_from_value)
{
}

double ParamGain::normalise(double gain)
{
    const double db = bdsp::decibel::raw_gain_to_db(gain);
    const auto val_norm = normalise_db(db);
    return val_norm;
}

double ParamGain::normalise_db(double db)
{
    double val_norm = bdsp::mappings::normalise<double>(db, GAIN_MIN, GAIN_MAX);
    val_norm = skew(val_norm);

    return val_norm;
}

double ParamGain::denormalise(double val_norm)
{
    const auto db = denormalise_db(val_norm);
    const double gain = bdsp::decibel::db_to_raw_gain(db);

    return gain;
}

double ParamGain::denormalise_db(double val_norm)
{
    val_norm = unskew(val_norm);
    const auto db = bdsp::mappings::linear_norm<double>(val_norm, GAIN_MIN, GAIN_MAX);

    return db;
}

double ParamGain::skew(double val_norm)
{
    const double zero_norm = bdsp::mappings::normalise(0.0, GAIN_MIN, GAIN_MAX);

    if (val_norm <= zero_norm)
    {
        return bdsp::mappings::linear(val_norm, 0.0, zero_norm, 0.0, 0.5);
    }

    return bdsp::mappings::linear(val_norm, zero_norm, 1.0, 0.5, 1.0);
}

double ParamGain::unskew(double val_skewed)
{
    const double zero_norm = bdsp::mappings::normalise(0.0, GAIN_MIN, GAIN_MAX);

    if (val_skewed <= 0.5)
    {
        return bdsp::mappings::linear(val_skewed, 0.0, 0.5, 0.0, zero_norm);
    }

    return bdsp::mappings::linear(val_skewed, 0.5, 1.0, zero_norm, 1.0);
}

String ParamGain::string_from_value(float value, int max_string_len)
{
    const double val_denorm = denormalise_db(value);
    std::stringstream val_formatted;
    const int num_decimal_places = 1;
    const String value_suffix = "dB";

    val_formatted << std::fixed << std::setprecision(num_decimal_places);
    val_formatted << val_denorm << value_suffix;
    String val_formatted_str = val_formatted.str();

    constrain_string_length(val_formatted_str, max_string_len);

    return val_formatted_str;
}

Optional<double> ParamGain::value_from_string(const String &string)
{
    if (string.endsWithIgnoreCase("dB"))
    {
        string.dropLastCharacters(2);
    }

    try
    {
        double value = 0.0;
        value = std::stod(string.toStdString());
        value = normalise_db(value);

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