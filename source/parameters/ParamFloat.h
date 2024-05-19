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