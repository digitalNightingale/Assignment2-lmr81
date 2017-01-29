#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "vectors.h"

typedef struct {
	float x;
	float y;
	float z;
	float length;
} vect;

char* joinrev(char *a, char *b);
void* joinrev_generic(void* arrayA, void* arrayB, size_t theTypeSize, size_t theSizeOfA, size_t theSizeOfB);
int readTextAddBinary(char* theFileNameTxt, char* theFileNameBin);
int readBinaryNormText(char* theFileNameBin, char* theFileNameTxt);
int readNormTextWriteNormBinary(char* theFileNameTxt, char* theFileNameBin);
int wc(char* theFileNameTxt);
