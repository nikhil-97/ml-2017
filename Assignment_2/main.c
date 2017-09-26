#include <stdio.h>
#include <stdlibh.h>
#include <string.h>

char datafile[] = "./data/zoo.data";
FILE *dataset;

int main(){
        //Reading the data file
        //Opening the data file is the first function because without that,
        //it's useless to initialize anything else
    dataset = fopen(datafile, "r");
    if(dataset == NULL)
    {
        fprintf(stderr, "Cannot open data file");
        exit(EXIT_FAILURE);
    }

    char data[1024];
    while(fgets(data, 1024, dataset) != NULL) {
        printf("Data : %s",data);
        read_data();
        build_tree_ID3();
    }
    reduced_error_pruning();
    random_forest();
    return 0;
}
