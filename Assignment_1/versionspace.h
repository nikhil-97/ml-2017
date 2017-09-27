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
//int no_of_gb[NUM_CLASS]={1,1,1,1,1,1,1};
int type = 0;
int i=0;
int class_type = 1;
char all_possible_values[NUM_CLASS][7];
all_possible_values[0]

void print_general_boundary(){
for(int g = 0; g < NUM_CLASS; g++)
    {
        ghypoPtr head = general_boundaries[g];
        printf("g = %d\n",g);
        while (head != NULL)
        {
            for(int h=0;h<ATTRIBS;h++){
                printf("%c ",head->hypothesis[h]);}
            printf(",");
            head = head->next;
        }
        printf(";\n");
    }
    }
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
    int value = (type == train_data[ATTRIBS]-'0');
    for(int c=0; c<ATTRIBS; c++){
        if(!(hypothesis[c] == '?' || hypothesis[c] == train_data[i]) || (value && hypothesis[c]=='o')) return !value;}
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
    //current = current->next;
    free(current);
}

void go_to_next_level(int type, char *train_data, ghypoPtr prev, ghypoPtr current)
{
    printf("Going to next level\n");
    int i;//, j;
    for(i=0; i<ATTRIBS; i++)
    {
        if(current->hypothesis[i] == '?' && specific_boundary[type-1][i] != '?')
        {
            ghypoPtr newHypo = (ghypoPtr)malloc(sizeof(ghypo));
            //for(int j=0; j<ATTRIBS; j++) newHypo->hypothesis[j] = current->hypothesis[j];
            memcpy(newHypo->hypothesis,current->hypothesis,sizeof(newHypo->hypothesis));
            newHypo->hypothesis[i] = specific_boundary[type-1][i];
            if(!consistent(type,newHypo->hypothesis,train_data)){
                free(newHypo);
                continue;
            }

            if(prev == NULL) general_boundaries[type-1] = newHypo;
            else prev->next = newHypo;
            newHypo->next = current;
            prev = newHypo;
        }
    }
    if(prev == NULL) general_boundaries[type-1] = current->next;
    else prev->next = current->next;
    //current = current->next;
    free(current);
}

void build_general_boundary(int type, char *train_data)
{
    printf("Building general boundary\n");
    ghypoPtr current = general_boundaries[type-1], prev = NULL;
    //for all hypotheses i.e. iterate through linked list
    //check consistency for all hypotheses
    //remove inconsistent ones
    while(current!=NULL){
        if(!consistent(type, current->hypothesis,train_data)){
            if(type == train_data[ATTRIBS]-'0'){ //+ve
                remove_hypothesis(type, prev, current);}
            else go_to_next_level(type, train_data, prev, current); //-ve
        }
        else{
            prev = current;
            //current = current->next;
        }
        current = current->next;
        }
    //}

    print_general_boundary();
}

void build_specific_boundary(int type, char *train_data)
{
    printf("Building specific boundary\n");
    if(type == train_data[ATTRIBS]-'0') // +ve
    {
        int x;
        for(x=0; x<ATTRIBS; x++)
        {
            if(specific_boundary[type-1][x] == 'o') specific_boundary[type-1][x] = train_data[x];
            else if(specific_boundary[type-1][x] != train_data[x]) specific_boundary[type-1][x] = '?';
            printf("%c ",specific_boundary[type-1][x]);
        }
        printf("\n");
    }
    else // -ve
    {
        //TODO
        //if(!consistent(type, specific_boundary[type-1], train_data)) no_concept[type-1] = 1;
    }
}

void remove_unnecessary_gb()
{
    int p;
    for(p=0; p<NUM_CLASS; p++)
    {
        //general_boundaries[0] is NULL here
        ghypoPtr left_node = general_boundaries[p], right_node , prev = NULL;
        if(left_node==NULL) continue;
        right_node = left_node->next;
        while (left_node != NULL && left_node->next != NULL)
        {
            right_node = left_node->next;
            while (right_node != NULL)
            {
                //getting some error here
                if(subsetOf(left_node, right_node))
                {
                     remove_hypothesis(p+1, prev, left_node);
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
    type = train_data[ATTRIBS] - '0';//This is to make type as int
    //train_data is of type int, train_data[ATTRIBS] is char
    //TODO
    //if(no_concept[type-1] >= 1) return;

    for(class_type=1; class_type<=NUM_CLASS; class_type++) // here i is type
    {
        printf("Training for class %d\n",class_type);
        if(class_type==type) // +ve example
        {
            build_general_boundary(class_type, train_data);
            build_specific_boundary(class_type, train_data);
        }
        else // -ve example
        {

            build_specific_boundary(class_type, train_data);
            build_general_boundary(class_type, train_data);
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
        for(int i=0;i<ATTRIBS;i++){
        printf("%c ", specific_boundary[x][i]);
        }
    printf("\n");
    }
    printf("General Boundary\n");
    print_general_boundary();
    return;
}
