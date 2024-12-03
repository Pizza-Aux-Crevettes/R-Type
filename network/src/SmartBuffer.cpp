/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** SmartBuffer.cpp
*/

#include "SmartBuffer.hpp"

SmartBuffer::SmartBuffer(size_t initialCapacity): buffer(initialCapacity, 0), readOffset(0), writeOffset(0) {}

void SmartBuffer::ensureCapacity(size_t additionalSize) {
    if (writeOffset + additionalSize > buffer.size()) {
        buffer.resize(buffer.size() + additionalSize * 2);
    }
}

void SmartBuffer::writeInt8(int8_t value) {
    ensureCapacity(sizeof(int8_t));
    buffer[writeOffset++] = value;
}

void SmartBuffer::writeInt16(int16_t value) {
    ensureCapacity(sizeof(int16_t));
    std::memcpy(&buffer[writeOffset], &value, sizeof(int16_t));
    writeOffset += sizeof(int16_t);
}

void SmartBuffer::writeInt32(int32_t value) {
    ensureCapacity(sizeof(int32_t));
    std::memcpy(&buffer[writeOffset], &value, sizeof(int32_t));
    writeOffset += sizeof(int32_t);
}

void SmartBuffer::writeFloat(float value) {
    ensureCapacity(sizeof(float));
    std::memcpy(&buffer[writeOffset], &value, sizeof(float));
    writeOffset += sizeof(float);
}

void SmartBuffer::writeString(const std::string& value) {
    writeInt16(static_cast<int16_t>(value.size()));
    ensureCapacity(value.size());
    std::memcpy(&buffer[writeOffset], value.data(), value.size());
    writeOffset += value.size();
}

void SmartBuffer::writeBytes(const uint8_t* data, size_t size) {
    ensureCapacity(size);
    std::memcpy(&buffer[writeOffset], data, size);
    writeOffset += size;
}

int8_t SmartBuffer::readInt8() {
    if (readOffset + sizeof(int8_t) > writeOffset) {
        throw std::runtime_error("Buffer underflow");
    }
    return buffer[readOffset++];
}

int16_t SmartBuffer::readInt16() {
    if (readOffset + sizeof(int16_t) > writeOffset) {
        throw std::runtime_error("Buffer underflow");
    }
    int16_t value;
    std::memcpy(&value, &buffer[readOffset], sizeof(int16_t));
    readOffset += sizeof(int16_t);
    return value;
}

int32_t SmartBuffer::readInt32() {
    if (readOffset + sizeof(int32_t) > writeOffset) {
        throw std::runtime_error("Buffer underflow");
    }
    int32_t value;
    std::memcpy(&value, &buffer[readOffset], sizeof(int32_t));
    readOffset += sizeof(int32_t);
    return value;
}

float SmartBuffer::readFloat() {
    if (readOffset + sizeof(float) > writeOffset) {
        throw std::runtime_error("Buffer underflow");
    }
    float value;
    std::memcpy(&value, &buffer[readOffset], sizeof(float));
    readOffset += sizeof(float);
    return value;
}

std::string SmartBuffer::readString() {
    int16_t length = readInt16();
    if (readOffset + length > writeOffset) {
        throw std::runtime_error("Buffer underflow");
    }
    std::string value(reinterpret_cast<char*>(&buffer[readOffset]), length);
    readOffset += length;
    return value;
}

void SmartBuffer::readBytes(uint8_t* dest, size_t size) {
    if (readOffset + size > writeOffset) {
        throw std::runtime_error("Buffer underflow");
    }
    std::memcpy(dest, &buffer[readOffset], size);
    readOffset += size;
}

void SmartBuffer::reset() {
    readOffset = 0;
    writeOffset = 0;
}

void SmartBuffer::resetRead() {
    readOffset = 0;
}

size_t SmartBuffer::getSize() const {
    return writeOffset;
}

const uint8_t* SmartBuffer::getBuffer() const {
    return buffer.data();
}
