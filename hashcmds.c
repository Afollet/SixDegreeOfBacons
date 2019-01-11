//Hashcmds.c holds functions relating to the hashtable and the adjacency node.

//insertMovie() places a movie node in the hashtable. initAdjArr() intiallizes the adjancy array.
//ArrInsertArr() marks the adjacency array according to the distance from Bacon
//FindDegree returns the lowest degree on the row and assumes it to be the shortest degree
//of the parent index

#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"hashStruct.h"

int FindDegree(struct Arr *adjArr, int actorIndex);
//Only used in this file.


//Takes a movie node and places it in the appropriate hashtable's linked list for that movie.
//Returns 0 if function runs successfully.

int insertMovie(struct movieNode* movie){
//Inserts movie
	struct movieNode * tmpPTR;

	char *tmpSTR1, *tmpSTR2;

	int isAMatch = 0;

	tmpSTR1 = (char*)movie->movieTitle;

	if(hashTable[movie->index] != 0){

		printf("\n Collision at index : %d \n", movie->index);
			


		for((tmpPTR = hashTable[movie->index]);((tmpPTR != 0x0)&&(isAMatch != 1));(tmpPTR = tmpPTR->nextMovie)){
			
			tmpSTR2 =(char*) tmpPTR->movieTitle;

			if(strcmp(tmpSTR1,tmpSTR2) == 0){
				
				printf("\n Strings have matched in the buffer \n");

				isAMatch = 1;
		
			}

		}

		if(isAMatch != 1){
			
			tmpPTR = hashTable[movie->index];

			movie->nextMovie = tmpPTR;

			hashTable[movie->index] = movie;
	
			printf("hash table added movie to buck at %d ",movie->index);
		}
		
	}

	else {
	
		hashTable[movie->index] = movie;

	}

	return 0;
}

//Initializes adjacency array. Returns the array for other functiosn to use.

struct Arr * initAdjArray(){
	
	struct Arr *adjArray = malloc(16);
	int size = INIT_ARRAY_SIZE;
	int **tmpPtr;

	if((tmpPtr = (int **)malloc(INIT_ARRAY_SIZE*8)) == NULL){

		printf("error in malloc for initadjarray, dude");

	}

	adjArray->array = tmpPtr;

	for(int i = 0; i < size - 1; i++){

		adjArray->array[i] = malloc(INIT_ARRAY_SIZE*sizeof(int));

	}

	adjArray->used = 0;

	adjArray->size = INIT_ARRAY_SIZE;

	return adjArray;
}

//Takes the adjacency array, actor index in the array and the parents index into the array.
//checks the parents degree from bacon. Marks both the parent and the child array for connectedness with a int 1+ degree of connectedness of the parent. Returns the degree of the parent.

int ArrInsertActor(struct Arr * adjArr,int actorIndex,int parentIndex){
	
	int degreeOfRow =  FindDegree(adjArr, parentIndex);	

	int **PTRtmp, *PTRtmp2;

	if(adjArr->used == (adjArr->size - 1)){
	
		adjArr->size *= 2;

		PTRtmp  = (int **)realloc(adjArr->array, adjArr->size * sizeof(int *));

		if(PTRtmp != NULL){

			adjArr->array = PTRtmp;

			//free(PTRtmp);

		} 
	
		else {

			printf("Error reallocating for the array. You are on your own");

			exit(1);

		}

		for(int i = 0; i < adjArr->size -1; i++){
	
			PTRtmp2  = realloc(adjArr->array[i], adjArr->size * sizeof(int));
				
			if(PTRtmp2 != NULL){

				adjArr->array[i] = PTRtmp2;
			
				//free(PTRtmp2);
	
			} 

			else {

				printf("error in reallocating for adj array. Exiting");

				exit(1);
			}

		}


	}

	degreeOfRow = *adjArr->array[parentIndex];

	adjArr->array[parentIndex][actorIndex] = degreeOfRow + 1;

	adjArr->array[actorIndex][parentIndex] = 1;

	adjArr->used += 1;

	return degreeOfRow;
}
		
	
	//This will look at the array and take the smallest integer value found 
	//as the degree away from Bacon with max being three.
	
int FindDegree(struct Arr *adjArr, int actorIndex){

	//Finds first lowest connection alread in the array and assumes it
	// to be the shortest parent I had difficulty actualizing the adjacency table.

	int *ActorRow =  adjArr->array[actorIndex];

	int lowestIndex = 3;

	if(actorIndex != 0){

		for(int count = 0; count < adjArr->size; count++, ActorRow++){

			if(ActorRow[count] < lowestIndex){

			 	lowestIndex= ActorRow[count];

			}
		}
	}
	else { lowestIndex = 0; }


	return lowestIndex + 1;
}




//prints the adjacency array. Printing the rows is not functional in this implementation.		
void printArray(struct Arr * adjArray){

	printf("************************Printing the adjaceny array*************************************");	

	for(int i = 0;(i < (adjArray->used -1)); i++){
				
			
		for(int j = 0; j < adjArray->used -1; j++){
			
			printf("%d ", adjArray->array[i][j]);

		}

	}
	
}



