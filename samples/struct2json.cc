// clang++ struct2json.cc -std=c++14 -Wall -o ../bin/struct2json && ../bin/struct2json

#include "struct2json.h"

int main() {
  using nlohmann::json;
  Schema s;


  std::memset(&s, 0, sizeof(Schema));
  // printf("int: %lu, char: %lu, bool: %lu, float: %lu, short: %lu, long: %lu\n", 
    // sizeof(int), sizeof(char), sizeof(bool), sizeof(float),sizeof(short), sizeof(long));
  
  int length = sizeof(s);
  // printf("leng: %d\n", length);
  std::memcpy(&s, &source, length);
  // printf("id: %d\n", s.id);

  // std::cout << s.data.desc << std::endl;
  // printf("time: %ld\n", s.data.timestamp);
  // printf("active: %d\n", s.data.active);
  // printf("name: %s\n", s.data.name);
  // printf("value: %d\n", s.data.value);

  std::cout << json(s)
                   .dump(2)
            << std::endl;
  return 0;
}
