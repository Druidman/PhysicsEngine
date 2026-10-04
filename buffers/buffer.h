



#ifndef BUFFER_H
#define BUFFER_H

#include <sys/types.h>
#include "../vendor/glad/glad.h"

class Buffer {
  private:
    uint binding;
    uint type;

    void release() noexcept {
      glDeleteBuffers(1, &this->binding);
    }
    void move(Buffer& other) noexcept {
      this->binding = other.binding;
      this->type = other.type;

      other.binding = 0; // make destructor harmless
    }
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
      move(other);
    }
    // move assignment
    Buffer& operator=(Buffer&& other) noexcept {
      if (this != &other){
        release();
        move(other);
      };
      return *this;
    }

  public:
    inline uint get() const noexcept {
      return binding;
    }
    inline void bind() const noexcept {
      glBindBuffer(type, this->binding);
    }
    inline void unbind() const noexcept {
      glBindBuffer(type, 0);
    }
    template <typename T, size_t N> 
    inline void setData(T (&data)[N]) noexcept {
      bind();
      std::cout << "SET DATA: " << sizeof(data) << std::endl;
      glBufferData(type, sizeof(data), data, GL_STATIC_DRAW);
      unbind();
    }
};
#endif