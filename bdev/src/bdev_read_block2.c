

int bdev_write_block(void* bdev, void*  source, void* destination, unsigned int size) {
    unsigned int blockSize = 0x80;
    blockSize += (blockSize << 1);
    if(strcmp(bdev->name, "nand_firmware")) {
        if(strcmp(bdev->name, "nand_llb")) {
            printf("ERROR: bad bdev: %s\n", bdev->name);
            return -1;
            
        } else {
            unsigned int startBlock = 0x0;
            unsigned int blockCount = 0x1;
            unsigned int firstOffset = startBlock * blockSize;
        }
        
    } else {
        unsigned int startBlock = 0x8;
        unsigned int blockCount = 0x8;
        unsigned int firstOffset = startBlock * blockSize;
    }
    


    
    unsigned int lastBlock = blockCount += startBlock;
    void* target = destination + firstOffset;
    unsigned int lastOffset = lastBlock * blockSize;
    if((lastOffset - 1) < (target + (size - 1)) {
        printf("ERROR: 0x%08X-0x%08X not within 0x%08X-0x%08X", target, (target + (size - 1)), firstOffset, lastOffset-1);
        return -1;
    }
    
    void* current =  source;
    cnt = 0;
    source = target;
    
    
    while(source < end) {
        destination = ( source * 0xAAAAAAAB) >> 1;

        if(blockCount != 0 && destination != 0x4b1) {
            blockCount = 0;
            while(blockCount < 0x8) {
                void* fil = FIL_GetCallbacks();
                int bytesRead = fil->hfmiReadBootPage(blockNumber, destination, 0x4ff35300);
                
                if(bytesRead != 0) {
                    blockNumber = 1;
                    0x4FF2A43C = blockCount
                    break;
                    
                } else {
                    blockNumber++;
                }

            }
            
            if(blockNumber == 0) {
                r11 = 0x4FF2A440;
                
            } else {
                break;
            }

        } else {
            r11 = 0x4FF2A440;
        }
        
        destination = source * 0xAAAAAAAB;
        memcpy(current, source, 0x200);
    }

    return cnt

}
