



#ifndef BUFFER_H
#define BUFFER_H

#include <sys/types.h>
#include <array>
#include <iostream>
#include "../vendor/glad/glad.h"

class BufferBase {
  private:
    uint binding;
    uint type;
    size_t buffer_size = 0;
    size_t used_size = 0;

    void release() noexcept {
      glDeleteBuffers(1, &this->binding);
    }
    void steal(BufferBase& other) noexcept {
      this->binding = other.binding;
      this->type = other.type;
      this->buffer_size = other.buffer_size;
      this->used_size = other.used_size;

      other.binding = 0; // make destructor harmless
    }
    void expandBuffer(size_t by);
  protected: // cannot be used as standalone
    BufferBase(uint type) : type(type) {
      // generate a buffer
      glGenBuffers(1, &this->binding); 
      
    }
    ~BufferBase(){release();}

    // DISALLOW COPY - we want only one object to contain key into gl buffer
    // copy constructor
    BufferBase(const BufferBase& other) = delete;
    // copy assignment
    BufferBase& operator=(const BufferBase& other) = delete;

    // HANDLE DESTRUCTOR SAFEGUARDS DURING MOVE
    // move constructor
    BufferBase(BufferBase&& other) noexcept {
      steal(other);
    }
    // move assignment
    BufferBase& operator=(BufferBase&& other) noexcept {
      if (this != &other){
        release();
        steal(other);
      };
      return *this;
    }

  public:
    uint id() const noexcept {
      return binding;
    }
    void bind() const noexcept {
      glBindBuffer(type, this->binding);
    }
    void unbind() const noexcept {
      glBindBuffer(type, 0);
    }
    void changeType(GLuint newType) noexcept {this->type=newType;};

    void allocate(size_t size);
  protected:
    
    void setData(const void* data, size_t size);
    void appendData(const void* data, size_t size);


};
#endif