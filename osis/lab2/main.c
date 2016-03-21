#include "stdio.h"
#include "stdlib.h"


int max(int, int);
int min(int, int);
int strlength(char*);

char** create_word_list(int);
void delete_word_list(char**, int);

int get_word_list_size(FILE*);
void fill_word_list(FILE*, char*[], int);
void check_n_correct_words(char*[], int, char*[], int);
void print_word_list(char*[], int);


const int MAX_WORD_LEN = 30;

inline int max(int a, int b) {
    return a > b ? a : b;
}

inline int min(int a, int b) {
    return a < b ? a : b;
}

inline int abs(int x) {
    return x < 0 ? -x : x;
}

inline int strlength(char* str) {
    const char *s;
    for (s = str; *s; ++s);
    return(s - str);
}


int get_word_list_size(FILE* f) {
    int line_count = 0;
    char ch;
    fseek(f, 0, SEEK_SET);
    while (!feof(f)) {
        ch = fgetc(f);
        if (ch == '\n') {
            line_count++;
        }
    }
    return line_count;
}

void fill_word_list(FILE* f, char* word_list[], int line_count) {
    fseek(f, 0, SEEK_SET);
    int i;
    for (i = 0; i < line_count; i++) {
        fscanf(f, "%s\n", word_list[i]);
    }
}

void check_n_correct_words(char* input_list[], int input_count, char* word_list[], int word_count) {
    int i = 0; 
    for (i = 0; i < input_count; i++) {
        int j = 0;
        for (j = 0; j < word_count; j++) {
            int i_len = strlength(input_list[i]);
            int w_len = strlength(word_list[j]);
            if (i_len != w_len) {
                continue;
            }

            int k, errors = 0, error_i = -1, n = i_len;
            for (k = 0; k < n; k++) {
                if (input_list[i][k] != word_list[j][k]) {
                    if (!errors) {
                        errors = 1;
                        error_i = k;
                    }    
                    else {
                        errors = 2;
                        break;
                    }
                }
            }

            if (errors == 2) {
                continue;
            }
            if (errors) {
                input_list[i][error_i] = word_list[j][error_i];
            }
            break;
        }
    }
}

void print_word_list(char* word_list[], int word_count) {
    int i = 0;
    for (i = 0; i < word_count - 1; i++) {
        printf("%s ", word_list[i]);
    }
    printf("%s", word_list[word_count - 1]);
}


char** create_word_list(int line_count) {
    char** result = (char**)calloc(1, sizeof(char*) * line_count);
    int i;
    for (i = 0; i < line_count; i++) {
        result[i] = (char*)calloc(1, sizeof(char) * MAX_WORD_LEN);
    }

    return result;
}

void delete_word_list(char* word_list[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        free(word_list[i]);
    }

    free(word_list);
}


int main() {
    FILE* f = fopen("dict.txt", "r");
    if (f == NULL) {
        puts("File not found (404)");
        return 1;
    }
    
    int input_count;
    scanf("%d\n", &input_count);
    if (input_count <= 0) {
        puts("Incorrect number");
        return 1;
    }
    char** input_list = create_word_list(input_count);

    int i;
    for (i = 0; i < input_count; i++) {
        fgets(input_list[i], MAX_WORD_LEN, stdin);
        input_list[i][strlength(input_list[i]) - 1] = '\0'; // remove trailing newline character
    }

    int word_count = get_word_list_size(f);
    if (word_count != 0) {
        char** word_list = create_word_list(word_count);
        fill_word_list(f, word_list, word_count);
        check_n_correct_words(input_list, input_count, word_list, word_count);
        delete_word_list(word_list, word_count);
        print_word_list(input_list, input_count);
        delete_word_list(input_list, input_count);
        fclose(f);
    }
    else {
        fclose(f);
        delete_word_list(input_list, input_count);
        return 1;
    } 

    return 0;
}
