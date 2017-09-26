#include "versionspace.h"

char datafile[] = "./data/zoo2.data";
FILE *dataset;

//char data[50];
//char train_data[17] ={'0'};

int main()
{
    //Reading the data file
    //Opening the data file is the first function because without that,
    //it's useless to initialize anything else

    dataset = fopen(datafile, "r");
    if(dataset == NULL)
    {
        fprintf(stderr, "Cannot open data file");
        exit(EXIT_FAILURE);
    }

    int s, g, k;
    // Initialize specific boundaries
    for(s = 0; s < NUM_CLASS; s++)
    {
        specific_boundary[s] = (char *)calloc(ATTRIBS, sizeof(char));
        for(k = 0; k < ATTRIBS; k++) specific_boundary[s][k] = 'o'; //237 is ASCII value for phi
    }

    for(g=0; g<NUM_CLASS;g++)  {
        general_boundaries[g] = (ghypoPtr)malloc(sizeof(ghypo));
        memset(general_boundaries[g]->hypothesis,'?',ATTRIBS*sizeof(char));
        general_boundaries[g]->next = NULL;
    }

    char data[50];
    char *train_data = calloc(17,sizeof(char));

    // The main loop
    //Parsing the data file to get individual strings line by line
    while(fgets(data, 50, dataset) != NULL) {
        printf("Data : %s\n",data);
        parse_data(train_data,data);
        build_version_space(train_data);
    }

    save_vs_to_file();

    for(s = 0; s < NUM_CLASS; s++) free(specific_boundary[s]);

    for(g = 0; g < NUM_CLASS; g++)
    {
        ghypoPtr tmp;
        ghypoPtr head = general_boundaries[g];
        while (head != NULL)
        {
            tmp = head;
            head = head->next;
            free(tmp);
        }
    }

    free(train_data);
    fclose(dataset);
    return 0;
}
