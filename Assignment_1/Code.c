#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char datafile[] = "zoo.data";
FILE *dataset;

int main(){
    printf("Hello\n");
    dataset = fopen(datafile,"r");
    if(dataset==NULL){
        fprintf(stderr,"Cannot open data file");
        exit(1);
    }
    char data[50];
    while(fgets(data,50,dataset)!=NULL){
        printf("%s %d\n",data,strlen(data));
    }
    fclose(dataset);

    return 0;
}
