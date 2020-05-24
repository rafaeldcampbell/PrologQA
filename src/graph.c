#include "graph.h"

ND* initializeGraph(){
    ND *graph = NULL;
    return graph;
}

ND* insertNode(char* term, ND** graph){
    if(*graph == NULL){ //if its already empty, create the very first element
        *graph = (ND*) calloc(1, sizeof(ND));
        (*graph)->term = term;
        (*graph)->relations = NULL;
        (*graph)->next = NULL;
        return *graph;
    }
    ND** aux = graph;
    while((*aux)->next != NULL) aux = &((*aux)->next); //if its not empty, it goes to the last element and insert a new node
    ND* newNode = (ND*) calloc(1, sizeof(ND));
    newNode->term = term;
    newNode->relations = NULL;
    newNode->next = NULL;
    (*aux)->next = newNode;
    free(aux); aux = NULL;
    return newNode;
}

RT* insertRelation(char *term, char *label, char *relationedTerm, ND** graph){
    ND **aux = graph, *termNode = NULL, *relationedTermNode = NULL;
    while((*aux) && (!termNode || !relationedTermNode)){
        if(!strcmp((*aux)->term, term)){ //set the first term node if found that
            termNode = *aux;
        }
        if(!strcmp((*aux)->term, relationedTerm)){ //set the relationedTerm node
            relationedTermNode = *aux;
        }
        aux = &((*aux)->next);
    }
    if(termNode == NULL){
        termNode = insertNode(term, &(*graph)); //if the term is not in the graph, insert it
    }
    if(relationedTermNode == NULL){
        relationedTermNode = insertNode(relationedTerm, &(*graph)); //if the relationedTerm is not in the graph, insert it
    }
    RT* relation1 = (RT*) malloc(sizeof(RT)); //creating the relation to insert in the termNode
    relation1->label = label;
    relation1->next = NULL;
    relation1->node1 = termNode;
    relation1->node2 = relationedTermNode;

    RT* relation2 = (RT*) malloc(sizeof(RT)); //creating the relation to insert in the termNode
    relation2->label = label;
    relation2->next = NULL;
    relation2->node1 = termNode;
    relation2->node2 = relationedTermNode;

    if(termNode->relations == NULL){ //if its the very first relation of the termNode
        termNode->relations = relation1;
    }else{ //if its not, goes till the last element and insert it
        RT* auxRelation = termNode->relations;
        while(auxRelation->next) auxRelation = auxRelation->next;
        auxRelation->next = relation1;
    }

    if(relationedTermNode->relations == NULL){ //if its the first element of relationedTerm node
            relationedTermNode->relations = relation2;
    }else{ //if its not, goes till the last element and insert it
        RT* auxRelationedRelation = relationedTermNode->relations;
        while(auxRelationedRelation->next) auxRelationedRelation = auxRelationedRelation->next;
        auxRelationedRelation->next = relation2;
    }
    free(aux); aux = NULL;
    return relation1;
}

ND* getCopyOfGraph(ND* graph){
    ND *headOfList, *newNDelement = (ND*) malloc(sizeof(ND));
    headOfList = newNDelement;
    ND* aux = graph;
    while(aux){ //for each node on graph, copy it to other memory space
        newNDelement->term = aux->term;
        newNDelement->relations = aux->relations;
        if(aux->next){
            newNDelement->next = (ND*) malloc(sizeof(ND));
            newNDelement = newNDelement->next;
        }else{
            newNDelement->next = NULL;
            newNDelement = NULL;
        }
        aux = aux->next;
    }
    return headOfList; //return the copy
}

void printGraph(ND* graph){
    if(graph == NULL){ printf("Grafo vazio!\n");}
    ND* aux = graph;
    RT* auxRelation;
    while(aux){
        printf("%s:\n", aux->term); //prints the node
        auxRelation = aux->relations;
        while(auxRelation != NULL){ //prints all relation of current node
            printf("    %s --%s--> %s\n", auxRelation->node1->term, auxRelation->label, auxRelation->node2->term);
            auxRelation = auxRelation->next;
        }
        printf("\n");
        aux = aux->next;
    }
    free(aux); aux = NULL; free(auxRelation); auxRelation = NULL;
}

void printRelations(RTL* relations){
    if(relations == NULL) printf("False\n");
    RTL* aux = relations;
    while(aux){ //print all relations
        printf("%s --%s--> %s\n", aux->relation->node1->term, aux->relation->label, aux->relation->node2->term);
        aux = aux->next;
    }
    free(aux); aux = NULL;
    printf("\n\n");
}
