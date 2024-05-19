#ifndef _PARAM_CHOICE_H
#define _PARAM_CHOICE_H

#include "ParamBase.h"
#include <JuceHeader.h>

class ParamChoice : public ParamBase
{
public:
    ParamChoice(const juce::String _name,
                int _version,
                juce::StringArray _choices,
                float _index_default,
                std::function<String(float value, int maximumStringLength)> _string_from_value = nullptr);
    ~ParamChoice() = default;

    String id() const;

    std::unique_ptr<juce::AudioParameterChoice> parameter();

private:
    const juce::String name;
    const int version;
    const juce::StringArray choices;
    const float index_default;
    std::function<String(float value, int maximumStringLength)> string_from_value;

protected:
};

#endif // _PARAM_CHOICE_H