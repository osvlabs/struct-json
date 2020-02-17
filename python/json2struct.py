import ctypes

json2struct = ctypes.CDLL('./libs/json2struct.so')

c_ubyte_p = ctypes.POINTER(ctypes.c_ubyte)

json2struct.set_debug(True)
json2struct.test.restype = ctypes.c_char_p
# json2struct.parse.argtypes = [ ctypes.c_char_p, ctypes.c_int ]

# 返回的数据中是包含有空值的二进制字符串，所以不能用字符串相关的c_char_p
json2struct.parse.restype = c_ubyte_p

print(json2struct.test(b'ABCDE'))

json2struct.set_debug(False)
ret_size = ctypes.c_int()
res = json2struct.parse(b"{\"data\":{\"active\":true,\"name\":\"ABCDEFGABCDEFGABCDEFGABCDEFGABCDEFGABCDEFGABCDEFG\",\"timestamp\":1581951848,\"value\":10},\"id\":10002}", ctypes.pointer(ret_size))

# print(len(res))
# print(ret_size.value)

res_bytes = ctypes.string_at(res, ret_size.value)

print('0x' + ' 0x'.join("{:02x}".format(x) for x in res_bytes))