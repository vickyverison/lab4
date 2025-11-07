#include "MyStruct.h"
#include <string>
#include <mutex>

MyStruct::MyStruct()
{
  for (int i = 0; i < 3; i++)
    fields[i] = 0;
}

int MyStruct::read(int i)
{
  std::lock_guard<std::mutex> lock(mtx[i]);
  return fields[i];
}

void MyStruct::write(int i, int value)
{
  std::lock_guard<std::mutex> lock(mtx[i]);
  fields[i] = value;
}

MyStruct::operator std::string()
{
  std::string s;
  for (int i = 0; i < 3; i++)
  {
    std::lock_guard<std::mutex> lock(mtx[i]);
    s += std::to_string(fields[i]) + " ";
  }
  return s;
}
