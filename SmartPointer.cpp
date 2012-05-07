///////////////////////////////////////////////////////////////////////////////
//                       Copyright (c) 2011 - 2012 by                        //
//                                Simon Pratt                                //
//                           (All rights reserved)                           //
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// FILE:    SmartPointer.cpp                                                 //
//                                                                           //
// MODULE:  Smart Pointer                                                    //
//                                                                           //
// NOTES:   None.                                                            //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#ifndef SMARTPOINTER_CPP
#define SMARTPOINTER_CPP

#include "SmartPointer.hpp"

using namespace smart_ptr;

template <class T>
SmartPointer<T>::SmartPointer(T* a)
  : _address(a), _references(new int(0))
{
  incReferences();
}

template <class T>
SmartPointer<T>::SmartPointer(SmartPointer<T>& toCopy)
  : _address(toCopy._address), _references(toCopy._references)
{
  incReferences();
}

template <class T>
const SmartPointer<T>& SmartPointer<T>::operator=(SmartPointer<T>& toCopy) {
  decReferences();
  _address = toCopy._address;
  _references = toCopy._references;
  incReferences();
  return *this;
}

template <class T>
SmartPointer<T>::~SmartPointer() {
  // one less reference
  decReferences();
}

template <class T>
void SmartPointer<T>::incReferences() {
  ++(*_references);
}

template <class T>
void SmartPointer<T>::decReferences() {
  --(*_references);

  // no more references
  if((*_references) < 1) {
    delete _references;
    delete _address;
  }
}

template <class T>
T& SmartPointer<T>::operator*() {
  return *_address;
}

#endif