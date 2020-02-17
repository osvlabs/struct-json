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

struct SampleStruct {
  long timestamp;
  bool active;
  char name[7];
  // std::string name;
  int value;
};

struct Schema {
  int id;
  SampleStruct data;
  // std::vector<SampleStruct> vector_data;
};
#pragma pack(pop)  

void from_json(const nlohmann::json& j, SampleStruct& value) {
  j.at("timestamp").get_to(value.timestamp);
  j.at("active").get_to(value.active);
  std::string name = j["name"];
  memcpy(value.name, name.c_str(), sizeof(value.name));
  // j.at("name").get_to(value.name);
  j.at("value").get_to(value.value);
}

void from_json(const nlohmann::json& j, Schema& value) {
  j.at("id").get_to(value.id);
  j.at("data").get_to(value.data);
}

static bool _DEBUG_ = false;

extern "C" {
  const char* test(char *source);
  const char* parse(char *source, int &ret_size);
  void set_debug(bool debug);
}

#endif //