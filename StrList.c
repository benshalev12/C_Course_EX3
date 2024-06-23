#include "StrList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _StrNode {
    char *data;
    struct _StrNode *next;
} StrNode;

struct _StrList {
    StrNode *head;
    size_t size;
};

StrList* StrList_alloc() {
    StrList *list = (StrList *)malloc(sizeof(StrList));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

void StrList_free(StrList *list) {
    if (list == NULL) return;
    //get the head of the list
    StrNode *current = list->head;
    //save the next node when freeing the current node
    StrNode *next;
    while (current != NULL) {
        next = current->next;
        //free the data and the node
        free(current->data);
        //free the node
        free(current);
        current = next;
    }
    //free the list
    free(list);
}

size_t StrList_size(const StrList *list) {
    return list->size;
}

void StrList_insertLast(StrList *list, const char *data) {
    if (list == NULL || data == NULL) return;

    //allocate memory for the new node
    StrNode *new_node = (StrNode *)malloc(sizeof(StrNode));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
     //insert the data into the new node
    new_node->data = strdup(data);
    //check if the data was inserted
    if (new_node->data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    new_node->next = NULL;
    
    //locate the new node at the end of the list
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        StrNode *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    //increment the size of the list
    list->size++;
}

void StrList_insertAt(StrList *list, const char *data, int index) {
    //check if the list is empty, the data is not null and the index is valid
    if (list == NULL || data == NULL || index < 0 || index > list->size) return;

    //allocate memory for the new node
    StrNode *new_node = (StrNode *)malloc(sizeof(StrNode));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
     //insert the data into the new node
    new_node->data = strdup(data);
    if (new_node->data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
     //locate the new node at the given index
    if (index == 0) {
        new_node->next = list->head;
        list->head = new_node;
    } else { 
    
        StrNode *current = list->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
    list->size++;
}

char* StrList_firstData(const StrList *list) {
    if (list->head == NULL) return NULL;
    return list->head->data;
}

void StrList_print(const StrList *list) {
    StrNode *current = list->head;
    while (current != NULL) {
        printf("%s ", current->data);
        current = current->next;
    }
    printf("\n");
}

void StrList_printAt(const StrList *list, int index) {
    //check if the index is valid
    if (index < 0 || index >= list->size) return;
    StrNode *current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    printf("%s\n", current->data);
}

int StrList_printLen(const StrList *list) {
    int total_len = 0;
    StrNode *current = list->head;
    //iterate through the list and sum the length of each string
    while (current != NULL) {
        total_len += strlen(current->data);
        current = current->next;
    }
    return total_len;
}

int StrList_count(StrList *list, const char *data) {
    //check if the list is empty or the data is null
    if (list == NULL || data == NULL) return 0;

    int count = 0;
    StrNode *current = list->head;
    while (current != NULL) { 
        //check if the data is equal to the current node data
        if (strcmp(current->data, data) == 0) {
            count++;
        }
        current = current->next;
    }
    return count;
}

void StrList_remove(StrList *list, const char *data) {
    if (list == NULL || data == NULL) return;

    StrNode *current = list->head;
    StrNode *prev = NULL;
    while (current != NULL) {
        if (strcmp(current->data, data) == 0) {
            //check if the node to be removed is the head
            if (prev == NULL) {
                list->head = current->next;
            } else {
                //let the previous node point to the next node
                prev->next = current->next;
            }
            StrNode *to_delete = current;
            current = current->next;
            //free the data and the node
            free(to_delete->data);
            //free the node
            free(to_delete);
            list->size--;
        } else {
            prev = current;
            current = current->next;
        }
    }
}

void StrList_removeAt(StrList *list, int index) {
    //check if the list is empty and the index is valid
    if (list == NULL || index < 0 || index >= list->size) return;

    StrNode *current = list->head;
    StrNode *prev = NULL;
    //iterate through the list to find the node to be removed
    for (int i = 0; i < index; i++) {
        prev = current;
        current = current->next;
    }
    //check if the node to be removed is the head
    if (prev == NULL) {
        list->head = current->next;
    } else {
        //let the previous node point to the next node
        prev->next = current->next;
    }
    //free the data and the node
    free(current->data);
    free(current);
    list->size--;
}

int StrList_isEqual(const StrList *list1, const StrList *list2) {
    //check if have the same size
    if (list1->size != list2->size) return 0;
    StrNode *current1 = list1->head;
    StrNode *current2 = list2->head;
    while (current1 != NULL) {
        //check if the data of the two nodes are equal
        if (strcmp(current1->data, current2->data) != 0) {
            return 0;
        }
        current1 = current1->next;
        current2 = current2->next;
    }
    return 1;
}

StrList* StrList_clone(const StrList *list) {
    if (list == NULL) return NULL;
    //allocate memory for the new list
    StrList *clone = StrList_alloc();
    StrNode *current = list->head;
    //iterate through the list and insert the data into the new list
    while (current != NULL) {
        StrList_insertLast(clone, current->data);
        current = current->next;
    }
    return clone;
}

void StrList_reverse(StrList *list) {
    //check if the list is empty
    if (list == NULL) return;

    StrNode *prev = NULL;
    StrNode *current = list->head;
    StrNode *next = NULL;
    //reverse the list
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    //set the head of the list to the last node
    list->head = prev;
}

void StrList_sort(StrList *list) {
    //check if the list is empty or has only one node
    if (list == NULL || list->size < 2) return;

    for (StrNode *i = list->head; i != NULL; i = i->next) {
        for (StrNode *j = i->next; j != NULL; j = j->next) {
            //swap the data of the two nodes if the first node data is greater than the second node data
            if (strcmp(i->data, j->data) > 0) {
                char *temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

int StrList_isSorted(StrList *list) {
    //check if the list is empty or has only one node
    if (list == NULL || list->size < 2) return 1;

    StrNode *current = list->head;
    while (current->next != NULL) {
        //check if the data of the current node is greater than the next node data
        if (strcmp(current->data, current->next->data) > 0) {
            return 0;
        }
        current = current->next;
    }
    return 1;
}
