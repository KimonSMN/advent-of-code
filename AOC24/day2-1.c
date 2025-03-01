#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LINE_BUFFER_SIZE 100  // For reading lines from the file
#define MAX_TOKENS 100        // Maximum numbers per line
#define MAX_SIZE 1000         // Maximum number of lines

struct array {
    int items[MAX_TOKENS];
    int size;
};

// Returns the absolute difference between two numbers.
int findDistance(int x, int y) {
    return abs(x - y);
}

// Checks if a sequence (given as an array of ints with length n) is safe.
// A safe sequence is either strictly increasing or strictly decreasing,
// and every adjacent difference is between 1 and 3.
bool checkSequenceSafe(const int *seq, int n) {
    if(n < 2)
        return false;
    bool increasing = (seq[1] > seq[0]);
    bool decreasing = (seq[1] < seq[0]);
    if(!increasing && !decreasing)
        return false;
    for (int i = 0; i < n - 1; i++) {
        int diff = findDistance(seq[i], seq[i+1]);
        if(diff < 1 || diff > 3)
            return false;
        if(increasing && seq[i+1] <= seq[i])
            return false;
        if(decreasing && seq[i+1] >= seq[i])
            return false;
    }
    return true;
}

// Try removing one element from the report to see if a single removal
// can fix exactly one violation. We assume that if there is exactly one
// violation, then one of the two elements in the violating adjacent pair is problematic.
// We try removing the first element of that pair, and if that doesn't work,
// we try removing the second.
bool trySingleRemoval(struct array *report) {
    int violationCount = 0;
    int violationIndex = -1; // index of the first element in the problematic adjacent pair

    if(report->size < 2)
        return false;
    bool increasing = (report->items[1] > report->items[0]);
    bool decreasing = (report->items[1] < report->items[0]);
    if(!increasing && !decreasing)
        return false;

    // Count violations over all adjacent pairs.
    // (A violation is either a gap outside 1–3 or a break in the monotonic trend.)
    for (int i = 0; i < report->size - 1; i++) {
        int diff = findDistance(report->items[i], report->items[i+1]);
        if(diff < 1 || diff > 3) {
            violationCount++;
            if(violationIndex == -1)
                violationIndex = i;
        }
        if(increasing && report->items[i+1] <= report->items[i]) {
            violationCount++;
            if(violationIndex == -1)
                violationIndex = i;
        }
        if(decreasing && report->items[i+1] >= report->items[i]) {
            violationCount++;
            if(violationIndex == -1)
                violationIndex = i;
        }
    }
    
    // Only proceed if exactly one violation (from one problematic element) is present.
    if(violationCount != 1)
        return false;

    int newSize = report->size - 1;
    int temp[MAX_TOKENS];

    // Option 1: Remove the first element of the problematic pair.
    {
        int k = 0;
        for (int i = 0; i < report->size; i++) {
            if(i == violationIndex)
                continue;
            temp[k++] = report->items[i];
        }
        if(checkSequenceSafe(temp, newSize)) {
            // Update the report.
            for(int i = 0; i < newSize; i++){
                report->items[i] = temp[i];
            }
            report->size = newSize;
            return true;
        }
    }

    // Option 2: Remove the second element of the problematic pair.
    {
        int k = 0;
        for (int i = 0; i < report->size; i++) {
            if(i == violationIndex + 1)
                continue;
            temp[k++] = report->items[i];
        }
        if(checkSequenceSafe(temp, newSize)) {
            // Update the report.
            for(int i = 0; i < newSize; i++){
                report->items[i] = temp[i];
            }
            report->size = newSize;
            return true;
        }
    }

    return false;
}

// Determines if a report is safe, either as originally read or by allowing
// a single removal (if exactly one problematic element is present).
bool isReportSafe(struct array *report) {
    if(checkSequenceSafe(report->items, report->size))
        return true;
    return trySingleRemoval(report);
}

int main() {
    FILE *fp = fopen("../puzzleInput/day2.txt", "r");
    if(fp == NULL) {
        perror("Error opening file");
        return 1;
    }
    
    char line[LINE_BUFFER_SIZE];
    // Allocate memory for up to MAX_SIZE reports.
    struct array *arr = malloc(sizeof(struct array) * MAX_SIZE);
    if(!arr) {
        perror("Memory allocation error");
        fclose(fp);
        return 1;
    }
    
    int arr_index = 0;
    while(fgets(line, sizeof(line), fp) && arr_index < MAX_SIZE) {
        line[strcspn(line, "\n")] = '\0';
        int index = 0;
        char *token = strtok(line, " \t");
        while(token != NULL && index < MAX_TOKENS) {
            arr[arr_index].items[index] = atoi(token);
            index++;
            token = strtok(NULL, " \t");
        }
        arr[arr_index].size = index;
        arr_index++;
    }
    fclose(fp);
    
    int safeCount = 0;
    for(int i = 0; i < arr_index; i++) {
        // Skip reports that are too short to decide.
        if(arr[i].size < 2)
            continue;
        if(isReportSafe(&arr[i]))
            safeCount++;
    }
    
    printf("%d reports were Safe\n", safeCount);
    
    // // (Optional) Print out the (possibly modified) reports.
    // for (int i = 0; i < arr_index; i++) {
    //     printf("Report[%d] (size=%d): ", i, arr[i].size);
    //     for (int j = 0; j < arr[i].size; j++) {
    //         printf("%d ", arr[i].items[j]);
    //     }
    //     printf("\n");
    // }
    
    free(arr);
    return 0;
}
