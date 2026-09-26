#include <sys/types.h>
#include "vendor/glad/glad.h"

class Buffer {
  private:
    uint binding;
    uint type;
  protected: // cannot be used as standalone
    Buffer(uint type){
      this->type = type;
      // generate a buffer
      glGenBuffers(1, &this->binding); 
    }
  public:
    uint getBinding(){
      return binding;
    };
    void bind(){
      glBindBuffer(type, this->binding);
    }
    void unbind(){
      glBindBuffer(type, 0);
    }
};