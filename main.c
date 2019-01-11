/*
* Alex Follette, CSV352, Capstone Project
*
*
* This is file includes the main function for the SixDegreesOfBacon Program
*
* The file includes the functions Main(), startQueue() and printHashTable()
*
* Main and startQueue run the program. Main pull up Bacons movies and adds t
* 
* them to the HashTable with their Actors included as a linked list.
*
* startQueue does the same, but starts to iterate through everything on the hash table
*/




#include<stdio.h>
#include<stdlib.h>
#include"dataReader.h"
#include"hashStruct.h"

int startQueue(struct Arr *adjArr);
//Declaration for functions used only in this file



//Main starts the program and by running Bacon's name, grabbing his movies and starts generating the hash table. return 0 or 1 based on programs exit status.
int main(){

	char *baconTest = "Bacon, Kevin (I)";
	unsigned char *movieBuffer = calloc(100, sizeof(unsigned char));
	static FILE *file = NULL;
	long int ActorFileLine;
	static char fileName1[] = "actors.list";
	
	struct Arr *AdjTMP = NULL;
	//struct movieNode *tmpMovieNode = NULL;
	//searchActor is a bit unneccessary since it's only used to start.
	ActorFileLine = (searchActor(baconTest,fileName1));
	
	//Make moviesFromActors loop-able, same with actorsFromMovies.
	//Run a loop. Create nodes and check the hashes as we go.
	
	file = openAndSet(ActorFileLine,fileName1);

	AdjTMP = initAdjArray();

	while(movieBuffer[0] != '\n'){
				
		movieBuffer = moviesFromActor(file);
		
		if((movieBuffer[0] != '\n')&&(movieBuffer[0] != '\0')){		
		
			addMovieNode(movieBuffer,AdjTMP,0);
			
//			printArray(AdjTMP);	

		}
		
	}

	return startQueue(AdjTMP);

}

//startQueue is called by main on it's return statement. Passed to it is the
//adjacency Array that holds all of the actors in matrix. It returns an int based on the completion of the program. When this function completes all 3 degrees of bacon have been generated. Passes when actor is third degree.
int startQueue(struct Arr *adjArr){


	struct movieNode * currentMovie, *movieIterator;
	
	struct actorNode * currentActor;

	long int actorFileLine; 

	unsigned char *movieBuffer = calloc(100, sizeof(unsigned char));
	
	static FILE *file = NULL;
	
	static char fileName1[] = "actors.list";

	for(int HashIndex = 0; HashIndex < HASHTABLESIZE; HashIndex++){

		currentMovie = hashTable[HashIndex];
	
		for(movieIterator = currentMovie; movieIterator->nextMovie != NULL; movieIterator = movieIterator->nextMovie){
	
			for(currentActor = movieIterator->actorLL; currentActor->next != NULL; currentActor=currentActor->next){

				if(currentActor->degreeOfBacon < 3){				

					actorFileLine = (searchActor(currentActor->actorName,fileName1));				
					openAndSet(actorFileLine , fileName1);
				
					while(movieBuffer[0] != '\n'){
				
						movieBuffer = moviesFromActor(file);
		
						if((movieBuffer[0] != '\n')&&(movieBuffer[0] != '\0')){				
							addMovieNode(movieBuffer,adjArr,currentActor->degreeOfBacon);
			
						}
					}

				}

			}

		}

	}

	

	return 1;
}


	

	

//Used for debug. will print hash table allowing the developer to check to make sure hashing algorithm is working effectivley.
void printHashTable(){
	
	printf("*****************************Hash-Table Generation Completed*****************************************");
//Print HASH TABLE!
	for(int i = 0; i <= HASHTABLESIZE; i++){
	
		if(hashTable[i] != NULL){
				printf("\n Hash Table Index %d is %p movie Title is : %s",i, hashTable[i], hashTable[i]->movieTitle);

			struct movieNode *tmp;
			if(hashTable[i]->nextMovie != NULL){
				tmp = hashTable[i]->nextMovie;

					printf("\n The next pointer is %p and contains the movie %s", hashTable[i]->nextMovie,tmp->movieTitle);
			}
		}
	}
	
}



