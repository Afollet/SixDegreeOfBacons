#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"dataReader.h"
//Returns file position for a give actor and filename. Would be phased out in further versions of the program

long int searchActor(char *actorQuery, char *fileName){

	static FILE *file = NULL;
	static char fileName2[] = "actresses.list"; 

	char *buffer = calloc(BUFFER_ALLOC, sizeof(char)), *i = NULL;
	char *actorBuffer = calloc(200, sizeof(char)); //Buffers were set fairly high. On the uneddited dataset bad formatting led to numerous heap errors
	
	int long line = 0, EndOfData, previousLine;
	int size, isDone = 0; 


	file = fopen(fileName, "r");

	if(file == NULL){

		printf("File failed to open");
	
		exit(1);	
	}

	EndOfData = fileLength(file);	


	while((line < EndOfData - TAIL_SIZE)&&(isDone == 0)){


		buffer = (readFile(file));

		previousLine = line;
	
		if((line = ftell(file)) == -1){


			printf("FTELL recieved an error in search.c");

		}

		//printf("\n This is the line variable %ld \n", line);
		
		if(!(buffer[0] == '\t')&&(!(buffer[0] == '\n'))){
				
			memset(actorBuffer,0,80);

			for(i = buffer, size = 0; (*i != '\t') && (size < 100); i++, size++){
		

					actorBuffer[size] = *i;
					
					//printf("%c", *i);			


			}
		
		//I would maybe like to break this off as a separate function here. Make it more accessible for matching, maybe.

		if(strcmp(actorBuffer, actorQuery) == 0){

			printf("\n actor located \n");

			isDone = 1;

		}

		//printf("\n");

		}
	}	

	pclose(file);
	
	if((line >= EndOfData - TAIL_SIZE)&&(fileName != fileName2)){
	
		//free(fileName);

		return searchActor(actorQuery, fileName2);
		//I would like to make this a tail end recursion, but don't konw how to do it	
	}

	printf("\n Found in filename : %s\n", fileName);

	return previousLine;
}












long int fileLength(FILE *file){
	//Finds the end of the file so that we can swith between actor and actress without error and avoid the junk at the end!
	long int prevOffset;

	prevOffset = ftell(file);


	if(fseek(file, 0, SEEK_END) != 0){

		printf("Cannot seek to end of file");
		
		exit(1);
	}

	long int FileSize = ftell(file);
	

	if(fseek(file, prevOffset, SEEK_SET) != 0){ 

		printf("Cannot seek to beginning of file");
		
		exit(1);
	}
	
	//printf("The File Size according to ftell %ld", FileSize);
	
	
	return FileSize;

}
