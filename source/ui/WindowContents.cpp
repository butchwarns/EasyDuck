/*
WindowContents.cpp
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

#include "WindowContents.h"

WindowContents::WindowContents(PluginProcessor &_processor)
    : processor(_processor), generic_editor(_processor)
{
    addAndMakeVisible(generic_editor);
}

void WindowContents::paint(Graphics &g)
{
    ignoreUnused(g);
}

void WindowContents::resized()
{
    auto bounds = getLocalBounds();

    generic_editor.setBounds(bounds);
}