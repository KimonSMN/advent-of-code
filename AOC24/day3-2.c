#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


/* 

flag = true;

if(ptr < dontPtr){
    flag is true 
} 

if(ptr > dontPtr) AND (ptr < doPtr){
    flag false;
}

if (ptr > doPtr) AND (doPtr > dontPtr){
    flag is true
    dontPtr += 7
}

if(dontPtr > doPtr){
    doPtr += 4

}



*/



void findMul(char *line, int *res, bool *flag){
    int x = 0,y = 0;
    char bufferX[4096];
    char bufferY[4096];
    char *ptr = line; 
    char *dontPtr = strstr(line, "don't()");
    char *doPtr = strstr(line, "do()");

    while((ptr = strstr(ptr, "mul(")) != NULL){ // while we find same string in line as "mul("
        // dontPtr = strstr(dontPtr, "don't()"); // we find "don't()"
        // doPtr = strstr(doPtr, "do()"); // we find "do()"
        if (dontPtr == NULL) dontPtr = ptr + strlen(ptr); // set it far away if not found
        if (doPtr == NULL) doPtr = ptr + strlen(ptr);     // set it far away if not found

        if(ptr < dontPtr){
            *flag = true;
        } 
        
        if((ptr > dontPtr) && (ptr < doPtr)){
            *flag = false;
        }
        
        if ((ptr > doPtr) && (doPtr > dontPtr)){
            *flag = true;
            dontPtr = strstr(dontPtr + 7, "don't()"); // find next occurrence safely
        }
        
        if(dontPtr > doPtr){
            doPtr += 4;
        }
            
        // if flag is true get the mul...
        if(sscanf(ptr, "mul(%d, %d)", &x, &y) == 2 && *flag){    // pass the values to x,y 
        // convert int to string
        sprintf(bufferX, "%d", x);
            sprintf(bufferY, "%d", y);

            ptr += 4 + strlen(bufferX) + strlen(bufferY) + 1; // move the pointer to the closing bracket
            if(*ptr == ')'){   // if curr == ')'
                printf("mul(%s,%s)\n", bufferX, bufferY);
                *res += x * y; // Update result
                ptr -= 4 + strlen(bufferX) + strlen(bufferY) + 1; // move the pointer to the closing bracket
            }             
        }
        ptr += 4; // search further
    }

}


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
    int res = 0;
    bool flag = true;
    while(fgets(line, sizeof(line), fp)){ // for every line of file.
        findMul(line, &res, &flag);
    }

    printf("Result is :%d\n", res);//184511516
    fclose(fp);


    return 0;
}