## Trabalho Prático Final - Fase 1

-   <b> Estruturas de Dados </b>
-   <b> Conversões de Estruturas de Dados </b>
-   <b> Funções de Grafos </b>

## Equipe:
*   Alexandre Grilo
*   Hemerson Batista
*   Ricardo Caldeira

## Execução:

<p> Para executar o trabalho, existem duas opções. </p> <br>
*   <b> Makefile: </b><br>
   *   Certifique-se que a linha 13 esteja comentada para executar o makefile<br>
   *   Abra o terminal no diretório do arquivo Makefile<br>
   *   Digite Makefile<br>
   *   Digite ./TP1_Main<br>
   *   Pronto, agora já pode utilizar o programa<br>
*  <b> Geany: </b><br>
   *   Para utilizar pelo Geany, basta Compilar, Construir e Executar o arquivo TP1_Main.cpp<br>
   *   Certifique-se que a linha 13 não esteja comentada, pois ela inclue as funções implementadas<br>
   *   Pronto, agora já pode utilizar o programa<br>

## Ideia:

<p> A ideia central do trabalho é armazenar os dados dos vértices (nohs) em um vetor principal do Grafo. Esse vetor se expande a medida que novos vértices entram no grafo. Assim que adicionados, os vértices ganham um ID. Esse ID corresponde a posição no vetor principal. </p>
<p> Para adicionar o vértice a estrutura de dados que guarda as vizinhanças (lista ou matriz de adjacências, matriz de incidências), é passado o ID do vértice no vetor principal. Portanto, a posição em qualquer uma das listas é determinada pela ordem de entrada do vértice atravéz do arquivo porém a adjacência é SEMPRE determinada pela ligação dos pares no arquivo de instância. Lembrando que embora o ID determine a posição na Estrutura de Dados escolhida, o valor de identificação estara no vetor principal do Grafo e para acessa-lo existe uma função expecífica que o retorna. </p>
