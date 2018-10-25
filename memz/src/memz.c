#define kMemzImageContainer 0x4D656D7A

typedef struct MemzDescriptor {
	unsigned int fileSize;
	unsigned int imageSize;
	unsigned int dataSize;
	unsigned int container;
	unsigned int flags;
	unsigned char* address;
	unsigned int unk18;
};

MemzDescriptor* memz_create(unsigned char* address, unsigned int size, unsigned int flags) {
    MemzDescriptor* memz = (MemzDescriptor*) malloc(sizeof(MemzDescriptor));
	if(memz != NULL) {
		memz->fileSize = size;
		memz->imageSize = size;
		memz->type = kMemzImageContainer;
		memz->flags = flags;
		memz->address = address;
    }
    return memz;
}

