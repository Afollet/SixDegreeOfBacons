//This is the begining of creating the Node structure for all the degrees of bacon program.

//Includes addActorNodes, addMovieNodes, and hash. hash() is the simplest function, returning the index number were the movie belongs on the HashTable. addMoveNodes() will add a movie to the hash table then find all the actors associated with the movie and add it to the movies actors linked list. While addActorNodes is the function that creates the linked list that is associated with the movie. Much of this program functionalities are found here in these functions.

#include<stdio.h>
#include<stdlib.h>
#include"hashStruct.h"
#include"dataReader.h"
#include<string.h>

//First, simple create node function! Putting struct definition in a .h as well.

struct actorNode* addActorNodes(char *movieTitle, struct Arr * adjArr, int parentIndex); //defined here because it is only used in this file.


//Takes the movie title and generates a hash as a unsigned long integer. The//constant HASHTABLESIZE is the size of the HASHTABLE set in hashStruct.

unsigned long hash(unsigned char *movieTitle){

	unsigned long hashVal;

	for(hashVal = 0; *movieTitle != '\0'; movieTitle++){

		hashVal = *movieTitle + 31*hashVal;
	}
	
	return hashVal % HASHTABLESIZE;
}
 
//Returns the movieNode (although unused in it's current implmentation) Takes the movie title, adjacency array and parent Index (of the adjacency Array). Generates the movie node and sticks it into the hashtable. Checks if the index on the has table is occupied. If it is it adds itself to the end of the linked list.

struct movieNode * addMovieNode(unsigned char *movieTitle, struct Arr * adjArr, int parentIndex){

	int len = 0, size = 0;

	unsigned char *i = NULL;

	struct movieNode *newNode = NULL;

	for(i = movieTitle, size = 0; (*i != '\0'); i++, size++){
		
		len = size;

	}
	printf("\n");

	newNode = malloc(sizeof(struct movieNode) + len + 1);

	newNode->index = hash(movieTitle);
	
	newNode->movieTitle = movieTitle;

	newNode->actorLL = addActorNodes(((char *)movieTitle), adjArr, parentIndex);
	
	newNode->nextMovie = NULL;

	insertMovie(newNode);

	return newNode;
}	


//Returns first actorNode for the linked list for a movie node. Inputs include movietitle, which is used to find all actors in the movie, the adjacency array, which allows for the adjacency array to be updated with thei information from the added actor, and the parent index which is used to find the degree of connection from Bacon.

struct actorNode* addActorNodes(char *movieTitle, struct Arr * adjArr, int  parentIndex){
	
	//Likely have to use an array here . . . 
	static FILE * file = NULL;
	char * actorBuffer = malloc(80), *fileName1 = "actors.list", *fileName2 = "actresses.list";
	struct actorNode *newNode = NULL ,*first = NULL, *tmpNode = NULL;
	static int adjacencyIndex;	
	int len = 0, isSecondFile = 0, isMatch = 0;
	long int endOfData;	
	
	file = openAndSet(0,fileName1);
	
	endOfData =fileLength(file);
	
	do {

		if(ftell(file) >= endOfData - TAIL_SIZE){

			fclose(file);			

			file = openAndSet(0,fileName2);
			
			endOfData = fileLength(file);

			isSecondFile = 1; 
		}
		
		actorBuffer = actorsFromMovies(movieTitle,file);	
		
		if((movieTitle[0] != '\0') && (movieTitle[0] != '\n'))
		
		printf("From movie title : %s", movieTitle);		

		if((actorBuffer[0] != '\0')&&(strcmp(actorBuffer,"Bacon, Kevin (I)") != 1)) {

			len  = strlen(actorBuffer);
			
	
			tmpNode = first;		
	
			isMatch = 0;

			while((tmpNode != NULL)&&(tmpNode->next != NULL)){
			
				if(strcmp(tmpNode->actorName, actorBuffer) == 0){

					isMatch = 1;

					printf("Actor has previously matched");			
				}
	
				tmpNode = tmpNode->next;

				}

			if(isMatch != 1){

				newNode = malloc(sizeof(struct actorNode) + len + 1);

				newNode->adjacencyIndex = ++adjacencyIndex;

				strncpy(newNode->actorName,actorBuffer,len+1);
			
				newNode->degreeOfBacon = ArrInsertActor(adjArr,adjacencyIndex, parentIndex);
				
				
				if(first == NULL){

					newNode->next = NULL;

					first = newNode;

				}	 
		
				else{

					newNode->next =(void*) first;

					first = newNode;

				}
	
				printf("\nActor %s \n",newNode->actorName);
			}
		}
	
	} while((ftell(file) < endOfData - TAIL_SIZE)&&(isSecondFile != 1));
	
	fclose(file);
	
	tmpNode = first;
//Below statments print all the actors attached to the movie in the LINKED LIST	
//	while((tmpNode != NULL)&&(tmpNode->next != NULL)){

//		printf("%p",tmpNode->next);
		
//		printf("The next actor in the node list is %s \n",tmpNode->actorName);
	
//		tmpNode = tmpNode->next;
//	}

	if(tmpNode == NULL){

		printf("tmpNode is Null");

	}

	return first;
}




