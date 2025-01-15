# R-Type Communication Protocol

## Introduction
This document describes the updated communication protocol for the R-Type server. It uses both TCP and UDP. TCP is used for reliable operations (e.g., creating a new player, hotkey inputs), while UDP is used for real-time updates (e.g., positions of players, obstacles, and bullets).

## Protocol Overview

### Transport Protocols
- **TCP**: For reliable commands (e.g., creating a player, hotkey processing).
- **UDP**: For real-time updates (e.g., player positions, obstacles, bullets).

### Message Structure
Each message has the following form:

| Field       | Type     | Size (bytes) | Description                               |
|-------------|----------|--------------|-------------------------------------------|
| **OpCode**  | `int16_t`| 2            | Identifies the operation (see below).     |
| **Payload** | Varies   | Variable     | Data relevant to the specific operation.  |

## OpCode Definitions

| OpCode                     | Value | Description                                   |
|----------------------------|-------|-----------------------------------------------|
| **DEFAULT**                | 0     | No operation (used for testing or ping).      |
| **HOTKEY_PRESSED**         | 1     | Process a hotkey (key press) from a player.   |
| **CREATE_PLAYER**          | 10    | Request to create a new player.               |
| **CREATE_PLAYER_CALLBACK** | 11    | Callback confirming the newly created player. |
| **CREATE_PLAYER_BROADCAST**| 12    | Broadcast to others about a new player.       |
| **UPDATE_PLAYERS**         | 20    | Update players (positions, states, etc.).     |
| **UPDATE_VIEWPORT**        | 21    | Update current map viewport.                  |
| **UPDATE_OBSTACLES**       | 22    | Update obstacles data.                        |
| **UPDATE_BULLETS**         | 23    | Update bullets data.                          |
| **DELETE_ENTITY**          | 30    | Delete an entity (player/obstacle/bullet).    |

## Detailed Protocol Descriptions

### DEFAULT
- **Description**: No specific action. Often used for heartbeat or basic connection tests.  
- **Payload**: None

---

### HOTKEY_PRESSED
- **Description**: Notifies the server of a key press by a specific player.  
- **Payload**:  
  - `playerId` (int32_t)  
  - `hotkeyCode` (int16_t)

---

### CREATE_PLAYER
- **Description**: Requests creation of a new player on the server.  
- **Payload**:  
  - `playerName` (string)

### CREATE_PLAYER_CALLBACK
- **Description**: Server response confirming the creation of a new player.  
- **Payload**:  
  - `playerId` (int32_t)
  - `width` (int16_t)
  - `height` (int16_t)

### CREATE_PLAYER_BROADCAST
- **Description**: Broadcasts to all clients that a new player has joined.  
- **Payload**:  
  - `playerId` (int32_t)  
  - `playerName` (string)
  - `width` (int16_t)
  - `height` (int16_t)

---

### UPDATE_PLAYERS
- **Description**: Updates the positions (and possibly other data) of multiple players.  
- **Payload** (implementation-dependent, for each player):
  - `playerId` (int32_t)  
  - `posX` (int32_t)  
  - `posY` (int32_t)

### UPDATE_VIEWPORT
- **Description**: Updates the current map viewport.  
- **Payload**:
  - `viewport` (double)

### UPDATE_OBSTACLES
- **Description**: Updates the positions or states of obstacles on the map.  
- **Payload** (implementation-dependent, for each obstacle):
  - `obstacleId` (int32_t)
  - `posX` (int32_t)
  - `posY` (int32_t)
  - `size` (int16_t)
  - `type` (int16_t)

### UPDATE_BULLETS
- **Description**: Updates the positions or states of bullets on the map.  
- **Payload** (implementation-dependent, for each bullet):
  - `bulletId` (int32_t)
  - `posX` (int32_t)
  - `posY` (int32_t)
  - `speed` (int16_t)
  - `type` (int16_t)

---

### DELETE_ENTITY
- **Description**: Deletes an existing entity (player, obstacle, or bullet).  
- **Payload**:
  - `entityId` (int32_t)

## Notes
- All OpCodes must be handled consistently by both server and client.
- The structure and interpretation of the payload must match exactly between sender and receiver.
- Some messages may be sent via TCP or UDP depending on the reliability required.