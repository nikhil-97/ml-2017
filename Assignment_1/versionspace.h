#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUM_CLASS 7
#define ATTRIBS 16

typedef struct node {
    char hypothesis[ATTRIBS];
    struct node *next;
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

int consistent(int type, char *hypothesis, char *train_data){
    int value = (type == train_data[16]);
    for(i=0; i<ATTRIBS; i++) if(!(hypothesis[i] == '?' || hypothesis[i] == train_data[i])) return !value;
    return value;
}

int subsetOf(ghypoPtr h1, ghypoPtr h2){ // h2 is more general than h2 if returned 1
    for(i=0; i<ATTRIBS; i++) if(h2->hypothesis[i] == '?' && h1->hypothesis[i] != h2->hypothesis[i]) return 0;
    return 1;
}

void remove_hypothesis(int type, ghypoPtr prev, ghypoPtr current)
{
    if(prev == NULL) general_boundaries[type-1] = current->next;
    else prev->next = current->next;
    free(current);
}

void go_to_next_level(int type, ghypoPtr prev, ghypoPtr current)
{
    int i, j;
    for(i=0; i<ATTRIBS; i++)
    {
        if(current->hypothesis[i] == '?' && specific_boundary[type-1][i] != '?')
        {
            ghypoPtr newHypo = (ghypoPtr)calloc(ATTRIBS, sizeof(ghypo));
            for(j=0; j<ATTRIBS; j++) newHypo->hypothesis[j] = current->hypothesis[j];
            newHypo->hypothesis[i] = specific_boundary[type-1][i];
            if(prev == NULL) general_boundaries[type-1] = newHypo;
            else prev->next = newHypo;
            newHypo->next = current;
            prev = newHypo;
        }
    }
    if(prev == NULL) general_boundaries[type-1] = current->next;
    else prev->next = current->next;
    free(current);
}

void build_general_boundary(int type, char *train_data)
{
    if(type == train_data[16]) // +ve
    {
        //for all hypotheses i.e. iterate through linked list
        //check consistency for all hypotheses
        //remove inconsistent ones
        ghypoPtr current = general_boundaries[type-1], prev = NULL;
        while(current!=NULL){
            printf("Iterating hypothesis list\n");
            if(!consistent(type, current->hypothesis,train_data)){
                remove_hypothesis(type, prev, current);
            }
            prev = current;
            current = current->next;
        }
    }

    else // -ve
    {
        ghypoPtr current = general_boundaries[type-1], prev = NULL;
        while(current!=NULL){
            printf("Iterating hypothesis list\n");
            if(!consistent(type, current->hypothesis,train_data)){
                go_to_next_level(type, prev, current);
            }
            prev = current;
            current = current->next;
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
        if(!consistent(type, specific_boundary[type-1], train_data)) no_concept[type-1] = 1;
    }
}

void remove_unnecessary_gb()
{
    int i;
    for(i=0; i<NUM_CLASS; i++)
    {
        ghypoPtr left_node = general_boundaries[i], right_node = general_boundaries[i]->next, prev = NULL;
        while (left_node != NULL && left_node->next != NULL)
        {
            right_node = left_node->next;
            while (right_node != NULL)
            {
                if(subsetOf(left_node, right_node))
                {
                     remove_hypothesis(i+1, prev, left_node);
                     break;
                }
                right_node = right_node->next;
            }
            prev = left_node;
            left_node = left_node->next;
        }
    }
}

void build_version_space(char *train_data)
{
    type = train_data[16];
    printf("Type = %c\n",type);
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
    remove_unnecessary_gb();
}

void save_vs_to_file()
{
    int x;
    printf("Specific Boundary\n");
    for(x=0; x<NUM_CLASS; x++)
    {
        printf("%s\n", specific_boundary[x]);
    }
    printf("General Boundary\n");
    for(x=0; x<NUM_CLASS; x++)
    {
        break;
    }
    return;
}
