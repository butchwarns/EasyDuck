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