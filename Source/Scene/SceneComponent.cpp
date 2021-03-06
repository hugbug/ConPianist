/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.7

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#include "ConnectionComponent.h"
#include "BalanceComponent.h"
#include "RegistrationMemory.h"
#include "GuiHelper.h"
//[/Headers]

#include "SceneComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
SceneComponent::SceneComponent (Settings& settings)
    : settings(settings)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    topbarPanel.reset (new GroupComponent ("Top Bar",
                                           TRANS("Top Bar")));
    addAndMakeVisible (topbarPanel.get());
    topbarPanel->setTextLabelPosition (Justification::centred);

    playbackPanel.reset (new Component());
    addAndMakeVisible (playbackPanel.get());
    playbackPanel->setName ("Playback Panel");

    largeContentPanel.reset (new Component());
    addAndMakeVisible (largeContentPanel.get());
    largeContentPanel->setName ("Large Content");

    muteButton.reset (new ImageButton ("Mute Button"));
    addAndMakeVisible (muteButton.get());
    muteButton->setTooltip (TRANS("Local Control on/off"));
    muteButton->setButtonText (TRANS("Mute"));
    muteButton->addListener (this);

    muteButton->setImages (false, true, true,
                           ImageCache::getFromMemory (BinaryData::buttonvolume_png, BinaryData::buttonvolume_pngSize), 1.000f, Colour (0x00000000),
                           Image(), 0.750f, Colour (0x00000000),
                           Image(), 1.000f, Colour (0x00000000));
    zoomInButton.reset (new ImageButton ("Zoom In UI Button"));
    addAndMakeVisible (zoomInButton.get());
    zoomInButton->setTooltip (TRANS("Zoom In UI"));
    zoomInButton->setButtonText (TRANS("Mute"));
    zoomInButton->addListener (this);

    zoomInButton->setImages (false, true, true,
                             ImageCache::getFromMemory (BinaryData::buttonzoomin_png, BinaryData::buttonzoomin_pngSize), 1.000f, Colour (0x00000000),
                             Image(), 0.750f, Colour (0x00000000),
                             Image(), 1.000f, Colour (0x00000000));
    zoomOutButton.reset (new ImageButton ("Zoom Out UI Button"));
    addAndMakeVisible (zoomOutButton.get());
    zoomOutButton->setTooltip (TRANS("Zoom Out UI"));
    zoomOutButton->setButtonText (TRANS("Mute"));
    zoomOutButton->addListener (this);

    zoomOutButton->setImages (false, true, true,
                              ImageCache::getFromMemory (BinaryData::buttonzoomout_png, BinaryData::buttonzoomout_pngSize), 1.000f, Colour (0x00000000),
                              Image(), 0.750f, Colour (0x00000000),
                              Image(), 1.000f, Colour (0x00000000));
    keyboardPanel.reset (new Component());
    addAndMakeVisible (keyboardPanel.get());
    keyboardPanel->setName ("Keyboard Panel");

    keyboardButton.reset (new ImageButton ("Virtual Keyboard Button"));
    addAndMakeVisible (keyboardButton.get());
    keyboardButton->setTooltip (TRANS("Virtual Keyboard"));
    keyboardButton->setButtonText (TRANS("Virtual Keyboard"));
    keyboardButton->addListener (this);

    keyboardButton->setImages (false, true, true,
                               ImageCache::getFromMemory (BinaryData::buttonkeyboard_png, BinaryData::buttonkeyboard_pngSize), 1.000f, Colour (0x00000000),
                               Image(), 0.750f, Colour (0x00000000),
                               Image(), 1.000f, Colour (0x00000000));
    balanceButton.reset (new ImageButton ("Balance Button"));
    addAndMakeVisible (balanceButton.get());
    balanceButton->setTooltip (TRANS("Balance"));
    balanceButton->setButtonText (TRANS("Balance"));
    balanceButton->addListener (this);

    balanceButton->setImages (false, true, true,
                              ImageCache::getFromMemory (BinaryData::buttonbalance_png, BinaryData::buttonbalance_pngSize), 1.000f, Colour (0x00000000),
                              Image(), 0.750f, Colour (0x00000000),
                              Image(), 1.000f, Colour (0x00000000));
    voiceButton.reset (new TextButton ("Voice Button"));
    addAndMakeVisible (voiceButton.get());
    voiceButton->setTooltip (TRANS("Voice Selection"));
    voiceButton->setButtonText (TRANS("Voice"));
    voiceButton->addListener (this);

    scoreButton.reset (new TextButton ("Score Button"));
    addAndMakeVisible (scoreButton.get());
    scoreButton->setTooltip (TRANS("Score View"));
    scoreButton->setButtonText (TRANS("Score"));
    scoreButton->addListener (this);

    statusLabel.reset (new Label ("Status Label",
                                  TRANS("Looking for the instrument")));
    addAndMakeVisible (statusLabel.get());
    statusLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    statusLabel->setJustificationType (Justification::centredLeft);
    statusLabel->setEditable (false, false, false);
    statusLabel->setColour (TextEditor::textColourId, Colours::black);
    statusLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    statusLabel->setBounds (48, 11, 240, 24);

    mixerButton.reset (new TextButton ("Mixer Button"));
    addAndMakeVisible (mixerButton.get());
    mixerButton->setTooltip (TRANS("Channel Mixer"));
    mixerButton->setButtonText (TRANS("Mixer"));
    mixerButton->addListener (this);

    menuButton.reset (new ImageButton ("Menu Button"));
    addAndMakeVisible (menuButton.get());
    menuButton->setTooltip (TRANS("Main Menu"));
    menuButton->setButtonText (TRANS("Menu"));
    menuButton->addListener (this);

    menuButton->setImages (false, true, true,
                           ImageCache::getFromMemory (BinaryData::buttonmenu_png, BinaryData::buttonmenu_pngSize), 1.000f, Colour (0x00000000),
                           Image(), 0.750f, Colour (0x00000000),
                           Image(), 1.000f, Colour (0x00000000));
    menuButton->setBounds (8, 8, 32, 28);


    //[UserPreSize]
    topbarPanel->setColour(GroupComponent::outlineColourId, Colours::transparentBlack);
    topbarPanel->setText("");

	playbackComponent.reset(new PlaybackComponent(settings, pianoController));
	playbackPanel->addAndMakeVisible(playbackComponent.get());

	keyboardComponent.reset(new KeyboardComponent(settings, pianoController));
	keyboardPanel->addAndMakeVisible(keyboardComponent.get());

	voiceComponent.reset(new VoiceComponent(settings, pianoController));
	scoreComponent.reset(ScoreComponent::Create(settings, pianoController));
	mixerComponent.reset(new MixerComponent(settings, pianoController));
	largeContentPanel->addChildComponent(voiceComponent.get());
    largeContentPanel->addChildComponent(scoreComponent.get());
	largeContentPanel->addChildComponent(mixerComponent.get());
	voiceButton->getProperties().set("tab", "yes");
	scoreButton->getProperties().set("tab", "yes");
	mixerButton->getProperties().set("tab", "yes");
    keyboardButton->getProperties().set("toggle", "yes");
    //[/UserPreSize]

    setSize (850, 550);


    //[Constructor] You can add your own custom stuff here..
	pianoConnector.startThread();
    pianoController.SetPianoConnector(&pianoConnector);
    pianoController.AddListener(this);
    settings.addChangeListener(this);
	applySettings();
	updateSettingsState();

	switchLargePanel(scoreButton.get());

	startTimer(250);
    //[/Constructor]
}

