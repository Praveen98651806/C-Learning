#include<stdio.h>
int main(){
    int a,b,c,d,e;
    float avg, total;
    printf("Enter the five number");
    int rc = scanf("%d %d %d %d %d",&a,&b,&c,&d,&e);

    if(rc != 5){
        printf("Scanf faild to get expected input\n");
        return 1;
    }

    total = a + b + c + d + e;
    avg = total/5;

    printf("The sum of the five number is %d\n", (int)total);
    printf("The average of the five number is %.2f\n", avg);

}