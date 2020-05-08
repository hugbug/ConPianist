/*
 *  This file is part of ConPianist. See <https://github.com/hugbug/conpianist>.
 *
 *  Copyright (C) 2018 Andrey Prygunkov <hugbug@users.sourceforge.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class LookAndFeel : public juce::LookAndFeel_V4
{
public:
	static void showModalDialog(Component* comp, const String& title);

	void drawButtonBackground(Graphics&, Button&, const Colour& backgroundColour,
		bool isMouseOverButton, bool isButtonDown) override;

	void drawImageButton(Graphics&, Image*,
		int imageX, int imageY, int imageW, int imageH,
		const Colour& overlayColour, float imageOpacity, ImageButton&) override;

	void drawLinearSlider(Graphics&, int x, int y, int width, int height,
		float sliderPos, float minSliderPos, float maxSliderPos,
		const Slider::SliderStyle, Slider&) override;

	void drawRotarySlider(Graphics&, int x, int y, int width, int height,
		float sliderPosProportional, float rotaryStartAngle,
		float rotaryEndAngle, Slider&) override;

	void drawLabel(Graphics&, Label&) override;
};
