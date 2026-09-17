#include "vendor/glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>

#define uint unsigned int

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

std::string readShader(std::string filePath) {

  std::ifstream file(filePath);

  if (!file.is_open()){
    std::cout << "File does not exist! " << filePath << '\n';
    std::exit(1);
  }

  std::string shaderContent;
  std::string line;
  while (std::getline(file, line)){
    shaderContent +=  '\n' + line;
  }
  std::cout << shaderContent << '\n';
  return shaderContent;
};

uint loadShader(std::string filePath, GLenum type){
  std::string shaderSource = readShader(filePath);
  const char* shaderSourceCstr = shaderSource.c_str();

  uint shader;
  shader = glCreateShader(type);
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
  return shader;
}


uint loadShaderProgram(){
  uint shaderProgram;
  shaderProgram = glCreateProgram();
  uint vertexShader = loadShader("shaders/vertex.glsl", GL_VERTEX_SHADER);
  uint fragmentShader = loadShader("shaders/fragment.glsl", GL_FRAGMENT_SHADER);

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  int  success;
  char infoLog[512];
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if(!success) {
      glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER_PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
      std::exit(1);
  }
  // all good, cleanup


  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);  
  return shaderProgram;
}
int main(){
  
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  
  GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGL(glfwGetProcAddress))
  {
      std::cout << "Failed to initialize GLAD" << std::endl;
      return -1;
  }    


  glViewport(0, 0, 800, 600);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

  float vertices[] = {
      -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.0f,  0.5f, 0.0f
  };  

  

  
  uint shaderProgram = loadShaderProgram();
  glUseProgram(shaderProgram);

  unsigned int VBO;
  glGenBuffers(1, &VBO);  
  glBindBuffer(GL_ARRAY_BUFFER, VBO);  
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  unsigned int VAO;
  glGenVertexArrays(1, &VAO); 
  glBindVertexArray(VAO);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0); 

  
  while(!glfwWindowShouldClose(window))
  {
    processInput(window);
    glfwSwapBuffers(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwPollEvents();    
  }
  glfwTerminate();
  std::cout << "Window closed...\n";
  
  return 0;
}
