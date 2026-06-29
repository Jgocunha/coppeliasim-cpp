#pragma once

#include <optional>
#include <string>
#include <memory>

extern "C"
{
#include "extApi.h"
#include "extApiPlatform.h"
}

namespace coppeliasim_cpp
{
	enum class LogMode
	{
		NO_LOGS = 0,
		LOG_CMD,
		LOG_COPPELIA,
		LOG_COPPELIA_CMD
	};

	// Relative-to-world-frame handle for the legacy remote API object queries.
	inline constexpr simxInt kWorldFrame = -1;

	struct Position
	{
		// x/y/z are an intrinsic vector triple; aggregate init keeps the type trivial.
		float x{0};
		float y{0};
		float z{0};
	};

	struct Orientation
	{
		// Euler angles are an intrinsic triple.
		float alpha{0};
		float beta{0};
		float gamma{0};
	};

	struct Pose
	{
		Position position;
		Orientation orientation;
	};

	class CoppeliaSimClient
	{
	private:
		int clientID{-1};
		simxInt connectionPort;
		LogMode logMode;
		std::unique_ptr<simxChar[]> connectionAddress; // NOLINT(modernize-avoid-c-arrays) -- C string buffer for the C API.

	public:
		explicit CoppeliaSimClient(const std::string& connectionAddress = "127.0.0.1",
			int connectionPort = 19999,
			LogMode logMode = LogMode::NO_LOGS);

		// Owns a connection handle that the destructor releases via simxFinish.
		// Not copyable. Movable: the move leaves the source with an inert handle
		// (clientID == -1) so its destructor's simxFinish becomes a no-op.
		CoppeliaSimClient(const CoppeliaSimClient&) = delete;
		CoppeliaSimClient& operator=(const CoppeliaSimClient&) = delete;
		CoppeliaSimClient(CoppeliaSimClient&& other) noexcept;
		CoppeliaSimClient& operator=(CoppeliaSimClient&& other) noexcept;

		~CoppeliaSimClient();

		// Construct and connect in one step. Returns nullopt if the connection
		// could not be established, so a returned client is always connected.
		[[nodiscard]] static std::optional<CoppeliaSimClient> connect(
			const std::string& connectionAddress = "127.0.0.1",
			int connectionPort = 19999,
			LogMode logMode = LogMode::NO_LOGS);

		// Establishes the connection. Prefer connect(); kept for callers that
		// construct first. Returns false (and leaves the client unconnected) on failure.
		[[nodiscard]] bool initialize();
		[[nodiscard]] bool isConnected() const;
		[[nodiscard]] int getClientID() const;

		// Commands return true on success, false if the API call did not complete.
		bool startSimulation() const;
		bool stopSimulation() const;

		bool setIntegerSignal(const std::string& signalName, int signalValue) const;
		bool setFloatSignal(const std::string& signalName, float signalValue) const;
		bool setStringSignal(const std::string& signalName, const std::string& signalValue) const;

		// Queries return nullopt if the API call failed; the value is never
		// fabricated from an unwritten out-parameter.
		[[nodiscard]] std::optional<int> getIntegerSignal(const std::string& signalName) const;
		[[nodiscard]] std::optional<float> getFloatSignal(const std::string& signalName) const;
		[[nodiscard]] std::optional<std::string> getStringSignal(const std::string& signalName) const;

		[[nodiscard]] std::optional<int> getObjectHandle(const std::string& objectName) const;
		[[nodiscard]] std::optional<Pose> getObjectPose(int objectHandle) const;
		[[nodiscard]] std::optional<Position> getObjectPosition(int objectHandle) const;
		[[nodiscard]] std::optional<Orientation> getObjectOrientation(int objectHandle) const;

		void setLogMode(LogMode mode);
		void logMsg(const std::string& message) const;
	};
}
