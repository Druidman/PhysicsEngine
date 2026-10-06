#include "shader.h"
#include <fstream>
#include <iostream>

void Shader::readShader(){

  std::ifstream file(filePath);

  if (!file.is_open()){
    std::cout << "File does not exist! " << filePath << '\n';
    std::exit(1);
  }


  std::string line;
  while (std::getline(file, line)){
    shaderContent +=  '\n' + line;
  }
  std::cout << shaderContent << '\n';
};

void Shader::loadShader(){
  readShader();
  
  const char* shaderSourceCstr = shaderContent.c_str();

  glShaderSource(shader, 1, &shaderSourceCstr, NULL);
  glCompileShader(shader);  
  // compilation done, check logs

  int  success;
  char infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if(!success)
  {
      glGetShaderInfoLog(shader, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::" << filePath << " ::COMPILATION_FAILED\n" << infoLog << std::endl;
      std::exit(1);
  }

  // all good
}