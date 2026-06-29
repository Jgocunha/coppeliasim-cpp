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
		return r.returnCode;
	}

	simxInt simxStopSimulation(simxInt clientID, simxInt operationMode)
	{
		auto& r = record();
		r.callCount++;
		r.lastFunction = "simxStopSimulation";
		r.lastClientID = clientID;
		r.lastOpMode = operationMode;
		return r.returnCode;
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
		return r.returnCode;
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
		return r.returnCode;
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
		return r.returnCode;
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
		if (r.returnCode != simx_return_ok)
		{
			return r.returnCode; // mimic the real API: out-param left untouched on failure
		}
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
		if (r.returnCode != simx_return_ok)
		{
			return r.returnCode;
		}
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
		if (r.returnCode != simx_return_ok)
		{
			// Mimic the real API: out-params left untouched on failure, so the
			// client must not read them.
			return r.returnCode;
		}
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
		if (r.returnCode != simx_return_ok)
		{
			return r.returnCode;
		}
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
		if (r.returnCode != simx_return_ok)
		{
			return r.returnCode;
		}
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
		if (r.returnCode != simx_return_ok)
		{
			return r.returnCode;
		}
		eulerAngles[0] = r.nextOrientation[0];
		eulerAngles[1] = r.nextOrientation[1];
		eulerAngles[2] = r.nextOrientation[2];
		return simx_return_ok;
	}

	simxInt simxPauseSimulation(simxInt clientID, simxInt operationMode)
	{
		auto& r = record();
		r.callCount++;
		r.lastFunction = "simxPauseSimulation";
		r.lastClientID = clientID;
		r.lastOpMode = operationMode;
		return r.returnCode;
	}

	simxInt simxGetPingTime(simxInt clientID, simxInt* pingTime)
	{
		auto& r = record();
		r.callCount++;
		r.lastFunction = "simxGetPingTime";
		r.lastClientID = clientID;
		if (r.returnCode != simx_return_ok)
		{
			return r.returnCode;
		}
		*pingTime = r.nextPingTime;
		return simx_return_ok;
	}

	simxInt simxGetObjectVelocity(simxInt clientID, simxInt objectHandle,
		simxFloat* linearVelocity, simxFloat* angularVelocity, simxInt operationMode)
	{
		auto& r = record();
		r.callCount++;
		r.lastFunction = "simxGetObjectVelocity";
		r.lastClientID = clientID;
		r.lastObjectHandle = objectHandle;
		r.lastOpMode = operationMode;
		if (r.returnCode != simx_return_ok)
		{
			return r.returnCode;
		}
		for (int i = 0; i < 3; ++i)
		{
			linearVelocity[i] = r.nextLinearVelocity[i];
			angularVelocity[i] = r.nextAngularVelocity[i];
		}
		return simx_return_ok;
	}

	simxInt simxSetObjectPosition(simxInt clientID, simxInt objectHandle,
		simxInt /*relativeToObjectHandle*/, const simxFloat* position, simxInt operationMode)
	{
		auto& r = record();
		r.callCount++;
		r.lastFunction = "simxSetObjectPosition";
		r.lastClientID = clientID;
		r.lastObjectHandle = objectHandle;
		r.lastOpMode = operationMode;
		for (int i = 0; i < 3; ++i)
		{
			r.lastVec3[i] = position[i];
		}
		return r.returnCode;
	}

	simxInt simxSetObjectOrientation(simxInt clientID, simxInt objectHandle,
		simxInt /*relativeToObjectHandle*/, const simxFloat* eulerAngles, simxInt operationMode)
	{
		auto& r = record();
		r.callCount++;
		r.lastFunction = "simxSetObjectOrientation";
		r.lastClientID = clientID;
		r.lastObjectHandle = objectHandle;
		r.lastOpMode = operationMode;
		for (int i = 0; i < 3; ++i)
		{
			r.lastVec3[i] = eulerAngles[i];
		}
		return r.returnCode;
	}

	simxInt simxGetObjectChild(simxInt clientID, simxInt parentObjectHandle,
		simxInt childIndex, simxInt* childObjectHandle, simxInt operationMode)
	{
		auto& r = record();
		r.callCount++;
		r.lastFunction = "simxGetObjectChild";
		r.lastClientID = clientID;
		r.lastObjectHandle = parentObjectHandle;
		r.lastChildIndex = childIndex;
		r.lastOpMode = operationMode;
		if (r.returnCode != simx_return_ok)
		{
			return r.returnCode;
		}
		// If a sequence is programmed, return it by index (then -1 past the end);
		// otherwise fall back to the single nextChildHandle value.
		if (!r.childHandleSequence.empty())
		{
			*childObjectHandle =
				(childIndex >= 0 && childIndex < static_cast<int>(r.childHandleSequence.size()))
					? r.childHandleSequence[childIndex]
					: -1;
		}
		else
		{
			*childObjectHandle = r.nextChildHandle;
		}
		return simx_return_ok;
	}

	simxInt simxGetJointPosition(simxInt clientID, simxInt jointHandle,
		simxFloat* position, simxInt operationMode)
	{
		auto& r = record();
		r.callCount++;
		r.lastFunction = "simxGetJointPosition";
		r.lastClientID = clientID;
		r.lastObjectHandle = jointHandle;
		r.lastOpMode = operationMode;
		if (r.returnCode != simx_return_ok)
		{
			return r.returnCode;
		}
		*position = r.nextJointPosition;
		return simx_return_ok;
	}

	simxInt simxSetJointTargetPosition(simxInt clientID, simxInt jointHandle,
		simxFloat targetPosition, simxInt operationMode)
	{
		auto& r = record();
		r.callCount++;
		r.lastFunction = "simxSetJointTargetPosition";
		r.lastClientID = clientID;
		r.lastObjectHandle = jointHandle;
		r.lastFloatValue = targetPosition;
		r.lastOpMode = operationMode;
		return r.returnCode;
	}

	simxInt simxSetJointTargetVelocity(simxInt clientID, simxInt jointHandle,
		simxFloat targetVelocity, simxInt operationMode)
	{
		auto& r = record();
		r.callCount++;
		r.lastFunction = "simxSetJointTargetVelocity";
		r.lastClientID = clientID;
		r.lastObjectHandle = jointHandle;
		r.lastFloatValue = targetVelocity;
		r.lastOpMode = operationMode;
		return r.returnCode;
	}

	simxInt simxLoadScene(simxInt clientID, const simxChar* scenePathAndName,
		simxUChar /*options*/, simxInt operationMode)
	{
		auto& r = record();
		r.callCount++;
		r.lastFunction = "simxLoadScene";
		r.lastClientID = clientID;
		r.lastStringValue = scenePathAndName;
		r.lastOpMode = operationMode;
		return r.returnCode;
	}

	simxInt simxCloseScene(simxInt clientID, simxInt operationMode)
	{
		auto& r = record();
		r.callCount++;
		r.lastFunction = "simxCloseScene";
		r.lastClientID = clientID;
		r.lastOpMode = operationMode;
		return r.returnCode;
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
