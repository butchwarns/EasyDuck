/*
WindowContents.h
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

#ifndef _WINDOW_CONTENTS_H_
#define _WINDOW_CONTENTS_H_

#include <JuceHeader.h>

class WindowContents : public Component
{
public:
    WindowContents(juce::AudioProcessor &processor);

private:
    void paint(Graphics &g) override;
    void resized() override;

    juce::GenericAudioProcessorEditor generic_editor;
};

#endif // _WINDOW_CONTENTS_H_