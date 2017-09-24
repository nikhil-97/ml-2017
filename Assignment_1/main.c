#include "versionspace.h"

char datafile[] = "./data/zoo.data";
FILE *dataset;

int main()
{
    int s, g, k, l;
    for(s = 0; s < NUM_CLASS; s++)
    {
        specific_boundary[s] = (char *)calloc(ATTRIBS, sizeof(char));
        for(k = 0; k < ATTRIBS; k++) specific_boundary[s][k] = 237;
    }

    for(g = 0; g < NUM_CLASS; g++)
    {
        general_boundary[g] = (char **)calloc(1, sizeof(char *));
        general_boundary[g][0] = (char *)calloc(ATTRIBS, sizeof(char));
        for(l = 0; l < ATTRIBS; l++) general_boundary[g][0][l] = '?';
    }

    //Reading the data file
    dataset = fopen(datafile, "r");
    if(dataset == NULL)
    {
        fprintf(stderr, "Cannot open data file");
        exit(1);
    }

    //Parsing the data file to get individual strings line by line
    char data[50];
    while(fgets(data, 50, dataset) != NULL) build_version_space(data, general_boundary, specific_boundary);
    fclose(dataset);
    for(g = 0; g < NUM_CLASS; g++)
    {
        free(general_boundary[g][0]);
        free(general_boundary[g]);
    }
    for(s = 0; s < NUM_CLASS; s++) free(specific_boundary[s]);
    return 0;
}
