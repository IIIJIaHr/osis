#include "helpers.h"
#include "word_list.h"


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
        puts("\n");
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
