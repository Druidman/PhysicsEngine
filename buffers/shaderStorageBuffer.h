#include "buffer.h"

#ifndef SHADER_STORAGE_BUFFER_H
#define SHADER_STORAGE_BUFFER_H

class ShaderStorageBuffer : public Buffer {
  public:
    ShaderStorageBuffer() : Buffer(GL_SHADER_STORAGE_BUFFER){};
};
#endif