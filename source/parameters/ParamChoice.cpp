/*
ParamChoice.cpp
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

#include "ParamChoice.h"

ParamChoice::ParamChoice(const juce::String _name,
                         int _version,
                         juce::StringArray _choices,
                         float _index_default,
                         std::function<String(float value, int maximumStringLength)> _string_from_value)

    : name(_name),
      version(_version),
      choices(_choices),
      index_default(_index_default),
      string_from_value(_string_from_value)
{
}

std::unique_ptr<juce::AudioParameterChoice> ParamChoice::parameter()
{
    return std::make_unique<juce::AudioParameterChoice>(juce::ParameterID(id(), version),
                                                        name, choices, index_default, "", string_from_value);
}

String ParamChoice::id() const
{
    return name.toUpperCase();
}