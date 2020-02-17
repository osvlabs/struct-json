from ctypes import *

json2struct = CDLL('./libs/json2struct.so')
struct2json = CDLL('./libs/struct2json.so')

c_ubyte_p = POINTER(c_ubyte)
json2struct.set_debug(True)

# 返回的数据中是包含有空值的二进制字符串，所以不能用字符串相关的c_char_p，需要是ubyte对应的指针
json2struct.parse.restype = c_ubyte_p

# 测试 将json转换为基于原有结构体的二进制数据
json2struct.set_debug(False)
ret_size = c_int()
res = json2struct.parse(b"{\"data\":{\"active\":true,\"name\":\"ABCDEFGABCDEFGABCDEFGABCDEFGABCDEFGABCDEFGABCDEFG\",\"timestamp\":1581951848,\"value\":10},\"id\":10002}", pointer(ret_size))
res_bytes = string_at(res, ret_size.value)
print('0x' + ' 0x'.join("{:02x}".format(x) for x in res_bytes))

# 针对结果反转一次作为测试
struct2json.parse.restype = c_ubyte_p
struct2json.parse.restype = c_char_p
print(struct2json.parse(cast(res_bytes, c_char_p)))