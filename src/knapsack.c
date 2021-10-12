#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int x, int y){   //returns maximum number out of two numbers
    if(x > y){
        return x;
    }
    else{
        return y;
    }
}

void printItems(int weightCap, int* weight, int* value, char** names, int len, int** knap){

    int* ind = (int*)malloc(len*sizeof(int));   //array for name indices
    
    //initialize with 0s
    for(int i = 0; i <= len; i++) {
        knap[i][0] = 0;
    }
    for(int i = 0; i <= weightCap; i++) {
        knap[0][i] = 0;
    }

    //fill knapsack array with values
    for(int i = 1; i <= len; i++){
        for(int j = 1; j <=weightCap; j++){
            if(weight[i-1] <= j){
                knap[i][j] = max(knap[i-1][j], value[i-1] + knap[i-1][j-weight[i-1]]);
            }
            else{
                knap[i][j] = knap[i-1][j];
            }
        }
    }

    int result = knap[len][weightCap];   //final number
    int res2 = knap[len][weightCap];   //final number to be adjusted
    int weight2 = weightCap;   //adjusted weightcap
    int x = 0;   //index counter for int array
    
    //store name indices
    for(int i = len; i > 0 && res2 > 0; i--){ 
        if(res2 != knap[i-1][weight2]){

            ind[x] = i-1;
            x++;
            
            //adjust adjusted result and adjusted weight cap
            res2 = res2 - value[i-1];
            weight2 = weight2-weight[i-1];
        }
    }

    //print out the items
    for(int i = x-1; i >= 0; i--){
        printf("%s\n",names[ind[i]]);
    }
    
    printf("%d / %d", result,weightCap-weight2);   //value / weight
    
    free(ind);   //free index array
    
}



//name, weight, value
int main(int argc, char* argv[]){
    
    if(argc != 3){   //not 3 arguments
        printf("error");
        return EXIT_FAILURE;
    }
    if(atoi(argv[1]) < 0){   //0 or negative weight value
        printf("error");
        return EXIT_FAILURE;
    }

    FILE* file = fopen(argv[2], "r");
    if(file == NULL){   //exit if file is null
        printf("error");
        return EXIT_FAILURE;
    }

    int maxw = atoi(argv[1]);   //total weight
    

    int len;   //amount of items
    fscanf(file,"%d", &len);
    if(len <= 0 ){
        printf("error");
        return EXIT_FAILURE;
    }

    //initialize all arays
    int* values = (int*)malloc(len*sizeof(int));   //array of values
    int* weights = (int*)malloc(len*sizeof(int)); //array of weights

    char** names = (char**)malloc(len*sizeof(char*));
    for(int i = 0; i < len;i++){
        names[i] = (char*)malloc(32*sizeof(char));
    }

       
    //len by weight
    int** xd = (int**)malloc((len+1)*sizeof(int*));   //table of values
    for(int i = 0; i <= len;i++){
        xd[i] = (int*)malloc((maxw+1)*sizeof(int*));
    }

    //scan in values into arrays
    for(int i = 0; i < len; i++){

        fscanf(file, "%31s %d %d" , names[i], &weights[i], &values[i]);

        if(weights[i] < 0 || values[i] < 0){   //exit if negative
            printf("error");
            return EXIT_FAILURE;
        }
    }

    //print!
    printItems(maxw,weights,values,names,len,xd);

    //free arrays
    free(values);
    free(weights);
    for(int i = 0; i < len; i++){
        free(names[i]);
    }
    free(names);

    for(int i = 0; i < len+1; i++){
        free(xd[i]);
    }
    free(xd);

    fclose(file);   //close file

    return EXIT_SUCCESS;
}