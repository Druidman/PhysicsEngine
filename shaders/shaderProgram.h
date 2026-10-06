#include <string>
#include <sys/types.h>
#include "shader.h"
#include "../vendor/glad/glad.h"

#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM

class ShaderProgram {
  private:
    std::string vertexShaderFileName;
    std::string fragmentShaderFileName;

    uint program;
  public:
    ShaderProgram(std::string vertexShaderFileName, std::string fragmentShaderFileName) 
    : vertexShaderFileName(vertexShaderFileName), fragmentShaderFileName(fragmentShaderFileName) {
      program = glCreateProgram();
      loadProgram();
    };
    // Rule of 5 dawg
    
    // destructor 1/5
    ~ShaderProgram(){
      release();
    }
    // copy
    // constructor
    ShaderProgram(ShaderProgram& other) = delete;
    // assignment
    ShaderProgram& operator=(ShaderProgram& other) = delete;

    // move
    // constructor
    ShaderProgram(ShaderProgram&& other){
      // new object no need to clean up this one
      move(other);
    }
    // assignment
    ShaderProgram& operator=(ShaderProgram&& other){
      if (this != &other){
        release();
      }
      move(other);
      
      return *this;
    }
    


    inline uint id() noexcept {return program;}

    inline void use() noexcept {
      glUseProgram(program);  
    };

    inline uint getUniformLocation(std::string uniformName) {
      return glGetUniformLocation(program, uniformName.c_str());
    };
  private:
    inline void move(ShaderProgram& other){
      this->program = other.program;
      this->fragmentShaderFileName = other.fragmentShaderFileName;
      this->vertexShaderFileName = other.vertexShaderFileName;
    }
    inline void release() noexcept { glDeleteProgram(program); }
    void loadProgram();
};
#endif