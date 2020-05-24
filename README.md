# Gráfo para *question answering*

Este projeto foi desenvolvido em 2019-1, para a cadeira de Inteligência Artificial do bacharelado de Ciência da Computação na Universidade Federal Fluminense (UFF). A primeira parte do trabalho consistia em construir um conjunto de fatos, regras e sentenças em **Prolog** a partir de uma página da Web; em seguida, construir um **grafo de conhecimento**. Para este projeto, o grafo foi implementado em C e utiliza um padrão para fatos e sentenças adaptados do Prolog.

### Prolog
Uma das características mais marcantes do Prolog é sua natureza declarativa. Em vez de se indicar os passos a serem executados, alimenta-se uma base com informações (fatos e regras) e, então, são feitas consultas a serem respondidas com estes dados. Para isso, são definidos padrões para a entrada de fatos, regras e sentenças.

Um **fato** em prolog é um predicado, um dado verdadeiro, compostosto por uma *cabeça* e alguns *argumentos*. Se queremos afirmar, por exemplo, que Ana é mãe de Maria e de Bruna, podemos escrever fatos que demonstram essas relações.
```prolog
maeDe(ana, maria).
maeDe(ana, bruna).
```
Para realizar **consultas**, o prolog conta com vários recursos. Uma das opções é verificar se um determinado predicado é verdadeiro, bastanto apenas perguntar seguindo o mesmo padrão para fatos.
```prolog
?- maeDe(ana, maria).
true
```
A resposta afirmativa nos diz que existe, dentre os fatos, algum predicado que satisfaz a relação proposta.
Outro recurso é o uso de **variáveis**. Indentificadas por uma letra maiúscula no início, as variáveis vão assumir todos os valores que satisfizerem as sentenças onde estão inseridas, por exemplo, se queremos saber todas as pessoas de quem *Ana é mãe*.
```prolog
?- maeDe(ana, Filha).
true
Filha = maria
Filha = bruna
```
Esse recurso é especialmente útil quando queremos **unificar** uma variável, ou seja, verificar mais de uma sentença para a mesma variável. Por exemplo, queremos saber *se alguém é mãe tanto de Maria quanto de Bruna*.
```prolog
?- maeDe(Alguem, maria), maeDe(Alguem, bruna).
true
Alguem = ana
```

### Adaptações
Para este projeto, apenas alguns recursos foram implementados e, em sua maioria, adaptados. O sistema reconhece apenas **fatos** e **consultas** simples, com algumas restrições, e implementa a **unificação** de variáveis por um algoritmo de busca adaptado.

Os **fatos** e **consultas** têm as mesmas restrições quanto ao padrão adotado. São aceitas entradas que contem com uma *cabeça* e *dois parâmetros*, no mesmo formato de prolog, desde que a *cabeça* comece com letra minúscula e todos os três componentes sejam composto apenas por letras, números e *underscore* ("\_"), com no máximo **40 caracteres** cada.

Para os **fatos**, todos os parâmetros devem iniciar com letra minúscula ou número, combinando com a *expressão regular* definida.

```
^[a-z][A-Za-z0-9_]{0,39}\([a-z0-9][A-Za-z0-9_]{0,39}, [a-z0-9][A-Za-z0-9_]{0,39}\)\.
```
Alguns exemplos de fatos são:
```prolog
ano_de_nascimento(joao, 1983).
origem(maria, rio_de_janeiro).
origem(joao, rio_de_janeiro).
ano_de_abertura(padaria, 1983).
local(padaria, rio_de_janeiro).
```

Para as **consultas**, os parâmetros podem começar com números ou letras, tanto maiúsculas quanto minúsculas. Entretanto, vale lembrar que um parâmetro iniciado com letra **maiúscula** é uma **variável**, logo, será processado de modo diferente dos demais casos. Todas as entradas devem combinar com a *expressão regular* definida.

```
^[a-z][A-Za-z0-9_]{0,39}\([A-Za-z0-9_]{0,40}, [A-Za-z0-9_]{0,40}\)
```
Alguns exemplos de consultas são:
```prolog
ano_de_nascimento(Quem, 1983)
ano_de_abertura(padaria, Quando)
origem(Quem, Onde)
local(padaria, rio_de_janeiro)
```

