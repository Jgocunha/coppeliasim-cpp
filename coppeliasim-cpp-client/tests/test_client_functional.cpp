// Tier 2: functional tests of the real CoppeliaSimClient logic.
//
// This executable compiles src/client.cpp against fake_simx.cpp instead of the
// real networking layer, so we can program what the simx* API "returns" and
// assert on what the client forwarded. This exercises the actual client code
// paths without a live CoppeliaSim simulator.
#include <gtest/gtest.h>

#include <optional>

#include "client.h"
#include "fake_simx.h"

using namespace coppeliasim_cpp;
using fake_simx::record;

class FunctionalTest : public ::testing::Test
{
protected:
	// CoppeliaSimClient owns a unique_ptr and declares a destructor, so it is
	// neither copyable nor movable -- hold it in an optional and emplace in place.
	std::optional<CoppeliaSimClient> client;

	void SetUp() override { fake_simx::reset(); }

	// Build a connected client (LOG off). The fake makes simxStart succeed and
	// the connection appear live.
	CoppeliaSimClient& makeConnectedClient(LogMode mode = LogMode::NO_LOGS)
	{
		record().startReturn = 0;  // simxStart -> clientID 0 (success)
		record().connectionId = 0; // simxGetConnectionId -> connected
		client.emplace("127.0.0.1", 19999, mode);
		client->initialize();
		return *client;
	}
};

// --- initialize() ---------------------------------------------------------

TEST_F(FunctionalTest, InitializeSucceedsWhenStartReturnsValidId)
{
	record().startReturn = 0; // valid clientID
	client.emplace("127.0.0.1", 19999, LogMode::NO_LOGS);
	EXPECT_TRUE(client->initialize());
	EXPECT_EQ(client->getClientID(), 0);
	EXPECT_EQ(record().lastFunction, "simxStart");
}

TEST_F(FunctionalTest, InitializeFailsWhenStartReturnsMinusOne)
{
	record().startReturn = -1; // connection failure
	client.emplace("127.0.0.1", 19999, LogMode::NO_LOGS);
	EXPECT_FALSE(client->initialize());
	EXPECT_EQ(client->getClientID(), -1);
}

// --- isConnected() --------------------------------------------------------

TEST_F(FunctionalTest, IsConnectedReflectsConnectionId)
{
	CoppeliaSimClient& client = makeConnectedClient();

	record().connectionId = 0; // connected
	EXPECT_TRUE(client.isConnected());

	record().connectionId = -1; // dropped
	EXPECT_FALSE(client.isConnected());
}

// --- set* forwarding ------------------------------------------------------

TEST_F(FunctionalTest, SetIntegerSignalForwardsNameValueAndOneshotMode)
{
	CoppeliaSimClient& client = makeConnectedClient();
	client.setIntegerSignal("speed", 42);

	EXPECT_EQ(record().lastFunction, "simxSetIntegerSignal");
	EXPECT_EQ(record().lastSignalName, "speed");
	EXPECT_EQ(record().lastIntValue, 42);
	EXPECT_EQ(record().lastOpMode, simx_opmode_oneshot);
}

TEST_F(FunctionalTest, SetFloatSignalForwardsNameValueAndOneshotMode)
{
	CoppeliaSimClient& client = makeConnectedClient();
	client.setFloatSignal("gain", 3.5f);

	EXPECT_EQ(record().lastFunction, "simxSetFloatSignal");
	EXPECT_EQ(record().lastSignalName, "gain");
	EXPECT_FLOAT_EQ(record().lastFloatValue, 3.5f);
	EXPECT_EQ(record().lastOpMode, simx_opmode_oneshot);
}

TEST_F(FunctionalTest, SetStringSignalForwardsExactBytesAndBlockingMode)
{
	CoppeliaSimClient& client = makeConnectedClient();
	client.setStringSignal("msg", "hello");

	EXPECT_EQ(record().lastFunction, "simxSetStringSignal");
	EXPECT_EQ(record().lastSignalName, "msg");
	EXPECT_EQ(record().lastStringValue, "hello");
	EXPECT_EQ(record().lastStringLength, 5);
	EXPECT_EQ(record().lastOpMode, simx_opmode_blocking);
}

// --- get* round-trip ------------------------------------------------------

TEST_F(FunctionalTest, GetIntegerSignalReturnsProgrammedValue)
{
	CoppeliaSimClient& client = makeConnectedClient();
	record().nextIntSignal = 7;

	EXPECT_EQ(client.getIntegerSignal("x"), 7);
	EXPECT_EQ(record().lastSignalName, "x");
	EXPECT_EQ(record().lastOpMode, simx_opmode_blocking);
}

TEST_F(FunctionalTest, GetFloatSignalReturnsProgrammedValue)
{
	CoppeliaSimClient& client = makeConnectedClient();
	record().nextFloatSignal = -1.25f;

	EXPECT_FLOAT_EQ(client.getFloatSignal("y"), -1.25f);
	EXPECT_EQ(record().lastSignalName, "y");
}

