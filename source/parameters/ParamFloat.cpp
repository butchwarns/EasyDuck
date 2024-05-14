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