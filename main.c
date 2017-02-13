#include <stdio.h>
#include <stdlib.h>
#include "chem.h"
#include "csv.h"

int main(int argc, char* argv[])
{
	#define DATA_FILENAME "periodic-data.csv"
	FILE *stream = fopen(DATA_FILENAME, "r");
	size_t lines = linecount(stream);
	char **symbols = malloc(lines * sizeof *symbols);
	float *atomic_masses = malloc(lines * sizeof *atomic_masses);
	
	stream = fopen(DATA_FILENAME, "r");
	load_data(stream, symbols, atomic_masses);
	fclose(stream);

	load_symbols(symbols, lines);
	free(symbols);

	size_t** atomic_numbers = malloc(sizeof *atomic_numbers);
	size_t** atom_counts = malloc(sizeof *atom_counts);
	size_t* length_ptr = malloc(sizeof *length_ptr);

	parse_molecule(argv[1], atomic_numbers, atom_counts, length_ptr);

	printf("%f", molar_mass(atomic_masses, *atomic_numbers, *atom_counts, *length_ptr));
}