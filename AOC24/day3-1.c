#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


int main(){
    FILE *fp = fopen("../puzzleInput/day3.txt","r");
    if(!fp){
        perror("Error opening file");
        return 1;
    }
    fseek(fp, 0, SEEK_END);
    int len = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    char line[4096];
    int x = 0,y = 0;
    int res = 0;
    char bufferX[4096];
    char bufferY[4096];
    while(fgets(line, sizeof(line), fp)){ // for every line of file.
        char *ptr = line; // starts at 0, ptr -> line
        while((ptr = strstr(ptr, "mul(")) != NULL){ // while we find same string in line as "mul("
            if(sscanf(ptr, "mul(%d, %d)", &x, &y) == 2){    // pass the values to x,y 
                // convert int to string
                sprintf(bufferX, "%d", x);
                sprintf(bufferY, "%d", y);

                ptr += 4 + strlen(bufferX) + strlen(bufferY) + 1; // move the pointer to the closing bracket
                char first = *ptr;  // if curr == ')'
                if(first == ')'){
                    printf("mul(%s,%s)\n", bufferX, bufferY);
                    res += x * y;
                    ptr -= 4 + strlen(bufferX) + strlen(bufferY) + 1; // go back to original ptr
                }             
            }
            ptr += 4; // search further
        }
    }
    

    printf("Result is :%d\n", res);//184511516
    fclose(fp);


    return 0;
}