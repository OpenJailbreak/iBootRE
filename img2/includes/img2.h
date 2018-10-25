typedef struct ImageImg2Container {
	unsigned int signature;
	unsigned int blockSize;
	unsigned int unk0x8;
	unsigned int unk0xC;
	unsigned int unk0x10;
	unsigned int unk0x14;
	unsigned int unk0x18;
	unsigned int unk0x1C;
	unsigned int unk0x20;
	unsigned int unk0x24;
	unsigned int unk0x28;
	unsigned int unk0x2C;
	unsigned int unk0x30;
}
0x41000000: 32 47 4d 49 (0x494d4732) IMG2
            00 02 00 00 (0x200) blockSize
            00 00 00 00 (0x0)
            03 00 00 00 (0x3) startBlock
0x41000010: fd 0b 00 00 (0xBFD) blockCount
            00 00 00 00 (0x0)
            00 00 00 00 (0x0)
            00 00 00 00 (0x0)
0x41000020: 00 00 00 00 (0x0)
            00 00 00 00 (0x0)
            00 00 00 00 (0x0)
            00 00 00 00 (0x0)
0x41000030: 71 5b 20 48 (0x48205B71) crc32
