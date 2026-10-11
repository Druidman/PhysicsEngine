#include "body.h"



std::array<float, 12> Body::generateBaseVertices(){
  glm::vec2 topLeft = glm::vec2(-width/2.0f, height/2.0f);
  glm::vec2 topRight = glm::vec2(width/2.0f, height/2.0f);
  glm::vec2 bottomLeft = glm::vec2(-width/2.0f, -height/2.0f);
  glm::vec2 bottomRight = glm::vec2(width/2.0f, -height/2.0f);
  return {
    // no color info no nothin
    topLeft[0], topLeft[1], 0.0f, //0
    topRight[0], topRight[1], 0.0f, //1
    bottomLeft[0], bottomLeft[1], 0.0f, //2
    bottomRight[0], bottomRight[1], 0.0f //3
  };
};