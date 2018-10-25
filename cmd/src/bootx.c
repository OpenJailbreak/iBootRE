#define kLoadAddress 0x41000000
#define kKernelMaxSize 0xF00000

int cmd_bootx(int argv, CmdArg* argv) {
    void* address = NULL;
    if(argc > 1 && !strcmp("help", argv[1].string)) {
        printf("usage:\n\t%s [<address>]\n", argv[0].string);
        return -1;
    }
    
    if(range_check(kLoadAddress, kKernelMaxSize) < 0) {
        printf("Permission Denied\n");
        return -1;
    }
    
    printf("Attempting to validate kernelcache @ 0x%08x\n", kLoadAddress);
    int err = load_macho_image(kLoadAddress, kKernelMaxSize, &address)
    if(err >= 0) {
        printf("kernelcache prepped at address 0x%08x\n", address);
        jump_to(3, address, gBootArgs);
        
    } else {
        printf("error loading kernelcache\n");
    }
    
    return err;
}
