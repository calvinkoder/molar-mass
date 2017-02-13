#ifndef CHEM_H
#define CHEM_H

#define ELEM_COUNT 118

static float *atomic_masses;

void load_symbols(char **elems, size_t len);
float molar_mass(float *atomic_masses, size_t* atomic_numbers, size_t* atom_counts, size_t length);
int str_to_digit(char* str);
size_t str_to_size_t(char* molec_str, size_t* molec_idx);
char* str_to_element(char* molec_str, size_t* molec_idx);
void parse_molecule(char* molec_str, size_t** atomic_numbers_ptr, size_t** atom_counts_ptr, size_t* length_ptr);

#endif