/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.3.0

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "PianoController.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class KeyboardComponent  : public Component,
                           public MidiKeyboardStateListener,
                           public PianoController::Listener
{
public:
    //==============================================================================
    KeyboardComponent (PianoController& pianoController);
    ~KeyboardComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void handleNoteOn(MidiKeyboardState *source, int midiChannel, int midiNoteNumber, float velocity) override;
    void handleNoteOff(MidiKeyboardState *source, int midiChannel, int midiNoteNumber, float velocity) override;
	void PianoNoteMessage(const MidiMessage& message) override;
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	MidiKeyboardState keyState;
    PianoController& pianoController;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<MidiKeyboardComponent> midiKeyboardComponent;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KeyboardComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
