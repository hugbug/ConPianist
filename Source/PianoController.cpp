/*
 *  This file is part of ConPianist. See <https://github.com/hugbug/conpianist>.
 *
 *  Copyright (C) 2018-2020 Andrey Prygunkov <hugbug@users.sourceforge.net>
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

#include "PianoController.h"
#include "PianoMessage.h"

static const std::vector<PianoController::Channel> ValidChannelIds = {
	PianoController::chMain, PianoController::chLayer, PianoController::chLeft,
	PianoController::chMidi1, PianoController::chMidi2, PianoController::chMidi3,
	PianoController::chMidi4, PianoController::chMidi5, PianoController::chMidi6,
	PianoController::chMidi7, PianoController::chMidi8, PianoController::chMidi9,
	PianoController::chMidi10, PianoController::chMidi11, PianoController::chMidi12,
	PianoController::chMidi13, PianoController::chMidi14, PianoController::chMidi15,
	PianoController::chMidi16, PianoController::chMic, PianoController::chAuxIn,
	PianoController::chWave, PianoController::chMidiMaster, PianoController::chStyle };

void Sleep(int milliseconds)
{
	Time::waitForMillisecondCounter(Time::getMillisecondCounter() + milliseconds);
}

void PianoController::SetMidiConnector(MidiConnector* midiConnector)
{
	m_midiConnector = midiConnector;
	m_midiConnector->SetListener(this);
}

void PianoController::Connect()
{
	SendCspMessage(PianoMessage(Action::Get, Property::PianoModel));
	SendCspMessage(PianoMessage(Action::Get, Property::FirmwareVersion));
}

void PianoController::InitEvents()
{
	// Activate feedback events from piano
	SendCspMessage(PianoMessage(Action::Events, Property::Length));
	SendCspMessage(PianoMessage(Action::Events, Property::Position));
	SendCspMessage(PianoMessage(Action::Events, Property::Play));
	SendCspMessage(PianoMessage(Action::Events, Property::Part));
	SendCspMessage(PianoMessage(Action::Events, Property::Guide));
	SendCspMessage(PianoMessage(Action::Events, Property::StreamLights));
	SendCspMessage(PianoMessage(Action::Events, Property::StreamLightsSpeed));
	SendCspMessage(PianoMessage(Action::Events, Property::Volume));
	SendCspMessage(PianoMessage(Action::Events, Property::Pan));
	SendCspMessage(PianoMessage(Action::Events, Property::Reverb));
	SendCspMessage(PianoMessage(Action::Events, Property::Octave));
	SendCspMessage(PianoMessage(Action::Events, Property::Tempo));
	SendCspMessage(PianoMessage(Action::Events, Property::Transpose));
	SendCspMessage(PianoMessage(Action::Events, Property::ReverbEffect));
	SendCspMessage(PianoMessage(Action::Events, Property::Loop));
	SendCspMessage(PianoMessage(Action::Events, Property::VoicePreset));
	SendCspMessage(PianoMessage(Action::Events, Property::Active));
	SendCspMessage(PianoMessage(Action::Events, Property::Present));
	SendCspMessage(PianoMessage(Action::Events, Property::VoiceMidi));
	SendCspMessage(PianoMessage(Action::Events, Property::SongName));
}

void PianoController::Sync()
{
	InitEvents();

	SetLocalControl(true);

	m_songLoaded = false;

	m_channels[chAuxIn].enabled = true;
	m_channels[chAuxIn].active = true;

	for (Channel ch : ValidChannelIds)
	{
		m_channels[ch].enabled = (ch < chMidi1 || ch > chMidi16); // these are always enabled

		if (chMidi1 <= ch && ch <= chMidi16)
		{
			SendCspMessage(PianoMessage(Action::Get, Property::Present, ch, 0));
			SendCspMessage(PianoMessage(Action::Get, Property::VoiceMidi, ch, 0));
		}
		if (ch != chAuxIn)
		{
			SendCspMessage(PianoMessage(Action::Get, Property::Active, ch, 0));
			SendCspMessage(PianoMessage(Action::Get, Property::Pan, ch, 0));
			SendCspMessage(PianoMessage(Action::Get, Property::Reverb, ch, 0));
		}

		SendCspMessage(PianoMessage(Action::Get, Property::Volume, ch, 0));

		// Sleep is not nice, we should wait for confirmation messages instead.
		// Without waiting the piano may miss some commands because there are too many.
		Sleep(10);
	}

	SendCspMessage(PianoMessage(Action::Get, Property::Guide));
	SendCspMessage(PianoMessage(Action::Get, Property::StreamLights));
	SendCspMessage(PianoMessage(Action::Get, Property::StreamLightsSpeed));
	SendCspMessage(PianoMessage(Action::Get, Property::ReverbEffect));
	SendCspMessage(PianoMessage(Action::Get, Property::Tempo));
	SendCspMessage(PianoMessage(Action::Get, Property::Transpose, 2, 0));
	SendCspMessage(PianoMessage(Action::Get, Property::VoicePreset, chMain, 0));
	SendCspMessage(PianoMessage(Action::Get, Property::VoicePreset, chLayer, 0));
	SendCspMessage(PianoMessage(Action::Get, Property::VoicePreset, chLeft, 0));
	SendCspMessage(PianoMessage(Action::Get, Property::Octave, chMain, 0));
	SendCspMessage(PianoMessage(Action::Get, Property::Octave, chLayer, 0));
	SendCspMessage(PianoMessage(Action::Get, Property::Octave, chLeft, 0));

	SendCspMessage(PianoMessage(Action::Get, Property::Length));
	SendCspMessage(PianoMessage(Action::Get, Property::Position));
	SendCspMessage(PianoMessage(Action::Get, Property::Loop));
	SendCspMessage(PianoMessage(Action::Get, Property::Play));
	SendCspMessage(PianoMessage(Action::Get, Property::SongName));
	SendCspMessage(PianoMessage(Action::Get, Property::Part, paRight, 0));
	SendCspMessage(PianoMessage(Action::Get, Property::Part, paLeft, 0));
	SendCspMessage(PianoMessage(Action::Get, Property::Part, paBacking, 0));
}

void PianoController::Reset()
{
	InitEvents();

	Stop();

	// Sleep is not nice, we should wait for a confirmation message instead.
	// Without waiting the config-commands below do not issue change events.
	Sleep(150);

	ResetSong();

	// Sleep is not nice, we should wait for a confirmation message instead.
	// Without waiting the config-commands below do not issue change events.
	Sleep(1000);

	SetLocalControl(true);

	SetGuide(true);
	SetStreamLights(false);
	SetStreamLightsFast(false);
	SetGuide(false);
	SetStreamLights(true);
	SetStreamLightsFast(true);

	for (Channel ch : ValidChannelIds)
	{
		m_channels[ch].enabled = (ch < chMidi1 || ch > chMidi16) && (ch != chMidiMaster);
		m_channels[ch].active = false;

		SetVolume(ch, MinVolume);
		SetVolume(ch, DefaultVolume);
		ResetVolume(ch);

		SetPan(ch, MinPan);
		SetPan(ch, DefaultPan);
		ResetPan(ch);

		SetReverb(ch, MinReverb);
		SetReverb(ch, DefaultReverb);
		ResetReverb(ch);

		// Sleep is not nice, we should wait for confirmation messages instead.
		// Without waiting the piano may miss some commands because there are too many.
		Sleep(20);
	}

	SetTempo(MinTempo);
	SetTempo(DefaultTempo);
	ResetTempo();
	SetTranspose(MinTranspose);
	SetTranspose(DefaultTranspose);
	SetReverbEffect(DefaultReverbEffect);

	SetOctave(chMain, 0);
	SetOctave(chLayer, 0);
	SetOctave(chLeft, 0);

	// set internal active for channels
	m_channels[chMain].active = true;
	m_channels[chLayer].active = false;
	m_channels[chLeft].active = false;
	m_channels[chMidiMaster].active = false;
	m_channels[chMic].active = true;
	m_channels[chAuxIn].active = true;

	SetActive(chMain, true);
	SetActive(chLayer, false);
	SetActive(chLeft, false);
	SetActive(chMidiMaster, false);
	SetActive(chMic, true);
	SetActive(chAuxIn, true);

	Sleep(50);
	SetVoice(chMain, "PRESET:/VOICE/Piano/Grand Piano/CFX Grand.T542.VRM");
	Sleep(50);
	SetVoice(chLayer, "PRESET:/VOICE/Strings & Vocal/String Ensemble/Real Strings.T250.SAR");
	Sleep(50);
	SetVoice(chLeft, "PRESET:/VOICE/Piano/FM E.Piano/DX7 EP.T232.NLV");
}

void PianoController::Disconnect()
{
	if (m_connected)
	{
		m_connected = false;
		NotifyChanged(apConnection);
	}
}

void PianoController::SetLocalControl(bool enabled)
{
	m_localControl = enabled;
	MidiMessage localControlMessage = MidiMessage::controllerEvent(1, 122, enabled ? 127 : 0);
	m_midiConnector->SendMessage(localControlMessage);
	NotifyChanged(apLocalControl);
}

bool PianoController::UploadSong(const File& file)
{
	m_songFilename = file.getFullPathName();

	String headerHex =
		"01 00 00 06 00 00 00 01 00 00 00 00 00 00 00 01 "
		"00 00 00 00 00 00 00 16 45 58 54 45 52 4e 41 4c "
		"3a 2f 41 70 70 53 6f 6e 67 2e 6d 69 64 00 00 00 "
		"00 00";

	MemoryBlock message;
	message.loadFromHexString(headerHex);

	int size = (int)file.getSize();
	message[8] = ((size + 38) & (0xFF << (8 * 3))) >> (8 * 3);
	message[9] = ((size + 38) & (0xFF << (8 * 2))) >> (8 * 2);
	message[10] = ((size + 38) & (0xFF << (8 * 1))) >> (8 * 1);
	message[11] = ((size + 38) & (0xFF << (8 * 0))) >> (8 * 0);

	message[46] = (size & (0xFF << (8 * 3))) >> (8 * 3);
	message[47] = (size & (0xFF << (8 * 2))) >> (8 * 2);
	message[48] = (size & (0xFF << (8 * 1))) >> (8 * 1);
	message[49] = (size & (0xFF << (8 * 0))) >> (8 * 0);

	file.loadFileAsData(message);

	Pause();
	Sleep(10);   // this is not nice, we should wait for a confirmation message instead

	char response[16];
	StreamingSocket socket;
	bool ok = socket.connect(m_remoteIp, 10504) &&
		socket.write(message.getData(), (int)message.getSize()) &&
		socket.read(response, 16, true);

	return ok;
}

void PianoController::SendCspMessage(const PianoMessage& message)
{
	MidiMessage midiMessage = MidiMessage::createSysExMessage(
		message.GetSysExData().getData(), (int)message.GetSysExData().getSize());
	m_midiConnector->SendMessage(midiMessage);
}

void PianoController::ResetSong()
{
	SendCspMessage(PianoMessage(Action::Set, Property::SongReset));
}

void PianoController::Play()
{
	SendCspMessage(PianoMessage(Action::Set, Property::Play, 1));
}

void PianoController::Pause()
{
	SendCspMessage(PianoMessage(Action::Set, Property::Play, 2));
}

void PianoController::Stop()
{
	SendCspMessage(PianoMessage(Action::Set, Property::Play, 0));
}

void PianoController::SetGuide(bool enable)
{
	SendCspMessage(PianoMessage(Action::Set, Property::Guide, enable ? 1 : 0));
}

void PianoController::SetStreamLights(bool enable)
{
	SendCspMessage(PianoMessage(Action::Set, Property::StreamLights, enable ? 1 : 0));
}

void PianoController::SetStreamLightsFast(bool fast)
{
	SendCspMessage(PianoMessage(Action::Set, Property::StreamLightsSpeed, fast ? 1 : 0));
}

void PianoController::SetPosition(const Position position)
{
	uint8_t data[4];
	data[0] = (position.measure >> 7) & 0x7f;
	data[1] = (position.measure >> 0) & 0x7f;
	data[2] = (position.beat >> 7) & 0x7f;
	data[3] = (position.beat >> 0) & 0x7f;
	SendCspMessage(PianoMessage(Action::Set, Property::Position, 0, data, 4));
}

void PianoController::SetVolume(Channel ch, int volume)
{
	SendCspMessage(PianoMessage(Action::Set, Property::Volume, ch, volume));
}

void PianoController::ResetVolume(Channel ch)
{
	SendCspMessage(PianoMessage(Action::Reset, Property::Volume, ch, 0));
}

void PianoController::SetPan(Channel ch, int pan)
{
	SendCspMessage(PianoMessage(Action::Set, Property::Pan, ch, pan + PanBase));
}

void PianoController::ResetPan(Channel ch)
{
	SendCspMessage(PianoMessage(Action::Reset, Property::Pan, ch, 0));
}

void PianoController::SetReverb(Channel ch, int reverb)
{
	SendCspMessage(PianoMessage(Action::Set, Property::Reverb, ch, reverb));
}

void PianoController::ResetReverb(Channel ch)
{
	SendCspMessage(PianoMessage(Action::Reset, Property::Reverb, ch, 0));
}

void PianoController::SetOctave(Channel ch, int octave)
{
	SendCspMessage(PianoMessage(Action::Set, Property::Octave, ch, octave + OctaveBase));
}

void PianoController::SetTempo(int tempo)
{
	SendCspMessage(PianoMessage(Action::Set, Property::Tempo, tempo));
}

void PianoController::ResetTempo()
{
	SendCspMessage(PianoMessage(Action::Reset, Property::Tempo));
}

void PianoController::SetTranspose(int transpose)
{
	SendCspMessage(PianoMessage(Action::Set, Property::Transpose, 2, transpose + TransposeBase));
}

void PianoController::SetReverbEffect(int effect)
{
	SendCspMessage(PianoMessage(Action::Set, Property::ReverbEffect, 0, effect));
}

void PianoController::SetPart(Part part, bool enable)
{
	SendCspMessage(PianoMessage(Action::Set, Property::Part, part, enable ? 1 : 0));
}

void PianoController::SetLoop(Loop loop)
{
	m_loopStart = {0,0};
	uint8_t data[9] = {1,
		(uint8_t)((loop.begin.measure >> 7) & 0x7f),
		(uint8_t)((loop.begin.measure >> 0) & 0x7f),
		(uint8_t)((loop.begin.beat >> 7) & 0x7f),
		(uint8_t)((loop.begin.beat >> 0) & 0x7f),
		(uint8_t)((loop.end.measure >> 7) & 0x7f),
		(uint8_t)((loop.end.measure >> 0) & 0x7f),
		(uint8_t)((loop.end.beat >> 7) & 0x7f),
		(uint8_t)((loop.end.beat >> 0) & 0x7f)};
	SendCspMessage(PianoMessage(Action::Set, Property::Loop, 0, data, 9));
}

void PianoController::ResetLoop()
{
	m_loopStart = {0,0};
	uint8_t data[9] = {0,0,1,0,1,0,2,0,1};
	SendCspMessage(PianoMessage(Action::Set, Property::Loop, 0, data, 9));
}

void PianoController::SetLoopStart(const Position loopStart)
{
	m_loopStart = loopStart;
	NotifyChanged(apLoop);
}

void PianoController::SetVoice(Channel ch, const String& voice)
{
	SendCspMessage(PianoMessage(Action::Set, Property::VoicePreset, ch, voice));
}

void PianoController::SetActive(Channel ch, bool active)
{
	SendCspMessage(PianoMessage(Action::Set, Property::Active, ch, active ? 1 : 0));
}

void PianoController::IncomingMidiMessage(const MidiMessage& message)
{
	if (message.isSysEx() &&
		PianoMessage::IsCspMessage(message.getSysExData(), message.getSysExDataSize()))
	{
		PianoMessage pm(message.getSysExData(), message.getSysExDataSize());
		const Action action = pm.GetAction();

		if (action != Action::Info)
		{
			return;
		}

		const Property property = pm.GetProperty();
		const uint8_t* data = pm.GetRawValue();
		const int size = pm.GetSize();
		const int index = pm.GetIndex();
		const int intValue = pm.GetIntValue();
		const bool boolValue = intValue == 1;
		Channel ch = (Channel)index;

		if (property == Property::Position && size == 4)
		{
			m_position = {(data[0] << 7) + data[1], (data[2] << 7) + data[3]};
			NotifyChanged(apPosition);
		}
		else if (property == Property::Length && size == 4)
		{
			m_length = {(data[0] << 7) + data[1], (data[2] << 7) + data[3]};
			m_songLoaded = m_length.measure > 1 || m_length.beat > 1;
			m_channels[chMidiMaster].enabled = m_songLoaded;
			m_channels[chMidiMaster].active = m_songLoaded;
			NotifyChanged(apLength);
			NotifyChanged(apEnable, chMidiMaster);
		}
		else if (property == Property::Play)
		{
			m_playing = boolValue;
			NotifyChanged(apPlayback);
		}
		else if (property == Property::Guide)
		{
			m_guide = boolValue;
			NotifyChanged(apGuide);
		}
		else if (property == Property::StreamLights)
		{
			m_streamLights = boolValue;
			NotifyChanged(apStreamLights);
		}
		else if (property == Property::StreamLightsSpeed)
		{
			m_streamLightsFast = boolValue;
			NotifyChanged(apStreamLights);
		}
		else if (property == Property::Part)
		{
			m_parts[(Part)index] = boolValue;
			NotifyChanged(apPart);
		}
		else if (property == Property::Volume)
		{
			m_channels[ch].volume = intValue;
			NotifyChanged(apVolume, ch);
		}
		else if (property == Property::Pan)
		{
			m_channels[ch].pan = intValue - PanBase;
			NotifyChanged(apPan, ch);
		}
		else if (property == Property::Reverb)
		{
			m_channels[ch].reverb = intValue;
			NotifyChanged(apReverb, ch);
		}
		else if (property == Property::Octave)
		{
			m_channels[ch].octave = intValue - OctaveBase;
			NotifyChanged(apOctave, ch);
		}
		else if (property == Property::Active)
		{
			m_channels[ch].active = boolValue;
			NotifyChanged(apActive, ch);
		}
		else if (property == Property::Present)
		{
			m_channels[ch].enabled = boolValue;
			NotifyChanged(apEnable, ch);
		}
		else if (property == Property::VoiceMidi && size == 4)
		{
			m_channels[ch].voice = String((data[0] << 7 * 3) + (data[1] << 7 * 2) + (data[2] << 7) + data[3]);
			NotifyChanged(apVoice, ch);
		}
		else if (property == Property::Tempo)
		{
			m_tempo = intValue;
			NotifyChanged(apTempo);
		}
		else if (property == Property::Transpose && index == 2)
		{
			m_transpose = intValue - TransposeBase;
			NotifyChanged(apTranspose);
		}
		else if (property == Property::ReverbEffect)
		{
			m_reverbEffect = intValue;
			NotifyChanged(apReverbEffect);
		}
		else if (property == Property::Loop && size == 9)
		{
			bool enabled = data[0] == 1;
			if (enabled)
			{
				m_loop = {{(data[1] << 7) + data[2], (data[3] << 7) + data[4]},
					{(data[5] << 7) + data[6], (data[7] << 7) + data[8]}};
				m_loopStart = {0,0};
			}
			else
			{
				m_loop = {{0,0},{0,0}};
			}
			NotifyChanged(apLoop);
		}
		else if (property == Property::VoicePreset)
		{
			//TODO: make thread safe
			m_channels[ch].voice = pm.GetStrValue();
			NotifyChanged(apVoice, ch);
		}
		else if (property == Property::PianoModel)
		{
			//TODO: make thread safe
			m_model = pm.GetStrValue();
		}
		else if (property == Property::FirmwareVersion)
		{
			//TODO: make thread safe
			m_version = pm.GetStrValue();
			m_connected = true;
			NotifyChanged(apConnection);
		}
		else if (property == Property::SongName)
		{
			NotifyChanged(apSongLoaded);
		}
	}
	else if (message.isNoteOnOrOff())
	{
		for (auto listener : m_listeners)
		{
			listener->PianoNoteMessage(message);
		}
	}
}

void PianoController::AddListener(Listener* listener)
{
	RemoveListener(listener);
	m_listeners.push_back(listener);
}

void PianoController::RemoveListener(Listener* listener)
{
	std::vector<Listener*>::iterator pos = std::find(m_listeners.begin(), m_listeners.end(), listener);
	if (pos != m_listeners.end())
	{
		m_listeners.erase(pos);
	}
}

void PianoController::SendMidiMessage(const MidiMessage& message)
{
	m_midiConnector->SendMessage(message);
}

void PianoController::NotifyChanged(Aspect aspect, Channel channel)
{
	for (auto listener : m_listeners)
	{
		listener->PianoStateChanged(aspect, channel);
	}
}
