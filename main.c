#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include "./flags.h"

#define START 0xC5FA086B
#define END 0xD51A086B
#define BIT 7250154

const unsigned char preallocate = 	0x1;	//0000 0001
const unsigned char afteralloc = 	0x2;	//0000 0010
const unsigned char afterfill = 	0x4;	//0000 0100
const unsigned char dealloc = 		0x8;	//0000 1000

void checkMem(char*);
void write_to_memory(unsigned char * pointer);

int main(int args, char * argv[]){
	//check flags
	//example: ./main -alloc=x, x={0,1,2,4,8}
	initFlag(args, argv);
	int flags = 0; //standart flag
	flag_int(&flags,"alloc");

	//check do we need dump before allocate
	if (flags & preallocate){
		puts("it's time to check memory(pre allocation)\npress enter to continue");
		getchar();
	}
	
	unsigned char* memory_pointer = (unsigned char*) START;
	
	/**There we allocate memory close to chosen memory
	 * 242 Mb = 242*1024*1024
	 * with permission to read and write
	 * shared with other process and don't use file (anonimus)
	 * because of anonimus file descriptor is -1
	 * offset is 0 by the rules*/
	memory_pointer = (unsigned char*)mmap(memory_pointer,242*1024*1024,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
	//assert will output error if there is something wrong
	assert(memory_pointer != MAP_FAILED);
	/*printf("address -> %X\n",memory_pointer);
	unsigned char test = 10;
	memory_pointer[1] = test;*/

	if (flags & afteralloc){
		puts("it's time to check memorry(afret allocation)\npress enter to continue");
		getchar();
	}

	write_to_memory(memory_pointer);

	if (flags & afterfill) {
		puts("it's time tocheck mamorry(after writting)\npress enter to continue");
		getchar();
	}

	return 0;
}
/**Thit function accepts memory pointer
 * start threads and make structures for thread's function
 * 35 threads for 242mb which is
 * 7 250 154 bytes for 1 thread and remainder 2 bytes*/
void write_to_memory(unsigned char * memory_pointer){
}
