SixDegreeOfBacons

Written by Alex Follette

For CSCV352 Capstone project


included are six .c files

main.c - Starts the program and holds overall logical proccess of the program

search.c - short file that contains a function to search the databases for actors

readFile.c - another short file. Reads a single line from a file and returns it.

parsers.c - Functions related to parsing the strings from the database files. Actions are more abstract and become more complex.

node.c - Handles node creation and data generation to fill the datastructure with meaningful results.

hashcmds.c - define the two major datastructures in the program and sets the methods on how to interact with them.

two .h files

dataReader.h - holds declarations for a few of the data parsers, file readers and searchers.

hashStruct - holds definitions of major data stuctures and the functions that work with them

and the actors and actress databases.



Note from the Author:

	The program is largely buggy at this point in development. Bugs and poor design choices exist within the overall program that need to be worked out. Because of the experience level I am at with programming, this being the largest program I have ever written, and the overall difficulty of C in general, the quality of the program is not do to lack of effort. I learned a great deal from this assignment and I have the intent of continuing to learn and use Cin my proffesional career.

	Notes about the program: 

	I had difficulty with memory leaks. They are abudant. I wanted to free memory but often recieved errors when I did. I tried to close the file stream when it seemed appropriate. However, the difficulty of having to pass the datastructure and file pointer from function to function made my unsure of how to wisely handle these situations. The datastructures and the output of the program are almost complete. All of the idea is there and is implemented, but needs to be revised several more times. 

	A few functions need to be re written. While many of the functions are very large and need to be broken down into smaller functions. I feel uncomfortable with this as well, but I imagine I will only get better with that in practice.

	I enjoyed the class. Although, it was very difficult for me. Thanks.






