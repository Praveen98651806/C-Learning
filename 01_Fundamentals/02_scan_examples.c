#include <stdio.h>
#include <string.h>

int main(void) {
    int i;
    float f;
    char ch;
    char name[64];
    long long ll;
    double d;

    printf("Enter an integer and a float (e.g. 42 3.14): ");
    if (scanf("%d %f", &i, &f) != 2) {
        printf("Invalid integer/float input\n");
        return 1;
    }

    /* consume leftover newline if any and read a single non-space character */
    printf("Enter a single character (e.g. A): ");
    if (scanf(" %c", &ch) != 1) { /* leading space skips whitespace/newline */
        printf("Invalid char input\n");
        return 1;
    }

    /* consume the rest of the line before using fgets */
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    printf("Enter a name (may contain spaces): ");
    if (!fgets(name, sizeof(name), stdin)) {
        printf("Failed to read name\n");
        return 1;
    }
    /* strip trailing newline */
    name[strcspn(name, "\n")] = '\0';

    printf("Enter a long long and a double (e.g. 1234567890123 2.71828): ");
    if (scanf("%lld %lf", &ll, &d) != 2) {
        printf("Invalid long long/double input\n");
        return 1;
    }

    printf("\n-- You entered --\n");
    printf("Integer: %d\n", i);
    printf("Float: %f\n", f);
    printf("Char: %c\n", ch);
    printf("Name: %s\n", name);
    printf("Long long: %lld\n", ll);
    printf("Double: %f\n", d);

    return 0;
}
