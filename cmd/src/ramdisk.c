#define kLoadAddress 0x41000000
#define kRamdiskMaxSize 0x2000000
#define kRamdiskAddress 0x44000000
#define kRamdiskImageType 0x7264736B

unsigned int* gRamdiskSize;
unsigned char** gRamdiskAddr;

int cmd_ramdisk(int argc, CmdArg* argv) {
	unsigned int filesize = 0;
	unsigned char* loadaddr = NULL;
	if(argc > 3 || !strcmp("help", argv[1].string)) {
		printf("usage:\n\t%s [<len>] [<address>]\n", argv[0].string);
		return -1;
	}
	
	filesize = (unsigned int) nvram_getint("filesize", 0);
	loadaddr = (unsigned char*) nvram_getint("loadaddr", kLoadAddress);
	if(filesize == 0) {
		printf("filesize variable invalid or not set, aborting\n");
		return -1;
	}
	
	if(range_check(loadaddr, filesize) == 0) {
		printf("Permission Denied\n");
		return -1;
	}
	
	MemzDescriptor* memz = memz_create(loadaddr, filesize, 0);
	if(memz == NULL) {
		printf("Ramdisk image not valid\n");
		return -1;
	}
	
	if(memz->imageSize > kRamdiskMaxSize) {
		printf("Ramdisk too large\n");
		return -1;
	}
	
	*gRamdiskAddr = kRamdiskAddress;
	*gRamdiskSize = memz->imageSize;
	if(image_load(memz, kRamdiskImageType, gRamdiskAddr, gRamdiskSize) >= 0) {
		printf("creating ramdisk at 0x%x of size 0x%x, from image at 0x%x\n", gRamdiskAddr, gRamdiskSize, loadaddr);
		return 0;
	}
	
	*gRamdiskAddr = 0;
	*gRamdiskSize = 0;
	return -1;
}
