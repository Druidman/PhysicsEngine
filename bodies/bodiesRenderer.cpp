#include "./bodiesRenderer.h"


void BodiesRenderer::addBody(Body* body){
  
  // yea ik everything is hardcoded
  std::array<float, 12>& vertices = body->getVertices();
  std::array<uint, 6>& indices = body->getIndices();
  vbo.appendData(vertices);
  ebo.appendData(indices);

  DrawElementsIndirectCommand cmd = {
    6,
    1,
    this->bodies.size() * 6,
    0,
    0
  };
  ibo.appendData(cmd);

  ssbo.appendData(body->getPosition());

  this->bodies.push_back(body);
}