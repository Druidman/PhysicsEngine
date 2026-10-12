#pragma once
#include "bufferBase.h"
#include <span>
template <typename T, GLenum target>
class Buffer : public BufferBase {
  public:
    Buffer() : BufferBase(target){};

    void setData(std::span<T> data){
      return BufferBase::setData(data.data(), data.size_bytes());
    };
    void appendData(std::span<T> data){
      return BufferBase::appendData(data.data(), data.size_bytes());
    };
};