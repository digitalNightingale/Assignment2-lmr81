#include <string.h>
#include <ctype.h>
#include "vectors.h"

char* joinrev(char *a, char *b);
void* joinrev_generic(void* arrayA, void* arrayB, size_t theTypeSize, size_t theSizeOfA, size_t theSizeOfB);
int readTextAddBinary(char* theFileNameTxt, char* theFileNameBin);
int readBinaryNormText(char* theFileNameBin, char* theFileNameTxt);
int readNormTextWriteNormBinary(char* theFileNameTxt, char* theFileNameBin);
int wc(char* theFileNameTxt);
