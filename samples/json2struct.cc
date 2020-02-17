// clang++ json2struct.cc -std=c++14 -Wall -o ../bin/json2struct && ../bin/json2struct

#include "json2struct.h"

int main() {
  using nlohmann::json;
  Schema s = json::parse(source).get<Schema>();
  
  // std::vector<std::uint8_t> v_cbor = json::to_bson(s);
  
  
  // for(int i = 0; i < v_cbor.size(); i++) {
  //   printf("0x%02x ", v_cbor[i]);
  // }

  int length = sizeof(s);

  unsigned char *buffer = (unsigned char *)malloc(length);
  memcpy(buffer, (unsigned char *)&s, length);

  for(int i = 0; i < length; i++) {
    printf("0x%02X ", buffer[i]);
    if((i+1)%4==0) {
      printf("\n");
    }
  }
  printf("\n");

  std::cout << "length:" << length << std::endl;
  std::cout << s.id  << std::endl;
  std::cout << s.data.timestamp  << std::endl;
  std::cout << s.data.active  << std::endl;
  std::cout << s.data.name  << std::endl;
  std::cout << s.data.value  << std::endl;
  return 0;
}
