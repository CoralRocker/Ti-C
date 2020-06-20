#include <stdlib.h>
#include <string.h>
#include <tice.h>
#include <stdint.h>
#include <fileioc.h>
#include <stdbool.h>
#include <debug.h>

typedef struct {
	uint8_t *arr;
	size_t size;	
} vec8_t;

/** Initializes a vec8_t struct with a size of one and an 
 * initial value of zero;
 *
 * Returns: a pointer to the initialized vec8_t
 */
vec8_t* initVec8(void){
	vec8_t *v8;

	v8 = malloc(sizeof(vec8_t));
	v8->arr  = NULL;
	v8->size = 0;

	return v8;
}

/** Frees a previously initialized vec8_t. Both the array and 
 * the structure must be created by malloc in order for this
 * to work correctly.
 *
 * Params:
 * 	vec8_t* v: pointer to vector to free.
 */
void freeVec8(vec8_t* v){
	free(v->arr);
	free(v);
}

/** Increments the size of the array by one. 
 *
 * Params:
 * 	vec8_t *v: pointer to vector to free.
 *
 * Returns: the slot containing the array's data in archive.
 */
ti_var_t resizeVec8(vec8_t* v){
	ti_var_t fVar;
	
	ti_CloseAll();

	fVar = ti_Open("ARCVECTOR", "w+");
	sprintf(0xFB0000, "ARCHIVE STATUS SET %d\n", ti_SetArchiveStatus(true, fVar));
	ti_Write(v->arr, 1, v->size, fVar);
	sprintf(0xFB0000, "Variable Written\n");

	free(v->arr);
	v->arr = malloc(++v->size);
	ti_Rewind(fVar);

	return fVar;
}

/** Adds a value to the end of the vector, increasing the 
 * vector's size.
 *
 * Params:
 * 	vec8_t* v: vector to modify
 * 	uint8_t val: value to add to end of the vector;
 *
 * Returns: the value added to the end of the array.
 */
uint8_t pushBackVector(vec8_t* v, uint8_t val){
	if(v->size > 0){
		ti_var_t fVar;
		fVar = resizeVec8(v);
		memcpy(v->arr, ti_GetDataPtr(fVar), v->size-1);
		v->arr[v->size-1] = val;
		ti_Close(fVar);
	}else{
		v->arr = malloc(1);
		v->arr[0] = val;
		v->size = 1;
	}
	return val;
}

/** Returns value at given index
 *
 * Params:
 * 	vec8_t* v: vector to read
 * 	size_t index: index to read from
 *
 * Returns: value at given index
 */
uint8_t atVector(vec8_t *v, size_t index){
	return v->arr[index];
}
