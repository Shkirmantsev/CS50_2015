/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#define BLOCK_SIZE 512


int main(int argc, char* argv[])
{
    uint8_t HEADER1[4]={0xff, 0xd8, 0xff, 0xe0};
    uint8_t HEADER2[4]={0xff, 0xd8, 0xff, 0xe1};
	if(argc != 1)
	    {
		    printf("usage: recover <card.raw>\n");
		    return 1;
	    }
	FILE* infile = fopen("./card.raw", "r");
	FILE* outfile = NULL;
	uint8_t* buffer = malloc(sizeof(char) * BLOCK_SIZE);
	char filename[8];
	int count = 0;
	// read the raw image 512 bytes at a time (per block)
	while(fread(buffer, sizeof(char), BLOCK_SIZE, infile) == BLOCK_SIZE && !feof(infile))
	{
	    // read the first 4 bytes of the block by making a pointer to an integer point to it
		// and determine if it contains a JPEG signature
		if (feof(infile))
		{
		    fclose(outfile);
		    break;
		} 
		if(memcmp(buffer, HEADER1, 4) == 0 || memcmp(buffer, HEADER2, 4) == 0)
		{
		    // close current file and begin writing to a new one
		    if(outfile != NULL)
		        {
				    fclose(outfile);
			    }
			
			sprintf(filename, "%03d.jpg", count++);
			outfile = fopen(filename, "a");
			
			if(outfile == NULL)
			    {
				    printf("Could not create file.\n");
				    return 1;
				}
			fwrite(buffer, sizeof(char), BLOCK_SIZE, outfile);
			
				
		}
		else 
		{
		    // continue writing blocks until we see another JPEG signature
			if(outfile != NULL)
			    {
				    fwrite(buffer, sizeof(char), BLOCK_SIZE, outfile);
				}
		
		}
	    
	}
	free(buffer);
	fclose(infile);
	fclose(outfile);
	return 0; 
	
}
