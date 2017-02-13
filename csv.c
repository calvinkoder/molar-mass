#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//from https://stackoverflow.com/questions/12911299/read-csv-file-in-c
const char* getfield(char* line, int num)
{
    const char* tok;
    for (tok = strtok(line, ",");
            tok && *tok;
            tok = strtok(NULL, ",\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}
//end from

size_t linecount(FILE *stream){
	size_t lines;
	char line[1024];
	for (lines=0; fgets(line, 1024, stream); lines++);
	return lines;
}

void load_data(FILE *stream, char **symbols, float *atomic_masses)
{
	char line[1024];
	for (int i=0; fgets(line, 1024, stream); i++)
	{
		char *l = strdup(line);
		*(symbols+i) = strdup(getfield(l, 1));
		l = strdup(line);
		*(atomic_masses+i) = atof(getfield(l, 2));
		free(l);
	}
}