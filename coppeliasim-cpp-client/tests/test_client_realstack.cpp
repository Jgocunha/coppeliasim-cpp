// Tier 3: smoke tests against the REAL networking stack (links the actual
// coppeliasim-cpp-client library, including the genuine simx* implementation).
//
// No simulator is running, so these verify the graceful-failure behaviour:
// the client must report "not connected" and fail initialize() cleanly without
// hanging or crashing.
#include <gtest/gtest.h>

#include "client.h"

using namespace coppeliasim_cpp;

TEST(RealStackTest, NotConnectedBeforeInitialize)
{
	CoppeliaSimClient client("127.0.0.1", 19999, LogMode::NO_LOGS);
	// clientID is -1 until initialize() succeeds, so the connection id query fails.
	EXPECT_FALSE(client.isConnected());
}

TEST(RealStackTest, InitializeFailsAgainstDeadPort)
{
	// Use a high, almost-certainly-unused port so we don't accidentally reach a
	// real CoppeliaSim instance. simxStart blocks ~2s then returns -1.
	CoppeliaSimClient client("127.0.0.1", 65501, LogMode::NO_LOGS);
	EXPECT_FALSE(client.initialize());
	EXPECT_EQ(client.getClientID(), -1);
	EXPECT_FALSE(client.isConnected());
	// Destructor (simxFinish) runs here and must not hang -- enforced by the
	// per-test CTest timeout configured in tests/CMakeLists.txt.
}
