/**
 *  compile commands:
 *  $ g++ -fPIC -shared json2struct.cc -std=c++14  -o libs/json2struct.so
 * 
 **/
// #include <Python.h> 

#include "json2struct.h"
using namespace std;
using nlohmann::json;

const char *test(char* source) {
  // cout << source << endl;
  string str = "Hi ";
  str += source;
  if(_DEBUG_) {
    cout << "c++ output: " << str << endl;
  }
  return str.c_str();  
}
void set_debug(bool debug) {
  _DEBUG_ = debug;
}

const char *parse(char* source, int &ret_size) {
  
  Schema s = json::parse(source).get<Schema>();
  
  int length = sizeof(s);

  // 结构体中包含有空值，所以必须用unsigned char来复制，否则会出错
  unsigned char *buffer = (unsigned char *)malloc(length);
  memcpy(buffer, (unsigned char *)&s, length);
  
  if(_DEBUG_) {
    printf("length: %d\nC++ output: \n", length);
    printf("id(%lu): %d\n", sizeof(s.id), s.id);

    for(int i = 0; i < length; i++) {
      printf("0x%02X ", buffer[i]);
      if((i+1)%4==0) {
        printf("\n");
      }
    }
    printf("\n");
  }

  ret_size = length;
  return (char *)buffer;
}
