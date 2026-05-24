#include<stdio.h>
int main(){
    float mark;
    printf("Enter the mark in within 100:");
    scanf("%f",&mark);

    if(mark >= 90 && mark <= 100){
        printf("Grade is A");
    }
    else if(mark >= 80 && mark < 90){
        printf("Grade is B");
    }
    else if(mark >= 70 && mark < 80){
        printf("Grade is C");
    }
    else if(mark >= 60 && mark < 70){
        printf("Grade is D");
    }
    else if(mark >= 0 && mark < 60){
        printf("No Grade");
    }
    else{
        printf("Invalid mark entered");
    }   
}