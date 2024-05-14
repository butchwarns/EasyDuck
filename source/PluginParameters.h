/*
PluginParameters.h
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

#ifndef PLUGIN_PARAMETERS_H
#define PLUGIN_PARAMETERS_H

#include <JuceHeader.h>
#include "typedefs.h"
#include "parameters/ParamVolume.h"
#include "parameters/ParamGain.h"

class PluginParameters
{
public:
    explicit PluginParameters(juce::AudioProcessor &processor);

private:
    ParamVolume param_volume;
    std::atomic<float> *normval_volume;
    float volume();

    ParamGain param_gain;
    std::atomic<float> *normval_gain;
    float gain();

    Apvts::ParameterLayout parameter_layout();

public:
    Apvts apvts;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginParameters)
};

#endif // PLUGIN_PARAMETERS_H