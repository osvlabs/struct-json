# STRUCT <> JSON Convertor

## Summary:

##### FOR converting data between BINARY STRUCT and JSON. It always be used for parse data between web application and socket protocols. Such as convert between MQTT and modbus(TCP or 485). #####

The core is C++, it included the library `json.hpp`

It can be running on server-end as a service, or edge compute.

Author: Ren Kun
Refer to: https://bot-man-jl.github.io/articles/2018/Cpp-Struct-Field-Reflection

## How to use:

### 1. Define "struct" in the C++ head file for JSON compiles

Please refer to the file `json2struct.h` and `struct2json.h`

```C++
#pragma pack(push,1)  

struct SampleStruct {
  long timestamp;
  bool active;
  char name[7];
  int value;
};

struct Schema {
  int id;
  SampleStruct data;
};
#pragma pack(pop)  

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
```



### 2. Compile to static library for calling

Use g++ with C++14 to compile the 2 source files to .so file

```sh
$ g++ -fPIC -shared json2struct.cc -std=c++14  -o libs/json2struct.so
$ g++ -fPIC -shared struct2json.cc -std=c++14  -o libs/struct2json.so
```

### 3. Load the libraries with any language

You can load those librarries in any languages such as Python, PHP, Java or any other language which support stardard "C" library. Below are a simple in python

```py
import ctypes
struct2json = ctypes.CDLL('./libs/struct2json.so')

struct2json.test.restype = ctypes.c_char_p
struct2json.parse.restype = ctypes.c_char_p

print(struct2json.test(b'\x41\x42\x43\x44\x45\x46\x47'))
# print(struct2json.test(b"abc"))
print(struct2json.parse(b'\x12\x27\x00\x00\x68\xAB\x4A\x5E\x00\x00\x00\x00\x01\x41\x42\x43\x44\x45\x46\x00\x0A\x00\x00\x00'))
```

There are 3 samples in folder `/python`

## Compile to execute bin file

Please refer to the files in folder `samples`

## !!!NOTES!!!

1. struct "Schema" will be used as the default root struct
2. ``#pragma pack(push,1)  `` is used for make sure the `struct` align with byte, it can be changed as the final usage. Also ``#pragma pack(pop) `` should be used after the `struct` is defined

## Running Result

```sh
$ python3 python/json2struct.py 
c++ output: Hi ABCDE
b'Hi ABCDE'
0x12 0x27 0x00 0x00 0x68 0xab 0x4a 0x5e 0x00 0x00 0x00 0x00 0x01 0x41 0x42 0x43 0x44 0x45 0x46 0x47 0x0a 0x00 0x00 0x00
```

```sh
$ python3 python/struct2json.py 
b'Hi ABCDEFG'
b'{"data":{"active":true,"name":"ABCDEF","timestamp":1581951848,"value":10},"id":10002}'
```

```sh
$ python3 python/mix.py 
0x12 0x27 0x00 0x00 0x68 0xab 0x4a 0x5e 0x00 0x00 0x00 0x00 0x01 0x41 0x42 0x43 0x44 0x45 0x46 0x47 0x0a 0x00 0x00 0x00
b'{"data":{"active":true,"name":"ABCDEFG\\n","timestamp":1581951848,"value":10},"id":10002}'
```

```sh
$ cd samples
$ clang++ json2struct.cc -std=c++14 -Wall -o ../bin/json2struct && ../bin/json2struct
0x37 0x00 0x00 0x00 
0x68 0xAB 0x4A 0x5E 
0x00 0x00 0x00 0x00 
0x01 0x41 0x42 0x43 
0x44 0x45 0x46 0x00 
0x0A 0x00 0x00 0x00 

length:24
55
1581951848
1
ABCDEF
10

$ clang++ struct2json.cc -std=c++14 -Wall -o ../bin/struct2json && ../bin/struct2json
{
  "data": {
    "active": true,
    "name": "ABCDEF",
    "timestamp": 1581951848,
    "value": 10
  },
  "id": 55
}
```





