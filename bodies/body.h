
#pragma once
#include "vendor/glm/glm.hpp"
#include "vendor/glm/vec2.hpp"

class Body{
  // currently only rectangular bodies

  private:
    float width, height;

    // used to move object around
    glm::vec2 position = glm::vec2(0.0f, 0.0f);
    float rotationRad = 0.0f;

    // vertices
    // 4 vertices
    std::array<float, 12> vertices;
    std::array<uint, 6> indices = {
      0,3,2, // first triangle
      0,1,3  // second triangle
    };
    
    
    
  public:
    Body(glm::vec2 position, float width, float height) : position(position), height(height), width(width) {
      this->vertices = generateBaseVertices();
    }

    inline std::array<float, 12> getVertices(){
      return this->vertices;
    }

    inline std::array<uint, 6> getIndices(){
      return this->indices;
    }

    inline glm::vec2 getPosition(){
      return this->position;
    }


    // transform

    inline void moveBy(glm::vec2 delta){
      this->position += delta;
    }
    inline void moveTo(glm::vec2 position){
      this->position = position;
    }

    inline void rotateBy(float angleRad){
      rotationRad += angleRad;
    }
    inline void rotateTo(float angleRad){
      rotationRad = angleRad;
    }
  
    private:
    std::array<float, 12> generateBaseVertices();
    
};