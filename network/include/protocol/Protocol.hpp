/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Protocol.hpp
*/

#pragma once

#include <SmartBuffer.hpp>

/**
 * @class Protocol
 * @brief Singleton class responsible for handling and dispatching opcodes.
 *
 * The Protocol class processes incoming messages from clients based on
 * predefined operation codes (opcodes) and routes them to the appropriate
 * handlers.
 */
class Protocol {
  public:
    /**
     * @enum OpCode
     * @brief Enumeration of operation codes for communication.
     *
     * Each opcode corresponds to a specific client request or server response.
     */
    enum OpCode {
        DEFAULT,              /**< Default or unrecognized operation code. */
        CREATE_ROOM,          /**< Request to create a new room. */
        CREATE_ROOM_CALLBACK, /**< Response to a create room request. */
        JOIN_ROOM,            /**< Request to join an existing room. */
        JOIN_ROOM_CALLBACK,   /**< Response to a join room request. */
        DELETE_ROOM,          /**< Request to delete an existing room. */
        DELETE_ROOM_CALLBACK, /**< Response to a delete room request. */
        NEW_PLAYER,           /**< Request to create or retrieve a player. */
        NEW_PLAYER_CALLBACK,  /**< Response to a new player request. */
    };

    /**
     * @brief Retrieves the singleton instance of the Protocol.
     *
     * @return Protocol& Reference to the Protocol instance.
     */
    static Protocol& getInstance();

    /**
     * @brief Handles incoming messages based on their opcode.
     *
     * Parses the opcode from the SmartBuffer and routes the message to the
     * appropriate handler function.
     *
     * @param clientSocket The socket associated with the client.
     * @param smartBuffer The buffer containing the message data.
     */
    void handleMessage(int clientSocket, SmartBuffer& smartBuffer);

  private:
    /**
     * @brief Constructs the Protocol instance.
     *
     * Private constructor to enforce the Singleton pattern.
     */
    Protocol();

    /**
     * @brief Destructs the Protocol instance.
     */
    ~Protocol();

    /**
     * @brief Deleted copy constructor to prevent copying.
     */
    Protocol(const Protocol&) = delete;

    /**
     * @brief Deleted assignment operator to prevent assignment.
     */
    Protocol& operator=(const Protocol&) = delete;

    /**
     * @brief Handles the CREATE_ROOM opcode.
     *
     * Processes a request to create a new room.
     *
     * @param clientSocket The socket associated with the client.
     * @param smartBuffer The buffer containing the message data.
     */
    void createRoom(int clientSocket, SmartBuffer& smartBuffer);

    /**
     * @brief Handles the JOIN_ROOM opcode.
     *
     * Processes a request to join an existing room.
     *
     * @param clientSocket The socket associated with the client.
     * @param smartBuffer The buffer containing the message data.
     */
    void joinRoom(int clientSocket, SmartBuffer& smartBuffer);

    /**
     * @brief Handles the DELETE_ROOM opcode.
     *
     * Processes a request to delete an existing room.
     *
     * @param clientSocket The socket associated with the client.
     * @param smartBuffer The buffer containing the message data.
     */
    void deleteRoom(int clientSocket, SmartBuffer& smartBuffer);
};
