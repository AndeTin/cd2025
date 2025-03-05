#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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

void readFile(const char* filename, Node** head) {
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
    }
    fclose(fp);
}

int main() {
    Node* head = NULL;
    readFile(__FILE__, &head);
    printList(head);
    freeList(head);
    return 0;
}
