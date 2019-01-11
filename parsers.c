//These functions include parsing the movies from a given actor and search for actors from given movie

//Includes functions openAndSet which handles opening the file. moviesFromActors and actorsFromMovies which generate content from the IMDB database.


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"dataReader.h"

//small function to replace the set command. Input includes the static file location which should be handled by higher function in the stack and the seekpos which has been returned by offset. Returnes a FILE pointer.

FILE* openAndSet(long int seekPos, char *fileName){
	
	static FILE *file = NULL;
	
	file = fopen(fileName, "r");

	if(file == NULL){
printf("File failed to open");
	
		exit(1);	
	}
	
	if(fseek(file, seekPos, SEEK_SET) != 0){

		printf("Failed in parser.c. Could not open actor location");
	
	}
	return file;
}


//Taks a static file input and will return one line at a time the movies from a given actor name. The file should be pointing to the actors position. Used from the FindActor() function.

//Function returns unsigned char. They are unsigned for use in the hash() algorithm.
unsigned char * moviesFromActor(FILE *file){

	char *buffer = calloc(BUFFER_ALLOC, sizeof(char)), *i = NULL, *start;
	unsigned char *movieBuffer = calloc(200, sizeof(unsigned char)); //Buffers were set fairly high. On the uneddited dataset bad formatting led to numerous heap errors
	const char doubleTab[] = {"\t\t"}, TV[] = {"(TV)"};
	int size;

	buffer = (readFile(file));
	
	//Theoretically this should not reach an endOfFile
	if(buffer[0] != '\n'){

		//printf("\n %ld \n", (ftell(file)));
		
		//strstr statement tries to avoid the numerous amount of television shows in the database 
		if(strstr(buffer, TV) == NULL){

			if((buffer[0] == '\t')&&(buffer[1] == '\t')&&(buffer[2] == '\t')){

				for(i = buffer + 1, size = 0 ; (*i != 0x29)&&(size < 100); i++, size++){

					movieBuffer[size] = *i;				
					
					//Adding some characters to make it more accessible to downstream applications.
					if(*(i + 1) == 0x29){
						
						movieBuffer[size + 1] = 0x29;
						movieBuffer[size + 2] = '\0';
					}
				
				}	

				
			}	

			//Looks for the double Tab before a movie title starts
			else if((start = strstr(buffer,doubleTab)) != NULL){

				for(i = start, size = 0; (*i != 0x29)&&(size < 100) ; i++,size++){

					movieBuffer[size] = *i;
					
					if(*(i + 1) == 0x29){
						
						movieBuffer[size + 1] = 0x29;
						movieBuffer[size + 2] = '\0';
					}


				
				}
					
	
			}

		}

	} else if(buffer[0] == '\n') { 
	
		movieBuffer[0] = '\n' ;

	}
		
	//free(buffer); //Generates pointer error
	
	return movieBuffer;
}

//Takes a movietitle and a file pointer and returns all the actors from that movie one line at a time. 

char* actorsFromMovies(char *movieTitle, FILE *file){

	char *buffer = calloc(BUFFER_ALLOC, sizeof(char)), *i;
	char *actorBuffer = calloc(BUFFER_ALLOC,sizeof(char));
	long int EndOfData, prevActor, prevLine, line;
	int size, isDone = 0;
	
//	printf("loop is running FILE POINTER: %p\n", file);

	if(file == NULL){

			printf("File failed to open");
	
			exit(1);	
		}
	//Next few lines are how I dealt with the end and beginning of file. I found the byte offset manually and hardcoded them in. fileLength finds the length of the file then it is subtracted from the TAIL_SIZE which is the byte size of the foot note.
		
	line = ftell(file);

	EndOfData = fileLength(file);
	
	while((line < EndOfData - TAIL_SIZE)&&(isDone == 0)){
	
		buffer = (readFile(file));
			
		prevLine = line;

		line = ftell(file);

		if((buffer[0] != '\n')&&(buffer[0] != '\t')&&(buffer[0] != '\0')){
			prevActor = prevLine;
	
		}	
		//check if the line matches the movieTitle
		if(strstr(buffer, movieTitle) != NULL){

			readFile(file);

			line = ftell(file);

			if(fseek(file, prevActor, SEEK_SET) != 0){

				printf("File seek error in parsers!");

			}

			buffer = (readFile(file));
			//grab the actor name part  of the line
			for(i = buffer, size = 0; ((*i != '\t')&&(size < 100)); i++, size++){
					
					actorBuffer[size] = *i;
				
					//printf("%c", *i);
				}
	
			printf("\n");
		

//check fileseek worked correclty	
			if(fseek(file, line, SEEK_SET) != 0){

				printf("File seek error in parsers 2 !");

			}			
				
				isDone = 1;				

			}

	}

	return actorBuffer;
}
