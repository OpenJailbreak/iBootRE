#define kImageTypeiBEC 0x69626563
#define kImageAddress 0x43000000
#define kImageMaxSize 0xF00000

int cmd_go(int argc, CmdArg* argv) {

	if(argc > 1) {
		if(!strcmp("help", argv[1].string)) {
			printf("%s [<address>]\n", argv[0].string);
			return -1;	
			
		} else {
			address = argv[1].uinteger;
		}
	}
	
	while(1) {
		if(range_check(address, 0xF00000) == NULL) {
			printf("Permission Denied\n");
			break;
		}
		
		MemzDescriptor* memz = memz_create(address, 0xF00000, 1);
		if(memz == NULL) {
			printf("Memory image corrupt\n");
			break;
		}
		
		unsigned int size = kImageMaxSize;
		unsigned char* address = kImageAddress;
		if(image_load(memz, kImageTypeiBEC, &dest, &size) < 0) {
			printf("Memory image not valid\n");
			break;
		}
		
		printf("jumping into image at 0x%08x\n", address);
		jump_to(0, address, NULL);
	}
	
	return -1;
}
