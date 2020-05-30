/*
 *  This file is part of ConPianist. See <https://github.com/hugbug/conpianist>.
 *
 *  Copyright (C) 2020 Andrey Prygunkov <hugbug@users.sourceforge.net>
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

#include "PianoMessage.h"

static const char* CSP_COMMAND_PREFIX = "\x43\x73\x01\x52\x25\x26";
static const int CSP_COMMAND_PREFIX_LENGTH = 6;

// ACTIONS

// Unknown Action (may occur only when parsing sysex)
const Action Action::Unknown = Action("ff ff");

// Request Property Value from Piano
// Format for Get Command:
//   Signature(2 Bytes) : Property(4 Bytes) : Index(1 Byte) : 01 00
const Action Action::Get = Action("01 00");

// Set Property Value
// Format for Set Command:
//   Signature(2 Bytes) : Property(4 Bytes) : Index(1 Byte) : 01 00 : Length(2 bytes) : Value(variable length)
const Action Action::Set = Action("01 01");

// Info from Piano, Containing Property Value
// Format for Info Command:
//   Signature(2 Bytes) : Property(4 Bytes) : Index(1 Byte) : 01 00 : Length(2 bytes) : Value(variable length)
const Action Action::Info = Action("00 00");

// Response from Piano to Set-Action; Contains New Property Value
// Format for Info-2 Command:
//   Signature(2 Bytes) : Property(4 Bytes) : Index(1 Byte) : 01 00 : 00 00 : Length(2 bytes) : Value(variable length)
const Action Action::Response = Action("00 01");

// Reset Property to Default Value
// Format for Reset Command:
//   Signature(2 Bytes) : Property(4 Bytes) : Index(1 Byte) : 01 00
const Action Action::Reset = Action("04 01");

// Activate Events for Property Change
// Format for Events Command:
//   Signature(2 Bytes) : Property(4 Bytes)
const Action Action::Events = Action("02 00");


// PROPERTIES

// Unknown Property (may occur only when parsing sysex)
const Property Property::Unknown = Property("ff ff ff ff", 0, 0);

// Value: Piano Model Name (variable length)
const Property Property::PianoModel = Property("0f 01 18 01", 0, 100);

// Value: Firmware Version String (variable length)
const Property Property::FirmwareVersion = Property("0f 01 0b 01", 0, 100);

// Value: 0 - Guide Off, 1 - Guide On
const Property Property::Guide = Property("04 03 00 01", 1, 100);

// Value: 0 - Correct Key, 1 - Any Key, 5 - Your Tempo
const Property Property::GuideType = Property("04 03 01 01", 1, 100);

// Value (4 Bytes): 2 Bytes for Measure; 2 Bytes for Beat
const Property Property::Position = Property("04 00 0a 01", 4, 200);

// Value (4 Bytes): 2 Bytes for Measure; 2 Bytes for Beat
const Property Property::Length = Property("04 00 1b 01", 4, 100);

// Value: 0 - Stream Lights Off; 1 - Stream Light On
const Property Property::StreamLights = Property("04 02 00 01", 1, 100);

// Value: 0 - Slow; 1 - Fast
const Property Property::StreamSpeed = Property("04 02 02 01", 1, 100);

// Value: 0 - Stop; 1 - Play; 2 - Pause
const Property Property::Play = Property("04 00 05 01", 1, 500);

// Index: 0 - Right Hand; 1 - Left Hand; 3 - Backing
// Value: 0 - Off; 1 - On
const Property Property::Part = Property("04 00 0e 01", 1, 100);

// Index: 0 - Right Hand, 1 - Left Hand, 3 - Backing
// Value: 0..F (Midi-Channel 1..16)
const Property Property::PartChannel = Property("04 00 0f 01", 1, 500);

// Value: 0 - Off, 1 - On
const Property Property::PartAuto = Property("04 00 10 01", 1, 200);

// Value: Song Name (variable length)
const Property Property::SongName = Property("04 00 01 01", 0, 500);

// Index: Channel; Value: 0..127
const Property Property::Volume = Property("0c 00 00 01", 1, 100);

// Index: Channel; Value: 0..127
const Property Property::Pan = Property("0c 00 03 01", 1, 100);

// Index: Channel; Value: 0..127
const Property Property::Reverb = Property("0c 00 04 01", 1, 100);

// Index: Channel; Value: -2..+2 (Base 0x40)
const Property Property::Octave = Property("0c 00 12 01", 1, 200);

// Value: 5..280 (2 Bytes)
const Property Property::Tempo = Property("08 00 00 01", 2, 200);

// Index: 2 (const); Value: -12..+12 (Base 0x40)
const Property Property::Transpose = Property("0a 00 00 01", 1, 200);

// Value: 3 Bytes
const Property Property::ReverbEffect = Property("0c 01 00 01", 3, 500);

// Value: 9 Bytes:
//   1 byte: 0 - Loop Off; 1 - Loop On
//   4 bytes: Start Position (Measure + Beat)
//   4 bytes: End Position (Measure + Beat)
// For Loop Off Use Start Position 1/1 and End Position 2/1 (00 00 01 00 01 00 02 00 01)
const Property Property::Loop = Property("04 00 0d 01", 9, 500);

// Index: Channel; Value: Voice Name from Presets (variable length)
const Property Property::VoicePreset = Property("02 00 00 01", 0, 500);

// Index: Channel; Value: 4 Bytes
// Value: combine four 7-bit MIDI-bytes into an integer; then split it into four 8-bit bytes:
//   0x00MMLLPP (MM - MSB; LL - LSB; PP - PC)
const Property Property::VoiceMidi = Property("02 00 01 01", 4, 100);

// Index: Channel; Value: 0 - Inactive; 1 - Active
const Property Property::Active = Property("0c 00 01 01", 1, 200);

// Index: Channel; Value: 0 - Not Present; 1 - Channel is Present in MIDI-Song
const Property Property::Present = Property("04 01 00 01", 1, 200);

// Value: 0 Bytes
const Property Property::SongReset = Property("04 00 00 01", 0, 5000);

// Value: 21(A1)..108(C7)
const Property Property::SplitPoint = Property("09 00 00 01", 1, 200);

// Value: 0 - Open, 1 - Half Open, 2 - Close
const Property Property::LidPosition = Property("02 02 07 01", 1, 200);

// Value: 00..7f
const Property Property::Environment = Property("02 02 03 01", 1, 200);

// Value: 2e(Mellow) .. 40(Default) .. 7f(Bright)
const Property Property::Brightness = Property("0c 00 0b 01", 1, 200);

// Value: 0 - Soft2, 1 - Soft1, 2 - Medium, 3 - Hard1, 4 - Hard2
const Property Property::TouchCurve = Property("00 00 00 01", 1, 200);

// Value: 2 Bytes: 04(Min) .. 08 00(440 Hz Default) .. 0f 7f (Max)
const Property Property::MasterTune = Property("03 00 00 01", 2, 200);

// Value: 0 - Off, 1 - On
const Property Property::Vrm = Property("02 02 00 01", 1, 200);

// Value: 0..5..10
const Property Property::DamperResonance = Property("02 02 01 01", 1, 200);

// Value: 0..5..10
const Property Property::StringResonance = Property("02 02 02 01", 1, 200);

// Value: 0..0x40..0x50
const Property Property::KeyOffSampling = Property("02 02 06 01", 1, 200);

const std::vector<Property> Property::AllProperties = {
	PianoModel, FirmwareVersion, Guide, GuideType, Position, Length, StreamLights,
	StreamSpeed, Play, Part, PartChannel, PartAuto, SongName, Volume, Pan, Reverb,
	Octave, Tempo, Transpose, ReverbEffect, Loop, VoicePreset, VoiceMidi, Active,
	Present, SongReset, SplitPoint, LidPosition, Environment, Brightness, TouchCurve,
	MasterTune, Vrm, DamperResonance, StringResonance, KeyOffSampling
};

constexpr char CharToCode(char ch)
{
	return ch - (ch >= 'a' ? 'a' - 10 : '0');
}

int Signature2(const char* str)
{
	char b1 = (CharToCode(str[0]) << 4) + CharToCode(str[1]);
	char b2 = (CharToCode(str[3]) << 4) + CharToCode(str[4]);
	return (b1 << 8) + b2;
}

int Signature4(const char* str)
{
	char b1 = (CharToCode(str[0]) << 4) + CharToCode(str[1]);
	char b2 = (CharToCode(str[3]) << 4) + CharToCode(str[4]);
	char b3 = (CharToCode(str[6]) << 4) + CharToCode(str[7]);
	char b4 = (CharToCode(str[9]) << 4) + CharToCode(str[10]);
	return (b1 << 24) + (b2 << 16) + (b3 << 8) + b4;
}

Action::Action(const char* signature) :
	signature(Signature2(signature))
{
}

Property::Property(const char* signature, int valueLength, int repeatInterval) :
	signature(Signature4(signature)), valueLength(valueLength), repeatInterval(repeatInterval)
{
}

String BytesToText(const uint8* buf, int size)
{
	if (size < 3)
	{
		return String();
	}

	int textSize = (buf[0] << 7) + buf[1];
	if (size < textSize + 2)
	{
		return String();
	}

	String text;
	buf += 2;
	int highbits = 0;
	int chunkSize = 0;
	wchar_t chunk[7];

	auto addChunk = [&]()
		{
			for (int a = 0; a < chunkSize; a++)
			{
				wchar_t ch = chunk[a];
				ch += (highbits >> (chunkSize - a - 1) & 1) ? 0x80 : 0;
				text += ch;
			}
		};

	for (int i = 0; i < textSize; i++)
	{
		if (i % 8 == 0)
		{
			addChunk();
			highbits = buf[i];
			chunkSize = 0;
			continue;
		}

		chunk[chunkSize++] = buf[i];
	}
	addChunk();

	return text;
}

int TextToBytesSize(const String& value)
{
	int size = value.length();
	size += (int)(size / 7) + (size % 7 > 0 ? 1 : 0);
	return size;
}

void TextToBytes(const String& value, uint8_t* data)
{
	int datalen = 0;
	char highbits = 0;
	uint8_t chunk[7];
	int chunklen = 0;

	auto addChunk = [&]()
		{
			data[datalen++] = highbits;
			for (int a = 0; a < chunklen; a++)
			{
				data[datalen++] = chunk[a];
			}
		};

	for (int i = 0; i < value.length(); i++)
	{
		if (i % 7 == 0 && i > 0)
		{
			addChunk();
			chunklen = 0;
			highbits = 0;
		}
		wchar_t ch = value[i];
		highbits = (highbits << 1) + (ch > 0x7f ? 1 : 0);
		chunk[chunklen++] = (uint8_t)(ch & 0x7f);
	}

	if (chunklen > 0)
	{
		addChunk();
	}
}

void PianoMessage::Init(const Action action, const Property property, int index,
	const uint8_t* value, int size)
{
	bool hasValue = action.signature == Action::Set.signature ||
		 action.signature == Action::Info.signature ||
		 action.signature == Action::Response.signature;

	int payloadSize = action.signature == Action::Events.signature ? 0 :
		1 + 2 + (hasValue ? 2 + size : 0) +
		(action.signature == Action::Response.signature ? 2 : 0);

	int blockSize = CSP_COMMAND_PREFIX_LENGTH + 2 + 4 + payloadSize;
	m_data.ensureSize(blockSize);

	int pos = 0;

	for (; pos < CSP_COMMAND_PREFIX_LENGTH; pos++)
	{
		m_data[pos] = CSP_COMMAND_PREFIX[pos];
	}

	m_data[pos++] = (action.signature >> 8) & 0xff;
	m_data[pos++] = (action.signature >> 0) & 0xff;

	m_data[pos++] = (property.signature >> 24) & 0xff;
	m_data[pos++] = (property.signature >> 16) & 0xff;
	m_data[pos++] = (property.signature >> 8) & 0xff;
	m_data[pos++] = (property.signature >> 0) & 0xff;

	if (action.signature != Action::Events.signature)
	{
		m_data[pos++] = index;

		m_data[pos++] = 0x01;
		m_data[pos++] = 0x00;

		if (action.signature == Action::Response.signature)
		{
			m_data[pos++] = 0x00;
			m_data[pos++] = 0x00;
		}

		if (hasValue)
		{
			m_data[pos++] = (size >> 7) & 0xff;
			m_data[pos++] = (size >> 0) & 0xff;

			for (int i = 0; i < size; i++)
			{
				m_data[pos++] = value[i];
			}
		}
	}
}

PianoMessage::PianoMessage(const Action action, const Property property, int index, int value)
{
	uint8_t data[4];
	int pos = 0;

	if (property.valueLength >= 4)
	{
		data[pos++] = (value >> 21) & 0x7f;
	}
	if (property.valueLength >= 3)
	{
		data[pos++] = (value >> 14) & 0x7f;
	}
	if (property.valueLength >= 2)
	{
		data[pos++] = (value >> 7) & 0x7f;
	}
	if (property.valueLength >= 1)
	{
		data[pos++] = (value >> 0) & 0x7f;
	}

	Init(action, property, index, data, property.valueLength);
}

PianoMessage::PianoMessage(const Action action, const Property property, int index,
	const uint8_t* value, int size)
{
	Init(action, property, index, value, size);
}

PianoMessage::PianoMessage(const Action action, const Property property, int index, String value)
{
	int size = TextToBytesSize(value);
	std::vector<uint8_t> data(size);
	TextToBytes(value, data.data());

	Init(action, property, index, data.data(), size);
}

PianoMessage::PianoMessage(const uint8_t* sysExData, int size)
{
	if (IsCspMessage(sysExData, size))
	{
		m_data.append(sysExData, size);
	}
}

const bool PianoMessage::IsCspMessage(const uint8_t* sysExData, int size)
{
	const int minCspSize = CSP_COMMAND_PREFIX_LENGTH + 2 + 4;
	bool isCspMessage = size >= minCspSize &&
		!strncmp((const char*)sysExData, CSP_COMMAND_PREFIX, CSP_COMMAND_PREFIX_LENGTH);
	return isCspMessage;
}

const bool PianoMessage::DataEqualsTo(const PianoMessage& other) const
{
	const Action a1 = GetAction();
	const Action a2 = other.GetAction();

	const bool similarAction = a1 == a2 ||
		(a1 == Action::Info && a2 == Action::Response) ||
		(a2 == Action::Info && a1 == Action::Response);

	if (similarAction && GetProperty() == other.GetProperty() &&
		GetIndex() == other.GetIndex())
	{
		const int offset1 = LengthOffset();
		const int offset2 = other.LengthOffset();
		if (offset1 > 0 && offset2 > 0)
		{
			const int size1 = GetSize(offset1);
			const int size2 = other.GetSize(offset2);
			if (size1 == size2)
			{
				const uint8_t* val1 = GetRawValue(offset1);
				const uint8_t* val2 = other.GetRawValue(offset2);
				bool equal = (!val1 && !val2) || (val1 && val2 && memcmp(val1, val2, size1) == 0);
				return equal;
			}
		}
	}

	return false;
}

const Action PianoMessage::GetAction() const
{
	if (m_data.getSize() >= CSP_COMMAND_PREFIX_LENGTH + 2)
	{
		return Action(
			(m_data[CSP_COMMAND_PREFIX_LENGTH] << 8) +
			m_data[CSP_COMMAND_PREFIX_LENGTH + 1]);
	}
	return Action::Unknown;
}

const Property PianoMessage::GetProperty(bool full) const
{
	if (m_data.getSize() >= CSP_COMMAND_PREFIX_LENGTH + 2 + 4)
	{
		int signature =
			(m_data[CSP_COMMAND_PREFIX_LENGTH + 2 + 0] << 24) +
			(m_data[CSP_COMMAND_PREFIX_LENGTH + 2 + 1] << 16) +
			(m_data[CSP_COMMAND_PREFIX_LENGTH + 2 + 2] << 8) +
			m_data[CSP_COMMAND_PREFIX_LENGTH + 2 + 3];

		if (full)
		{
			for (Property prop : Property::AllProperties)
			{
				if (prop.signature == signature)
				{
					return prop;
				}
			}
		}
		return Property(signature, 0, 0);
	}
	return Property::Unknown;
}

const int PianoMessage::GetIndex() const
{
	if (m_data.getSize() >= CSP_COMMAND_PREFIX_LENGTH + 2 + 4 + 1)
	{
		return m_data[CSP_COMMAND_PREFIX_LENGTH + 2 + 4];
	}
	return 0;
}

const int PianoMessage::GetIntValue() const
{
	int ind = LengthOffset();
	if (m_data.getSize() > ind + 2)
	{
		int size = GetSize(ind);
		ind += 2;
		const uint8_t* data = (const uint8_t*)m_data.getData();
		switch (size)
		{
			case 1:
				return data[ind];
			case 2:
				return (data[ind + 0] << 7) + data[ind + 1];
			case 3:
				return (data[ind + 0] << 7*2) + (data[ind + 1] << 7) + data[ind + 2];
			case 4:
				return (data[ind + 0] << 7*3) + (data[ind + 1] << 7*2) +
					(data[ind + 2] << 7) + data[ind + 3];
		}
	}
	return 0;
}

const String PianoMessage::GetStrValue() const
{
	int ind = LengthOffset();
	if (m_data.getSize() >= ind + 2)
	{
		const uint8_t* data = (const uint8_t*)m_data.getData();
		return BytesToText(data + ind, (int)m_data.getSize() - ind);
	}
	return String();
}

const int PianoMessage::GetSize() const
{
	return GetSize(LengthOffset());
}

const int PianoMessage::GetSize(int lengthOffset) const
{
	if (lengthOffset > 0)
	{
		return (m_data[lengthOffset + 0] << 7) + m_data[lengthOffset + 1];
	}
	return 0;
}

const uint8_t* PianoMessage::GetRawValue() const
{
	return GetRawValue(LengthOffset());
}

const uint8_t* PianoMessage::GetRawValue(int lengthOffset) const
{
	if (m_data.getSize() > lengthOffset + 2)
	{
		return (const uint8_t*)m_data.getData() + lengthOffset + 2;
	}
	return nullptr;
}

const int PianoMessage::LengthOffset() const
{
	const Action action = GetAction();
	if ((action == Action::Set || action == Action::Info) &&
		m_data.getSize() >= CSP_COMMAND_PREFIX_LENGTH + 2 + 4 + 1 + 2 + 2)
	{
		return CSP_COMMAND_PREFIX_LENGTH + 2 + 4 + 1 + 2;
	}
	else if ((action == Action::Response) &&
		m_data.getSize() >= CSP_COMMAND_PREFIX_LENGTH + 2 + 4 + 1 + 2 + 2 + 2)
	{
		return CSP_COMMAND_PREFIX_LENGTH + 2 + 4 + 2 + 1 + 2;
	}
	return 0;
}
