#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_CLASS 7
#define ATTRIBS 16

typedef struct node {
    char hypothesis[16];
    struct node* next;
    }ghypo;

typedef ghypo* ghypoPtr;


int no_concept[NUM_CLASS] = {0};

//Initialize specific boundary
char *specific_boundary[NUM_CLASS]; //char specific_boundary[NUM_CLASS][16];

//Initialize general boundary
ghypoPtr general_boundaries[NUM_CLASS];
int no_of_gb[NUM_CLASS]={1,1,1,1,1,1,1};
int type = 0;
int i=0;

void parse_data(char *train_data,char *data){
    //This function parses the string data from the dataset file and tokenizes it
    //Each tokenized string is stored as char in train_data
    char *token = strtok(data,",");
    int t=0;
    while(token){
        token = strtok(NULL,",");
        if(token==NULL) break; //Without this line, code gets paused here.
        train_data[t++] = *token;
        }
    return;
    }

int consistent(char *array2){
    return 0;
}

void build_general_boundary(int type, char *train_data)
{
    if(type == train_data[16]) // +ve
    {
        int x;
        for(x=0; x<no_of_gb[type-1]; x++)
        {

            }
        }

    else // -ve
    {
        int x;
        for(x=0; x<no_of_gb[type-1]; x++)
        {
/*            if(general_boundary[type-1][x] != NULL && !consistent(general_boundary[type-1][x], train_data))
            {
                free(general_boundary[type-1][x]);
                general_boundary[type-1][x] = NULL;
            }*/
        }
    }
}

void build_specific_boundary(int type, char *train_data)
{
    if(type == train_data[16]) // +ve
    {
        int x;
        for(x=0; x<ATTRIBS; x++)
        {
            if(specific_boundary[type-1][x] == 237) specific_boundary[type-1][x] = train_data[x];
            else if(specific_boundary[type-1][x] != train_data[x]) specific_boundary[type-1][x] = '?';
        }
    }
    else // -ve
    {
//        if(!consistent(specific_boundary[type-1], train_data)) no_concept[type-1] = 1;
    }
}

void build_version_space(char *train_data)
{
    type = train_data[16];
    if(no_concept[type-1] >= 1) return;

    for(i=0; i<NUM_CLASS; i++) // here i is type
    {
        if(i+1==type) // +ve example
        {
            build_general_boundary(i+1, train_data);
            build_specific_boundary(i+1, train_data);
        }
        else // -ve example
        {
            build_specific_boundary(i+1, train_data);
            build_general_boundary(i+1, train_data);
        }
    }
}
