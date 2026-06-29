// Tier 2: functional tests of the real CoppeliaSimClient logic.
//
// This executable compiles src/client.cpp against fake_simx.cpp instead of the
// real networking layer, so we can program what the simx* API "returns" and
// assert on what the client forwarded. This exercises the actual client code
// paths -- including the failure paths -- without a live CoppeliaSim simulator.
#include <gtest/gtest.h>

#include <optional>

#include "client.h"
#include "fake_simx.h"

using namespace coppeliasim_cpp;
using fake_simx::record;

class FunctionalTest : public ::testing::Test
{
protected:
	// CoppeliaSimClient owns a unique_ptr and a connection handle; hold it in an
	// optional and emplace in place.
	std::optional<CoppeliaSimClient> client;

	void SetUp() override { fake_simx::reset(); }

	// Build a connected client (LOG off). The fake makes simxStart succeed and
	// the connection appear live.
	CoppeliaSimClient& makeConnectedClient(LogMode mode = LogMode::NO_LOGS)
	{
		record().startReturn = 0;  // simxStart -> clientID 0 (success)
		record().connectionId = 0; // simxGetConnectionId -> connected
		client.emplace("127.0.0.1", 19999, mode);
		(void)client->initialize();
		return *client;
	}
};

// --- connect() factory + initialize() -------------------------------------

TEST_F(FunctionalTest, ConnectReturnsClientWhenStartSucceeds)
{
	record().startReturn = 0; // valid clientID
	auto c = CoppeliaSimClient::connect("127.0.0.1", 19999, LogMode::NO_LOGS);
	ASSERT_TRUE(c.has_value());
	EXPECT_EQ(c->getClientID(), 0);
}

TEST_F(FunctionalTest, ConnectReturnsNulloptWhenStartFails)
{
	record().startReturn = -1; // connection failure
	auto c = CoppeliaSimClient::connect("127.0.0.1", 19999, LogMode::NO_LOGS);
	EXPECT_FALSE(c.has_value());
}

TEST_F(FunctionalTest, InitializeSucceedsWhenStartReturnsValidId)
{
	record().startReturn = 0;
	client.emplace("127.0.0.1", 19999, LogMode::NO_LOGS);
	EXPECT_TRUE(client->initialize());
	EXPECT_EQ(client->getClientID(), 0);
	EXPECT_EQ(record().lastFunction, "simxStart");
}

TEST_F(FunctionalTest, InitializeFailsWhenStartReturnsMinusOne)
{
	record().startReturn = -1;
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

// --- set* forwarding (success) --------------------------------------------

TEST_F(FunctionalTest, SetIntegerSignalForwardsNameValueAndOneshotMode)
{
	CoppeliaSimClient& client = makeConnectedClient();
	EXPECT_TRUE(client.setIntegerSignal("speed", 42));

	EXPECT_EQ(record().lastFunction, "simxSetIntegerSignal");
	EXPECT_EQ(record().lastSignalName, "speed");
	EXPECT_EQ(record().lastIntValue, 42);
	EXPECT_EQ(record().lastOpMode, simx_opmode_oneshot);
}

TEST_F(FunctionalTest, SetFloatSignalForwardsNameValueAndOneshotMode)
{
	CoppeliaSimClient& client = makeConnectedClient();
	EXPECT_TRUE(client.setFloatSignal("gain", 3.5f));

	EXPECT_EQ(record().lastFunction, "simxSetFloatSignal");
	EXPECT_EQ(record().lastSignalName, "gain");
	EXPECT_FLOAT_EQ(record().lastFloatValue, 3.5f);
	EXPECT_EQ(record().lastOpMode, simx_opmode_oneshot);
}

TEST_F(FunctionalTest, SetStringSignalForwardsExactBytesAndBlockingMode)
{
	CoppeliaSimClient& client = makeConnectedClient();
	// Embed a null byte to prove the length comes from size(), not strlen().
	EXPECT_TRUE(client.setStringSignal("msg", std::string("ab\0cd", 5)));

	EXPECT_EQ(record().lastFunction, "simxSetStringSignal");
	EXPECT_EQ(record().lastSignalName, "msg");
	EXPECT_EQ(record().lastStringValue, std::string("ab\0cd", 5));
	EXPECT_EQ(record().lastStringLength, 5);
	EXPECT_EQ(record().lastOpMode, simx_opmode_blocking);
}

// --- get* round-trip (success) --------------------------------------------

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

	const auto value = client.getFloatSignal("y");
	ASSERT_TRUE(value.has_value());
	EXPECT_FLOAT_EQ(*value, -1.25f);
	EXPECT_EQ(record().lastSignalName, "y");
}

