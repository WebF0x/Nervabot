/*
============================================================================
 Name : Armus.cpp
 Author :
 Version :
 Description : Hello world - Exe source file
============================================================================
*/

// Include Files

#include "Robot.h"

// Global Functions

int main()
{
	Robot robot;

	robot.qualification();
	
	/*FILE *f = fopen("file.txt", "w");
	if (f == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}

	/* print some text */
	/*const char *text = "Write this to the file";
	fprintf(f, "Some text: %s\n", text);

	/* print integers and floats */
	/*int i = 1;
	float py = 3.1415927;
	fprintf(f, "Integer: %d, float: %f\n", i, py);

	/* printing single chatacters */
	/*char c = 'A';
	fprintf(f, "A character: %c\n", c);

	fclose(f);*/

	return 0;
}

