#include "protocol/Protocol.hpp"
#include "util/Logger.hpp"

Protocol::Protocol() {}

void Protocol::handleMessage(int clientSocket, SmartBuffer& smartBuffer) {
    uint8_t opCode;
    smartBuffer >> opCode;

    switch (opCode) {
    case CREATE_ROOM:
        //
        break;
    case JOIN_ROOM:
        //
        break;
    case DELETE_ROOM:
        //
        break;
    default:
        Logger::error("Received unknown OpCode: " + std::to_string(opCode));
    }
}

void createRoom(int clientSocket, SmartBuffer& smartBuffer) {
    /*
     * Protocol CREATE_ROOM
     * int8_t opCode
     * Data sent in response: CREATE_ROOM_CALLBACK
     */
    Logger::info("CREATE_ROOM ==> No data");
}

void joinRoom(int clientSocket, SmartBuffer& smartBuffer) {
    /*
     * Protocol JOIN_ROOM:
     * int8_t opCode
     * int32_t roomCode
     * Data sent in response: JOIN_ROOM_CALLBACK
     */
    int32_t roomCode;
    smartBuffer >> roomCode;
    Logger::info("JOIN_ROOM ==> roomCode = " + std::to_string(roomCode));
}

void deleteRoom(int clientSocket, SmartBuffer& smartBuffer) {
    /*
     * Protocol DELETE_ROOM:
     * int8_t opCode
     * int32_t roomCode
     * Data sent in response: DELETE_ROOM_CALLBACK
     */
    int32_t roomCode;
    smartBuffer >> roomCode;
    Logger::info("DELETE_ROOM ==> roomCode = " + std::to_string(roomCode));
}
