#include "ParseQA.h"

int ParsePrologFactToGraph(ND** graph, char *fact)
{
    char *term  = (char*) calloc(41, sizeof(char)); //allocate space for items
    char *label = (char*) calloc(41, sizeof(char));
    char *term2 = (char*) calloc(41, sizeof(char));
    char *ver = (char*) calloc(2, sizeof(char));
    /*
    %40[A-z0-9_] - reads and store every letter, number or underscore up to 40 characters
    %1[)]%1[.] - ensures that the last two characters read are ")."
    %*[^\n] - reads and discards everything until the end of line (clean buffer)
    parses line into an valid form, something like  >> label(term, term2). <<
    */
    if(sscanf(fact, "%40[A-Za-z0-9_](%40[A-Za-z0-9_], %40[A-Za-z0-9_]%1[)]%1[.]%*[^\n]", label, term, term2, ver, ver) != 5 ||
       !islower(label[0]) || isupper(term[0]) || term[0] == '_' || isupper(term2[0]) || term2[0] == '_')
    {
        printf("Formato invalido! Tente novamente: \n");
        return 1;
    }
    insertRelation(term, label, term2, &(*graph)); //insert relation on graph
    return 0;
}

int ParsePrologToGraph(ND** graph, char *filename)
{
    int total = 0;
    int success = 0;
    FILE *file = fopen ( filename, "r" );
    if ( file != NULL )
    {
        char buffer[128];
        while(fgets ( buffer, sizeof(buffer), file ) != NULL){ //read each line from file
          if(!ParsePrologFactToGraph(&(*graph), buffer)) success++;
          total++;
        }
        printf("Arquivo \"%s\" aberto com sucesso! Arestas inseridas: %d/%d\n\n", filename, success, total);
    }
    else
    {
        perror ( filename ); /* why didn't the file open? */
    }
    return 0;
}

S* getSentenceByProlog(char* line){
    char *term  = (char*) calloc(41, sizeof(char));
    char *label = (char*) calloc(41, sizeof(char));
    char *term2 = (char*) calloc(41, sizeof(char));
    char *ver = (char*) calloc(2, sizeof(char));
    /*
    parses one received prolog-like line to a sentence structure
    %40[A-z0-9_] - reads and store every letter, number or underscore up to 40 characters
    %1[)] - ensures that the last character read is ")"
    %*[^\n] - reads and discards everything until the end of line (clean buffer)
    */
     if(sscanf(line, "%40[A-Za-z0-9_](%40[A-Za-z0-9_], %40[A-Za-z0-9_]%1[)]*[^\n]", label, term, term2, ver) != 4 ||
       !islower(label[0]) || term[0] == '_' || term2[0] == '_') return NULL;
    return getSentenceByLabelAndTerms(label, term, term2);
}

