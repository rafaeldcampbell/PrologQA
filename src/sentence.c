#include "sentence.h"

void insertSentenceInSentenceList(S* sentence, SL** sentenceList){
    if(!(*sentenceList)){ //if its the first sentence of the list
        *sentenceList = (SL*) malloc(sizeof(SL));
        (*sentenceList)->sentence = &(*sentence);
        (*sentenceList)->next = NULL;
    }else{ //if not, goes till the last one
        SL** aux = sentenceList, *newSentenceListItem;
        while((*aux)->next != NULL) aux = &((*aux)->next);
        newSentenceListItem = (SL*) malloc(sizeof(SL));
        newSentenceListItem->sentence = &(*sentence);
        newSentenceListItem->next = NULL;
        (*aux)->next = newSentenceListItem; //insert a new sentence
        free(aux); aux = NULL;
    }
}

void insertTermInTermList(T* term, TL** termList){
    if(!(*termList)){ //if its the first term of termlist
        *termList = (TL*) malloc(sizeof(TL));
        (*termList)->term = &(*term);
        (*termList)->next = NULL;
    }else{ //if not, goes till the last one
        TL** aux = termList, *newTermListItem;
        while((*aux)->next != NULL) aux = &((*aux)->next);
        newTermListItem = (TL*) malloc(sizeof(TL));
        newTermListItem->term = &(*term);
        newTermListItem->next = NULL;
        (*aux)->next = newTermListItem; //insert it
        free(aux); aux = NULL;
    }
}

/*
******THIS FUNCTION MAY BE IMPORTANT FOR FUTURE PURPOSES******

void removeNodeFromAssociatedGraph(char* identifier, ND** associatedGraph){
    if(*associatedGraph ==  NULL) return NULL;
    ND** aux = associatedGraph, *removed;
    if(!strcmp((*aux)->term, identifier)){
            removed = *aux;
            *aux = (*aux)->next;
            free(&(*removed)); free(removed); removed = NULL;
    }
    else{
        while( (*aux)->next!=NULL && strcmp( ((*aux)->next)->term, identifier) ) aux = &((*aux)->next);
        if((*aux)->next != NULL){
            removed = (*aux)->next;
            (*aux)->next = ((*aux)->next)->next;
            free(&(*removed)); free(removed); removed = NULL;
        }
    }
}*/

RTL* getRelationsBySentence(S* sentence, ND* graph){
    ND* aux = graph;
    RTL* relationList = (RTL*) malloc(sizeof(RTL));
    RTL *headOfList = relationList, *lastElement;
    char *label = sentence->label, *term1 = sentence->term1, *term2 = sentence->term2;
    while(aux){ //for each graph node
        if((!term1 && !term2) || //if both terms are null, than try the node
           (term1 && !strcmp(aux->term, term1)) || //if at least one of the terms is not null
           (term2 && !strcmp(aux->term, term2))){ //compare it to the current node term
            RT* relation = aux->relations;
            while(relation){ //for each relation
                if(( !strcmp(aux->term, relation->node1->term) ||
                    (!term1 && !strcmp(aux->term, relation->node2->term))) && //compare if the terms passed
                    (!label || !strcmp(relation->label, label)) &&            //are part of the relation
                    (!term1 || !strcmp(relation->node1->term, term1)) &&
                    (!term2 || !strcmp(relation->node2->term, term2)) ){
                    relationList->relation = relation;
                    relationList->next = (RTL*) malloc(sizeof(RTL));
                    lastElement = relationList;
                    relationList = relationList->next; //if it is, add it
                }
                relation = relation->next;
            }
        }
        aux = aux->next;
    }
    if(headOfList == relationList) return NULL;
    lastElement->next = NULL;
    free(relationList); relationList = NULL;
    return headOfList; //return all relations that proves the terms passed
}

