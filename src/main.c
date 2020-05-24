#include<stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "ParseQA.h"
#include "sentence.h"
#include <string.h>
#include "utils.h"

int main(){
    ND* graph = initializeGraph();
    char ans;
    int op;
    printf("Deseja abrir o arquivo exemplo de fatos (exampleFacts.pl)? (s/n)\n");
    scanf(" %c", &ans);
    if(ans == 's' || ans == 'S'){
        ParsePrologToGraph(&graph, "../exemplos/exampleFacts.pl"); //read the full file and parses each line to a valid relation item
    }
    do{
        showMenuAndGetAns(&op);
        if(op == 1){
            printf("\n\n**** Grafo de Conhecimento ****\n");
            printGraph(graph); //prints graphs on screen
            printf("****Fim do grafo ****\n\n");
        }else if(op == 2){
            printf("Digite os fatos que deseja incluir, um por linha:\n");
            char line[128];
            scanf(" ", &line); //clean up input buffer
            gets(&line);
            while(strcmp(line, "")){
                //parses each line into a fact and adds to the graph
                if(!ParsePrologFactToGraph(&graph, line)) printf("Aresta inserida com sucesso!\n");
                gets(&line);
            }
        }
        else if(op == 3){
            char path[500];
            printf("Digite o caminho relativo do arquivo de fatos que deseja incluir:\n");
            scanf(" ", &path); //clean up input buffer
            gets(&path);
            ParsePrologToGraph(&graph, path); //read the full file and parses each line to a valid relation item
        }
        else if(op == 4){
            printf("Digite as sentencas da busca, uma por linha:\n");
            char line[128];
            SL* sentences = NULL;
            S* sentence;
            scanf(" ", &line);
            gets(&line);
            while(strcmp(line, "")){
                sentence = getSentenceByProlog(line);
                if(!sentence) printf("Comando invalido! Tente novamente: \n");
                else insertSentenceInSentenceList(sentence, &sentences); //parses all valid sentences to insert in sentenceList
                gets(&line);
            }
            printSentenceList(sentences);
            TL* termList = NULL;
            int i = sentences ? testTermListForSentenceList(&termList, sentences, graph) : 1; //tests sentences
            if(!i) printf("False\n\n");
            else printf("True\n\n");
        }
    }while(op != 0);
    return 0;
}
