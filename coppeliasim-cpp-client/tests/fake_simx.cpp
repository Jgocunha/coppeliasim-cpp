#include "fake_simx.h"

namespace fake_simx
{
	static Record g_record;

	Record& record() { return g_record; }

	void reset() { g_record = Record(); }
}

using fake_simx::record;

// Buffer kept alive past the simxGetStringSignal call so the client can read it.
static std::string g_stringSignalBuffer;

extern "C"
{

	simxInt simxStart(const simxChar* /*connectionAddress*/, simxInt /*connectionPort*/,
		simxUChar /*waitUntilConnected*/, simxUChar /*doNotReconnectOnceDisconnected*/,
		simxInt /*timeOutInMs*/, simxInt /*commThreadCycleInMs*/)
	{
		auto& r = record();
		r.callCount++;
		r.lastFunction = "simxStart";
		return r.startReturn;
	}

	simxVoid simxFinish(simxInt clientID)
	{
		auto& r = record();
		r.callCount++;
		r.lastFunction = "simxFinish";
		r.lastClientID = clientID;
	}

	simxInt simxGetConnectionId(simxInt clientID)
	{
		auto& r = record();
		r.callCount++;
		r.lastFunction = "simxGetConnectionId";
		r.lastClientID = clientID;
		return r.connectionId;
	}

	simxInt simxStartSimulation(simxInt clientID, simxInt operationMode)
	{
		auto& r = record();
		r.callCount++;
		r.lastFunction = "simxStartSimulation";
		r.lastClientID = clientID;
		r.lastOpMode = operationMode;
		return simx_return_ok;
	}

	simxInt simxStopSimulation(simxInt clientID, simxInt operationMode)
	{
		auto& r = record();
		r.callCount++;
		r.lastFunction = "simxStopSimulation";
		r.lastClientID = clientID;
		r.lastOpMode = operationMode;
		return simx_return_ok;
	}

	simxInt simxSetIntegerSignal(simxInt clientID, const simxChar* signalName,
		simxInt signalValue, simxInt operationMode)
	{
		auto& r = record();
		r.callCount++;
		r.lastFunction = "simxSetIntegerSignal";
		r.lastClientID = clientID;
		r.lastSignalName = signalName;
		r.lastIntValue = signalValue;
		r.lastOpMode = operationMode;
		return simx_return_ok;
	}

	simxInt simxSetFloatSignal(simxInt clientID, const simxChar* signalName,
		simxFloat signalValue, simxInt operationMode)
	{
		auto& r = record();
		r.callCount++;
		r.lastFunction = "simxSetFloatSignal";
		r.lastClientID = clientID;
		r.lastSignalName = signalName;
		r.lastFloatValue = signalValue;
		r.lastOpMode = operationMode;
		return simx_return_ok;
	}

	simxInt simxSetStringSignal(simxInt clientID, const simxChar* signalName,
		const simxUChar* signalValue, simxInt signalLength, simxInt operationMode)
	{
		auto& r = record();
		r.callCount++;
		r.lastFunction = "simxSetStringSignal";
		r.lastClientID = clientID;
		r.lastSignalName = signalName;
		r.lastStringValue.assign(reinterpret_cast<const char*>(signalValue), signalLength);
		r.lastStringLength = signalLength;
		r.lastOpMode = operationMode;
		return simx_return_ok;
	}

	simxInt simxGetIntegerSignal(simxInt clientID, const simxChar* signalName,
		simxInt* signalValue, simxInt operationMode)
	{
		auto& r = record();
		r.callCount++;
		r.lastFunction = "simxGetIntegerSignal";
		r.lastClientID = clientID;
		r.lastSignalName = signalName;
		r.lastOpMode = operationMode;
		*signalValue = r.nextIntSignal;
		return simx_return_ok;
	}

	simxInt simxGetFloatSignal(simxInt clientID, const simxChar* signalName,
		simxFloat* signalValue, simxInt operationMode)
	{
		auto& r = record();
		r.callCount++;
		r.lastFunction = "simxGetFloatSignal";
		r.lastClientID = clientID;
		r.lastSignalName = signalName;
		r.lastOpMode = operationMode;
		*signalValue = r.nextFloatSignal;
		return simx_return_ok;
	}

	simxInt simxGetStringSignal(simxInt clientID, const simxChar* signalName,
		simxUChar** signalValue, simxInt* signalLength, simxInt operationMode)
	{
		auto& r = record();
		r.callCount++;
		r.lastFunction = "simxGetStringSignal";
		r.lastClientID = clientID;
		r.lastSignalName = signalName;
		r.lastOpMode = operationMode;
		g_stringSignalBuffer = r.nextStringSignal;
		*signalValue = reinterpret_cast<simxUChar*>(g_stringSignalBuffer.data());
		*signalLength = static_cast<simxInt>(g_stringSignalBuffer.size());
		return simx_return_ok;
	}

	simxInt simxGetObjectHandle(simxInt clientID, const simxChar* objectName,
		simxInt* handle, simxInt operationMode)
	{
		auto& r = record();
		r.callCount++;
		r.lastFunction = "simxGetObjectHandle";
		r.lastClientID = clientID;
		r.lastObjectName = objectName;
		r.lastOpMode = operationMode;
		*handle = r.nextHandle;
		return simx_return_ok;
	}

	simxInt simxGetObjectPosition(simxInt clientID, simxInt objectHandle,
		simxInt /*relativeToObjectHandle*/, simxFloat* position, simxInt operationMode)
	{
		auto& r = record();
		r.callCount++;
		r.lastFunction = "simxGetObjectPosition";
		r.lastClientID = clientID;
		r.lastObjectHandle = objectHandle;
		r.lastOpMode = operationMode;
		position[0] = r.nextPosition[0];
		position[1] = r.nextPosition[1];
		position[2] = r.nextPosition[2];
		return simx_return_ok;
	}

	simxInt simxGetObjectOrientation(simxInt clientID, simxInt objectHandle,
		simxInt /*relativeToObjectHandle*/, simxFloat* eulerAngles, simxInt operationMode)
	{
		auto& r = record();
		r.callCount++;
		r.lastFunction = "simxGetObjectOrientation";
		r.lastClientID = clientID;
		r.lastObjectHandle = objectHandle;
		r.lastOpMode = operationMode;
		eulerAngles[0] = r.nextOrientation[0];
		eulerAngles[1] = r.nextOrientation[1];
		eulerAngles[2] = r.nextOrientation[2];
		return simx_return_ok;
	}

	simxInt simxAddStatusbarMessage(simxInt clientID, const simxChar* message,
		simxInt operationMode)
	{
		auto& r = record();
		r.callCount++;
		r.lastFunction = "simxAddStatusbarMessage";
		r.lastClientID = clientID;
		r.lastStringValue = message;
		r.lastOpMode = operationMode;
		return simx_return_ok;
	}

} // extern "C"
