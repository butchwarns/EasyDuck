/*
PluginProcessor.cpp
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

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ui/sizes.h"

int PluginProcessor::window_width_saved = sizes_ui::WIN_WIDTH;
int PluginProcessor::window_height_saved = sizes_ui::WIN_HEIGHT;

PluginProcessor::PluginProcessor()
    : AudioProcessor(BusesProperties()
                         .withInput("Input", juce::AudioChannelSet::stereo())
                         .withOutput("Output", juce::AudioChannelSet::stereo(), true)
                         .withInput("Sidechain", juce::AudioChannelSet::stereo())),
      parameters(*this)
{
}

PluginProcessor::~PluginProcessor()
{
}

const juce::String PluginProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PluginProcessor::acceptsMidi() const
{
    return true;
}

bool PluginProcessor::producesMidi() const
{
    return false;
}

bool PluginProcessor::isMidiEffect() const
{
    return false;
}

double PluginProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PluginProcessor::getNumPrograms()
{
    return 1; // NB: some hosts don't cope very well if you tell them there are 0 programs,
              // so this should be at least 1, even if you're not really implementing programs.
}

int PluginProcessor::getCurrentProgram()
{
    return 0;
}

void PluginProcessor::setCurrentProgram(int index)
{
    juce::ignoreUnused(index);
}

const juce::String PluginProcessor::getProgramName(int index)
{
    juce::ignoreUnused(index);
    return {};
}

void PluginProcessor::changeProgramName(int index, const juce::String &newName)
{
    juce::ignoreUnused(index, newName);
}

void PluginProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::ignoreUnused(sampleRate, samplesPerBlock);
}

void PluginProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool PluginProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const
{
    // Do not support disabled inputs/outputs
    if (layouts.getMainInputChannelSet() == juce::AudioChannelSet::disabled() || layouts.getMainOutputChannelSet() == juce::AudioChannelSet::disabled())
        return false;

    // Stereo output
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
    {
        return false;
    }

    // Stereo input
    if (layouts.getMainInputChannelSet() != juce::AudioChannelSet::stereo())
    {
        return false;
    }

    // Stereo sidechain input
    if (layouts.getNumChannels(true, 2) != 2)
    {
        return false;
    }

    return true;
}

void PluginProcessor::processBlock(juce::AudioBuffer<float> &buffer,
                                   juce::MidiBuffer &midiMessages)
{
    juce::ignoreUnused(midiMessages);

    juce::ScopedNoDenormals noDenormals;
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    const int OFFSET_SIDECHAIN_CHANNELS = 2;

    for (int channel = 0; channel < totalNumOutputChannels; ++channel)
    {
        auto input_sidechain = buffer.getReadPointer(channel + OFFSET_SIDECHAIN_CHANNELS);

        auto *y = buffer.getWritePointer(channel);

        for (int i = 0; i < buffer.getNumSamples(); ++i)
        {
            y[i] += input_sidechain[i];
        }
    }
}

bool PluginProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor *PluginProcessor::createEditor()
{
    return new PluginEditor(*this);
}

void PluginProcessor::getStateInformation(juce::MemoryBlock &destData)
{
    // Save window size to state
    auto elem = parameters.apvts.state.getOrCreateChildWithName("window_size", nullptr);
    elem.setProperty("window_width", window_width_saved, nullptr);
    elem.setProperty("window_height", window_height_saved, nullptr);

    auto state = parameters.apvts.copyState();

    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void PluginProcessor::setStateInformation(const void *data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xml = getXmlFromBinary(data, sizeInBytes);
    if (xml != nullptr)
    {
        if (xml->hasTagName(parameters.apvts.state.getType()))
        {
            auto state = juce::ValueTree::fromXml(*xml);
            parameters.apvts.replaceState(state);

            // Restore window size from state
            auto elem = parameters.apvts.state.getChildWithName("window_size");
            const int width = elem.getProperty("window_width");
            const int height = elem.getProperty("window_height");
            set_saved_window_size(width, height);
        }
    }
}

void PluginProcessor::set_saved_window_size(int _window_width_saved, int _window_height_saved)
{
    window_width_saved = _window_width_saved;
    window_height_saved = _window_height_saved;
}

int PluginProcessor::get_saved_window_width()
{
    return window_width_saved;
}

int PluginProcessor::get_saved_window_height()
{
    return window_height_saved;
}

// This creates new instances of the plugin..
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}
