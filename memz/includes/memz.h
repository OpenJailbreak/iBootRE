#define kImageMemzContainer 0x4D656D7A

typedef struct {
	unsigned int filesize;
	unsigned int fullSize;
	unsigned int dataSize;
	unsigned int type;
	unsigned int flags;
	void* data;
	unsigned int x18;
} MemzDescriptor;

//MemzDescriptor* memz_create(void* data, unsigned int size, unsigned int flags);
void* memz_create(void* data, int size, int flags);
