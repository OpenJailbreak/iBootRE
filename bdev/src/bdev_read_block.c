int bdev_write_block(void* bdev, void*  source, void* destination, unsigned int size) {
    //PUSH    {R4-R7,LR}
    //ADD     R7, SP, #0xC
    //PUSH.W  {size_R8,dest_R10,R11}
    //SUB     SP, SP, #0x10
    
    //MOV     size_R8, R3          ; size
    //LDR     R3, =unk_4FF2A420 // 0x80
    unsigned int blockSize = 0x80;
    //ADD.W   R4, R0, #0x30   ; bdev.name
    //MOV     dest_R10, R1         ;  source
    //LDR     R3, [R3]
    //MOV     source_R6, R2          ; destination
    //MOV     R0, R4          ; s1
    //LSLS    R2, R3, #1
    //LDR     R1, =aNand_firmware ; "nand_firmware"
    //ADD.W   blockSizeR5, R2, R3
    blockSize += (blockSize << 1);
    //BL      strcmp
    //CBNZ    R0, loc_4FF0EC3C
    if(strcmp(bdev->name, "nand_firmware")) {
        //MOV     R0, R4          ; s1
        //LDR     R1, =aNand_llb  ; "nand_llb"
        //BL      strcmp
        //CBNZ    R0, loc_4FF0EC52
        if(strcmp(bdev->name, "nand_llb")) {
            //MOV     R1, R4          ; param_R1
            //LDR     R0, =aErrorBadBdevS ; "ERROR: bad bdev: %s\n"
            //BL      printf
            //B       loc_4FF0EC8C
            printf("ERROR: bad bdev: %s\n", bdev->name);
            return -1;
            
        } else {
            //LDR     R3, =startBlock  // 0x0
            unsigned int startBlock = 0x0;
            //LDR     R2, =blockCount  // 0x1
            unsigned int blockCount = 0x1;
            //LDR     R1, [R3]
            //MUL.W   R3, R1, blockSizeR5
            unsigned int firstOffset = startBlock * blockSize;
            //B       loc_4FF0EC5C
        }
        
    } else {
        //LDR     R3, =startBlock // 0x8
        unsigned int startBlock = 0x8;
        //LDR     R2, =blockCount // 0x8
        unsigned int blockCount = 0x8;
        //LDR     R1, [R3]
        //MUL.W   R3, R1, blockSizeR5
        unsigned int firstOffset = startBlock * blockSize;
        //B       loc_4FF0EC5C
    }
    
    //LDR     R2, [R2]
    //ADD     R2, R1
    unsigned int lastBlock = blockCount += startBlock;
    //ADD.W   R1, R3, source_R6      ; param_R1
    void* target = destination + firstOffset;
    //MUL.W   R2, blockSizeR5, R2
    unsigned int lastOffset = lastBlock * blockSize;
    //SUBS    R0, R2, #1
    //ADD.W   R2, size_R8, #0xFFFFFFFF
    //ADDS    R2, R2, R1
    //CMP     R0, R2
    //STR     R2, [SP,#0x30+end]
    //BCC     loc_4FF0EC82
    if((lastOffset - 1) < (target + (size - 1)) {
        //STR     R0, [SP,#0x30+var_30]
        //LDR     R2, [SP,#0x30+var_2c] ; param_R2
        //LDR     R0, =aError0x08x0x08 ; "ERROR: 0x%08X-0x%08X not within 0x%08X-"...
        //BL      printf
        printf("ERROR: 0x%08X-0x%08X not within 0x%08X-0x%08X", target, (target + (size - 1)), firstOffset, lastOffset-1);
        return -1;
    }
    
    //MOVS    R2, #0
    //STR.W   dest_R10, [SP,#0x30+current]
    void* current =  source;
    //STR     R2, [SP,#0x30+cnt]
    cnt = 0;
    //MOV     dest_R10, R1
     source = target;
    //B       loc_4FF0ED22

    //LDR     R3, [SP,#0x30+end]
    //CMP     dest_R10, R3
    //BLS     loc_4FF0EC92
    
    
    while( source < end) {
        //LDR     R3, =0xAAAAAAAB
        //UMULL.W R2, R1, R3, R10
        //LDR     R2, =blockCount
        //LDR     R3, [R2]
        //LSRS    R6, R1, #1
        destination = ( source * 0xAAAAAAAB) >> 1;
        //CBZ     R3, loc_4FF0ECA8
        
        //LDR     R3, =unk_4FF2A43C // 0x4b1
        //LDR     R3, [R3]
        //CMP     R6, R3
        //BEQ     loc_4FF0ECE8

        if(blockCount != 0 && destination != 0x4b1) {
            //LDR     R3, =blockCount
            //LDR.W   R8, =startBlock // 0x8
            //MOVS    R5, #0
            //STR     R5, [R3]
            blockCount = 0;
            //B       loc_4FF0ECDA
            //LDR.W   R3, [R8]
            //CMP     R5, R3
            //BCC     loc_4FF0ECB4

            while(blockCount < 0x8) {
                //BL      FIL_GetCallbacks
                void* fil = FIL_GetCallbacks();
                //LDR.W   R11, =unk_4FF2A440 ; 0x4ff35300 
                //UXTH    R3, R5          ; (block)
                //MOV     R1, R6          ; destination
                //LDR.W   R2, [R11]       ; DImg3D
                //LDR     R4, [R0,#0x18]  ; hfmiReadBootPage(unsigned int block, void* destination, void* img3);
                //MOV     R0, R3          ; block
                //BLX     R4
                int bytesRead = fil->hfmiReadBootPage(blockNumber, destination, 0x4ff35300);
                //CBNZ    R0, loc_4FF0ECD8
                
                if(bytesRead != 0) {
                    //LDR     R2, =blockCount
                    //MOVS    R3, #1
                    //STR     R3, [R2]
                    blockNumber = 1;
                    //LDR     R3, =unk_4FF2A43C ;0x4b1
                    //STR     R6, [R3]
                    0x4FF2A43C = blockCount
                    //B       loc_4FF0ECEC
                    break;
                    
                } else {
                    //ADDS    R5, #1
                    blockNumber++;
                }

            }
            
            //LDR     R2, =blockCount
            //LDR     R3, [R2]
            //CBZ     R3, loc_4FF0ED28
            if(r3 == 0) {
                //LDR.W   R11, =unk_4FF2A440 ; 0x4ff35300
                
            } else {
                break;
            }

        } else {
            //LDR.W   R11, =unk_4FF2A440 ; 0x4ff35300
        }
        
        //LDR     R1, =0xAAAAAAAB
        //LDR     R0, [SP,#0x30+current] ; dest
        //UMULL.W R2, R3, R1, R10
        destination = source * 0xAAAAAAAB
        //LDR.W   R2, [R11]
        //BIC.W   R1, R3, #1
        //ADD.W   R1, R1, R3,LSR#1
        //RSB.W   R1, R1, R10
        //ADD.W   R10, R10, #1
        //LSLS    R1, R1, #9
        //ADDS    R1, R1, R2      ; source
        //MOV.W   R2, #0x200      ; n
        //BLX     memcpy
        memcpy(current, source, 0x200);
        //LDR     R3, [SP,#0x30+cnt]
        //LDR     R2, [SP,#0x30+current]
        //ADDS    R3, #1
        //ADD.W   R2, R2, #0x200
        //STR     R3, [SP,#0x30+cnt]
        //STR     R2, [SP,#0x30+current]
    }

    //LDR     R0, [SP,#0x30+cnt]

}
