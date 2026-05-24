#include<stdio.h>
float rectangle_area(float length, float width);
int main(){
    float area, length, width;
    printf("Enter the length and width of the area:");
    scanf("%f %f", &length, &width);
    area = rectangle_area(length,width);
    printf(" Area of the Rectangle is : %.2f\n ", area);
    return 0;
}
float rectangle_area(float length, float width){
    return length * width;
}
