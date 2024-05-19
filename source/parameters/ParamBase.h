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