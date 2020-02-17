/***
 * 
 * !!!!!!IMPORTANT!!!!!!
 * "Schema" should be pre-defined and cannot be changed to other name
 * 
 * 
 **/
#include <iostream>
#include <string>
#include <vector>

#include "../includes/optional_json.h"

#pragma pack(push,1)  
// #pragma  pack (1)  

struct SampleStruct {
  long timestamp;
  bool active;
  char name[7];
  int value;
  // std::string desc;
  // std::unique_ptr<bool> optional;
};

struct Schema {
  int id;
  SampleStruct data;
  // std::vector<SampleStruct> vector_data;
};
#pragma pack(pop)  
// #pragma pack()  

void to_json(nlohmann::json& j, const SampleStruct& value) {
  j["timestamp"] = value.timestamp;
  j["active"] = value.active;
  j["name"] = std::string(value.name);
  j["value"] = value.value;
  // j["desc"] = value.desc;
  // j["optional"] = value.optional;
}

void to_json(nlohmann::json& j, const Schema& value) {
  j["id"] = value.id;
  j["data"] = value.data;
  // j["vector_data"] = value.vector_data;
}

const unsigned char source[24] = {
    0x37, 0x00, 0x00, 0x00,
    0x68, 0xAB, 0x4A, 0x5E, 
    0x00, 0x00, 0x00, 0x00,
    0x01, 0x41, 0x42, 0x43,
    0x44, 0x45, 0x46, 0x00,
    0x0A, 0x00, 0x00, 0x00
};

