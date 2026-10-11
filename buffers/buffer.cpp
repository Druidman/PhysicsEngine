#include "buffer.h"
#include <iostream>
#include "../vendor/glad/glad.h"

void Buffer::allocate(size_t size){
  
  if (size == 0){
    std::cout << "cannot allocate 0 bytes for a buffer" << std::endl;
    exit(0);
  }
  
  bind();
  glBufferData(type, size, nullptr, GL_DYNAMIC_DRAW);

  buffer_size = size;
  used_size = 0;
  unbind();
    
}

void Buffer::expandBuffer(size_t by){
  if (by == 0){
    return;
  }
  // 1. make new buffer
  Buffer newBuf(GL_COPY_WRITE_BUFFER);
  newBuf.allocate(buffer_size + by);

  // 2. copy data to it

  GLuint originalType = type;
  
  this->changeType(GL_COPY_READ_BUFFER);

  newBuf.bind();
  this->bind();

  glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, buffer_size);

  glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
  glBindBuffer(GL_COPY_READ_BUFFER,  0);

  newBuf.used_size = buffer_size;
  newBuf.changeType(originalType);
  
  // 3. delete old buffer
  *this = std::move(newBuf);

}