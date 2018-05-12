## Trabalho Prático Final - Fase 1

<li> <b> Estruturas de Dados </b> </li>
<li> <b> Conversões de Estruturas de Dados </b> </li>
<li> <b> Funções de Grafos </b> </li>

## Equipe:
<li> Alexandre Grillo </li>
<li> Hemerson Batista </li>
<li> Ricardo Caldeira </li>

## Execução:

<p> Para executar o trabalho, existem duas opções: </p>
<li> <b> Makefile: </b> </li>
    <ul>
        <li> Certifique-se que a linha 13 esteja comentada para executar o makefile </li>
        <li> Abra o terminal no diretório do arquivo Makefile
        <li> Digite Makefile </li>
        <li> Digite ./TP1_Main </li>
        <li> Pronto, agora já pode utilizar o programa </li>
   </ul>
<li> <b> Geany: </b>  </li>
    <ul>
        <li> Para utilizar pelo Geany, basta Compilar, Construir e Executar o arquivo TP1_Main.cpp </li>
        <li> Certifique-se que a linha 13 não esteja comentada, pois ela inclue as funções implementadas </li>
        <li> Pronto, agora já pode utilizar o programa </li>
    </ul>
    
## Ideia:

<p> A ideia central do trabalho é armazenar os dados dos vértices (nohs) em um vetor principal do Grafo. Esse vetor se expande a medida que novos vértices entram no grafo. Assim que adicionados, os vértices ganham um ID. Esse ID corresponde a posição no vetor principal. </p>
<p> Para adicionar o vértice a estrutura de dados que guarda as vizinhanças (lista ou matriz de adjacências, matriz de incidências), é passado o ID do vértice no vetor principal. Portanto, a posição em qualquer uma das listas é determinada pela ordem de entrada do vértice atravéz do arquivo porém a adjacência é SEMPRE determinada pela ligação dos pares no arquivo de instância. Lembrando que embora o ID determine a posição na Estrutura de Dados escolhida, o valor de identificação estara no vetor principal do Grafo e para acessa-lo existe uma função expecífica que o retorna. </p>
