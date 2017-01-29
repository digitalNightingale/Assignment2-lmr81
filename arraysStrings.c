#include "arraysStrings.h"

	//Part 1 - 2 points
	//write a function joinrev that takes 2 strings and returns a 3rd 
	//string that is th first string followed by the 2nd string reversed
	//Output should be:
	//Hello dlroW

char* joinrev(char *a, char *b){

	int lengthB = strlen(b);
	char* temp = malloc(lengthB + 1), *end = b + lengthB - 1;
	do {
		*temp++ = *end;
	} while (end-- != b);
		*temp = 0;
	
	char* reversedB = temp - lengthB;

	char *c;
	c = malloc(sizeof(char) * (strlen(a) + strlen(reversedB) + 1));
	*c = '\0';

	strcat(c,a);
	strcat(c,reversedB);

	return c;
}


	//Part 2 - 2 points 
	//write a function joinrev_generic that takes pointers to any two
	//arrays, a typesize, and the number of elements in each array and does the same 
	//thing as joinrev except that it will return a void pointer and 
	//will work on any type of array. 
	//HINT - copy the code from 
	//part 1 and change the code so that the pointer arithmetic is done
	//explicitly and the copies are done using memcpy and memmove as in the class example reverse3
	
void* joinrev_generic(void* arrayA, void* arrayB, size_t theTypeSize, size_t theSizeOfA, size_t theSizeOfB) {
	
	printf("\n*** Part 2 ***\n\n");
	
	char *left = (char*) arrayB, *right = (char*)arrayB + (theSizeOfB-1) * theTypeSize;
	char temp[theTypeSize];
	while (left < right) {	
		memcpy(temp, right, theTypeSize);
		memmove(right, left, theTypeSize);
		memcpy(left, temp, theTypeSize);
		left += theTypeSize;
		right -= theTypeSize;
	}
	int *arrayC = malloc((theSizeOfA + theSizeOfB) * theTypeSize);
	memcpy(arrayC, arrayA, theSizeOfA * theTypeSize);
    memcpy((char*)arrayC + theSizeOfA * theTypeSize, arrayB, theSizeOfB * theTypeSize);
    
	return arrayC;
}

	
	//Part 3 - 2 points
	//Write a function readTextAddBinary that takes two strings (filenames) 
	//and returns 0 if the function completes successfully.
	// The function reads from the first filename,  a set of vectors,
	// 2 per line and add them together and writes out a binary file 
	//(the second filename) with the new vectors 
	//(just the vectors - no spaces or other delimiters)
	//A test file is given to you along with the expected 
	//output - you can use the Unix diff function to compare your 
	//output with the expected output in testFiles.  
	//"vectors.txt", "vectors.bin"
	

int readTextAddBinary(char* theFileNameTxt, char* theFileNameBin) {

	printf("*** Part 3 *** \n\n");
	
	//checking to see that it was successfully opened
	FILE *fileOut = fopen(theFileNameBin, "wb");
	if (!fileOut) {
		fprintf(stderr, "Error! Unable to open the file\n");
		return 1;
	}

    FILE *fileIn = fopen(theFileNameTxt, "r");   
	if (!fileIn) {
		fprintf(stderr, "Error! Unable to open the file\n");
		return 1;
	}
	
    if (fileIn != NULL) {
		double atof(const char *str);
		char line[BUFSIZ]; //space to read a line into
        char data[6][100];
        //reading each line
        while (fgets(line, sizeof(line), fileIn) != NULL) {
            
            size_t i = 0, size;
            char *token = line;
			//printf("The line of the file\n");
            //fputs(line, stdout); //prints whole line
            for (;;) {
				size_t len = strcspn(token, " "); //search for delim
                sprintf(data[i], "%.*s", (int)len, token);
                token += len; //advancing pointer
                if (*token == '\n') {
                    break; //advancing to terminating null char
                }
                ++token; //skip to the delim
                if (++i >= sizeof(data) / sizeof(*data)) {
                    break;
                }
            }
            for (size = i, i = 0; i < size; ++i) {
                //printf("data[%d] = %s\n", (int)i, data[i]);
                float num = atof(data[i]); //changing the data to float
            } 
            vector v1 = vector_init(atof(data[0]), atof(data[1]), atof(data[2]));
            vector v2 = vector_init(atof(data[3]), atof(data[4]), atof(data[5]));
            //printf("------The 1st vector is-------\n");
			//vector_print(v1);
			//printf("------The 2nd vector is-----\n");
			//vector_print(v2);
			vector v3 = vector_add(v1, v2);
			//printf("\n------Added Together------\n");
			//vector_print(v3);

			vect v;	
			vector *vPointer;
			vPointer = &v3;
			//printf("%f%f%f%f", vPointer->x, vPointer->y, vPointer->z, vPointer->length);
			
			if (fileOut != NULL) {
				fwrite(vPointer, 1, 16, fileOut); //writing to bin file
			}
			if (ferror(fileOut)){
				fprintf(stderr, "Could not write to the file\n");
				return 1;
			}
        }
	}
	fclose(fileIn);
    fclose(fileOut);
    printf("Please check out the %s file", theFileNameBin);
	return 0;
}


	//Part 4 - 2 points
	//Write a function readBinaryNormText that takes two strings as 
	//input (filenames) and returns 0 if the function completes successfully. 
	//The first argument is a binary file of type produced in part 3. 
	//The function will read it in,  normalize a, and print out to the 
	//text file in argument 2, the components, x,y,z, and length separated 
	//by tabs (all as one big line).  
	//"vectors.bin", "norm.txt"
	
