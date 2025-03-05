#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Define the hash table entry structure
typedef struct hashEntry {
    char character;
    int frequency;
} hashEntry;

// Define the hash table structure
typedef struct hashTable {
    hashEntry* table[256];
} hashTable;

typedef struct Node {
    char character;
    int frequency;
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(char character) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->character = character;
    newNode->frequency = 1;
    newNode->next = NULL;
    return newNode;
}

// Function to append a node to the linked list
void appendNode(Node** head, char character) {
    Node* newNode = createNode(character);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* last = *head;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = newNode;
}

// Function to add frequency to an existing node
void addFrequency(Node* head, char character) {
    Node* current = head;
    while (current != NULL) {
        if (current->character == character) {
            current->frequency++;
            return;
        }
        current = current->next;
    }
}

// Function to print the linked list
void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        if (current->character == '\n') {
            printf("\\n : %d\n", current->frequency);
        } else {
            printf("%c : %d\n", current->character, current->frequency);
        }
        current = current->next;
    }
}

// Function to free the linked list
void freeList(Node* head) {
    Node* current = head;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

// Function to search the linked list
void searchList(Node* head, char character) {
    Node* current = head;
    while (current != NULL && current->next != NULL) {
        if (current->character == character) {
            addFrequency(current, character);
            return;
        }
        current = current->next;
    }
    if (current->character == character) {
        addFrequency(current, character);
    } else {
        appendNode(&head, character);
    }
}

// Function to create a hash table
hashTable* createHashTable() {
    hashTable* newTable = (hashTable*)malloc(sizeof(hashTable));
    for (int i = 0; i < 256; i++) {
        newTable->table[i] = NULL;
    }
    return newTable;
}

// Hash function to map characters to indices
unsigned int hashFunction(char character) {
    return (unsigned int)character % 256;
}

// Function to insert or update a character in the hash table
void insertOrUpdate(hashTable* table, char character) {
    unsigned int index = hashFunction(character);
    if (table->table[index] == NULL) {
        table->table[index] = (hashEntry*)malloc(sizeof(hashEntry));
        table->table[index]->character = character;
        table->table[index]->frequency = 1;
    } else {
        table->table[index]->frequency++;
    }
}

// Function to print the hash table
void printHashTable(hashTable* table) {
    for (int i = 0; i < 256; i++) {
        if (table->table[i] != NULL) {
            if (table->table[i]->character == '\n') {
                printf("\\n : %d\n", table->table[i]->frequency);
            } else {
                printf("%c : %d\n", table->table[i]->character, table->table[i]->frequency);
            }
        }
    }
}

// Function to read a file and update the linked list and hash table
void readFile(const char* filename, Node** head, hashTable* table) {
    FILE* fp = fopen(__FILE__, "r");
    if (fp == NULL) {
        printf("Failed to open file\n");
        return;
    }
    char character;
    while ((character = fgetc(fp)) != EOF) {
        if (*head == NULL) {
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
    readFile(__FILE__, &head, table); // Specify your file name here
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
