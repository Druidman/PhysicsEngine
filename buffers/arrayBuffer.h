#include "buffer.h"

#ifndef ARRAY_BUFFER_H
#define ARRAY_BUFFER_H

template <typename T>
class ArrayBuffer : public Buffer<T,GL_ARRAY_BUFFER>  {
  public:
    using Buffer<T,GL_ARRAY_BUFFER>::Buffer;
};
#endif