#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dict.h"
#include "chem.h"

static struct nlist *periodictab[ELEM_COUNT];
static size_t MAX_ATOMIC_DIGIT = (size_t) ceil(log10((double)ELEM_COUNT)+1);

void load_symbols(char **elems, size_t len)
{
	char num[MAX_ATOMIC_DIGIT];
	for(int i = 0; i<len; i++)
	{
		sprintf(num, "%i", i+1);
		install(*(elems+i), num);
		free(*(elems+i));
	}
}


float molar_mass(float *atomic_masses, size_t* atomic_numbers, size_t* atom_counts, size_t length)
{
	float mass = 0;
	for(int i=0; i<length; ++i)
	{
		mass+=atomic_masses[*(atomic_numbers+i)-1] * *(atom_counts+i);
	}
	return mass;
}

int str_to_digit(char* str)
{
	if(*str >= 48 && *str < 58)
	{
		return (int)*str - 48;
	}else{
		return -1;
	}
}

size_t str_to_size_t(char* molec_str, size_t* molec_idx)
{
	char *num_str = calloc(MAX_ATOMIC_DIGIT, sizeof *num_str);
	for(int i=0; *molec_idx<strlen(molec_str) && str_to_digit(molec_str+*molec_idx) >=0; i++)
	{
		*(num_str + i) = *(molec_str + *molec_idx);
		// printf("%i| cur_char: %c, digit: %c, num:%s\n", *molec_idx, *(molec_str+*molec_idx), *(num_str + i), num_str);
		++(*molec_idx);
	}
	size_t num = (size_t) atoi(num_str);
	free(num_str);
	return num;
}

char *str_to_element(char* molec_str, size_t* molec_idx)
{
	#define MAX_ELEM_LEN 3
	char *element = calloc(MAX_ELEM_LEN, sizeof *element);
	for(int i=0; *molec_idx<strlen(molec_str) && str_to_digit(molec_str+*molec_idx) == -1; i++)
	{
		*(element+i) = *(molec_str+*molec_idx);
		// printf("%i| cur_char: %c, element: %s\n", *molec_idx, *(molec_str+*molec_idx), element);
		++(*molec_idx);
	}
	return element;
}

void parse_molecule(char* molec_str, size_t** atomic_numbers, size_t** atom_counts, size_t* length_ptr)
{
	char *element;
	size_t atom_count;

	size_t *molec_idx = malloc(sizeof *molec_idx);
	*molec_idx = 0;

	*atomic_numbers = malloc(sizeof **atomic_numbers);
	*atom_counts = malloc(sizeof **atom_counts);

	for(*length_ptr = 0; *molec_idx<strlen(molec_str) && *length_ptr<strlen(molec_str); ++(*length_ptr))
	{
		// printf("%i| i:%i\n", *molec_idx, *length_ptr);
		element = str_to_element(molec_str, molec_idx);
		// printf("%i| element: %s\n", *molec_idx, element);
		atom_count = str_to_size_t(molec_str, molec_idx);
		if (atom_count == 0)
			atom_count=1;
		// printf("%i| atom_count:%i\n", *molec_idx, atom_count);

		*atomic_numbers = realloc(*atomic_numbers, (*length_ptr+1) * sizeof **atomic_numbers);
		*atom_counts = realloc(*atom_counts, (*length_ptr+1) * sizeof **atom_counts);

		*(*atomic_numbers+*length_ptr) = (size_t) atoi(lookup(element)->defn);
		*(*atom_counts+*length_ptr) = atom_count;
		free(element);
	}
	free(molec_idx);
}