SceneComponent::~SceneComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    if (rtpMidiConnector)
    {
		rtpMidiConnector->stopThread(1000);
	}
	pianoConnector.stopThread(1000);

    //[/Destructor_pre]

    topbarPanel = nullptr;
    playbackPanel = nullptr;
    largeContentPanel = nullptr;
    muteButton = nullptr;
    zoomInButton = nullptr;
    zoomOutButton = nullptr;
    keyboardPanel = nullptr;
    keyboardButton = nullptr;
    balanceButton = nullptr;
    voiceButton = nullptr;
    scoreButton = nullptr;
    statusLabel = nullptr;
    mixerButton = nullptr;
    menuButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SceneComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    {
        int x = 0, y = 43, width = getWidth() - 0, height = 1;
        Colour fillColour = Colour (0xff4e5b62);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void SceneComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    topbarPanel->setBounds (0, -8, getWidth() - 0, 52);
    playbackPanel->setBounds (0, (-8) + 52, 290, getHeight() - 111);
    largeContentPanel->setBounds (0 + 290, (-8) + 52, getWidth() - 290, getHeight() - 111);
    muteButton->setBounds (getWidth() - 80 - 32, 8, 32, 28);
    zoomInButton->setBounds (getWidth() - 10 - 32, 8, 32, 28);
    zoomOutButton->setBounds (getWidth() - 45 - 32, 8, 32, 28);
    keyboardPanel->setBounds (0, getHeight() - 67, getWidth() - 0, 67);
    keyboardButton->setBounds (getWidth() - 115 - 32, 8, 32, 28);
    balanceButton->setBounds (getWidth() - 150 - 32, 8, 32, 28);
    voiceButton->setBounds (0 + 378, (-8) + 18, 80, 34);
    scoreButton->setBounds (0 + 298, (-8) + 18, 80, 34);
    mixerButton->setBounds (0 + 458, (-8) + 18, 80, 34);
    //[UserResized] Add your own custom resize handling here..
    playbackPanel->setBounds(playbackPanel->getX(), playbackPanel->getY(), playbackPanel->getWidth(),
    	playbackPanel->getHeight() + (keyboardPanel->isVisible() ? 0 : keyboardPanel->getHeight()));
    largeContentPanel->setBounds(largeContentPanel->getX(), largeContentPanel->getY(), largeContentPanel->getWidth(),
        largeContentPanel->getHeight() + (keyboardPanel->isVisible() ? 0 : keyboardPanel->getHeight()));
	playbackComponent->setBounds(0, 0, playbackPanel->getWidth(), playbackPanel->getHeight());
    keyboardComponent->setBounds(0, 0, keyboardPanel->getWidth(), keyboardPanel->getHeight());

	if (voiceComponent->isVisible())
	{
		voiceComponent->setBounds(0, 0, largeContentPanel->getWidth(), largeContentPanel->getHeight());
	}
	if (scoreComponent->isVisible())
	{
    	scoreComponent->setBounds(0, 0, largeContentPanel->getWidth(), largeContentPanel->getHeight());
	}
	if (mixerComponent->isVisible())
	{
		mixerComponent->setBounds(0, 0, largeContentPanel->getWidth(), largeContentPanel->getHeight());
	}
    //[/UserResized]
}

void SceneComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == muteButton.get())
    {
        //[UserButtonCode_muteButton] -- add your button handler code here..
        pianoController.SetLocalControl(!pianoController.GetLocalControl());
        //[/UserButtonCode_muteButton]
    }
    else if (buttonThatWasClicked == zoomInButton.get())
    {
        //[UserButtonCode_zoomInButton] -- add your button handler code here..
        zoomUi(true);
        //[/UserButtonCode_zoomInButton]
    }
    else if (buttonThatWasClicked == zoomOutButton.get())
    {
        //[UserButtonCode_zoomOutButton] -- add your button handler code here..
        zoomUi(false);
        //[/UserButtonCode_zoomOutButton]
    }
    else if (buttonThatWasClicked == keyboardButton.get())
    {
        //[UserButtonCode_keyboardButton] -- add your button handler code here..
        toggleKeyboard();
        //[/UserButtonCode_keyboardButton]
    }
    else if (buttonThatWasClicked == balanceButton.get())
    {
        //[UserButtonCode_balanceButton] -- add your button handler code here..
		BalanceComponent::showDialog(settings, pianoController);
        //[/UserButtonCode_balanceButton]
    }
    else if (buttonThatWasClicked == voiceButton.get())
    {
        //[UserButtonCode_voiceButton] -- add your button handler code here..
		switchLargePanel(buttonThatWasClicked);
        //[/UserButtonCode_voiceButton]
    }
    else if (buttonThatWasClicked == scoreButton.get())
    {
        //[UserButtonCode_scoreButton] -- add your button handler code here..
		switchLargePanel(buttonThatWasClicked);
        //[/UserButtonCode_scoreButton]
    }
    else if (buttonThatWasClicked == mixerButton.get())
    {
        //[UserButtonCode_mixerButton] -- add your button handler code here..
		switchLargePanel(buttonThatWasClicked);
        //[/UserButtonCode_mixerButton]
    }
    else if (buttonThatWasClicked == menuButton.get())
    {
        //[UserButtonCode_menuButton] -- add your button handler code here..
        showMenu();
        //[/UserButtonCode_menuButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void SceneComponent::PianoStateChanged(PianoController::Aspect aspect, PianoController::Channel channel)
{
	if (aspect == PianoController::apConnection || aspect == PianoController::apLocalControl)
	{
		MessageManager::callAsync([=](){updateSettingsState();});
	}
	if (aspect == PianoController::apConnection && pianoController.IsConnected())
	{
		MessageManager::callAsync([=](){pianoController.Sync();});
	}
	else if (aspect == PianoController::apActive && channel == PianoController::chLeft)
	{
		MessageManager::callAsync([=](){updateKeyboard();});
	}
	else if (aspect == PianoController::apSongLoaded)
	{
		MessageManager::callAsync([=](){loadSongState();});
	}
}

void SceneComponent::updateSettingsState()
{
	bool mute = !pianoController.GetLocalControl() && pianoController.IsConnected();
	muteButton->setImages(false, true, true, ImageCache::getFromMemory(
			mute ? BinaryData::buttonmute_png : BinaryData::buttonvolume_png,
			mute ? BinaryData::buttonmute_pngSize : BinaryData::buttonvolume_pngSize),
			1.000f, Colour (0x00000000), Image(), 0.750f, Colour (0x00000000), Image(), 1.000f, Colour (0x00000000));

	balanceButton->setEnabled(pianoController.IsConnected());
	keyboardButton->setEnabled(pianoController.IsConnected());
	muteButton->setEnabled(pianoController.IsConnected());
}

void SceneComponent::showMenu()
{
	PopupMenu menu;
	menu.addSectionHeader("INSTRUMENT");
	if (pianoController.IsConnected())
	{
		menu.addItem(10, pianoController.GetModel() + " • Firmware " + pianoController.GetVersion(), false, false);
	}
	menu.addItem(1, "Connection Settings");
	menu.addItem(4, "Reset Connection");
	menu.addItem(2, "Resync State from Piano");
	menu.addItem(3, "Reset Piano to Default State");
	menu.addSectionHeader("REGISTRATION MEMORY");
	menu.addItem(101, "Load Piano State");
	menu.addItem(102, "Save Piano State");
	menu.addSectionHeader("ABOUT");
	menu.addItem(998, "Version: \t" + JUCEApplication::getInstance()->getApplicationVersion(), false, false);
	menu.addItem(999, "Homepage");

	GuiHelper::ShowMenuAsync(menu, menuButton.get(),
		[this](int result)
		{
			switch (result)
			{
				case 1:
					ConnectionComponent::showDialog(settings);
					break;
				case 2:
					MessageManager::callAsync([=](){pianoController.Sync();});
					break;
				case 3:
					MessageManager::callAsync([=](){pianoController.Reset();});
					break;
				case 4:
					resetMidiConnector();
					break;
				case 101:
					loadState();
					break;
				case 102:
					saveState();
					break;
				case 999:
					URL("https://github.com/hugbug/conpianist").launchInDefaultBrowser();
					break;
			}
		});
}

void SceneComponent::timerCallback()
{
	checkConnection();
}

void SceneComponent::checkConnection()
{
	if (!midiConnector->IsConnected())
	{
		pianoController.Disconnect();
	}

	Time curTime = Time::getCurrentTime();

	if (!pianoController.IsConnected())
	{
		String prefix = midiConnector->IsConnected() ? "Connecting to the instrument" : "Looking for the instrument";
		String status = statusLabel->getText();
		if (status.startsWith(prefix) && status.length() < prefix.length() + 10)
		{
			status += ".";
		}
		else
		{
			status = prefix;
		}
		statusLabel->setText(status, NotificationType::dontSendNotification);
		statusLabel->setColour(Label::textColourId, Colours::white);

		if (midiConnector->IsConnected() && pianoConnector.QueueSize() == 0)
		{
			pianoController.Connect();
		}

		if ((pianoConnector.GetAttempt() > 2 && (curTime - pianoConnector.GetStallTime()).inSeconds() > ResetStalledInterval) ||
			(curTime - lastResetTime).inSeconds() > ResetConnectingInterval)
		{
			resetMidiConnector();
		}
	}
	else if (pianoConnector.GetAttempt() > 2 && (curTime - pianoConnector.GetStallTime()).inSeconds() > ResetStalledInterval)
	{
		resetMidiConnector();
	}
	else
	{
		int queueSize = pianoConnector.QueueSize();
		if (queueSize > 0)
		{
			String status = statusLabel->getText();
			int pos = status.indexOf(".");
			int numDots = pos == -1 ? 0 : status.length() - pos;
			numDots = numDots < 10 ? numDots + 1 : 0;
			status = "Exchanging " + String(queueSize) + " messages" + String::repeatedString(".", numDots);
			statusLabel->setText(status, NotificationType::dontSendNotification);
		}
		else
		{
			statusLabel->setText("Connected and ready", NotificationType::dontSendNotification);
		}
		bool stalled = queueSize > 0 && pianoConnector.GetAttempt() > 1 &&
			(curTime - pianoConnector.GetStallTime()).inSeconds() > IndicateStalledInterval;
		statusLabel->setColour(Label::textColourId, stalled ? Colours::red : Colours::white);
	}
}

void SceneComponent::applySettings()
{
	if (currentPianoIp != settings.pianoIp ||
		currentMidiPort != settings.midiPort ||
		!midiConnector)
	{
		resetMidiConnector();
		currentPianoIp = settings.pianoIp;
		currentMidiPort = settings.midiPort;
	}

	float scale = settings.zoomUi;
	scale = std::min(std::max(scale, 0.25f), 4.0f);
	scale = round(scale * 20) / 20;
	Desktop::getInstance().setGlobalScaleFactor(scale);

#if JUCE_ANDROID || JUCE_IOS
	if (getParentComponent())
	{
		Rectangle<int> r = Desktop::getInstance().getDisplays().getMainDisplay().userArea;
		Component* win = (DocumentWindow*)getParentComponent();
		win->setBounds(r.getX(), r.getY(), r.getWidth(), r.getHeight());
	}
#endif

	updateKeyboard();
}

void SceneComponent::resetMidiConnector()
{
	Logger::writeToLog(midiConnector ? "Reset Midi-Connector" : "Init Midi-Connector");

	pianoController.Disconnect();
	pianoConnector.ClearQueue();

	if (midiConnector)
	{
		midiConnector->SetListener(nullptr);
	}

	pianoController.SetRemoteIp(settings.pianoIp);

	if (rtpMidiConnector)
	{
		rtpMidiConnector->stopThread(1000);
	}

	if (settings.midiPort == "")
	{
		rtpMidiConnector = std::make_unique<RtpMidiConnector>(settings.pianoIp, settings.rtpLogging);
		midiConnector = rtpMidiConnector.get();
		pianoConnector.SetMidiConnector(midiConnector);
		rtpMidiConnector->startThread();
		localMidiConnector.reset();
	}
	else
	{
		audioDeviceManager.setMidiInputEnabled(settings.midiPort, true);
		audioDeviceManager.setDefaultMidiOutput(settings.midiPort);
		localMidiConnector = std::make_unique<LocalMidiConnector>(&audioDeviceManager);
		midiConnector = localMidiConnector.get();
		pianoConnector.SetMidiConnector(midiConnector);
		rtpMidiConnector.reset();
	}

	lastResetTime = Time::getCurrentTime();
}

void SceneComponent::zoomUi(bool zoomIn)
{
	float scale = Desktop::getInstance().getGlobalScaleFactor();
	scale += zoomIn ? + 0.05 : -0.05;
	scale = std::min(std::max(scale, 0.25f), 4.0f);
	scale = round(scale * 20) / 20;

	settings.zoomUi = scale;
	settings.Save();
}

void SceneComponent::toggleKeyboard()
{
	if (keyboardPanel->isVisible() && voiceComponent->isVisible() &&
		pianoController.GetActive(PianoController::chLeft))
	{
		keyboardManuallyHidden = true;
	}

	settings.keyboardVisible = !keyboardPanel->isVisible();
	settings.Save();
}

void SceneComponent::updateKeyboard()
{
	keyboardButton->setToggleState(settings.keyboardVisible, NotificationType::dontSendNotification);
	bool keyboardMustBeShown = settings.keyboardVisible ||
		(voiceComponent->isVisible() && pianoController.GetActive(PianoController::chLeft) && !keyboardManuallyHidden);
	if (keyboardPanel->isVisible() != keyboardMustBeShown ||
		keyboardComponent->GetSplitMode() != voiceComponent->isVisible())
	{
		keyboardComponent->SetSplitMode(voiceComponent->isVisible());
		keyboardPanel->setVisible(keyboardMustBeShown);
		keyboardButton->setToggleState(keyboardPanel->isVisible(), NotificationType::dontSendNotification);
		resized();
    }
}

void SceneComponent::switchLargePanel(Button* button)
{
	voiceComponent->setVisible(button == voiceButton.get());
	scoreComponent->setVisible(button == scoreButton.get());
	mixerComponent->setVisible(button == mixerButton.get());

	voiceButton->setToggleState(button == voiceButton.get(), NotificationType::dontSendNotification);
	scoreButton->setToggleState(button == scoreButton.get(), NotificationType::dontSendNotification);
	mixerButton->setToggleState(button == mixerButton.get(), NotificationType::dontSendNotification);

	resized();
	updateKeyboard();
}

void SceneComponent::saveState()
{
	String initialLocation;
	String songname = pianoController.GetSongName();
	if (songname.isEmpty())
	{
		initialLocation = settings.workingDirectory + File::getSeparatorString() + "Untitled.conmem";
	}
	else
	{
		initialLocation = File(songname).withFileExtension(".conmem").getFullPathName();
	}

	GuiHelper::ShowFileSaveDialogAsync("Please select the name for registration memory file...",
		initialLocation, "*.conmem",
		[this](const URL& url)
		{
			settings.workingDirectory = url.getLocalFile().getParentDirectory().getFullPathName();
			settings.Save();
			MessageManager::callAsync([=](){
				// generate access token on sandboxed platforms (iOS)
				std::unique_ptr<OutputStream> outp(url.createOutputStream());
				outp.reset();

				RegistrationMemory::Options opts;
				RegistrationMemory regmem(pianoController, settings, opts, url.getLocalFile());
				regmem.Save();
			});
		});
}

void SceneComponent::loadState()
{
	GuiHelper::ShowFileOpenDialogAsync("Please select the registration memory file to load...",
		settings.workingDirectory, "*.conmem",
		[this](const URL& url)
		{
			settings.workingDirectory = url.getLocalFile().getParentDirectory().getFullPathName();
			settings.Save();
			MessageManager::callAsync([=](){
				// generate access token on sandboxed platforms (iOS)
				std::unique_ptr<InputStream> inp(url.createInputStream(false));

				RegistrationMemory regmem(pianoController, settings, {}, url.getLocalFile());
				regmem.Load();
			});
    	});
}

void SceneComponent::loadSongState()
{
	File file = File(pianoController.GetSongName()).withFileExtension(".conmem");
	if (file.existsAsFile() && file.getSize() > 0)
	{
		RegistrationMemory regmem(pianoController, settings, {}, file);
		regmem.Load();
	}
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SceneComponent" componentName=""
                 parentClasses="public Component, public PianoController::Listener, public ChangeListener, public Timer"
                 constructorParams="Settings&amp; settings" variableInitialisers="settings(settings)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="850" initialHeight="550">
  <BACKGROUND backgroundColour="ff323e44">
    <RECT pos="0 43 0M 1" fill="solid: ff4e5b62" hasStroke="0"/>
  </BACKGROUND>
  <GROUPCOMPONENT name="Top Bar" id="69305d91c2150486" memberName="topbarPanel"
                  virtualName="" explicitFocusOrder="0" pos="0 -8 0M 52" title="Top Bar"
                  textpos="36"/>
  <GENERICCOMPONENT name="Playback Panel" id="cf6dcbcdc3b17ace" memberName="playbackPanel"
                    virtualName="" explicitFocusOrder="0" pos="0 52 290 111M" posRelativeY="69305d91c2150486"
                    class="Component" params=""/>
  <GENERICCOMPONENT name="Large Content" id="5d00b51e97f2c31f" memberName="largeContentPanel"
                    virtualName="" explicitFocusOrder="0" pos="0R 52 290M 111M" posRelativeX="cf6dcbcdc3b17ace"
                    posRelativeY="69305d91c2150486" class="Component" params=""/>
  <IMAGEBUTTON name="Mute Button" id="ca510a4be11fdde2" memberName="muteButton"
               virtualName="" explicitFocusOrder="0" pos="80Rr 8 32 28" posRelativeX="c7b94b60aa96c6e2"
               posRelativeY="c7b94b60aa96c6e2" tooltip="Local Control on/off"
               buttonText="Mute" connectedEdges="0" needsCallback="1" radioGroupId="0"
               keepProportions="1" resourceNormal="BinaryData::buttonvolume_png"
               opacityNormal="1.0" colourNormal="0" resourceOver="" opacityOver="0.75"
               colourOver="0" resourceDown="" opacityDown="1.0" colourDown="0"/>
  <IMAGEBUTTON name="Zoom In UI Button" id="8f2ba3f851b38bd8" memberName="zoomInButton"
               virtualName="" explicitFocusOrder="0" pos="10Rr 8 32 28" posRelativeX="c7b94b60aa96c6e2"
               posRelativeY="c7b94b60aa96c6e2" tooltip="Zoom In UI" buttonText="Mute"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="BinaryData::buttonzoomin_png" opacityNormal="1.0"
               colourNormal="0" resourceOver="" opacityOver="0.75" colourOver="0"
               resourceDown="" opacityDown="1.0" colourDown="0"/>
  <IMAGEBUTTON name="Zoom Out UI Button" id="9c93ecb0c87ce0c4" memberName="zoomOutButton"
               virtualName="" explicitFocusOrder="0" pos="45Rr 8 32 28" posRelativeX="c7b94b60aa96c6e2"
               posRelativeY="c7b94b60aa96c6e2" tooltip="Zoom Out UI" buttonText="Mute"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="BinaryData::buttonzoomout_png" opacityNormal="1.0"
               colourNormal="0" resourceOver="" opacityOver="0.75" colourOver="0"
               resourceDown="" opacityDown="1.0" colourDown="0"/>
  <GENERICCOMPONENT name="Keyboard Panel" id="d578dbfb8bf47c83" memberName="keyboardPanel"
                    virtualName="" explicitFocusOrder="0" pos="0 0Rr 0M 67" class="Component"
                    params=""/>
  <IMAGEBUTTON name="Virtual Keyboard Button" id="802f8ad4daaeee49" memberName="keyboardButton"
               virtualName="" explicitFocusOrder="0" pos="115Rr 8 32 28" posRelativeX="c7b94b60aa96c6e2"
               posRelativeY="c7b94b60aa96c6e2" tooltip="Virtual Keyboard" buttonText="Virtual Keyboard"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="BinaryData::buttonkeyboard_png" opacityNormal="1.0"
               colourNormal="0" resourceOver="" opacityOver="0.75" colourOver="0"
               resourceDown="" opacityDown="1.0" colourDown="0"/>
  <IMAGEBUTTON name="Balance Button" id="b26d1a0a73e9171c" memberName="balanceButton"
               virtualName="" explicitFocusOrder="0" pos="150Rr 8 32 28" tooltip="Balance"
               buttonText="Balance" connectedEdges="0" needsCallback="1" radioGroupId="0"
               keepProportions="1" resourceNormal="BinaryData::buttonbalance_png"
               opacityNormal="1.0" colourNormal="0" resourceOver="" opacityOver="0.75"
               colourOver="0" resourceDown="" opacityDown="1.0" colourDown="0"/>
  <TEXTBUTTON name="Voice Button" id="f0432a7d7961584d" memberName="voiceButton"
              virtualName="" explicitFocusOrder="0" pos="378 18 80 34" posRelativeX="69305d91c2150486"
              posRelativeY="69305d91c2150486" tooltip="Voice Selection" buttonText="Voice"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Score Button" id="470fdf4dc9f8f0cd" memberName="scoreButton"
              virtualName="" explicitFocusOrder="0" pos="298 18 80 34" posRelativeX="69305d91c2150486"
              posRelativeY="69305d91c2150486" tooltip="Score View" buttonText="Score"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="Status Label" id="71086bde8935001" memberName="statusLabel"
         virtualName="" explicitFocusOrder="0" pos="48 11 240 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Looking for the instrument" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="Mixer Button" id="e43c013391cb868" memberName="mixerButton"
              virtualName="" explicitFocusOrder="0" pos="458 18 80 34" posRelativeX="69305d91c2150486"
              posRelativeY="69305d91c2150486" tooltip="Channel Mixer" buttonText="Mixer"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <IMAGEBUTTON name="Menu Button" id="c87eaad1c0559e4c" memberName="menuButton"
               virtualName="" explicitFocusOrder="0" pos="8 8 32 28" posRelativeX="c7b94b60aa96c6e2"
               posRelativeY="c7b94b60aa96c6e2" tooltip="Main Menu" buttonText="Menu"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="BinaryData::buttonmenu_png" opacityNormal="1.0"
               colourNormal="0" resourceOver="" opacityOver="0.75" colourOver="0"
               resourceDown="" opacityDown="1.0" colourDown="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

