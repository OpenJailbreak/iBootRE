#include <heap.h>

static void* gHeapHeader;

void* malloc(size_t size) {
	void* candidate = NULL;
	enter_critical_section();
	
	unsigned size = get_min_alloc(size);
	void* zone = get_zone(size);
	chunk_header* candidate = gZoneHeader + (zone * 4);

	NEXT_ZONE:
	if(zone > 0x1F) {
		*gZoneHeader  -= *(unsigned int)(0x4)) << 3
		exit_critical_section();
		return NULL;
	}
		
	NEXT_CANDIDATE:
	if(candidate == NULL) {
		zone++;
		candidate += 4;
		goto NEXT_ZONE;
	}
		
	if(size > (candidate->fwd << 3)) {
		candidate = candidate->prev;
		goto NEXT_CANDIDATE;
	}
	
	chunk_header* next = candidate->next;
	chunk_header* prev = candidate->prev;
	*next = prev;
	if(prev == NULL) {
		prev->next = candidate->next;
	}
		
	assign_chunk(candidate, size);
	*gZoneHeader -= candidate->fwd << 3;
	exit_critical_section();

	return candidate + 8;
}
