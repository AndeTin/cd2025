#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct hashEntry {
    char character;
    int frequency;
} hashEntry;

typedef struct hashTable {
    hashEntry* table[256];
} hashTable;

typedef struct Node{
    char character;
    int frequency;
    struct Node* next;
} Node;

Node* createNode(char character) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->character = character;
    newNode->frequency = 1;
    newNode->next = NULL;
    return newNode;
}

void appendNode(Node** head, char character) {
    Node* newNode = createNode(character);
    if(*head == NULL) {
        *head = newNode;
        return;
    }
    Node* last = *head;
    while(last->next != NULL) {
        last = last->next;
    }
    last->next = newNode;
}

void addFrequency(Node* head, char character) {
    Node* current = head;
    while(current != NULL) {
        if(current->character == character) {
            current->frequency++;
            return;
        }
        current = current->next;
    }
}

void printList(Node* head) {
    Node* current = head;
    while(current != NULL) {
        if(current->character == '\n') {
            printf("\\n : %d\n", current->frequency);
            current = current->next;
            continue;
        }
        printf("%c : %d\n", current->character, current->frequency);
        current = current->next;
    }
}

void freeList(Node* head) {
    Node* current = head;
    Node* next;
    while(current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

void searchList(Node* head, char character) {
    Node* current = head;
    while(current != NULL && current->next != NULL) {
        if(current->character == character) {
            addFrequency(current, character);
            return;
        }
        current = current->next;
    }
    if(current->character == character) {
        addFrequency(current, character);
    } else {
        appendNode(&head, character);
    }
}

hashTable* createHashTable() {
    hashTable* newTable = (hashTable*)malloc(sizeof(hashTable));
    for(int i = 0; i < 256; i++) {
        newTable->table[i] = NULL;
    }
    return newTable;
}

unsigned int hashFunction(char character) {
    return (unsigned int)character % 256;
}

void insertOrUpdate(hashTable* table, char character) {
    unsigned int index = hashFunction(character);
    if(table->table[index] == NULL) {
        table->table[index] = (hashEntry*)malloc(sizeof(hashEntry));
        table->table[index]->character = character;
        table->table[index]->frequency = 1;
    } else {
        if (table->table[index]->character == character) {
            table->table[index]->frequency++;
        } else {
            // Handle collision: use separate chaining, open addressing, etc.
            // For simplicity, let's ignore collisions here.
            printf("Hash collision detected at index %d for character %c\n", index, character);
        }
    }
}

void printHashTable(hashTable* table) {
    for (int i = 0; i < 256; i++) {
        if (table->table[i] != NULL) {
            if (table->table[i]->character == '\n') {
                printf("\\n : %d\n", table->table[i]->frequency);
            } else {
                printf("%c : %d\n", table->table[i]->frequency);
            }
        }
    }
}

void readFile(const char* filename, Node** head, hashTable* table) {
    FILE* fp = fopen(filename, "r");
    if(fp == NULL) {
        printf("Failed to open file\n");
        return;
    }
    char character;
    while((character = fgetc(fp)) != EOF) {
        if(*head == NULL) {
            appendNode(head, character);
        } else {
            searchList(*head, character);
        }
        insertOrUpdate(table, character);
    }
    fclose(fp);
}

int main() {
    Node* head = NULL;
    hashTable* table = createHashTable();
    readFile(__FILE__, &head, table);
    printf("Using sequential search: O(n)\n");
    printList(head);
    printf("\nUsing hash table: O(1) average time complexity\n");
    printHashTable(table);

    // Free allocated memory
    freeList(head);
    for (int i = 0; i < 256; i++) {
        if (table->table[i] != NULL) {
            free(table->table[i]);
        }
    }
    free(table);

    return 0;
}
