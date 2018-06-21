## Trabalho Prático Final - Fase 1

<li> <b> Problema A </b> </li>
<li> <b> Divisão de alunos em grupos equilibrados </b> </li>
<li> <b> Problema NP Completo </b> </li>

## Equipe:
<li> Alexandre Grillo </li>
<li> Hemerson Batista </li>

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

<p> A montagem de grupos de estudo é um desafio para docentes, visto que a resolução dos
problemas propostos aos estudantes requer habilidades distintas. Deste modo, é desejável
que estes grupos de alunos sejam o mais heterogêneo possível, para que as características
dos indivíduos envolvidos crie uma sinergia e torne o processo de aprendizado construtivo e
eficaz. </p>
<p> Sistematicamente, podemos definir este problema como segue. Cada estudante u possui
uma nota pu, que indica o grau de aptidão para a resolução do problema proposto. O total
de grupos de estudantes a ser formado é igual a g. Os grupos possuem limites mínimos e
máximos de aptidão dados por L e U, respectivamente. Cada estudante deve pertencer a
apenas um grupo. A relação entre cada par de estudantes u e v é dado pelo valor duv 2 R,
que quantifica a similaridade das características entre os dois estudantes relativas à resolução
do problema proposto por um docente. Nosso objetivo é criar g grupos de estudantes que
maximize o somatório das distâncias entre os elementos escolhidos a pertencer em cada
grupo. </p>
