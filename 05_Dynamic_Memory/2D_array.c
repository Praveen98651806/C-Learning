#include<stdio.h>
#include<stdlib.h>
int main(){
    int i,j,c,r;
    printf("Enter the number of rows and columns\n");
    scanf("%d %d",&r,&c);
    int **p = (int**)malloc(r*sizeof(int*));
    for(i=0;i<r;i++){
        p[i] = (int *)malloc(c*sizeof(int));
    }

    for(i=0;i<r;i++){
        for(j=0;j<c;j++){
            printf("Enter the value for p[%d][%d]\n",i,j);
            scanf("%d",&p[i][j]);
        }
    }
    for(i=0;i<r;i++){
        for(j=0;j<c;j++){
            printf("%d ",p[i][j]);
        }
        printf("\n");
    }
    for(i=0;i<r;i++){
        free(p[i]);
    }
    free(p);
}