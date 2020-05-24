#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>
#include <stdio.h>

struct relationedTerm;

typedef struct node {
    char* term;
    struct relationedTerms* relations;
    struct node* next;
}ND;

typedef struct relationedTerms {
    char* label;
    struct node* node1;
    struct node* node2;
    struct node* next;
} RT;

typedef struct relationsList {
    struct relationedTerms* relation;
    struct relationsList* next;
} RTL;

ND* initializeGraph();

ND* insertNode(char* term, ND** graph);

RT* insertRelation(char *term, char *label, char *relationedTerm, ND** graph);

ND* getCopyOfGraph(ND* graph);

void printGraph(ND* graph);

void printRelations(RTL* relations);

#endif // GRAPH_H
