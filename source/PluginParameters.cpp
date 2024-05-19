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
    : param_mode(), param_duck(),
      apvts(processor, nullptr, "parameters", parameter_layout())
{
    normval_mode = apvts.getRawParameterValue(param_mode.id());
    normval_duck = apvts.getRawParameterValue(param_duck.id());
}

float PluginParameters::mode()
{
    return *normval_mode;
}

float PluginParameters::duck()
{
    return (float)param_duck.denormalise(*normval_duck);
}

Apvts::ParameterLayout PluginParameters::parameter_layout()
{
    Apvts::ParameterLayout layout;

    typedef juce::AudioProcessorParameterGroup ParameterGroup;

    auto grp_easyduck = std::make_unique<ParameterGroup>("EasyDuck", "EASY_DUCK", "|");
    grp_easyduck->addChild(param_mode.parameter());
    grp_easyduck->addChild(param_duck.parameter());

    layout.add(std::move(grp_easyduck));

    return layout;
}
