#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10000

int left[MAX_SIZE], right[MAX_SIZE]; // Initialize arrays. 


int compare(const void *a, const void *b){
    return (*(int*)a - *(int*)b);
}

int main() {
    FILE *fp = fopen("data.txt", "r"); // Open data file.
    if (!fp) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }

    int size = 0; // to start at pos 0
    while (size < MAX_SIZE && fscanf(fp, "%d %d", &left[size], &right[size])){
        size++;
    }
    fclose(fp);

    qsort(left, size, sizeof(int), compare);
    qsort(right, size, sizeof(int), compare);

    long distance = 0;
    for(int i = 0; i < size; i++){
        distance += abs(left[i] - right[i]);
    }

    printf("Total Distance is: %ld", distance); // 1882714
    return 0;

}
