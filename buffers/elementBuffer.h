#include "buffer.h"

#ifndef ELEMENT_BUFFER_H
#define ELEMENT_BUFFER_H

class ElementBuffer : public Buffer {
  public:
    ElementBuffer() : Buffer(GL_ELEMENT_ARRAY_BUFFER){}
};
#endif