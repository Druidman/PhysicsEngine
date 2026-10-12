#include "buffer.h"

#ifndef ELEMENT_BUFFER_H
#define ELEMENT_BUFFER_H

class ElementBuffer : public Buffer<uint,GL_ELEMENT_ARRAY_BUFFER> {
  public:
    using Buffer::Buffer;

};
#endif