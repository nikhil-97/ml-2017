#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMCLASS 7
#define ATTRIBS 16


char datafile[] = "./data/zoo.data";
FILE *dataset;

void process_input(char *train_data,char *data){
    char *token = strtok(data,",");
    int i=0;
    while(token){
        token = strtok(NULL,","); //
        if(token==NULL) break; //Without this line, code gets paused here.
        train_data[i++] = *token;
        }
    return;
    }


int main(){

    //Initialize specific boundaries
    char *specific_boundaries[NUMCLASS];
    //char specific_boundaries[NUMCLASS][16];
    for(int s=0;s<NUMCLASS;s++){
        specific_boundaries[s] = calloc(16,sizeof *specific_boundaries[s]);
        for(int k=0;k<16;k++){specific_boundaries[s][k] = (char)'o';}}

    for(int s=0;s<NUMCLASS;s++){
        for(int k=0;k<16;k++){printf("%c ",specific_boundaries[s][k]);}
        printf("\n");}

    //Initialize general boundaries
    char **general_boundaries[NUMCLASS] ;
    //general_boundaries = (char ***)malloc(NUMCLASS*sizeof(char **));
    for(int g=0;g<NUMCLASS;g++){
        general_boundaries[g] = calloc(16,sizeof *general_boundaries[g]);
        for(int l=0;l<16;l++){general_boundaries[g][l] = (char)'?';}}
    for(int s=0;s<NUMCLASS;s++){
        for(int k=0;k<16;k++){printf("%c ",general_boundaries[s][k]);}
        printf("\n");}


    //Reading the data file
    dataset = fopen(datafile,"r");
    if(dataset==NULL){
        fprintf(stderr,"Cannot open data file");
        exit(1);}

    //Parsing the data file to get individual strings line by line
    char data[50];
    char *train_data = calloc(17,sizeof(char));
    while(fgets(data,50,dataset)!=NULL){
        //printf("Data now : %s\n",data);
        process_input(train_data,data);
        for(int j=0;j<17;j++) {printf("%c ",train_data[j]);}printf("\n");
        char train_class = train_data[16];
        printf("%c\n",train_class);
    }
    free(train_data);
    fclose(dataset);

    return 0;
}
