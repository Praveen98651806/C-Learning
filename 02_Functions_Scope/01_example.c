#include <stdio.h>

/* Function definition */
void say_hello(void) {
    printf("Hello, World!\n");
}

int main(void) {
    say_hello();   /* Function call */
    say_hello();   /* Call it again! */
    return 0;
}