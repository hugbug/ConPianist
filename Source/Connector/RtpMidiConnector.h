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

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "MidiConnector.h"

class RtpMidiConnector : public MidiConnector, public Thread
{
public:
	RtpMidiConnector(String remoteIp, bool detailLogging) :
		Thread("RtpMidiConnector"), m_remoteIp(remoteIp), m_detailLogging(detailLogging) {}
	void SendMessage(const MidiMessage& message) override;
	bool IsConnected() override { return m_connected; }
	void run() override;

private:
	String m_remoteIp;
	bool m_connected = false;
	std::mutex m_mutex;
	bool m_detailLogging = false;
	bool m_wantReset = false;
	const static int ConnectionLostThreshold = 15000; // milliseconds

	void ResetMidi();
	int FindFreePort();
};
