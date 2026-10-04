#include "buffer.h"

#ifndef ARRAY_BUFFER_H
#define ARRAY_BUFFER_H

class ArrayBuffer : public Buffer {
  public:
    ArrayBuffer() : Buffer(GL_ARRAY_BUFFER){};
};
#endif