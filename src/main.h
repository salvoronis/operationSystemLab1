#ifndef MAIN_H
#define MAIN_H
#include <stdint.h>
#include <stdio.h>
#define START 0xC5FA086B
void write_to_memory(void * pointer);
void *write_thread(void *arg);
void read_from_memory(FILE *file, void * memory_pointer);
struct chunk{
	void * mem_pointer;
	uint64_t size;
	uint64_t start;
};
enum errors {
	OK,
	FILE_ERR
};
#endif
