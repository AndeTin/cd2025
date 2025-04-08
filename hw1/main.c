#include <stdio.h>
#include <regex.h> // <=== Old Code Reference: Regex library for pattern matching
#include <string.h>

#define MAX_INPUT_SIZE 1000
#define MAX_TOKEN_LENGTH 100

// === Old Code Reference ===
// Recognized token types as strings are updated for new functionality, while still retaining compatibility with the old classification system.
const char *TOKEN_TYPE[] = {
    "DATE_PATTERN",   // From old code
    "PHONE_PATTERN",  // From old code
    "MONEY_PATTERN",  // From old code
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

// === TokenType Enumeration (Enhanced but compatible with Old Code) ===
// Retains UNKNOWN from the old code and adds new types for broader functionality
typedef enum {
    DATE_PATTERN,  // From old code
    PHONE_PATTERN, // From old code
    MONEY_PATTERN, // From old code
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

// === Old Code Reference ===
// Function to match patterns using regex. This is directly from the old code with no changes.
TokenType match_pattern(const char *pattern, const char *text) {
    regex_t regex;
    int result;

    // Compile the regex
    result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result) {
        printf("Could not compile regex\n");
        return UNKNOWN;
    }

    // Execute regex
    result = regexec(&regex, text, 0, NULL, 0);
    regfree(&regex);

    if (!result) {
        return DATE_PATTERN; // This is just an example. You can extend as needed.
    }
    return UNKNOWN;
}

// === Old Code Reference (Pattern Checking Logic) ===
// Function from the old code that uses match_pattern to classify inputs based on regex patterns.
void check_patterns(const char *input_text) {
    const char *date_pattern = "([0-1][0-9])/([0-3][0-9])/([0-9]{2})";
    const char *phone_pattern = "\\([0-9]{3}\\) [0-9]{3} [0-9]{4}";
    const char *money_pattern = "^\\$[0-9]+(\\.[0-9]{2})?$";

    if (match_pattern(date_pattern, input_text) == DATE_PATTERN) {
        printf("DATE_PATTERN: %s\n", input_text);
    } else if (match_pattern(phone_pattern, input_text) == PHONE_PATTERN) {
        printf("PHONE_PATTERN: %s\n", input_text);
    } else if (match_pattern(money_pattern, input_text) == MONEY_PATTERN) {
        printf("MONEY_PATTERN: %s\n", input_text);
    }
}

// === New Lexer Function ===
// This is the new function to tokenize input into keywords, symbols, and literals. It complements the old pattern-matching logic.
void lexer(const char *input_text) {
    char token[MAX_TOKEN_LENGTH];
    int index = 0;

    for (int i = 0; i < strlen(input_text); i++) {
        char c = input_text[i];

        // Treat whitespace (space, tab, newline) as token delimiters
        if (c == ' ' || c == '\n' || c == '\t') {
            if (index > 0) {
                token[index] = '\0'; // Null-terminate the token
                TokenType type = classify_token(token);
                printf("%-15s : %-15s\n", token, TOKEN_TYPE[type]); // New formatted output
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

// Main function integrates both the old and new logic
int main() {
    char input_text[MAX_INPUT_SIZE] = {0};
    char buffer[200];

    printf("Enter your code (press Ctrl+D when done):\n");

    // Read multiple lines of input until EOF
    while (fgets(buffer, sizeof(buffer), stdin)) {
        strcat(input_text, buffer); // Concatenate each line into input_text
    }

    // === Old Code Reference ===
    // First, check for specific patterns (date, phone, money) using the old logic
    check_patterns(input_text);

    // Call the new lexer to classify tokens
    lexer(input_text);

    return 0;
}