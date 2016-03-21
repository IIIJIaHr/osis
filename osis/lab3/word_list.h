#ifndef WORD_LIST_H
#define WORD_LIST_H

#include "stdio.h"
#include "stdlib.h"

// #include "helpers.h"

extern const int MAX_WORD_LEN;

// Delarations
char** create_word_list(int);
void delete_word_list(char**, int);

int get_word_list_size(FILE*);
void fill_word_list(FILE*, char*[], int);
void check_n_correct_words(char*[], int, char*[], int);
void print_word_list(char*[], int);
#endif