T* getTermFromIdentifier(char* identifier, ND* graph){
    T* term = (T*) malloc(sizeof(T));
    term->identifier = identifier;
    ND* aux = graph, *associatedGraph = NULL;
    if(isupper(identifier[0])){ //if its start with capitalLetter
        associatedGraph = (ND*) malloc(sizeof(ND));
        ND *headOfGraph = associatedGraph, *lastElement;
        while(aux){
            associatedGraph->term = aux->term;                  //than its a variable, so add the whole graph
            associatedGraph->relations = aux->relations;        //to its subgraph of possible nodes values
            associatedGraph->next = (ND*) malloc(sizeof(ND));
            lastElement = associatedGraph;
            associatedGraph = associatedGraph->next;
            aux = aux->next;
        }
        if(headOfGraph == associatedGraph) term->associatedGraph = NULL;
        else term->associatedGraph = headOfGraph;
        lastElement->next = NULL;
        free(associatedGraph); associatedGraph = NULL;
    }else{ //if not
        while(aux){
            if(!strcmp(aux->term, identifier)){                 //this is a atomic term
                associatedGraph = (ND*) malloc(sizeof(ND));     //so get the relative node value for that
                associatedGraph->term = identifier;
                associatedGraph->relations = aux->relations;    //or null, if the term is not part of the graph
                associatedGraph->next = NULL;
                term->associatedGraph = associatedGraph;
                return term;
            }
            aux = aux->next;
        }
        term->associatedGraph = associatedGraph;
    }
    return term;
}

S* getSentenceByLabelAndTerms(char* label, char* term1, char* term2){
    S* sentence = (S*) malloc(sizeof(S));
    if(label && !strcmp(label, "")) sentence->label = NULL;  //gets all strings for label, term1 and term2
    else sentence->label = label;
    if(term1 && !strcmp(term1, "")) sentence->term1 = NULL; //and put them into an sentence structure
    else sentence->term1 = term1;
    if(term2 && !strcmp(term2, "")) sentence->term2 = NULL;
    else sentence->term2 = term2;
    return sentence;
}

int testIfTermListIsValid(TL* termList){
    if(termList == NULL) return 0; //if the list is NULL
    TL* aux = termList;
    while(aux){
        if(aux->term->associatedGraph == NULL) return 0; //or if any of associatedGraphs is null
        aux = aux->next;
    }
    return 1; //if not, then the termList is valid
}

TL* getNewTermListByTakeOneNodeForAnIdentifier(char* identifier, char* nodeTerm, TL* termList){
    TL* newTermList , *newTermListItem = (TL*) malloc(sizeof(TL));
    newTermList = newTermListItem;
    TL* auxcpy = termList;
    T* newTerm;
    while(auxcpy){
        newTerm = (T*) malloc(sizeof(T)); //make a copy of all the terms on termList
        newTerm->identifier = auxcpy->term->identifier;
        newTerm->associatedGraph = getCopyOfGraph(auxcpy->term->associatedGraph);
        newTermListItem->term = newTerm;
        if(auxcpy->next){
            newTermListItem->next = (TL*) malloc(sizeof(TL));
            newTermListItem = newTermListItem->next;
        }else{
            newTermListItem->next = NULL;
            newTermListItem = NULL;
        }
        auxcpy = auxcpy->next;
    }
    TL *aux = newTermList;
    while(aux && strcmp(aux->term->identifier, identifier)) aux = aux->next; //goes to the identifier term on the new list
    if(aux){
        ND* associatedGraph = (ND*) malloc(sizeof(ND));
        ND* auxGraph = aux->term->associatedGraph;
        while(auxGraph){
            if(!strcmp(auxGraph->term, nodeTerm)){ //changes the previous term's subgraph
                *(associatedGraph) = *(auxGraph); //to a new subgraph, including only the identifier node
                associatedGraph->next = NULL;
            }
            auxGraph = auxGraph->next;
        }
        aux->term->associatedGraph = associatedGraph;
    }
    return newTermList;
}

T* getTermFromTermListByIdentifier(char *identifier, TL** termList, ND* graph){
    TL** aux = termList;
    while(*aux){
        if(!strcmp((*aux)->term->identifier, identifier)) return (*aux)->term; //goes to the identifier term on termList
        aux = &((*aux)->next);                                                 //if its found, return it
    }
    T* term = getTermFromIdentifier(identifier, graph); //if not found, insert it
    if(term) insertTermInTermList(term, termList);
    return term; //and return
}

int testSentenceForRelation(RT* relation, S* sentence){
    if(sentence->label && strcmp(sentence->label, relation->label)) return 0; //if any of the elements do not coincide
    if(sentence->term1 && strcmp(sentence->term1, relation->node1->term)) return 0; //return false
    if(sentence->term2 && strcmp(sentence->term2, relation->node2->term)) return 0;
    return 1; //else return true
}

