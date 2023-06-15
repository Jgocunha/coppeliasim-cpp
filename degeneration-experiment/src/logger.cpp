#include "./logger.h"

Logger::Logger(int clientID)
    : clientID(clientID)
{
}

void Logger::log(const std::string& message)
{
    // Log to the console
    if(LOG_ON_CMD)
        printf("%s\n", message.c_str());

    // Log to CoppeliaSim's status bar
    if(LOG_ON_COPPELIA)
        simxAddStatusbarMessage(clientID, message.c_str(), simx_opmode_oneshot);
}
