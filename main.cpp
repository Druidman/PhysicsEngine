#include "vendor/glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sys/types.h>


#include "vendor/glm/glm.hpp"
#include "vendor/glm/vec2.hpp"
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
  const int AMOUNT_OF_VERTICES = 8;
  {
    float vertices[AMOUNT_OF_VERTICES * 6] = {
        

        0.5f,  0.5f, 0.5f,    1.0f, 0.5f, 1.0f, // top right front
        0.5f, -0.5f, 0.5f,    1.0f, 0.5f, 1.0f, // bottom right front
      -0.5f,  0.5f, 0.5f,    1.0f, 0.5f, 1.0f, // top left  front
      -0.5f, -0.5f, 0.5f,    1.0f, 0.5f, 1.0f, // bottom left front

       0.5f,  0.5f, -0.5f,    1.0f, 0.5f, 1.0f, // top right back
        0.5f, -0.5f, -0.5f,    1.0f, 0.5f, 1.0f, // bottom right back
      -0.5f,  0.5f, -0.5f,    1.0f, 0.5f, 1.0f, // top left  back
      -0.5f, -0.5f, -0.5f,    1.0f, 0.5f, 1.0f, // bottom left back

    }; 

    uint indices[] = {
      // front
      2, 0, 1, // first triangle
      2, 1, 3,  // second triangle

      // back
      6, 4, 5, // first triangle
      6, 5, 7,  // second triangle,
      // top
      2, 6, 4,
      2, 4, 0,

      // bottom
      3, 7, 5,
      3, 5, 1,
      
      // right
      0, 4, 5,
      0, 5, 1,

      // left
      2, 6, 7,
      2, 7, 3
    };

    uint indices2[] = {
      2, 0, 1, // first triangle
    };


    // SHADERS
    ShaderProgram shaderProgram("shaders/vertex.glsl", "shaders/fragment.glsl");
    

    // VERTICIES DATA
    ArrayBuffer<float> VBO;
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


    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);



    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));  

    
    unsigned int transformLoc = shaderProgram.getUniformLocation("transform");

    double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();
    double delta = lastTime - currentTime;
    while(!glfwWindowShouldClose(window))
    {
      currentTime = glfwGetTime();
      delta = currentTime - lastTime;
      lastTime = currentTime;


      // rendering
      processInput(window);
  
      trans = glm::rotate(trans, glm::radians((float)delta * 90.0f), glm::vec3(1,0.5,1));
      

      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      // drawing using first vao
      // shaders
      shaderProgram.use();
      glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

      // vao1
      glBindVertexArray(VAO);
      EBO.bind();
      glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(uint), GL_UNSIGNED_INT, 0);

      // vao2
      // glBindVertexArray(VAO2);
      

      // glDrawElements(GL_TRIANGLES, sizeof(indices2) / sizeof(uint), GL_UNSIGNED_INT, 0);

      

      glfwSwapBuffers(window);
      glfwPollEvents();    
    }
  }
  glfwTerminate();
  std::cout << "Window closed...\n";
  
  return 0;
}
