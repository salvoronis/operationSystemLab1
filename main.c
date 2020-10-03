#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "./flags.h"

#define START 0xC5FA086B
#define END 0xD51A086B
#define BIT 7250154

const unsigned char preallocate = 	0x1;	//0000 0001
const unsigned char afteralloc = 	0x2;	//0000 0010
const unsigned char afterfill = 	0x4;	//0000 0100
const unsigned char dealloc = 		0x8;	//0000 1000

void checkMem(char*);
void *writeThread(void *argp);
struct Vargp {
	int from,to;
};

int main(int args, char * argv[]){
	initFlag(args, argv);
	int flags = 0;
	flag_int(&flags,"alloc");

	//check do we need dump before allocate
	if (flags & preallocate)
		checkMem("./prealloc");


	unsigned int written = START;
	unsigned int to = written + 7080;
	pthread_t tid;
	for (int i = 0; i < 35; i++){
		if ((END-to) < BIT)
			to += END - to;
		struct Vargp var = {written, to};
		pthread_create(&tid, NULL, writeThread, &var);
		written += BIT;
		to += BIT;
	}
	pthread_exit(NULL);
	return 0;
}

void checkMem(char* filename){
	unsigned int i = START;
	short* symbol = i;
	FILE* fp;
	if ((fp = fopen(filename,"wb")) == NULL){
		perror("File opening error\n");
		exit(1);
	}
	while(i <= END){
		putc(symbol, fp);
		i++;
		symbol = i;
	}
}

void *writeThread(void *vargp){
	struct Vargp* variables = (struct Vargp*) vargp;
	printf("from -> %x; to ->%x\n",variables->from, variables->to);
}
