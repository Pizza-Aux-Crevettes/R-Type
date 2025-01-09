
# R-Type Communication Protocol

## Introduction

This document provides a detailed explanation of the communication protocol for the R-Type server. The protocol supports both TCP and UDP for managing game actions, player initialization, room management, and real-time game updates.

---

## Protocol Overview

### Transport Protocols

- **TCP**: Used for reliable communication such as room management, player initialization, and other critical actions.
- **UDP**: Used for real-time communication like player movement updates, map viewport updates, and obstacle updates.

### Message Structure

Each message contains the following fields:

| Field       | Type     | Size (bytes) | Description                             |
|-------------|----------|--------------|-----------------------------------------|
| **OpCode**  | `int16_t`| 2            | Operation Code identifying the message. |
| **Payload** | Varies   | Variable     | Additional data relevant to the operation. |

---

## OpCode Definitions

| OpCode                   | Value | Description                                |
|--------------------------|-------|--------------------------------------------|
| DEFAULT                  | 0     | No operation.                             |
| CREATE_ROOM              | 1     | Create a new room.                        |
| JOIN_ROOM                | 2     | Join an existing room.                    |
| LEAVE_ROOM               | 3     | Leave an existing room.                   |
| DELETE_ROOM              | 4     | Delete an existing room.                  |
| NEW_PLAYER               | 5     | Initialize a new player.                  |
| HOTKEY_PRESSED           | 6     | Process a player's key press.             |
| START_GAME               | 7     | Start a game in a room.                   |
| STOP_GAME                | 8     | Stop an ongoing game.                     |
| CREATE_ROOM_CALLBACK     | 9     | Callback: Room creation result.           |
| LEAVE_ROOM_CALLBACK      | 10    | Callback: Room leave result.              |
| JOIN_ROOM_CALLBACK       | 11    | Callback: Room join result.               |
| DELETE_ROOM_CALLBACK     | 12    | Callback: Room deletion result.           |
| NEW_PLAYER_CALLBACK      | 13    | Callback: New player initialization.      |
| START_GAME_CALLBACK      | 14    | Callback: Game start confirmation.        |
| STOP_GAME_CALLBACK       | 15    | Callback: Game stop confirmation.         |
| CREATE_ROOM_BROADCAST    | 16    | Broadcast: Room creation announcement.    |
| LEAVE_ROOM_BROADCAST     | 17    | Broadcast: Player leaving a room.         |
| JOIN_ROOM_BROADCAST      | 18    | Broadcast: Player joining a room.         |
| DELETE_ROOM_BROADCAST    | 19    | Broadcast: Room deletion announcement.    |
| NEW_PLAYER_BROADCAST     | 20    | Broadcast: New player creation.           |
| START_GAME_BROADCAST     | 21    | Broadcast: Game started in a room.        |
| STOP_GAME_BROADCAST      | 22    | Broadcast: Game stopped in a room.        |
| PLAYER_POSITION_UPDATE   | 23    | Update: Player position (UDP).            |
| PLAYER_LIFE_UPDATE       | 24    | Update: Player life (UDP).                |
| MAP_VIEWPORT_UPDATE          | 25    | Update: Map viewport (UDP).               |
| MAP_OBSTACLES_UPDATE            | 26    | Update: Map obstacles (UDP).              |

---

## Detailed Protocol Descriptions

### **DEFAULT**
- **Description**: Default operation with no meaningful effect. Primarily used for testing or pinging the server.
- **Payload**:
  - **None**

---

### **CREATE_ROOM**
- **Description**: Creates a new room for players to join.
- **Payload**:
  - `capacity` (int16_t): Maximum number of players allowed in the room.
  - `isPublic` (int16_t): Boolean flag (1 for public, 0 for private room).
  - `mapId` (int16_t): ID of the map assigned to the room.

---

### **JOIN_ROOM**
- **Description**: Allows a player to join an existing room.
- **Payload**:
  - `roomCode` (string): Code of the room the player wants to join.

---

### **LEAVE_ROOM**
- **Description**: Allows a player to leave an existing room.
- **Payload**:
  - `roomCode` (string): Code of the room the player is leaving.

---

### **DELETE_ROOM**
- **Description**: Deletes a room created by the requesting player.
- **Payload**:
  - `roomCode` (string): Code of the room to delete.

---

### **NEW_PLAYER**
- **Description**: Initializes a new player in the server system.
- **Payload**:
  - `playerName` (string): Name of the player being created.

