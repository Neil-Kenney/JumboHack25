/* vector.h 
 *
 * Richard Townsend   4/2/20
 *
 * Define the Vector class type and the type name that will be used to refer to
 * the Data in a Vector (using a typedef). Here, I've defined a Vector that
 * will hold Card pointers.
 *
 */
#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <string>
#include "movie.h"
using namespace std;

typedef Movie * Data;

class Vector {
public:
  Vector();
  ~Vector();
  int size();
  void push_back(Data value);
  void pop_back();
  Data at(int index);
  void insert(int index, Data value);
  void erase(int index);
  //Some additional methods!
  Data front();
  Data back();
  bool empty();
private:
  int capacity; 
  int vSize;    //We can't use the same name as the size() method above!
  Data *buffer; 
  void reserve_more();
};

#endif
