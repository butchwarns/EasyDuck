/*
PluginParameters.cpp
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

#include "PluginParameters.h"

PluginParameters::PluginParameters(juce::AudioProcessor &processor)
    : param_volume(),
      param_gain(),
      apvts(processor, nullptr, "parameters", parameter_layout())
{
    normval_volume = apvts.getRawParameterValue(param_volume.id());
    normval_gain = apvts.getRawParameterValue(param_gain.id());
}

float PluginParameters::volume()
{
    return (float)param_volume.denormalise(*normval_volume);
}

float PluginParameters::gain()
{
    return (float)param_volume.denormalise(*normval_gain);
}

Apvts::ParameterLayout PluginParameters::parameter_layout()
{
    Apvts::ParameterLayout layout;

    typedef juce::AudioProcessorParameterGroup ParameterGroup;

    auto grp_output = std::make_unique<ParameterGroup>("output", "OUTPUT", "|");
    grp_output->addChild(param_volume.parameter());
    grp_output->addChild(param_gain.parameter());

    layout.add(std::move(grp_output));

    return layout;
}
