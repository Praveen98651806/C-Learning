#include<stdio.h>
int main(){
    int a,count = 0;
    printf("ENter the number:");
    int rc = scanf("%d",&a);
        if(rc != 1){
        printf("Scanf faild to get expected input\n");
        return 1;
    }

    for(int i = 1; i <= a; i++){
        if(a%i == 0){
            count ++;
        }
    }
if(count > 2){
    printf("Given number %d is Not Prime Number", a);
}
else if(count == 2){
    printf("Given number %d is Prime Number", a);
}
else if( a==0 || a==1 ){
    printf("Given number %d is Neither Prime Nor Composite", a);
}
else{
    printf("Invalid input");
}
}