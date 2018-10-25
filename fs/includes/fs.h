void fs_unmount(const char* path);
int fs_load_file(const char* path, void* address, unsigned int* size);
void fs_mount(const char* partition, const char* type, const char* path);
