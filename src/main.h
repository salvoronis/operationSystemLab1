#include <stdint.h>
#define START 0xC5FA086B
void checkMem(char*);
void write_to_memory(unsigned char * pointer);
void *write_thread(void *arg);
struct chunk{
	unsigned char * mem_pointer;
	uint64_t size;
	uint64_t start;
};
