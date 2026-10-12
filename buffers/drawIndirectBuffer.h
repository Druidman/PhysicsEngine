#include "buffer.h"

#ifndef DRAW_INDIRECT_BUFFER_H
#define DRAW_INDIRECT_BUFFER_H

typedef  struct {
  uint  count;
  uint  instanceCount;
  uint  firstIndex;
  int  baseVertex;
  uint  baseInstance;
} DrawElementsIndirectCommand;

class DrawIndirectBuffer : public Buffer<DrawElementsIndirectCommand,GL_DRAW_INDIRECT_BUFFER>  {
  public:
    using Buffer<DrawElementsIndirectCommand,GL_DRAW_INDIRECT_BUFFER>::Buffer;
};
#endif