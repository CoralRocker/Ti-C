#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <tice.h>
#include <fileioc.h>
#include <stdbool.h>

#define DBGO (char*)0xFB0000

int main(void){
	ti_var_t fVar;
	char i;
	char* buf, *str, *str2;
	size_t S;

	os_ClrHome();

	ti_CloseAll();

	fVar = ti_Open("BFVAR", "w+");
	str = (char*)0xFFFFFF;
	str2 = malloc(16);
	buf = malloc(16);
	for(i = 0;i<16;i++){
		str2[i] = i*2;
		buf[i]  = i;
	}
	
	sprintf(DBGO, "BUF: %X\n", buf);
	sprintf(DBGO, "STR2: %X\n", str2);
	sprintf(DBGO, "fVar VAT: %X, DATA: %X\n", ti_GetVATPtr(fVar), ti_GetDataPtr(fVar));
	*str = 2;
	sprintf(DBGO, "BUF: %X\n", buf);
	sprintf(DBGO, "STR2: %X\n", str2);
	sprintf(DBGO, "fVar VAT: %X, DATA: %X\n", ti_GetVATPtr(fVar), ti_GetDataPtr(fVar));
	*str = 2;
	
	free(str2);
	free(buf);

	return 0;
}
