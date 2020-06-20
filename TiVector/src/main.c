#include <stdint.h>
#include <stdlib.h>
#include <tice.h>
#include "VectorArchive.h"
#include <stdio.h>
#include <debug.h>

void printOutVector(vec8_t* v){
	char* str;
	int i;

	for(i = 0; i < v->size; i++){
		str = malloc(32);
		sprintf(str, "%X: %d ", i, atVector(v, i));
		os_PutStrFull(str);
		free(str);
	}
}

int main(void){
	vec8_t* v;
	int i;

	os_ClrHome();
	
	v = initVec8();
	sprintf((char*)0xFB0000, "Initialized Vector\0");

	for(i = 0; i < 23;i++){
		sprintf((char*)0xFB0000, "Pushing back vector %d\n\0", i);
		pushBackVector(v, i*2);
		sprintf((char*)0xFB0000, "Pushed back vector %d, DATA ARR: %X\n\n\0", i, v->arr);
	}
	//dbg_sprintf(dbgout, "Pushed back all to vector, %d", v->size);


	//printOutVector(v);

	while(!os_GetCSC());

	return 0;
}

