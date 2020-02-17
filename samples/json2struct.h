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
  // std::string name;
  int value;
  // std::unique_ptr<bool> optional;
};

struct Schema {
  int id;
  SampleStruct data;
  // std::vector<SampleStruct> vector_data;
};
#pragma pack(pop)  
// #pragma pack()  


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

const char *source = "{\"data\":{\"active\":true,\"name\":\"ABCDEF\",\"timestamp\":1581951848,\"value\":10},\"id\":55}";

