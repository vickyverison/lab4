#ifndef MYSTRUCT_H
#define MYSTRUCT_H

#include <string>
#include <mutex>
using namespace std;

struct MyStruct
{
  int fields[3];
  mutex mtx[3];

  MyStruct();
  int read(int i);
  void write(int i, int value);
  operator string();
};

#endif
