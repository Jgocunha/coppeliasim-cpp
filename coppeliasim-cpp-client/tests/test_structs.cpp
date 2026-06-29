// Tier 1: pure-logic tests for the data types in client.h.
// No networking, no fake layer -- these only need the header.
#include <gtest/gtest.h>

#include <set>

#include "client.h"

using namespace coppeliasim_cpp;

TEST(PositionTest, DefaultConstructorZeroesFields)
{
	Position p;
	EXPECT_FLOAT_EQ(p.x, 0.0f);
	EXPECT_FLOAT_EQ(p.y, 0.0f);
	EXPECT_FLOAT_EQ(p.z, 0.0f);
}

TEST(PositionTest, ValueConstructorStoresFields)
{
	Position p(1.5f, -2.0f, 3.25f);
	EXPECT_FLOAT_EQ(p.x, 1.5f);
	EXPECT_FLOAT_EQ(p.y, -2.0f);
	EXPECT_FLOAT_EQ(p.z, 3.25f);
}

TEST(OrientationTest, DefaultConstructorZeroesFields)
{
	Orientation o;
	EXPECT_FLOAT_EQ(o.alpha, 0.0f);
	EXPECT_FLOAT_EQ(o.beta, 0.0f);
	EXPECT_FLOAT_EQ(o.gamma, 0.0f);
}

TEST(OrientationTest, ValueConstructorStoresFields)
{
	Orientation o(0.1f, 0.2f, 0.3f);
	EXPECT_FLOAT_EQ(o.alpha, 0.1f);
	EXPECT_FLOAT_EQ(o.beta, 0.2f);
	EXPECT_FLOAT_EQ(o.gamma, 0.3f);
}

TEST(PoseTest, DefaultConstructorZeroesBothMembers)
{
	Pose pose;
	EXPECT_FLOAT_EQ(pose.position.x, 0.0f);
	EXPECT_FLOAT_EQ(pose.position.y, 0.0f);
	EXPECT_FLOAT_EQ(pose.position.z, 0.0f);
	EXPECT_FLOAT_EQ(pose.orientation.alpha, 0.0f);
	EXPECT_FLOAT_EQ(pose.orientation.beta, 0.0f);
	EXPECT_FLOAT_EQ(pose.orientation.gamma, 0.0f);
}

TEST(PoseTest, ComposesPositionAndOrientation)
{
	Position p(1.0f, 2.0f, 3.0f);
	Orientation o(4.0f, 5.0f, 6.0f);
	Pose pose(p, o);
	EXPECT_FLOAT_EQ(pose.position.x, 1.0f);
	EXPECT_FLOAT_EQ(pose.position.z, 3.0f);
	EXPECT_FLOAT_EQ(pose.orientation.alpha, 4.0f);
	EXPECT_FLOAT_EQ(pose.orientation.gamma, 6.0f);
}

TEST(LogModeTest, EnumeratorsAreDistinctAndNoLogsIsZero)
{
	EXPECT_EQ(static_cast<int>(LogMode::NO_LOGS), 0);

	// All four enumerators must be distinct values.
	std::set<int> values{
		static_cast<int>(LogMode::NO_LOGS),
		static_cast<int>(LogMode::LOG_CMD),
		static_cast<int>(LogMode::LOG_COPPELIA),
		static_cast<int>(LogMode::LOG_COPPELIA_CMD)};
	EXPECT_EQ(values.size(), 4u);
}