### Menu e utilização
Ao iniciar o programa, o usuário deve informar se deseja carregar o *grafo de conhecimento* com um arquivo exemplo de fatos. Esse arquivo, disponível em *exemplos/exampleFacts.pl*, conta com 121 fatos extraídos da página da banda americana Slipknot na [Wikipedia](https://pt.wikipedia.org/wiki/Slipknot).

Depois, é exibido um **menu de ações** que o usuário utilizará para gerenciar sua interação com o *grafo*. Para cada uma das opções será exibida uma nova mensagem e, encerrado a entrada dos dados, o usuário retornará ao menu.
```
*** MENU ***
1 - Desenhar grafo de conhecimento
2 - Adicionar aresta ao grafo
3 - Adicionar arquivo de fatos
4 - Fazer consulta
0 - Sair
```
Caso o usuário deseje **desenhar o grafo**, será impresso na tela todos os termos (*nós*) e, para cada um, todas os fatos (arestas) relacionado. O grafo produzido a partir da inserção dos fatos no exemplo anterior está abaixo.
```
**** Grafo de Conhecimento ****

joao:
    joao --ano_de_nascimento--> 1983
    joao --origem--> rio_de_janeiro
    
1983:
    joao --ano_de_nascimento--> 1983
    padaria --ano_de_abertura--> 1983

maria:
    maria --origem--> rio_de_janeiro

rio_de_janeiro:
    maria --origem--> rio_de_janeiro
    joao --origem--> rio_de_janeiro
    padaria --local--> rio_de_janeiro
    
padaria:
    padaria --ano_de_abertura--> 1983
    padaria --local--> rio_de_janeiro

**** Fim do grafo ****
```

Além de carregar o arquivo exemplo de fatos, o usuário pode inserir **arestas** no grafo de conhecimento. Neste caso, o usuário deve digitar um fato por linha; caso o fato não siga o padrão definido, um erro de leitura será indicado. Uma linha vazia indica o fim da entrada de fatos, retornando ao menu.

Outra opção para carregar o grafo é abrir um **arquivo de fatos**. Nesse caso, basta ter um arquivo com um fato por linha e indicar seu caminho relativo. O arquivo de fatos padrão, por exemplo, está dentro da pasta de "*exemplos*" e o programa, em "*src*"; o caminho relativo seria "*../exemplos/exampleFacts.pl*".

Caso seja possível encontrar e abrir o arquivo, uma mensagem indicará o sucesso e, também, quantas arestas foram identificadas e aceitas para o total de linhas lidas.

> Arquivo "../exemplos/exampleFacts.pl" aberto com sucesso! Arestas inseridas: 121/121

Caso ocorra algum erro durante o processo de leitura, será impresso na tela a mensagem original (em inglês).

> ../exemplos2/exampleFacts.pl: No such file or directory

Por último, o usuário pode **realizar consultas** dentro das restrições já definidas. Ao escolher essa opção, o usuário deve entrar com uma sentença por linha; uma linha vazia indica o fim das entradas. Em seguida, será impresso na tela a consulta equivalente em prolog e o resultado (true" ou "false"). Caso a consulta conte com *variáveis*, será impresso cada conjunto de valores possíveis.

Com base no grafo do exemplo anterior, podemos buscar ***quem** tem como **origem** a mesma cidade que uma **loja** aberta em **1983***; para isso, basta entrar com a seguinte sequência:
```
ano_de_abertura(Loja, 1983)
origem(Nome, Local)
local(Loja, Local)
```
E a resposta será:
```
Query ==> ano_de_abertura(Loja, 1983), origem(Nome, Local), local(Loja, Local).

==========================
Loja = padaria
Nome = joao
Local = rio_de_janeiro

==========================
Loja = padaria
Nome = maria
Local = rio_de_janeiro

True
```
### Unificação

O processo de verificar sentença é bastante simples, pois, dado uma consulta do tipo `q(x, y)`, basta procurar se existe alguma aresta `q` que ligue `x` a `y`. Se, por exemplo, temos uma consulta ` origem(joao, rio_de_janeiro)`, basta buscar no subgrafo de *Joao* (ou de *rio_de_janeiro*) se existe a aresta *joao --origem--> rio_de_janeiro*.

O processo formal é uma tentativa de *unificação*. Dado uma consulta `q(x, y)`, busca-se no banco algum fato `q(a, b)` onde `x = a` e `y = b`. Caso seja encontrado, responde-se como verdadeiro (**true**); caso não seja, retorna-se falso (**false**).

A verificação, entretanto, fica um pouco mais complicada quando usamos **variáveis**. Uma vez que não estão instanciadas, é necessário verificar qual (ou quais) valores satisfazem a *unificação*. Se temos a mesma consulta do exemplo anterior usando uma variável, algo como ` origem(Quem, rio_de_janeiro)`, não basta buscar em um subgrafo específico. É necessário assumir que *Quem* pode ser qualquer um dos termos inseridos e buscar em cada subgrafo correspondente uma aresta *\<termo\> --origem--> rio_de_janeiro*.

Caso uma mesma variável apareça em mais de uma sentença, o processo fica um pouco mais longo. Com uma consulta do tipo `origem(joao, Onde), local(padaria, Onde)`, é necessário que o mesmo valor (ou vários) que satisfaz a primeira consulta (`origem(joao, Onde)`) também satisfaça a segunda (`local(padaria, Onde)`).

O algoritmo implementado é recursivo e começa com uma lista de sentenças, o grafo de conhecimento e uma lista de termos vazia.

1. Verifica se ainda existem sentenças. Se não existem mais sentenças na lista, verifica-se os termos. Se existem termos válidos, então a resposta é verdadeiro e estes termos são uma combinação que satisfaz todas as sentenças. Retorna 1.
2. Recupera a primeira sentença da lista e identifica quem são os parâmetros.
3. Para cada um dos parâmetros, define-se quais são os ainda possíveis valores.
4. Para uma combinação de valores, testa-se a sentença.
    1. Caso a sentença se verifique com esses valores, o algoritmo retorna ao passo **1** avançando para a próxima sentença e atualizando a lista de modo que os valores selecionados sejam os únicos possíveis para cada termo.
        1. Caso a chamada recursiva se verifique, retorna 1.
        2. Caso contrário, continua para o passo **5**.
    2. Caso a sentença não se verifique, segue para o passo **5**.
5. Caso ainda existam valores possíveis, retorna-se ao passo **4** com uma nova combinação.

### Como utilizar
O repositório conta com todos os arquivos em C e, também, as configurações do projeto para [**Code::Blocks**](http://www.codeblocks.org/). Uma opção é abrir pela IDE, construir e executar. Outra opção é abrir o executável já construído (*src/QAGraph.exe*). Para os usuários de *Windows*, basta clicar em *execute.cmd* para rodar a aplicação pelo prompt de comando.

*Obs.: Está incluso um arquivo exemplos de perguntas (*exemplos/exampleQuestions.txt*) que podem ser respondidas com o arquivo exemplo de fatos (*exemplos/exampleFacts.pl*).
