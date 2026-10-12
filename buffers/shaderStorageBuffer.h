#include "buffer.h"

#ifndef SHADER_STORAGE_BUFFER_H
#define SHADER_STORAGE_BUFFER_H
template <typename T>
class ShaderStorageBuffer : public Buffer<T, GL_SHADER_STORAGE_BUFFER>  {
  public:
    using Buffer::Buffer;

};
#endif