import ctypes
struct2json = ctypes.CDLL('./libs/struct2json.so')

struct2json.test.restype = ctypes.c_char_p
struct2json.parse.restype = ctypes.c_char_p

print(struct2json.test(b'\x41\x42\x43\x44\x45\x46\x47'))
# print(struct2json.test(b"abc"))
print(struct2json.parse(b'\x12\x27\x00\x00\x68\xAB\x4A\x5E\x00\x00\x00\x00\x01\x41\x42\x43\x44\x45\x46\x00\x0A\x00\x00\x00'))