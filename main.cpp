#include "vendor/glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sys/types.h>


#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "vendor/glm/gtc/type_ptr.hpp"

#include "buffers/arrayBuffer.h"
#include "buffers/elementBuffer.h"
#include "shaders/shaderProgram.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  
  glViewport(0, 0, width, height );
}  

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
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


  glViewport(0, 0, 1920, 1080);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  
  // scope because of destructors
  {
    float vertices[] = {
        // first triangle
        0.5f,  0.5f, 0.0f,    1.0f, 0.5f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,    1.0f, 0.5f, 1.0f, // bottom right
      -0.5f,  0.5f, 0.0f,    1.0f, 0.5f, 1.0f, // top left 
      -0.5f, -0.5f, 0.0f,    1.0f, 0.5f, 1.0f, // bottom left

    }; 

    uint indices[] = {
      2, 0, 1, // first triangle
      2, 1, 3  // second triangle
    };

    uint indices2[] = {
      2, 0, 1, // first triangle
    };


    // SHADERS
    ShaderProgram shaderProgram("shaders/vertex.glsl", "shaders/fragment.glsl");
    

    // VERTICIES DATA
    ArrayBuffer VBO;
    VBO.setData(vertices);


    // FIRST ELEMENT BUFFER (RECTANGLE)
    ElementBuffer EBO;
    EBO.setData(indices);


    // SECOND ELEMENT BUFFER (TRIANGLE)
    ElementBuffer EBO2;
    EBO2.setData(indices2);

    // VAO FOR RECTANGLE
    unsigned int VAO;
    glGenVertexArrays(1, &VAO); 
    glBindVertexArray(VAO);

    VBO.bind();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); 
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1); 
    VBO.unbind();
    

    glBindVertexArray(0); // unbind

    // VAO FOR TRIANGLE
    unsigned int VAO2;
    glGenVertexArrays(1, &VAO2); 
    glBindVertexArray(VAO2);

    VBO.bind();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); 
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1); 
    VBO.unbind();

    glBindVertexArray(0); // unbind


    // map ebos to vaos
    glBindVertexArray(VAO);
    EBO.bind();
    glBindVertexArray(0); // unbind

    glBindVertexArray(VAO2);
    EBO2.bind();
    glBindVertexArray(0); // unbind


    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);



    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    // trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));  

    
    unsigned int transformLoc = shaderProgram.getUniformLocation("transform");

    double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();
    double delta = lastTime - currentTime;
    while(!glfwWindowShouldClose(window))
    {
      currentTime = glfwGetTime();
      delta = lastTime - currentTime;
      lastTime = currentTime;


      
      // handle object state updates
      // rotate 90 deg per second
      trans = glm::rotate(trans, glm::radians(90.0f * (float)delta), glm::vec3(0.0, 0.0, 1.0));


      // rendering
      processInput(window);
      glfwSwapBuffers(window);

      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      // drawing using first vao
      // shaders
      shaderProgram.use();
      glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

      // vao1
      glBindVertexArray(VAO);
      glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(uint), GL_UNSIGNED_INT, 0);

      // vao2
      // glBindVertexArray(VAO2);
      

      // glDrawElements(GL_TRIANGLES, sizeof(indices2) / sizeof(uint), GL_UNSIGNED_INT, 0);

      glfwPollEvents();    
    }
  }
  glfwTerminate();
  std::cout << "Window closed...\n";
  
  return 0;
}
