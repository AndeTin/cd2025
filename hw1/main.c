#include <stdio.h>
#include <string.h>

#define MAX_INPUT_SIZE 1000
#define MAX_TOKEN_LENGTH 100

// Recognized token types as strings
const char *TOKEN_TYPE[] = {
    "TYPE_TOKEN",
    "MAIN_TOKEN",
    "LEFTPAREN_TOKEN",
    "RIGHTPAREN_TOKEN",
    "LEFTBRACE_TOKEN",
    "RIGHTBRACE_TOKEN",
    "ID_TOKEN",
    "ASSIGN_TOKEN",
    "LITERAL_TOKEN",
    "SEMICOLON_TOKEN",
    "IF_TOKEN",
    "ELSE_TOKEN",
    "WHILE_TOKEN",
    "EQUAL_TOKEN",
    "GREATEREQUAL_TOKEN",
    "LESSEQUAL_TOKEN",
    "GREATER_TOKEN",
    "LESS_TOKEN",
    "PLUS_TOKEN",
    "MINUS_TOKEN",
    "UNKNOWN_TOKEN"
};

// Token type enumeration
typedef enum {
    TYPE,
    MAIN,
    LEFTPAREN,
    RIGHTPAREN,
    LEFTBRACE,
    RIGHTBRACE,
    ID,
    ASSIGN,
    LITERAL,
    SEMICOLON,
    IF,
    ELSE,
    WHILE,
    EQUAL,
    GREATEREQUAL,
    LESSEQUAL,
    GREATER,
    LESS,
    PLUS,
    MINUS,
    UNKNOWN
} TokenType;

// Check if the string is a keyword and map to the correct token type
TokenType classify_token(const char *token) {
    if (strcmp(token, "int") == 0) return TYPE;
    if (strcmp(token, "main") == 0) return MAIN;
    if (strcmp(token, "if") == 0) return IF;
    if (strcmp(token, "else") == 0) return ELSE;
    if (strcmp(token, "while") == 0) return WHILE;
    if (strcmp(token, "==") == 0) return EQUAL;
    if (strcmp(token, ">=") == 0) return GREATEREQUAL;
    if (strcmp(token, "<=") == 0) return LESSEQUAL;
    if (strcmp(token, ">") == 0) return GREATER;
    if (strcmp(token, "<") == 0) return LESS;
    if (strcmp(token, "+") == 0) return PLUS;
    if (strcmp(token, "-") == 0) return MINUS;
    if (strcmp(token, "=") == 0) return ASSIGN;
    if (strcmp(token, ";") == 0) return SEMICOLON;
    if (strcmp(token, "(") == 0) return LEFTPAREN;
    if (strcmp(token, ")") == 0) return RIGHTPAREN;
    if (strcmp(token, "{") == 0) return LEFTBRACE;
    if (strcmp(token, "}") == 0) return RIGHTBRACE;

    // Check if token is numeric (integer literal)
    int is_numeric = 1;
    for (int i = 0; token[i] != '\0'; i++) {
        if (token[i] < '0' || token[i] > '9') {
            is_numeric = 0;
            break;
        }
    }
    if (is_numeric) return LITERAL;

    // Otherwise, assume it's an identifier
    return ID;
}

// Lexer function to split and classify tokens
void lexer(const char *input_text) {
    char token[MAX_TOKEN_LENGTH];
    int index = 0;

    for (int i = 0; i < strlen(input_text); i++) {
        char c = input_text[i];

        // Treat whitespace as token delimiters
        if (c == ' ' || c == '\n' || c == '\t') {
            if (index > 0) {
                token[index] = '\0'; // Null-terminate the token
                TokenType type = classify_token(token);
                printf("%-15s : %-15s\n", token, TOKEN_TYPE[type]); // Align output
                index = 0; // Reset token index
            }
        }
        // Check for single-character symbols or multi-character operators
        else if (c == '=' || c == '<' || c == '>' || c == '!' ||
                 c == '{' || c == '}' || c == '(' || c == ')' ||
                 c == ';' || c == '+' || c == '-') {
            if (index > 0) {
                token[index] = '\0'; // Null-terminate the token
                TokenType type = classify_token(token);
                printf("%-15s : %-15s\n", token, TOKEN_TYPE[type]);
                index = 0; // Reset token index
            }
            // Handle symbols or operators
            token[0] = c;
            token[1] = '\0';
            TokenType type = classify_token(token);
            printf("%-15s : %-15s\n", token, TOKEN_TYPE[type]);
        } else {
            token[index++] = c; // Build token
        }
    }

    // Process the last token if there is one
    if (index > 0) {
        token[index] = '\0';
        TokenType type = classify_token(token);
        printf("%-15s : %-15s\n", token, TOKEN_TYPE[type]);
    }
}

int main() {
    char input_text[MAX_INPUT_SIZE] = {0};
    char buffer[200];

    printf("Enter your code (press Ctrl+D when done):\n");

    // Read multiple lines of input until EOF
    while (fgets(buffer, sizeof(buffer), stdin)) {
        strcat(input_text, buffer); // Concatenate each line into input_text
    }

    lexer(input_text);

    return 0;
}
