#ifndef SENTENCE_H
#define SENTENCE_H
#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

typedef struct sentence {
    char* label;
    char* term1;
    char* term2;
} S;

typedef struct sentenceList {
    struct sentence* sentence;
    struct sentenceList* next;
} SL;

typedef struct term {
    char* identifier;
    ND* associatedGraph;
} T;

typedef struct termList {
    struct term* term;
    struct termList* next;
} TL;

void insertSentenceInSentenceList(S* sentence, SL** sentenceList);

void insertTermInTermList(T* term, TL** termList);

void removeNodeFromAssociatedGraph(char* identifier, ND** associatedGraph);

RTL* getRelationsBySentence(S* sentence, ND* graph);

T* getTermFromIdentifier(char* identifier, ND* graph);

S* getSentenceByLabelAndTerms(char* label, char* term1, char* term2);

int testIfTermListIsValid(TL* termList);

TL* getNewTermListByTakeOneNodeForAnIdentifier(char* identifier, char* nodeTerm, TL* termList);

T* getTermFromTermListByIdentifier(char *identifier, TL** termList, ND* graph);

int testTermListForSentence(TL** termList, S* sentence, ND* graph);

int testTermListForSentenceList(TL** termList, SL* sentenceList, ND* graph);

int testSentenceForRelation(RT* relation, S* sentence);

void printSentenceList(SL* sentenceList);

void printTermList(TL* termList);

void printPossibleValuesForSearch(TL* termList);

#endif // SENTENCE_H