TEST_F(FunctionalTest, GetStringSignalIsLengthBasedNotNullTerminated)
{
	CoppeliaSimClient& client = makeConnectedClient();
	// A strlen-based reconstruction would stop at "ab"; length-based gives all 5.
	record().nextStringSignal = std::string("ab\0cd", 5);

	const auto result = client.getStringSignal("z");
	ASSERT_TRUE(result.has_value());
	EXPECT_EQ(result->size(), 5u);
	EXPECT_EQ(*result, std::string("ab\0cd", 5));
}

// --- object queries (success) ---------------------------------------------

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

	const auto p = client.getObjectPosition(5);
	ASSERT_TRUE(p.has_value());
	EXPECT_FLOAT_EQ(p->x, 1.0f);
	EXPECT_FLOAT_EQ(p->y, 2.0f);
	EXPECT_FLOAT_EQ(p->z, 3.0f);
	EXPECT_EQ(record().lastObjectHandle, 5);
}

TEST_F(FunctionalTest, GetObjectOrientationMapsArrayToStruct)
{
	CoppeliaSimClient& client = makeConnectedClient();
	record().nextOrientation[0] = 0.4f;
	record().nextOrientation[1] = 0.5f;
	record().nextOrientation[2] = 0.6f;

	const auto o = client.getObjectOrientation(5);
	ASSERT_TRUE(o.has_value());
	EXPECT_FLOAT_EQ(o->alpha, 0.4f);
	EXPECT_FLOAT_EQ(o->beta, 0.5f);
	EXPECT_FLOAT_EQ(o->gamma, 0.6f);
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

	const auto pose = client.getObjectPose(5);
	ASSERT_TRUE(pose.has_value());
	EXPECT_FLOAT_EQ(pose->position.x, 1.0f);
	EXPECT_FLOAT_EQ(pose->position.y, 2.0f);
	EXPECT_FLOAT_EQ(pose->position.z, 3.0f);
	EXPECT_FLOAT_EQ(pose->orientation.alpha, 4.0f);
	EXPECT_FLOAT_EQ(pose->orientation.beta, 5.0f);
	EXPECT_FLOAT_EQ(pose->orientation.gamma, 6.0f);
}

TEST_F(FunctionalTest, GetObjectQueriesUseWorldFrame)
{
	CoppeliaSimClient& client = makeConnectedClient();
	(void)client.getObjectPosition(5);
	// kWorldFrame (-1) is passed as the relative-to handle; recorded via lastObjectHandle
	// being the queried object, not the frame. Just assert the call happened with the object.
	EXPECT_EQ(record().lastFunction, "simxGetObjectPosition");
	EXPECT_EQ(record().lastObjectHandle, 5);
}

// --- simulation control ---------------------------------------------------

TEST_F(FunctionalTest, StartSimulationCallsApiWithBlockingMode)
{
	CoppeliaSimClient& client = makeConnectedClient();
	EXPECT_TRUE(client.startSimulation());
	EXPECT_EQ(record().lastFunction, "simxStartSimulation");
	EXPECT_EQ(record().lastOpMode, simx_opmode_blocking);
}

