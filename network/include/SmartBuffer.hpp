#ifndef SMARTBUFFER_HPP
#define SMARTBUFFER_HPP

#include <vector>
#include <string>
#include <cstdint>
#include <stdexcept>
#include <cstring>
#include "Config.hpp"

class SmartBuffer {
public:
    explicit SmartBuffer(size_t initialCapacity = DEFAULT_SMART_BUFFER_ALLOC);
    ~SmartBuffer() = default;

    void writeInt8(int8_t value);
    void writeInt16(int16_t value);
    void writeInt32(int32_t value);
    void writeFloat(float value);
    void writeString(const std::string &value);
    void writeBytes(const uint8_t *data, size_t size);

    int8_t readInt8();
    int16_t readInt16();
    int32_t readInt32();
    float readFloat();
    std::string readString();
    void readBytes(uint8_t *dest, size_t size);

    void reset();
    void resetRead();

    size_t getSize() const;
    const uint8_t *getBuffer() const;

private:
    std::vector<uint8_t> buffer;
    size_t readOffset;
    size_t writeOffset;

    void ensureCapacity(size_t additionalSize);
};

#endif // SMARTBUFFER_HPP
