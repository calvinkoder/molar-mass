#ifndef CSV_H
#define CSV_H

const char* getfield(char* line, int num);
size_t linecount(FILE *stream);
void load_data(FILE *stream, char **symbols, float *atomic_masses);

#endif