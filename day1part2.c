#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 10000
#define TABLE_SIZE 10000

int left[MAX_SIZE], right[MAX_SIZE]; // Initialize arrays. 

struct node{
    int key;
    int count;
    struct node *next;
};

unsigned int hash(unsigned int x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x % TABLE_SIZE;
}

int compare(const void *a, const void *b){
    return (*(int*)a - *(int*)b);
}

// Insert an integer key into the hash table
void insert(struct node **map, int key) {
    int index = hash(key);

    struct node *current = map[index];
    while (current != NULL) {
        if (current->key == key) {
            current->count++;
            return;
        }
        current = current->next;
    }

    // Insert new integer key
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->key = key;
    new_node->count = 1;
    new_node->next = map[index];
    map[index] = new_node;
}
// Remove or decrement an integer key count
bool pop(struct node **map, int key) {
    int index = hash(key);

    struct node *prev = NULL;
    struct node *curr = map[index];

    while (curr != NULL) {
        if (curr->key == key) {
            if (curr->count > 1) {
                curr->count--;  // Decrement count
                return true;
            } else {
                // Remove node completely
                if (prev == NULL) {
                    map[index] = curr->next;
                } else {
                    prev->next = curr->next;
                }
                free(curr);
                return true;
            }
        }
        prev = curr;
        curr = curr->next;
    }
    return false;
}

void free_table(struct node **map) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        struct node *curr = map[i];
        while (curr) {
            struct node *temp = curr;
            curr = curr->next;
            free(temp);
        }
        map[i] = NULL;
    }
}

void int_to_array(int x, int arr[], int size) {
    for(int i = size - 1; i >= 0; i--) {
        arr[i] = x % 10;
        x /= 10;
    }
}

int main() {
    FILE *fp = fopen("data.txt", "r"); // Open data file.
    if (!fp) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }

    int size = 0; // to start at pos 0
    while (size < MAX_SIZE && fscanf(fp, "%d %d", &left[size], &right[size]) == 2) {
        size++;
    }
    fclose(fp);

    // Calculate a total similarity score by adding up each number in the left list
    // after multiplying it by the number of times that number appears in the right list.

    int similarity_score = 0;
    // struct node* map = {NULL};

    for(int row = 0; row < size; row++){
        int counter = 0;
        int numL = left[row]; // L: 56634  
        printf("%d\n",left[row]); 
        for(int k = 0; k < size; k++){
            int numR = right[k]; //R: 53662
            if(numL == numR){
                counter++;
                printf("Counter: %d\n",counter);
            }
        }
        similarity_score += numL * counter;

    
    }
    printf("Sum of Similarity score: %d\n", similarity_score);

    return 0;

}
