/***
 * 
 * !!!!!!IMPORTANT!!!!!!
 * "Schema" should be pre-defined and cannot be changed to other name
 * 
 * 
 **/

#ifndef DATACONVERTOR_H_
#define DATACONVERTOR_H_

#include <iostream>
#include <string>
#include <vector>

#include "includes/optional_json.h"

#pragma pack(push,1)  
// #pragma  pack (1)  

struct SampleStruct {
  long timestamp;
  bool active;
  char name[7];
  int value;
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
}

void to_json(nlohmann::json& j, const Schema& value) {
  j["id"] = value.id;
  j["data"] = value.data;
}

extern "C" {
  const char* test(char *source);
  const char* parse(char *source);
}

#endif //