#include <stdio.h>

int main() {
    int arr[] = {10,20,30,40,20,20,40,10};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("size of array = %d\n", size);

    int i, j, k;

    for(i = 0; i < size; i++) {
        for(j = i + 1; j < size; j++) {

            if(arr[i] == arr[j]) {

                // shift elements left
                for(k = j; k < size - 1; k++) {
                    arr[k] = arr[k + 1];
                }

                size--;   // reduce size
                j--;      // check same index again
            }
        }
    }

    printf("Array after removing duplicates:\n");
    for(i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    size = sizeof(arr) / sizeof(arr[0]);

    printf("size of array = %d\n", size);

    return 0;
}