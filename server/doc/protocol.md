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
| NEW_PLAYER_BROADCAST     | 12    | Broadcast: New player creation (UDP).     |
| PLAYER_POSITION_UPDATE   | 13    | Update: Player position (UDP).            |
| PLAYER_DELETED           | 15    | Notify: Player deletion (UDP).            |
| VIEWPORT_UPDATE          | 20    | Update: Map viewport (UDP).               |
| OBSTACLES_UPDATE         | 30    | Update: Map obstacles (UDP).              |
| OBSTACLE_DELETED         | 31    | Notify: Obstacle deletion (UDP).          |
| BULLETS_UPDATE           | 40    | Update: Bullets positions (UDP).          |
| BULLET_DELETED           | 41    | Notify: Bullet deletion (UDP).            |

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
  - `playerId` (int32_t): ID of the player pressing the key.
  - `hotkey` (int16_t): Code of the key pressed.

---

### **NEW_PLAYER**
- **Description**: Initializes a new player in the server system.
- **Payload**:
  - `playerName` (string): Name of the player being created.

### **NEW_PLAYER_CALLBACK**
- **Description**: Confirms the initialization of a new player.
- **Payload**:
  - `playerId` (int32_t): ID of the newly created player.

### **NEW_PLAYER_BROADCAST**
- **Description**: Announces the creation of a new player.
- **Payload**:
  - `playerId` (int32_t): ID of the newly created player.
  - `playerName` (string): Name of the newly created player.

---

### **PLAYER_UPDATE**
- **Description**: Updates the position of a player in real-time.
- **Payload**:
  - `playerId` (int32_t): ID of the player whose position is updated.
  - `posX` (int32_t): X-coordinate of the player.
  - `posY` (int32_t): Y-coordinate of the player.

### **PLAYER_DELETED**
- **Description**: Deletes the player from its ID.
- **Payload**:
  - `playerId` (int32_t): ID of the player.

---

### **VIEWPORT_UPDATE**
- **Description**: Updates the viewport of the map.
- **Payload**:
  - `viewport` (double): Current viewport value.

---

### **OBSTACLES_UPDATE**
- **Description**: Updates the obstacle positions on the map.
- **Payload**:
  - `obstacleId` (int32_t): ID of the obstacle.
  - `obstacleX` (int32_t): X-coordinate of the obstacle.
  - `obstacleY` (int32_t): Y-coordinate of the obstacle.
  - `size` (int16_t): Size of the block.
  - `type` (int16_t): Type identifier for the obstacle.

### **OBSTACLE_DELETED**
- **Description**: Deletes the obstacle from its ID.
- **Payload**:
  - `obstacleId` (int32_t): ID of the obstacle.

---

### **BULLETS_UPDATE**
- **Description**: Updates the positions of bullets on the map.
- **Payload**:
  - `bulletId` (int32_t): ID of the bullet.
  - `bulletX` (int32_t): X-coordinate of the bullet.
  - `bulletY` (int32_t): Y-coordinate of the bullet.
  - `speed` (int16_t): Speed of the bullet.
  - `type` (int16_t): Type identifier for the bullet.

### **BULLET_DELETED**
- **Description**: Deletes the bullet from its ID.
- **Payload**:
  - `bulletId` (int32_t): ID of the bullet.

---

## Notes
- All OpCodes must be processed by both the server and the client for proper synchronization.
- Payload data types must match exactly to avoid communication errors.