---

### **HOTKEY_PRESSED**
- **Description**: Processes a key press from a player.
- **Payload**:
  - `hotkey` (int16_t): Code of the key pressed.

---

### **START_GAME**
- **Description**: Starts a game within a room.
- **Payload**:
  - `roomCode` (string): Code of the room where the game will start.

---

### **STOP_GAME**
- **Description**: Stops an ongoing game within a room.
- **Payload**:
  - `roomCode` (string): Code of the room where the game will stop.

---

### **CREATE_ROOM_CALLBACK**
- **Description**: Provides the result of a room creation request.
- **Payload**:
  - `status` (int16_t): Status code (0 for success, non-zero for failure).
  - `roomCode` (string): Code of the newly created room (if successful).

---

### **LEAVE_ROOM_CALLBACK**
- **Description**: Indicates whether a room was successfully left.
- **Payload**:
  - `status` (int16_t): Status code (0 for success, non-zero for failure).

---

### **JOIN_ROOM_CALLBACK**
- **Description**: Indicates whether a room was successfully joined.
- **Payload**:
  - `status` (int16_t): Status code (0 for success, non-zero for failure).

---

### **DELETE_ROOM_CALLBACK**
- **Description**: Indicates whether a room was successfully deleted.
- **Payload**:
  - `status` (int16_t): Status code (0 for success, non-zero for failure).

---

### **NEW_PLAYER_CALLBACK**
- **Description**: Confirms the initialization of a new player.
- **Payload**:
  - `playerId` (int32_t): ID of the newly created player.

---

### **START_GAME_CALLBACK**
- **Description**: Confirms that a game has started successfully.
- **Payload**:
  - `status` (int16_t): Status code (0 for success, non-zero for failure).

---

### **STOP_GAME_CALLBACK**
- **Description**: Confirms that a game has stopped successfully.
- **Payload**:
  - `status` (int16_t): Status code (0 for success, non-zero for failure).

---

### **CREATE_ROOM_BROADCAST**
- **Description**: Announces the creation of a new room to all clients.
- **Payload**:
  - `roomCode` (string): Code of the newly created room.

---

### **LEAVE_ROOM_BROADCAST**
- **Description**: Announces that a player has left a room.
- **Payload**:
  - `roomCode` (string): Code of the room.
  - `playerId` (int32_t): ID of the player who left.

---

### **JOIN_ROOM_BROADCAST**
- **Description**: Announces that a player has joined a room.
- **Payload**:
  - `roomCode` (string): Code of the room.
  - `playerId` (int32_t): ID of the player who joined.

---

### **DELETE_ROOM_BROADCAST**
- **Description**: Announces that a room has been deleted.
- **Payload**:
  - `roomCode` (string): Code of the deleted room.

---

### **NEW_PLAYER_BROADCAST**
- **Description**: Announces the creation of a new player.
- **Payload**:
  - `playerId` (int32_t): ID of the newly created player.
  - `playerName` (string): Name of the newly created player.

---

### **START_GAME_BROADCAST**
- **Description**: Announces that a game has started in a room.
- **Payload**:
  - `roomCode` (string): Code of the room where the game started.

---

### **STOP_GAME_BROADCAST**
- **Description**: Announces that a game has stopped in a room.
- **Payload**:
  - `roomCode` (string): Code of the room where the game stopped.

---

### **PLAYER_POSITION_UPDATE**
- **Description**: Updates the position of a player in real-time.
- **Payload**:
  - `playerId` (int32_t): ID of the player whose position is updated.
  - `posX` (float): X-coordinate of the player.
  - `posY` (float): Y-coordinate of the player.

---

### **PLAYER_LIFE_UPDATE**
- **Description**: Updates the life status of a player.
- **Payload**:
  - `playerId` (int32_t): ID of the player whose life is updated.
  - `life` (float): Current life value of the player.

---

### **MAP_VIEWPORT_UPDATE**
- **Description**: Updates the viewport of the map.
- **Payload**:
  - `viewport` (int32_t): Current viewport value.

---

### **MAP_OBSTACLES_UPDATE**
- **Description**: Updates the obstacle positions on the map.
- **Payload**:
  - `obstacleX` (float): X-coordinate of the obstacle.
  - `obstacleY` (float): Y-coordinate of the obstacle.
  - `type` (int16_t): Type identifier for the obstacle.

---
