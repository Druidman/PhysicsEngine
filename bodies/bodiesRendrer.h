#pragma once
#include "../buffers/arrayBuffer.h"
#include "../buffers/elementBuffer.h"
#include "../buffers/drawIndirectBuffer.h"
#include "../buffers/shaderStorageBuffer.h"
// this one needs to handle:
// - BodyVerticiesBuffer
// - BodyTransformBuffer
class BodiesRenderer {
  private:

    ArrayBuffer vbo; // for object base vertices
    ElementBuffer ebo; // in what order to draw vertices
    DrawIndirectBuffer ibo; // gl_DrawId for each object (set of indices)
    ShaderStorageBuffer ssbo; // for object transform, rotation
    
  public:
    BodiesRenderer(){
      // nothin
    }
};