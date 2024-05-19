/*
ParamFloat.cpp
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

#include "ParamFloat.h"

ParamFloat::ParamFloat(const juce::String _name,
                       int _version,
                       float _val_default,
                       std::function<String(float value, int maximumStringLength)> _string_from_value,
                       juce::AudioProcessorParameter::Category _category,
                       juce::NormalisableRange<float> _range)
    : name(_name),
      version(_version),
      val_default(_val_default),
      string_from_value(_string_from_value),
      category(_category),
      range(_range)
{
}

std::unique_ptr<juce::AudioParameterFloat> ParamFloat::parameter()
{
    return std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(id(), version),
                                                       name,
                                                       range,
                                                       val_default,
                                                       "",
                                                       category,
                                                       string_from_value);
}

String ParamFloat::id() const
{
    return name.toUpperCase();
}