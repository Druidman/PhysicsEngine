#include "buffer.h"

#ifndef DRAW_INDIRECT_BUFFER_H
#define DRAW_INDIRECT_BUFFER_H

class DrawIndirectBuffer : public Buffer {
  public:
    DrawIndirectBuffer() : Buffer(GL_DRAW_INDIRECT_BUFFER){};
};
#endif