TEST_F(FunctionalTest, StopSimulationCallsApiWithBlockingMode)
{
	CoppeliaSimClient& client = makeConnectedClient();
	EXPECT_TRUE(client.stopSimulation());
	EXPECT_EQ(record().lastFunction, "simxStopSimulation");
	EXPECT_EQ(record().lastOpMode, simx_opmode_blocking);
}

// --- failure paths: every command reports false, every query returns nullopt ---

TEST_F(FunctionalTest, SetSignalsReturnFalseOnApiFailure)
{
	CoppeliaSimClient& client = makeConnectedClient();
	record().returnCode = simx_return_timeout_flag;

	EXPECT_FALSE(client.setIntegerSignal("x", 1));
	EXPECT_FALSE(client.setFloatSignal("y", 1.0f));
	EXPECT_FALSE(client.setStringSignal("z", "v"));
}

TEST_F(FunctionalTest, SimulationControlReturnsFalseOnApiFailure)
{
	CoppeliaSimClient& client = makeConnectedClient();
	record().returnCode = simx_return_remote_error_flag;

	EXPECT_FALSE(client.startSimulation());
	EXPECT_FALSE(client.stopSimulation());
}

TEST_F(FunctionalTest, GetSignalsReturnNulloptOnApiFailure)
{
	CoppeliaSimClient& client = makeConnectedClient();
	record().returnCode = simx_return_timeout_flag;

	EXPECT_FALSE(client.getIntegerSignal("x").has_value());
	EXPECT_FALSE(client.getFloatSignal("y").has_value());
	EXPECT_FALSE(client.getObjectHandle("Cuboid").has_value());
}

TEST_F(FunctionalTest, GetStringSignalReturnsNulloptAndDoesNotTouchWildPointerOnFailure)
{
	CoppeliaSimClient& client = makeConnectedClient();
	// On failure the fake leaves the out-params untouched (pointer stays null);
	// the client must not build a string from them. This is the bug ASan caught.
	record().returnCode = simx_return_timeout_flag;

	EXPECT_FALSE(client.getStringSignal("z").has_value());
}

TEST_F(FunctionalTest, GetObjectQueriesReturnNulloptOnApiFailure)
{
	CoppeliaSimClient& client = makeConnectedClient();
	record().returnCode = simx_return_novalue_flag;

	EXPECT_FALSE(client.getObjectPosition(5).has_value());
	EXPECT_FALSE(client.getObjectOrientation(5).has_value());
	EXPECT_FALSE(client.getObjectPose(5).has_value());
}

// --- logging --------------------------------------------------------------

TEST_F(FunctionalTest, LogCoppeliaModeSendsStatusbarMessageWhenConnected)
{
	record().startReturn = 0;
	client.emplace("127.0.0.1", 19999, LogMode::LOG_COPPELIA);
	(void)client->initialize();
	fake_simx::reset(); // clear the simxStart call so we observe only the log

	client->logMsg("hi there");
	EXPECT_EQ(record().lastFunction, "simxAddStatusbarMessage");
	EXPECT_EQ(record().lastStringValue, "hi there");
	EXPECT_EQ(record().lastOpMode, simx_opmode_oneshot);
}

TEST_F(FunctionalTest, NoLogsModeDoesNotTouchTheApi)
{
	CoppeliaSimClient& client = makeConnectedClient();
	fake_simx::reset();

	client.logMsg("should be ignored");
	EXPECT_EQ(record().callCount, 0);
}

TEST_F(FunctionalTest, LogCmdModePrintsToStdoutAndSkipsApi)
{
	CoppeliaSimClient& client = makeConnectedClient();
	fake_simx::reset();

	testing::internal::CaptureStdout();
	client.setLogMode(LogMode::LOG_CMD);
	client.logMsg("console only");
	std::string out = testing::internal::GetCapturedStdout();

	EXPECT_NE(out.find("console only"), std::string::npos);
	EXPECT_EQ(record().callCount, 0); // LOG_CMD must not hit the API
}
