# R-Type Communication Protocol

## Introduction

This document provides a detailed explanation of the communication protocol for the R-Type server. The protocol supports both TCP and UDP for managing player initialization, hotkey processing, and real-time updates.

---

## Protocol Overview

### Transport Protocols

- **TCP**: Used for reliable communication such as player initialization and key press processing.
- **UDP**: Used for real-time updates like player position, map viewport updates, and obstacle updates.

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
| HOTKEY_PRESSED           | 1     | Process a player's key press.             |
| NEW_PLAYER               | 10    | Initialize a new player.                  |
| NEW_PLAYER_CALLBACK      | 11    | Callback: New player initialization.      |
| NEW_PLAYER_BROADCAST     | 12    | Broadcast: New player creation.           |
| PLAYER_POSITION_UPDATE   | 13    | Update: Player position (UDP).            |
| MAP_VIEWPORT_UPDATE      | 20    | Update: Map viewport (UDP).               |
| MAP_OBSTACLES_UPDATE     | 21    | Update: Map obstacles (UDP).              |

---

## Detailed Protocol Descriptions

### **DEFAULT**
- **Description**: Default operation with no meaningful effect. Primarily used for testing or pinging the server.
- **Payload**:
  - **None**

---

### **HOTKEY_PRESSED**
- **Description**: Processes a key press from a player.
- **Payload**:
  - `playerId` (int16_t): ID of the player pressing the key.
  - `hotkey` (int16_t): Code of the key pressed.

---

### **NEW_PLAYER**
- **Description**: Initializes a new player in the server system.
- **Payload**:
  - `playerName` (string): Name of the player being created.

---

### **NEW_PLAYER_CALLBACK**
- **Description**: Confirms the initialization of a new player.
- **Payload**:
  - `playerId` (int16_t): ID of the newly created player.

---

### **NEW_PLAYER_BROADCAST**
- **Description**: Announces the creation of a new player.
- **Payload**:
  - `playerId` (int16_t): ID of the newly created player.
  - `playerName` (string): Name of the newly created player.

---

### **PLAYER_POSITION_UPDATE**
- **Description**: Updates the position of a player in real-time.
- **Payload**:
  - `playerId` (int16_t): ID of the player whose position is updated.
  - `posX` (int32_t): X-coordinate of the player.
  - `posY` (int32_t): Y-coordinate of the player.

---

### **MAP_VIEWPORT_UPDATE**
- **Description**: Updates the viewport of the map.
- **Payload**:
  - `viewport` (int16_t): Current viewport value.

---

### **MAP_OBSTACLES_UPDATE**
- **Description**: Updates the obstacle positions on the map.
- **Payload**:
  - `obstacleId` (int16_t): ID of the obstacle.
  - `obstacleX` (int32_t): X-coordinate of the obstacle.
  - `obstacleY` (int32_t): Y-coordinate of the obstacle.
  - `type` (int16_t): Type identifier for the obstacle.

---

## Notes
- All OpCodes must be processed by both the server and the client for proper synchronization.
- Payload data types must match exactly to avoid communication errors.
