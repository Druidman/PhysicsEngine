#pragma once
#include "../buffers/arrayBuffer.h"
#include "../buffers/elementBuffer.h"
#include "../buffers/drawIndirectBuffer.h"
#include "../buffers/shaderStorageBuffer.h"
#include "./body.h"


#include <vector>
// this one needs to handle:
// - BodyVerticiesBuffer
// - BodyTransformBuffer
class BodiesRenderer {
  private:

    ArrayBuffer vbo; // for object base vertices
    ElementBuffer ebo; // in what order to draw vertices
    DrawIndirectBuffer ibo; // gl_DrawId for each object (set of indices)
    ShaderStorageBuffer ssbo; // for object transform, rotation
    
    std::vector<Body*> bodies; // list of bodies
  public:
    BodiesRenderer(){} // nothin

    // should add a already exists check
    void addBody(Body* body);



};