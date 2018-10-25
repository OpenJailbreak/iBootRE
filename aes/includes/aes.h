typedef enum {
    kAesTypeGid 0x20000200,
    kAesTypeUid 0x20000201
} AesType;

typedef enum {
	kAesEncrypt = 0x10,
	kAesDecrypt = 0x11
} AesOption;

typedef enum {
	kAesMode128 = 0x00000000,
	kAesMode192 = 0x10000000,
	kAesMode256 = 0x20000000
} AesMode;

typedef enum {
	kAesSize128 = 0x20,
	kAesSize192 = 0x28,
	kAesSize256 = 0x30
} AesSize;

int aes_crypto_cmd(int option, void* input, void* output, int size, int mode, void* iv, void* key);