int testTermListForSentence(TL** termList, S* sentence, ND* graph){
    ND* term1Graph = getTermFromTermListByIdentifier(sentence->term1, termList, graph)->associatedGraph;
    if(!term1Graph) return 0;
    ND* term2Graph = getTermFromTermListByIdentifier(sentence->term2, termList, graph)->associatedGraph;
    if(!term2Graph) return 0; //gets the terms' subgraphs

    if(!term1Graph->next && !term2Graph->next){ //verify if the term on termList has only one options
        S* newSentence = (S*) malloc(sizeof(S));
        newSentence->label = sentence->label;
        newSentence->term1 = term1Graph->term;
        newSentence->term2 = term2Graph->term; //put them into an sentence structure
        RTL* relations = getRelationsBySentence(newSentence, graph); //and try to get any relation that proves the sentence
        if(relations){
            return 1; //relation found
        }return 0; //not found
    }else{
        printf("ERROR -- MULTIPLE VALUES FOR ONE TERM\n\n"); //if it has more than one, thats an error
        return 0;
    }

}

int testTermListForSentenceList(TL** termList, SL* sentenceList, ND* graph){
    if(sentenceList == NULL && testIfTermListIsValid(*termList)){ //if it do not has any more sentence
        printPossibleValuesForSearch(*termList);                  //and do have terms, its true
        return 1;                                                 //so it prints the chosen terms and returns true
    }
    int exists = 0;
    S* currentSentence = sentenceList->sentence;
    ND* term1Graph = getTermFromTermListByIdentifier(currentSentence->term1, termList, graph)->associatedGraph;
    if(!term1Graph) return 0;
    ND* term2Graph = getTermFromTermListByIdentifier(currentSentence->term2, termList, graph)->associatedGraph;
    if(!term2Graph) return 0; //get the current sentence's term's subgraphs

    ND *term1Graph1Aux = term1Graph, *term2GraphAux = term2Graph;
    TL *newTermListForTerm1, *newTermListForTerm1AndTerm2;
    while(term1Graph1Aux){ //tests all possible values for the first term of current sentence
        newTermListForTerm1 = getNewTermListByTakeOneNodeForAnIdentifier(currentSentence->term1, //decide who is going to be the chosen
                                                                         term1Graph1Aux->term, //for the first term on this test
                                                                         *termList);
        while(term2GraphAux){ //testes all possible values for the second term of current sentence
            TL* newTermListForTerm1AndTerm2 = getNewTermListByTakeOneNodeForAnIdentifier(currentSentence->term2, //decide who is going to be
                                                                                         term2GraphAux->term, //chosen for the second term
                                                                                         newTermListForTerm1); //on this test
            if( testTermListForSentence(&newTermListForTerm1AndTerm2, currentSentence, graph)){ //if the chosen terms proves the current sentence
                if( testTermListForSentenceList(&newTermListForTerm1AndTerm2, sentenceList->next, graph)){ //try all the next sentences
                    exists = 1; // if the chosen terms
                }
            }
            term2GraphAux = term2GraphAux->next;
        }
        term1Graph1Aux = term1Graph1Aux->next;
        term2GraphAux = term2Graph;
    }
    return exists;
}

void printSentenceList(SL* sentenceList){
    if(sentenceList == NULL) printf("Sem sentencas\n");
    else{
        printf("Query ==>");
        SL* aux = sentenceList;
        while(aux){
            printf((aux->next? " %s(%s, %s)," : " %s(%s, %s)." ), //prints all sentences like a prolog query
                   aux->sentence->label, aux->sentence->term1, aux->sentence->term2);
            aux = aux->next;
        }
        free(aux); aux = NULL;
        printf("\n\n");
    }
}

/*
*******THIS IS A DEBUG FUNCTION*******************

void printTermList(TL* termList){
    if(termList == NULL) printf("Sem termos\n");
    else{ //prints all terms from a termList
        TL* aux = termList;
        while(aux){
            printf("IDENTIFICADOR: %s\n", aux->term->identifier);
            printGraph(aux->term->associatedGraph);
            aux = aux->next;
        }
        free(aux); aux = NULL;
    }
}*/

void printPossibleValuesForSearch(TL* termList){
    TL* aux = termList;
    printf("==========================\n");
    while(aux){
        char* identifier = aux->term->identifier; //prints an possible value for sentences
        char* value = aux->term->associatedGraph->term;
        if(isupper(identifier[0])) printf("%s = %s\n", identifier, value);
        aux = aux->next;
    }
    printf("\n");

}
