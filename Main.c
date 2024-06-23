#include "StrList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_dynamic_input() {
    char* input = NULL;
    size_t size = 0;
    size_t len = 0;
    int c;
    // reads characters one by one 
    while ((c = getchar()) != '\n' && c != EOF) {
        // if the input is bigger than the size make it bigger
    // (for the first time it will be 4 and then it will be doubled every time it is full)
        if (len + 1 >= size) {
            size = size ? size * 2 : 4;
            //reallocates the memory
            char* new_input = realloc(input, size);
            if (!new_input) {
                free(input);
                return NULL;
            }
            //assigns the new memory to the input
            input = new_input;
        }
        //inserts the character into the input
        input[len++] = c;
    }
     // if the input is not empty add a null terminator
    if (input) {
        input[len] = '\0';
    }

    return input;
}

int main() {
    StrList *list = StrList_alloc();
    int choice;
    char* buffer;
    char* data;
    int index;

    while (1) {
        scanf("%d", &choice);
        getchar(); // Consume newline

        switch (choice) {
            case 1:
                int numNodes;
                scanf("%d", &numNodes);
                getchar(); 
                
                buffer = get_dynamic_input();
                if (!buffer) {
                    fprintf(stderr, "Memory allocation failed\n");
                    break;
                }
                
                char *token = strtok(buffer, " ");
                for (int i = 0; i < numNodes && token != NULL; i++) {
                    StrList_insertLast(list, token);
                    token = strtok(NULL, " ");
                }
                free(buffer);
                break;
            case 2:
                scanf("%d", &index);
                getchar(); // Consume newline
                data = get_dynamic_input();
                if (data) {
                    StrList_insertAt(list, data, index);
                    free(data);
                }
                break;
            case 3:
                StrList_print(list);
                break;
            case 4:
                printf("%lu\n", (unsigned long)StrList_size(list));
                break;
            case 5:
                scanf("%d", &index);
                StrList_printAt(list, index);
                break;
            case 6:
                printf("%d\n", StrList_printLen(list));
                break;
            case 7:
                data = get_dynamic_input();
                if (data) {
                    printf("%d\n", StrList_count(list, data));
                    free(data);
                }
                break;
            case 8:
                data = get_dynamic_input();
                if (data) {
                    StrList_remove(list, data);
                    free(data);
                }
                break;
            case 9:
                scanf("%d", &index);
                StrList_removeAt(list, index);
                break;
            case 10:
                StrList_reverse(list);
                break;
            case 11:
                StrList_free(list);
                list = StrList_alloc();
                break;
            case 12:
                StrList_sort(list);
                break;
            case 13:
                if (StrList_isSorted(list)) {
                    printf("true\n");
                } else {
                    printf("false\n");
                }
                break;
            case 0:
                StrList_free(list);
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}