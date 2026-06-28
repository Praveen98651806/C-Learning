#include<stdio.h>
int main(){
    int a[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    int (*p)[3] = a; // Pointer to an array of 3 integers


    printf("address of q = %p and q+1 = %p\n", p, p+1);
    printf("(*p)[0] = %d\n", (*p)[0]);
    printf("*p[0] = %d\n", *p[0]);
    printf("(*p)[0] = %d (*p)[1] = %d (*p)[2] = %d (*p)[3] = %d (*p)[4] = %d (*p)[5] = %d (*p)[6] = %d (*p)[7] = %d (*p)[8] = %d\n", (*p)[0], (*p)[1], (*p)[2], (*p)[3], (*p)[4], (*p)[5], (*p)[6], (*p)[7], (*p)[8]);
    printf("*p[0] = %d *p[1] = %d *p[2] = %d\n", *p[0], *p[1], *p[2]);

}