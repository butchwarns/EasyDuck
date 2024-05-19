/*
ParamFloat.h
Copyright (C) 2024 Butch Warns

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef _PARAM_FLOAT_H
#define _PARAM_FLOAT_H

#include "ParamBase.h"
#include <JuceHeader.h>

class ParamFloat : public ParamBase
{
public:
    ParamFloat(const juce::String _name,
               int _version,
               float _val_default,
               std::function<String(float value, int maximumStringLength)> _string_from_value = nullptr,
               juce::AudioProcessorParameter::Category _category = CATEGORY_DEFAULT,
               juce::NormalisableRange<float> _range = RANGE_DEFAULT);
    ~ParamFloat() = default;

    String id() const;

    std::unique_ptr<juce::AudioParameterFloat> parameter();

private:
    const juce::String name;
    const int version;
    const float val_default;
    std::function<String(float value, int maximumStringLength)> string_from_value;
    const juce::AudioProcessorParameter::Category category;
    const juce::NormalisableRange<float> range;
};

#endif // _PARAM_FLOAT_H