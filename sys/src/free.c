#include <sys/heap.h>

unsigned int* gHeapRemaining;

struct chunk_header* get_next_chunk(struct chunk_header* chunk) {
	unsigned int chunk_size = chunk->size << 3;
	return ((struct chunk_header*)(chunk + chunk_size));
}

struct chunk_header* get_prev_chunk(struct chunk_header* chunk) {
	unsigned int chunk_size = (chunk->prev_size >> 2) << 3;
	return ((struct chunk_header*)(chunk - chunk_size));
}

void free(void* ptr) {
	if(ptr == NULL) {
		return;
	}
	enter_critical_section();
	struct chunk_header* current = (struct chunk_header*)(ptr - 8);
	*gHeapRemaining += (current->size << 3);
		
	struct chunk_header* next = get_next_chunk(current);
	struct chunk_header* prev = get_prev_chunk(current);
	if(current != next && current != prev
		&& current == get_prev_chunk(next)
		&& current == get_next_chunk(prev)
		&& current & 1)) panic(NULL, NULL);
		
	exit_critical_section();
}
