#include "versionspace.h"

//datafile is the dataset to be used for training.
char datafile[] = "./data/zoo.data";
//dataset is the file pointer to the data file.
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

    int s, g;
    //Please see versionspace.h for definitions of specific_boundary and general_boundaries

    // Initialize specific boundaries to o,o,o.....
    for(s = 0; s < NUM_CLASS; s++)
    {
        specific_boundary[s] = (char *)calloc(ATTRIBS, sizeof(char));
        memset(specific_boundary[s],'o',ATTRIBS*sizeof(char));
    }

    //Initialize general boundaries to ?,?,?....

    for(g=0; g<NUM_CLASS;g++)
    {
        general_boundaries[g] = (ghypoPtr)malloc(sizeof(ghypo));
        memset(general_boundaries[g]->hypothesis,'?',ATTRIBS*sizeof(char));
        general_boundaries[g]->next = NULL;
    }

    char data[1024];
    char *train_data = calloc(ATTRIBS+1,sizeof(char)); //train_data is a char array of size ATTRIBS+1

    // The main loop
    //Parsing the data file to get individual strings line by line
    int count=1;

    while(fgets(data, 50, dataset) != NULL) {
        printf("\nData #%d : %s\n",count,data);
        count++;
        parse_data(train_data,data);
        build_version_space(train_data);
    }

    print_version_space();

    //Free all the heap memory.
    int sb,gb;


    for(sb = 0; sb < NUM_CLASS; sb++) free(specific_boundary[sb]);

    for(gb = 0; gb < NUM_CLASS; gb++)
    {
        ghypoPtr tmp;
        ghypoPtr head = general_boundaries[gb];
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
