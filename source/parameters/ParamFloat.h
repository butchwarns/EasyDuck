#ifndef _PARAM_FLOAT_H
#define _PARAM_FLOAT_H

#include <JuceHeader.h>

static const auto RANGE_DEFAULT = juce::NormalisableRange<float>(0.0f, 1.0f, 0.0000001f);
static const auto CATEGORY_DEFAULT = juce::AudioProcessorParameter::genericParameter;

class ParamFloat
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
    int version;
    float val_default;
    std::function<String(float value, int maximumStringLength)> string_from_value;
    juce::AudioProcessorParameter::Category category;
    juce::NormalisableRange<float> range;

protected:
    static void constrain_string_length(String &s, int max_len)
    {
        const int len = s.length();
        if (len > max_len)
        {
            s = s.dropLastCharacters(len - max_len);
        }
    }
};

#endif // _PARAM_FLOAT_H