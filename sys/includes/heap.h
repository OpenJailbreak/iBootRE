#define WILDERNESS 1
#define UNKNOWN 2
#define PREV_IN_USE 4

typedef struct chunk_header {
	unsigned int prev_size;
	unsigned int size;
	void* bck;
	void* fwd;
}
