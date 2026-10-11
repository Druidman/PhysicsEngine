



#ifndef BUFFER_H
#define BUFFER_H

#include <sys/types.h>

#include "../vendor/glad/glad.h"

class Buffer {
  private:
    uint binding;
    uint type;
    size_t buffer_size;
    size_t used_size;

    void release() noexcept {
      glDeleteBuffers(1, &this->binding);
    }
    void steal(Buffer& other) noexcept {
      this->binding = other.binding;
      this->type = other.type;
      this->buffer_size = other.buffer_size;
      this->used_size = other.used_size;

      other.binding = 0; // make destructor harmless
    }
    void expandBuffer(size_t by);
  protected: // cannot be used as standalone
    Buffer(uint type) : type(type) {
      // generate a buffer
      glGenBuffers(1, &this->binding); 
      
    }
    virtual ~Buffer(){release();}

    // DISALLOW COPY - we want only one object to contain key into gl buffer
    // copy constructor
    Buffer(const Buffer& other) = delete;
    // copy assignment
    Buffer& operator=(const Buffer& other) = delete;

    // HANDLE DESTRUCTOR SAFEGUARDS DURING MOVE
    // move constructor
    Buffer(Buffer&& other) noexcept {
      steal(other);
    }
    // move assignment
    Buffer& operator=(Buffer&& other) noexcept {
      if (this != &other){
        release();
        steal(other);
      };
      return *this;
    }

  public:
    inline uint id() const noexcept {
      return binding;
    }
    inline void bind() const noexcept {
      glBindBuffer(type, this->binding);
    }
    inline void unbind() const noexcept {
      glBindBuffer(type, 0);
    }
    inline void changeType(GLuint newType) noexcept {this->type=newType;};

    template <typename T, size_t N> 
    inline void setData(T (&data)[N]) noexcept {
      bind();
      std::cout << "SET DATA: " << sizeof(data) << std::endl;
      glBufferData(type, sizeof(data), data, GL_DYNAMIC_DRAW);

      buffer_size = sizeof(data);
      used_size = sizeof(data);
    }

    template <typename T, size_t N> 
    inline void appendData(T (&data)[N]) noexcept {
      // checks
      if (sizeof(data) + used_size > buffer_size){
        // need to grow
        this->expandBuffer(sizeof(data));
      };
      bind();
      glBufferSubData(type, used_size, sizeof(data), data);

      used_size += sizeof(data);
    }

    
    void allocate(size_t size);

    


};
#endif