/*
PluginEditor.cpp
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

#include "PluginEditor.h"
#include "PluginProcessor.h"
#include "ui/sizes.h"

PluginEditor::PluginEditor(PluginProcessor &_processor)
    : AudioProcessorEditor(&_processor), processor_ref(_processor), window_contents(_processor)
{
    // // Get (usable) screen size, might be useful later..
    // const juce::Displays::Display *display = juce::Desktop::getInstance().getDisplays().getPrimaryDisplay();
    // juce::Rectangle<int> user_area = display->userArea;

    const auto width_saved = (int)processor_ref.get_saved_window_width();
    const auto height_saved = (int)processor_ref.get_saved_window_height();
    setSize(width_saved, height_saved);

    // Make window resizable only with corner resizer, not by host
    setResizable(false, true);

    // Constrain aspect ratio
    setFixedAspectRatio((float)sizes_ui::WIN_WIDTH / (float)sizes_ui::WIN_HEIGHT);
    setMinimumSize(sizes_ui::WIN_WIDTH / 2, sizes_ui::WIN_HEIGHT / 2);
    setConstrainer(this);

    addAndMakeVisible(&window_contents);
}

PluginEditor::~PluginEditor()
{
    setLookAndFeel(nullptr);
}

void PluginEditor::paint(juce::Graphics &g)
{
    g.fillAll(juce::Colours::black);
}

void PluginEditor::resized()
{
    const float window_scale = (float)getWidth() / (float)sizes_ui::WIN_WIDTH;

    window_contents.setBounds(0, 0, sizes_ui::WIN_WIDTH, sizes_ui::WIN_HEIGHT);
    window_contents.setTransform(AffineTransform::scale(window_scale));

    processor_ref.set_saved_window_size(getWidth(), getHeight());
}