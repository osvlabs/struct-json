/**
 *  compile commands:
 *  $ g++ -fPIC -shared struct2json.cc -std=c++14  -o libs/struct2json.so
 * 
 **/
// #include <Python.h> 



#include "struct2json.h"
using namespace std;
using nlohmann::json;

const char *test(char* source) {
  // cout << source << endl;
  string str = "Hi ";
  str += source;
  // cout << "c++ output: " << str << endl;
  return str.c_str();  
}

const char *parse(char* source) {
  Schema s;
  
  int length = sizeof(s);
  memset(&s, 0, length);
  memcpy(&s, source, length);

  string str = json(s).dump();

  // cout << "c++ output: " << str << endl;
  return str.c_str();
}
