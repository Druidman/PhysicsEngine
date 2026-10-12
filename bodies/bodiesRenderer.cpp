#include "./bodiesRenderer.h"


void BodiesRenderer::addBody(Body* body){
  vbo.appendData(body->getVertices());
  ebo.appendData(body->getIndices());
  // ibo.appendData()

  this->bodies.push_back(body);
}