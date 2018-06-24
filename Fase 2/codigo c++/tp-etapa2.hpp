/*
* Trabalho de Algoritmo Em Grafos - Etapa 2 - Problema A
* Copyright 2018 by Alexandre And Hemerson 
* 
* Descrição do problema:
	A montagem de grupos de estudo é um desafio para docentes, visto que a resolução dos
	problemas propostos aos estudantes requer habilidades distintas. Deste modo, é desejável
	que estes grupos de alunos sejam o mais heterogêneo possível, para que as características
	dos indivíduos envolvidos crie uma sinergia e torne o processo de aprendizado construtivo e
	eficaz.
	Sistematicamente, podemos definir este problema como segue. Cada estudante u possui
	uma nota pu, que indica o grau de aptidão para a resolução do problema proposto. O total
	de grupos de estudantes a ser formado é igual a g. Os grupos possuem limites mínimos e
	máximos de aptidão dados por L e U, respectivamente. Cada estudante deve pertencer a
	apenas um grupo. A relação entre cada par de estudantes u e v é dado pelo valor duv 2 R,
	que quantifica a similaridade das características entre os dois estudantes relativas à resolução
	do problema proposto por um docente. Nosso objetivo é criar g grupos de estudantes que
	maximize o somatório das distâncias entre os elementos escolhidos a pertencer em cada
	grupo.
*/

#ifndef TP2H
#define TP2H 1

//~ #include <iostream>

using namespace std;

typedef int dado;

//// Classe noh que guardara as informações de cada vertice do grafo ////
class noh
{
	friend class vertices;

  private:
	int id;			   //id que guarda a posição no vetor com vertices no grafo
	dado peso;	 //Para vertices com peso

  public:
	noh(int id, dado peso);
};

//////////////////////////  Matriz de Adjacencias  /////////////////////////
//              Estrutura de Dados: Matriz de Adjacêndias                 //
////////////////////////////////////////////////////////////////////////////
class matrizAdj
{
  private:
	float **matriz;
	int tamanhoMat;
	void expand(int t);
	void deleteMat();
	void create(int tamanhoMat);

  public:
	matrizAdj();
	~matrizAdj();
	void insert(int linha, int coluna, float distancia);
	int getTam();
	float getDistancia(int verticeA, int verticeB);
	void printMat();
	bool search(int linha, int coluna);
	void remove(int verticeA, int verticeB);
	void removeVertice(int verticeA);
};

///////////////////////////// Classe Vertice ///////////////////////////////
// São os vertices da lista de adjacencias. Esses vertices possuem um id, //
// que é uma identificação de onde ele está no vetor de nohs do grafo     //
// (nesse vetor que estão as informações de valores ou as coordenadas     //
// desse vertive), e também possuem um peso caso o grafo seja ponderado.  //
////////////////////////////////////////////////////////////////////////////
class verticeDeAdj
{
	friend class lista;		//lista individual de cada vertice
	friend class listasAdj; //Todas as listas de adjacencias dos vertices
							//do grafo
  private:
	int id;
	float distancia; //Caso o grafo seja ponderado
	verticeDeAdj *proximo;

  public:
	verticeDeAdj(int id, float distancia);
	int getId();
	int getDistancia();
	verticeDeAdj *getProximo();
};

////////////////////////////  Classe Lista  ////////////////////////////////
//              Estrutura de Dados: Lista encadeada simples               //
////////////////////////////////////////////////////////////////////////////
class lista
{
  private:
	verticeDeAdj *primeiro;
	verticeDeAdj *ultimo;
	int tamanhoLista;
  public:
	lista();
	~lista();
	void insert(int id, float distancia);
	bool removeFirst();
	bool remove(int id);
	bool search(int id);
	bool deleteList();
	void print();
	int getTam();
};

////////////////////  Classe Listas de Adjacencia  //////////////////////////
// Estrutura de Dados: Lista de Adjacencias; é um vetor de listas          //
// encadeadas descrita anteriormente                                       //
/////////////////////////////////////////////////////////////////////////////
class listasAdj
{
  private:
	lista **listas;
	int qntListas;
	void create(int qntListas);
	void deleteListas();
	void expandListas(int qntExpand);

  public:
	listasAdj();
	listasAdj(int qntListas);
	~listasAdj();
	void insertIn(int posVertice, int verticeInserir, float distancia);
	bool removeIn(int posVertice, int idRemover);
	bool removeVertice(int idRemover); //Remove o vertice das listas dos outros vertices
	inline int getQnt();
	void print();
};

//////////////////////  Classe vertices do Grafo  ///////////////////////////
class vertices
{
  private:
	noh **vetor;
	int qntVertices;
	void expandVetor();
	bool compare(dado A, dado B);

  public:
	vertices(int qntVertices);
	vertices();
	~vertices();
	int insertVertice(dado novo);
	void deletePos(int pos);
	int deleteVertice(dado del);
	//~ int deleteVertice(coord del);
	void print();
	void printPos(int pos);
	int search(dado pos);
	//~ int search(coord pos);
	int getQntVertices();
};

//////////////////////////////  Classe Grafo  ///////////////////////////////
class grafo
{
  private:
	vertices *verticesDoGrafo;
	listasAdj *lAdj;
	matrizAdj *mAdj;
	int qualEstrutura; //Vem do main contendo a opção de estrutura de
					   //dados escolhida pelo usuario para armazenar os
					   //vertices e as arestas.
	void inserctIn(int idA, int idB, float distancia); //Insere na estrutura de dados
												//escolhida com grafos ponderados
  public:
	grafo();
	~grafo();
	void insertAresta(dado dadosNohA, dado dadosNohB, float distancia);	 //Para grafos ponderados
	void removeVertice(int pos);
	int getQntVertices();
	listasAdj *getLAdj();
	matrizAdj *getMAdj();
	void printVertices();
	void printGrafo();
};

#endif
