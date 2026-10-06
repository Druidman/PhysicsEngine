#include <string>
#include <sys/types.h>
#include "../vendor/glad/glad.h"

#ifndef SHADER_H
#define SHADER

class Shader {
  private:
    std::string filePath;
    std::string shaderContent;

    uint type;
    uint shader;
  public:
    Shader(std::string filePath, uint type):filePath(filePath), type(type){
      shader = glCreateShader(type);
      loadShader();
    }
    ~Shader(){release();}

    // rule of 5 ...

    // copy const, assign - disallowed
    Shader(const Shader& obj) = delete;
    Shader& operator=(Shader& other) = delete;

    // move const, assign - allowed under certain conditions
    Shader(Shader&& other) {
      // we dont have currently a different shader so just move
      move(other);
      
    }
    Shader& operator=(Shader&& other) {
      if (this != &other){
        // we have currently a different shader
        release();
      }
      move(other);

      return *this;
    }


    inline uint id() noexcept {return shader;}
  private:
    inline void release() noexcept {glDeleteShader(shader);};
    inline void move(Shader &other) noexcept {
      this->shader = other.shader;
      this->type = other.type;
      this->shaderContent = other.shaderContent;
      this->filePath = other.filePath;

      other.shader = 0; // destructor harmless
    }
    void readShader();

    void loadShader();
};
#endif