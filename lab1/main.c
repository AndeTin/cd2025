#include <stdio.h>
#include <regex.h>
#include <string.h>

void match_pattern(const char *pattern, const char *text) {
    regex_t regex;
    int result;

    // Compile the regex
    result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result) {
        printf("Could not compile regex\n");
        return;
    }

    // Execute regex
    result = regexec(&regex, text, 0, NULL, 0);
    if (!result) {
        printf("Match found: %s\n", text);
    } else {
        printf("No match found: %s\n", text);
    }

    // Free compiled regex
    regfree(&regex);
}

int main() {
    // Patterns
    const char *date_pattern = "([0-1][0-9])/([0-3][0-9])/([0-9]{2})";
    const char *phone_pattern = "\\([0-9]{3}\\) [0-9]{3} [0-9]{4}";
    const char *money_pattern = "^\\$[0-9]+(\\.[0-9]{2})?$";

    char input_text[100];
    printf("Enter a string: ");
    fgets(input_text, sizeof(input_text), stdin);
    input_text[strcspn(input_text, "\n")] = '\0'; // Remove newline character

    // Check date pattern
    regex_t regex_date;
    regcomp(&regex_date, date_pattern, REG_EXTENDED);
    if (!regexec(&regex_date, input_text, 0, NULL, 0)) {
        printf("The input matches the date pattern.\n");
    } else {
        // Check phone pattern
        regex_t regex_phone;
        regcomp(&regex_phone, phone_pattern, REG_EXTENDED);
        if (!regexec(&regex_phone, input_text, 0, NULL, 0)) {
            printf("The input matches the phone pattern.\n");
        } else {
            // Check money pattern
            regex_t regex_money;
            regcomp(&regex_money, money_pattern, REG_EXTENDED);
            if (!regexec(&regex_money, input_text, 0, NULL, 0)) {
                printf("The input matches the money pattern.\n");
            } else {
                printf("The input does not match any pattern.\n");
            }
            regfree(&regex_money);
        }
        regfree(&regex_phone);
    }
    regfree(&regex_date);

    return 0;
}
