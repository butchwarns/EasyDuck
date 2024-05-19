/*
ParamBase.h
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

#ifndef _PARAM_BASE_H
#define _PARAM_BASE_H

#include <JuceHeader.h>

class ParamBase
{
public:
    ParamBase() = default;
    ~ParamBase() = default;

    inline static void constrain_string_length(String &s, int max_len)
    {
        const int len = s.length();
        if (len > max_len)
        {
            s = s.dropLastCharacters(len - max_len);
        }
    }

protected:
    static const juce::NormalisableRange<float> RANGE_DEFAULT;
    static const juce::AudioProcessorParameter::Category CATEGORY_DEFAULT;
};

#endif // _PARAM_BASE_H_