# R-Type Communication Protocol

## Introduction

This document provides a detailed explanation of the communication protocol for the R-Type server. The protocol supports TCP and UDP to manage game actions such as player initialization, room management, and real-time game updates.

---

## Protocol Overview

### Transport Protocols

- **TCP**: Reliable communication for room management, player initialization, and other critical actions.
- **UDP**: Real-time communication for fast updates like player movement, map viewport changes, and obstacle updates.

### Message Structure

Each message contains the following fields:

| Field       | Type     | Size (bytes) | Description                             |
|-------------|----------|--------------|-----------------------------------------|
| **OpCode**  | `int16_t`| 2            | Operation Code identifying the message. |
| **Payload** | Varies   | Variable     | Additional data relevant to the operation. |

---

## OpCode Definitions

| OpCode               | Value | Description                                |
|----------------------|-------|--------------------------------------------|
| DEFAULT              | 0     | No operation.                             |
| CREATE_ROOM          | 1     | Create a new room.                        |
| JOIN_ROOM            | 2     | Join an existing room.                    |
| DELETE_ROOM          | 3     | Delete an existing room.                  |
| NEW_PLAYER           | 4     | Initialize a new player.                  |
| HOTKEY_PRESSED       | 5     | Process a player's key press.             |
| PLAYER_UPDATE_POSITION | 6   | Update player position (UDP).             |
| VIEWPORT_UPDATE      | 7     | Update map viewport (UDP).                |
| BLOCKS_UPDATE        | 8     | Update map obstacles (UDP).               |

---

## Detailed Protocol Descriptions

### **CREATE_ROOM**

- **Description**: Creates a new room for players to join.
- **Direction**: Client → Server
- **Input Payload**:
  | Field       | Type       | Size (bytes) | Description                  |
  |-------------|------------|--------------|------------------------------|
  | `playerId`    | `int32_t`  | 4            | ID of the player creating the room. |
  | `capacity`  | `int16_t`  | 2            | Maximum number of players.   |
  | `isPublic`  | `int16_t`  | 2            | 1 for public, 0 for private. |
  | `mapId`     | `int16_t`  | 2            | ID of the map to assign.     |
- **Output Payload**:
  | Field       | Type       | Size (bytes) | Description                  |
  |-------------|------------|--------------|------------------------------|
  | `status`    | `int16_t`  | 2            | 0 for success, 1 for failure.|

---

### **JOIN_ROOM**

- **Description**: Allows a player to join an existing room.
- **Direction**: Client → Server
- **Input Payload**:
  | Field       | Type       | Size (bytes) | Description                  |
  |-------------|------------|--------------|------------------------------|
  | `roomCode`  | `string`   | Variable     | Code of the room to join.    |
  | `playerId`    | `int32_t`  | 4            | ID of the joining player.    |
- **Output Payload**:
  | Field       | Type       | Size (bytes) | Description                  |
  |-------------|------------|--------------|------------------------------|
  | `status`    | `int16_t`  | 2            | 0 for success, non-zero for failure.|

---

### **DELETE_ROOM**

- **Description**: Deletes a room created by the player.
- **Direction**: Client → Server
- **Input Payload**:
  | Field       | Type       | Size (bytes) | Description                  |
  |-------------|------------|--------------|------------------------------|
  | `roomCode`  | `string`   | Variable     | Code of the room to delete.  |
  | `playerId`    | `int32_t`  | 4            | ID of the player requesting deletion. |
- **Output Payload**:
  | Field       | Type       | Size (bytes) | Description                  |
  |-------------|------------|--------------|------------------------------|
  | `status`    | `int16_t`  | 2            | 0 for success, non-zero for failure.|

---

### **PLAYER_UPDATE_POSITION (UDP)**

- **Description**: Updates the position of a player in real-time.
- **Direction**: Server → Client
- **Payload**:
  | Field       | Type       | Size (bytes) | Description                  |
  |-------------|------------|--------------|------------------------------|
  | `playerId`    | `int32_t`  | 4            | ID of the player.            |
  | `posX`      | `float`    | 4            | X-coordinate of the player.  |
  | `posY`      | `float`    | 4            | Y-coordinate of the player.  |

---

### **VIEWPORT_UPDATE (UDP)**

- **Description**: Updates the viewport of the map.
- **Direction**: Server → Client
- **Payload**:
  | Field       | Type       | Size (bytes) | Description                  |
  |-------------|------------|--------------|------------------------------|
  | `viewport`  | `int32_t`  | 4            | Current viewport value.      |

---

### **BLOCKS_UPDATE (UDP)**

- **Description**: Updates the obstacle positions on the map.
- **Direction**: Server → Client
- **Payload**:
  | Field       | Type       | Size (bytes) | Description                  |
  |-------------|------------|--------------|------------------------------|
  | `obstacleX` | `float`    | 4            | X-coordinate of the obstacle.|
  | `obstacleY` | `float`    | 4            | Y-coordinate of the obstacle.|
  | `type`      | `int16_t`  | 2            | Type identifier for the obstacle.|

---

## SmartBuffer

SmartBuffer is a core component of the protocol, enabling efficient binary data serialization and deserialization. 
Its lightweight and extensible design makes it ideal for handling game-related data in real-time.

### Features

- Dynamic buffer management with automatic resizing.
- Supports custom types and user-defined objects via template specializations.
- Optimized for low-latency operations in real-time systems.
- Simple API for injecting, reading, and writing data.

### Example Usage

#### Writing to SmartBuffer
```cpp
SmartBuffer buffer;
buffer << int32_t(12345) << std::string("Hello, World!");
```

#### Reading from SmartBuffer
```cpp
int32_t number;
std::string text;
buffer >> number >> text;
// number = 12345, text = "Hello, World!"
```

### Methods

| Method                | Description                                                      |
|-----------------------|------------------------------------------------------------------|
| `inject(rawData, size)` | Injects raw binary data into the buffer.                       |
| `write(value)`         | Serializes a value into the buffer.                            |
| `read()`               | Deserializes and returns a value from the buffer.             |
| `reset()`              | Clears the buffer completely.                                 |
| `resetRead()`          | Resets the read pointer to the start of the buffer.           |
| `getSize()`            | Returns the size of the written data in the buffer.           |
| `getBuffer()`          | Returns a pointer to the buffer's internal data.              |

---
