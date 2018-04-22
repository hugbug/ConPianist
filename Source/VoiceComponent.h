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
#include "Presets.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class VoiceComponent  : public Component,
                        public PianoController::Listener,
                        public Button::Listener
{
public:
    //==============================================================================
    VoiceComponent (PianoController& pianoController);
    ~VoiceComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void PianoStateChanged() override { MessageManager::callAsync([=](){updateVoiceState();}); }
    void updateVoiceState();
    static String voiceTitle(String preset);
    void buildVoiceTree();
    void voiceItemClicked(Voice* voice);
    void voiceButtonClicked(Button* button);
    void scrollToVoice(const String& preset);
	void updateEnabledControls();
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    PianoController& pianoController;
    TreeViewItem* rootItem;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TreeView> voicesTree;
    ScopedPointer<GroupComponent> targetGroup;
    ScopedPointer<TextButton> leftVoiceButton;
    ScopedPointer<TextButton> mainVoiceButton;
    ScopedPointer<TextButton> layerVoiceButton;
    ScopedPointer<TextButton> mainTitleButton;
    ScopedPointer<TextButton> leftTitleButton;
    ScopedPointer<TextButton> layerTitleButton;
    ScopedPointer<Label> leftIndicatorLabel;
    ScopedPointer<Label> mainIndicatorLabel;
    ScopedPointer<Label> layerIndicatorLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VoiceComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