int readBinaryNormText(char* theFileNameBin, char* theFileNameTxt) {
	
	printf("\n\n*** Part 4 ***\n\n");

	FILE *fileIn = fopen(theFileNameBin, "rb");
	if (!fileIn) {
		fprintf(stderr, "Error! Unable to open the file\n");
		return 1;
	}
	
	FILE *fileOut = fopen(theFileNameTxt, "w");
	if (!fileOut) {
		fprintf(stderr, "Error! Unable to open the file\n");
		exit(1);
	}
	
	//printf("\nData from file:\n");
	vect v;
	
	while (1) {
		fread(&v, sizeof(v), 1, fileIn);
		if(feof(fileIn)!= 0) {
			break;
		}
		//printf("\nVector:\n");
		//printf("x: %f\ny: %f\nz: %f\nlength: %f\n", v.x, v.y, v.z, v.length);
		//printf("%f%f%f%f", v.x, v.y, v.z, v.length);
		
		vector vBin = vector_init(v.x, v.y, v.z);
		vector *vPointer;
		vPointer = &vBin;
		int vNormalizeA = vector_normalize(vPointer);
		if (vNormalizeA == 1) {
			printf("Vector was not normalized\n");
		}
		
		//printf("\nVector after normalization:\n");
		//vector_print(vBin);
		//printf("\nNorm x: %f",vPointer->x);
			
		//prints floats to file with tabs
		fprintf(fileOut, "%f\t%f\t%f\t%f\t", vPointer->x, vPointer->y, vPointer->z, vPointer->length);	
	
		if (ferror(fileOut)){
			fprintf(stderr, "Could not write to the file\n");
			return 1;
		}
	}
	fclose(fileIn);
	fclose(fileOut);
	printf("Please check out the %s file\n", theFileNameTxt);
	return 0;
}


	//Part 5 - 2 points
	//Write a function readNormTextWriteNormBinary that takes two 
	//strings as input (filenames) and returns 0 if the function 
	//completes successfully. The first argument is the text file of
	//type produced in part 4.  Read in the line using fgets or fread. 
	//Either use realloc or check for the size of the file using fseek, 
	//ftell to allocate enough space to store the line. 
	//Then use strtok to parse the file. Print the results out to a 
	//binary file in the same format as the binary file produced 
	//in part 3. Remember to free the memory.  
	//"norm.txt","norm.bin"
	
int readNormTextWriteNormBinary(char* theFileNameTxt, char* theFileNameBin) {
	
	printf("\n*** Part 5 ***\n\n");
	
	FILE *fileOut = fopen(theFileNameBin, "wb");
	if (!fileOut) {
		fprintf(stderr, "Error! Unable to open the file\n");
		return 1;
	}
	
	FILE *fileIn = fopen(theFileNameTxt, "r");
	if(!fileIn){
		fprintf(stderr, "Error! Unable to open the file\n");
		return 1;
	} 
	
		
	char *buffer = NULL;
	int strLen, readLen; 

	if (fileIn) {
        // Seek the last byte of the file
		fseek(fileIn, 0, SEEK_END);
		strLen = ftell(fileIn);
		rewind(fileIn);

		//allocating a string to hold all data
		buffer = (char*) malloc(sizeof(char) * (strLen + 1));
		readLen = fread(buffer, sizeof(char), strLen, fileIn);
		buffer[strLen] = '\0';

		if (strLen != readLen) {
			//if didnt work set everything back
			free(buffer);
			buffer = NULL;
		}
	}
    //puts(buffer); //print out the file
       
	const char s[2] = "\t"; //for findint the tabs
	char *token;
	token = strtok(buffer, s); //get the first token

	while (token != NULL) {

		//printf("%s", token); //print token
		
		float data = atof(token);
		float *ftemp;
		ftemp = &data;
		
		//printf("%f", data); //print data
		
		if (fileOut != NULL) {
			fwrite(ftemp, 1, 4, fileOut);
		}
		if (ferror(fileOut)){
			fprintf(stderr, "Could not write to the file\n");
			return 1;
		}
		token = strtok(NULL, s);
	} 
	fclose(fileIn);
	fclose(fileOut);
    free(buffer);
    printf("Please check out the %s file", theFileNameBin); 
	return 0;
}


	//Bonus - 1 bonus point
	//Write a function wc that reads in the text file given and 
	//count the number of lines, number of words and number of characters. 
	//The output should be the same as given by the UNIX function wc 
	//i.e by typing the command "wc gettysburg.txt" (8 283 1511)
	//Hint read in char by char and use the built in C isspace() 
	//function to determine if the character is whitespace
	//"gettysburg.txt"

	
int wc(char* theFileNameTxt) {
	
	printf("\n\n*** Bonus ***\n");
	
	int lineCount = 0;
	int wordCount = 0;
	int charCount = 0;
	int boolean;
	int count;
	
    FILE *fileIn = fopen(theFileNameTxt, "r");
    if(!fileIn){
		fprintf(stderr, "Error! Unable to open the file\n");
		return 1;
	}
    
    while ((count = fgetc(fileIn)) != EOF) {
		charCount++;
		//checking for all whitespace chars '  ', '\t', '\n'
		if (isspace(count)) { 
			boolean = 0;
		}    
		else if (boolean == 0) {
			wordCount++;
			boolean = 1;
		}
		if (count == '\n') {
			lineCount++;
		}
	}	
	
	printf("\nThe %s file stats are:\n", theFileNameTxt);
	printf("\nNumber of lines: %d\nNumber of words: %d\nNumber of characters: %d", lineCount, wordCount, charCount);
	
	fclose(fileIn);
	return 0;
}

