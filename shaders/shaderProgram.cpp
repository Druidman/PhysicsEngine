#include "shaderProgram.h"
#include <iostream>

void ShaderProgram::loadProgram(){
  Shader vertexShader(vertexShaderFileName, GL_VERTEX_SHADER);
  Shader fragmentShader(fragmentShaderFileName, GL_FRAGMENT_SHADER);

  glAttachShader(program, vertexShader.id());
  glAttachShader(program, fragmentShader.id());
  glLinkProgram(program);

  int  success;
  char infoLog[512];
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if(!success) {
      glGetProgramInfoLog(program, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER_PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
      std::exit(1);
  }
  // all good, cleanup will be handled automatically via shader destructors 
  
}