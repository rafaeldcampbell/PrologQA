#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "sentence.h"

int ParsePrologToGraph(ND** graph, char *filename);

int ParsePrologFactToGraph(ND** graph, char *fact);

S* getSentenceByProlog(char* line);
