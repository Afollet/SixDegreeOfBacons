/******************************************************************************************
 *
 * Alex Follette
 * CSVC 352 Capstone
 *
* File contains the functions involved with simply returning a line from an 
*
*open file. 
 *****************************************************************************************
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"dataReader.h"

#define MAX_SIZE 500
#define HEADER_SIZE 11590 


//Basic readfile function. takes static FILE* input and return a character pointer of a read line.
char * readFile(FILE *file){
	
	static char buffer[500];

	
	if((ftell(file) == -1)|| (file == NULL)){

		printf("\nfile read erorr in readFile.c (readFile()\n");
			exit(1);
	}

	
	if(ftell(file) == 0){	


		if(fseek(file, HEADER_SIZE, SEEK_SET) != 0){

			printf("File seek error");

		}
	
	}

	if(fgets(buffer, MAX_SIZE, file) == NULL){

		printf("fgets is returning NULL");
		
	
	
	}	


	return buffer;
}







