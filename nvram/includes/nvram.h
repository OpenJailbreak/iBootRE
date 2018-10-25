typedef struct NvramVar {
	struct NvramVar* prev;
	struct NvramVar* next;
	unsigned char* string;
	unsigned int integer;
	unsigned int save;
	char name[0x40];
} NvramVar;

