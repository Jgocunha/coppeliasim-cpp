// Test double for the CoppeliaSim legacy remote API (simx*).
//
// The functional test executable compiles src/client.cpp together with this
// fake instead of the real lib/extApi.c + lib/extApiPlatform.c. That lets each
// test program the values the API "returns" and inspect the arguments the
// client forwarded, exercising the real CoppeliaSimClient logic with no live
// simulator and no sockets.
#pragma once

#include <string>

extern "C"
{
#include "extApi.h"
}

namespace fake_simx
{
	// Everything the client pushed down / what the fake should hand back.
	struct Record
	{
		// --- call tracking ---
		int callCount = 0;
		std::string lastFunction;

		// --- captured arguments ---
		int lastClientID = -999;
		std::string lastSignalName;
		std::string lastObjectName;
		int lastIntValue = 0;
		float lastFloatValue = 0.0f;
		std::string lastStringValue; // captured by (ptr, length), so binary-safe
		int lastStringLength = 0;
		int lastObjectHandle = -999;
		int lastOpMode = -999;

		// --- programmable behaviour (what the next/all calls return) ---
		int startReturn = 0;          // value simxStart returns (clientID, or -1)
		int connectionId = 0;         // value simxGetConnectionId returns
		int nextIntSignal = 0;        // out-value for simxGetIntegerSignal
		float nextFloatSignal = 0.0f; // out-value for simxGetFloatSignal
		std::string nextStringSignal; // out-bytes for simxGetStringSignal
		int nextHandle = 0;           // out-value for simxGetObjectHandle
		float nextPosition[3] = {0, 0, 0};
		float nextOrientation[3] = {0, 0, 0};
	};

	// Single global instance the fake reads/writes and tests inspect.
	Record& record();

	// Reset to defaults between tests.
	void reset();
}
