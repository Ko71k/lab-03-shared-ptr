// Copyright 2022 Ko71k <rassmagin.rrr@gmail.com>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include <iostream>
#include <atomic>
template <typename T>
class SharedPtr {
  T*Sptr = nullptr;
  std::atomic_uint* counter;
 public:
  SharedPtr(){
    Sptr = nullptr;
    counter = nullptr;
  }
  SharedPtr(T* ptr){
    Sptr = ptr;
    counter = new std::atomic_uint[1];
  }
  SharedPtr(const SharedPtr& r){
    *this = r;
  }
  SharedPtr(SharedPtr&& r){
    *this = std::move(r);
  }
  ~SharedPtr(){
    if(counter == nullptr) {return;}
    else{
      *(counter) = *(counter) - 1;
      if(*(counter) == 0){
        delete Sptr;
        delete counter;
      }
      else if(*(counter) > 0){
        Sptr = nullptr;
        counter = nullptr;
      }
    }
  }
  auto operator=(const SharedPtr& r){
    if(*this == r){
      return *this;
    }
    this->~SharedPtr();
    Sptr = r.Sptr;
    counter = r.counter;
    counter++;
    return *this;
  }
  auto operator=(SharedPtr&& r){
    if(*this == r){
      return *this;
    }
    this->~SharedPtr();
    Sptr = r.Sptr;
    counter = r.counter;
    r.Sptr = nullptr;
    r.counter = nullptr;
    *(counter) = *(counter) + 1;
    return *this;
  }