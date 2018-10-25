typedef struct BlockDevice {
    struct BlockDevice* next;
    unsigned int unk4;
    unsigned int blockSize;
    unsigned int blockCount;
    unsigned int unk10;
    unsigned long long totalBytes;
    int(*blockdev_read_hook)(struct BlockDevice* bdev, void* address, unsigned int offset, unsigned int unknown, unsigned int size);
    int(*default_block_read)(struct BlockDevice* bdev, void* address, unsigned int startBlock, unsigned int blockCount);
    int(*blockdev_write_hook)(struct BlockDevice* bdev, void* address, unsigned int offset, unsigned int unknown, unsigned int size);
    int(*default_block_write)(struct BlockDevice* bdev, void* address, unsigned int startBlock, unsigned int blockCount);
    int(*default_block_erase)(void);
    char bdevName[16];
} BlockDevice;

int blockdev_read_hook(void* bdev, void* destination, unsigned int source, unsigned int offset, unsigned int size);
int default_block_read(void* bdev, void* address, unsigned int startBlock, unsigned int blockCount);
int blockdev_write_hook(void* bdev, void* address, unsigned int offset, unsigned int unknown, unsigned int size);
int default_block_write(void* bdev, void* address, unsigned int startBlock, unsigned int blockCount);
int default_block_erase(void);