TEST_F(FunctionalTest, GetStringSignalIsLengthBasedNotNullTerminated)
{
	CoppeliaSimClient& client = makeConnectedClient();
	// Embed a null byte: a strlen-based reconstruction would stop at "ab",
	// but getStringSignal uses the reported length, so we get all 5 bytes.
	record().nextStringSignal = std::string("ab\0cd", 5);

	std::string result = client.getStringSignal("z");
	EXPECT_EQ(result.size(), 5u);
	EXPECT_EQ(result, std::string("ab\0cd", 5));
}

// --- object queries -------------------------------------------------------

TEST_F(FunctionalTest, GetObjectHandleReturnsProgrammedHandle)
{
	CoppeliaSimClient& client = makeConnectedClient();
	record().nextHandle = 99;

	EXPECT_EQ(client.getObjectHandle("Cuboid"), 99);
	EXPECT_EQ(record().lastObjectName, "Cuboid");
	EXPECT_EQ(record().lastOpMode, simx_opmode_blocking);
}

TEST_F(FunctionalTest, GetObjectPositionMapsArrayToStruct)
{
	CoppeliaSimClient& client = makeConnectedClient();
	record().nextPosition[0] = 1.0f;
	record().nextPosition[1] = 2.0f;
	record().nextPosition[2] = 3.0f;

	Position p = client.getObjectPosition(5);
	EXPECT_FLOAT_EQ(p.x, 1.0f);
	EXPECT_FLOAT_EQ(p.y, 2.0f);
	EXPECT_FLOAT_EQ(p.z, 3.0f);
	EXPECT_EQ(record().lastObjectHandle, 5);
}

TEST_F(FunctionalTest, GetObjectOrientationMapsArrayToStruct)
{
	CoppeliaSimClient& client = makeConnectedClient();
	record().nextOrientation[0] = 0.4f;
	record().nextOrientation[1] = 0.5f;
	record().nextOrientation[2] = 0.6f;

	Orientation o = client.getObjectOrientation(5);
	EXPECT_FLOAT_EQ(o.alpha, 0.4f);
	EXPECT_FLOAT_EQ(o.beta, 0.5f);
	EXPECT_FLOAT_EQ(o.gamma, 0.6f);
}

TEST_F(FunctionalTest, GetObjectPoseComposesPositionAndOrientation)
{
	CoppeliaSimClient& client = makeConnectedClient();
	record().nextPosition[0] = 1.0f;
	record().nextPosition[1] = 2.0f;
	record().nextPosition[2] = 3.0f;
	record().nextOrientation[0] = 4.0f;
	record().nextOrientation[1] = 5.0f;
	record().nextOrientation[2] = 6.0f;

	Pose pose = client.getObjectPose(5);
	EXPECT_FLOAT_EQ(pose.position.x, 1.0f);
	EXPECT_FLOAT_EQ(pose.position.y, 2.0f);
	EXPECT_FLOAT_EQ(pose.position.z, 3.0f);
	EXPECT_FLOAT_EQ(pose.orientation.alpha, 4.0f);
	EXPECT_FLOAT_EQ(pose.orientation.beta, 5.0f);
	EXPECT_FLOAT_EQ(pose.orientation.gamma, 6.0f);
}

// --- simulation control ---------------------------------------------------

TEST_F(FunctionalTest, StartSimulationCallsApiWithBlockingMode)
{
	CoppeliaSimClient& client = makeConnectedClient();
	client.startSimulation();
	EXPECT_EQ(record().lastFunction, "simxStartSimulation");
	EXPECT_EQ(record().lastOpMode, simx_opmode_blocking);
}

TEST_F(FunctionalTest, StopSimulationCallsApiWithBlockingMode)
{
	CoppeliaSimClient& client = makeConnectedClient();
	client.stopSimulation();
	EXPECT_EQ(record().lastFunction, "simxStopSimulation");
	EXPECT_EQ(record().lastOpMode, simx_opmode_blocking);
}

// --- logging --------------------------------------------------------------

TEST_F(FunctionalTest, LogCoppeliaModeSendsStatusbarMessageWhenConnected)
{
	record().startReturn = 0;
	client.emplace("127.0.0.1", 19999, LogMode::LOG_COPPELIA);
	client->initialize();
	fake_simx::reset(); // clear the simxStart call so we observe only the log

	client->log_msg("hi there");
	EXPECT_EQ(record().lastFunction, "simxAddStatusbarMessage");
	EXPECT_EQ(record().lastStringValue, "hi there");
	EXPECT_EQ(record().lastOpMode, simx_opmode_oneshot);
}

TEST_F(FunctionalTest, NoLogsModeDoesNotTouchTheApi)
{
	CoppeliaSimClient& client = makeConnectedClient();
	fake_simx::reset();

	client.log_msg("should be ignored");
	EXPECT_EQ(record().callCount, 0);
}

TEST_F(FunctionalTest, LogCmdModePrintsToStdoutAndSkipsApi)
{
	CoppeliaSimClient& client = makeConnectedClient();
	fake_simx::reset();

	testing::internal::CaptureStdout();
	client.setLogMode(LogMode::LOG_CMD);
	client.log_msg("console only");
	std::string out = testing::internal::GetCapturedStdout();

	EXPECT_NE(out.find("console only"), std::string::npos);
	EXPECT_EQ(record().callCount, 0); // LOG_CMD must not hit the API
}
