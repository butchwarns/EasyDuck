#include "ParamBase.h"

const auto ParamBase::RANGE_DEFAULT = juce::NormalisableRange<float>(0.0f, 1.0f, 0.0000001f);
const auto ParamBase::CATEGORY_DEFAULT = juce::AudioProcessorParameter::genericParameter;