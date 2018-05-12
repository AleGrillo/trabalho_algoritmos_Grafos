/*
* Trabalho de Algoritmo Em Grafos - Etapa 1 - Estrutura de Dados
* Copyright 2018 by Alexandre And Hemerson And Ricardo
* TP1.h - Local das assinaturas das funções
* TP1.cpp - Códigos das assinaturas das funções
* TP1_Main.cpp - Função principal que implementa as funções
*/

#ifndef TP1H
#define TP1H 1

using namespace std;

struct coord //Para Grafos eucledianos
{
	double x;
	double y;
};

typedef double dado; //Para ficar mais fácil substituir o tipo no futuro

//// Classe noh que guardara as informações de cada vertice do grafo ////
class noh
{
	friend class vertices;

private:
	int id;						 //id que guarda a posição no vetor com vertices no grafo
	dado dadosNoh;		 //Para vertices com peso
	coord coordenadas; //Para grafos eucledianos
	bool eucledian;

public:
	noh(int id, dado dadosNoh);
	noh(int id, coord coordenadas);
};

///////////////////////////// Classe Vertice ///////////////////////////////
// São os vertices da lista de adjacencias. Esses vertices possuem um id, //
// que é uma identificação de onde ele está no vetor de nohs do grafo     //
// (nesse vetor que estão as informações de valores ou as coordenadas     //
// desse vertive), e também possuem um peso caso o grafo seja ponderado.  //
////////////////////////////////////////////////////////////////////////////
class verticeDeAdj
{
	friend class lista;			//lista individual de cada vertice
	friend class listasAdj; //Todas as listas de adjacencias dos vertices
													//do grafo
private:
	int id;
	int peso; //Caso o grafo seja ponderado
	verticeDeAdj *proximo;

public:
	verticeDeAdj(int id);
	verticeDeAdj(int id, int peso);
	int getId();
	int getPeso();
	verticeDeAdj *getProximo();
};

//////////////////////////  Matriz de Adjacencias  /////////////////////////
//              Estrutura de Dados: Matriz de Adjacêndias                 //
////////////////////////////////////////////////////////////////////////////
class matrizAdj
{
private:
	int **matriz;
	int tamanhoMat;
	void expand(int t);
	void deleteMat();
	void create(int tamanhoMat);

public:
	matrizAdj(int tamanhoMat);
	matrizAdj();
	~matrizAdj();
	void insert(int linha, int coluna, int peso);
	void insert(int linha, int coluna);
	int getTam();
	int getPeso(int verticeA, int verticeB);
	void printMat();
	bool search(int linha, int coluna);
	void remove(int verticeA, int verticeB);
	void removeVertice(int verticeA);
};

///////////////////////    Matriz de Incidencias   /////////////////////////
class matrizInc
{
private:
	int **matriz;
	int qntLinhas;	//Qnt de arestas, LEMBRANDO que cada linha
									//da matriz representa uma aresta
	int qntColunas; //Qnt de vertices, LEMBRANDO que cada coluna
									//da matriz é um vertice
	void expandLinhas();
	void expandColunas(int qntExpand);
	void deleteMat();
	void create(int qntVertices);
	string orientation;

public:
	matrizInc(string orientation, int qntVertices);
	matrizInc(string orientation);
	~matrizInc();
	void insert(int verticeA, int verticeB);
	void printMat();
	bool search(int verticeA, int verticeB, int &comecoAresta);
	int getQntColunas();
	int getQntLinhas();
	void remove(int verticeA, int verticeB);
	void removeVertice(int verticeA);
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
	void copyList(lista *copy); // copia a lista
public:
	lista();
	~lista();
	void insert(int id);
	void insert(int id, int peso);
	bool remove(int id);
	bool search(int id);
	bool deleteList();
	verticeDeAdj *getFirst(); //Retorna uma copia do primeiro verticeDeAdj da lista
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
	bool removeIn(int posVertice, int verticeRemover);
	void insertIn(int posVertice, int verticeInserir);
	void insertIn(int posVertice, int verticeInserir, int peso);
	bool removeVertice(int posVertice);
	inline int getQnt();
	verticeDeAdj *getListaPos(int pos);
	bool searchIn(int posVertice, int procurar);
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
	bool compare(coord A, coord B);

public:
	vertices(int qntVertices);
	vertices();
	~vertices();
	int insertVertice(dado novo);
	int insertVertice(coord novo);
	void deletePos(int pos);
	int deleteVertice(dado del);
	int deleteVertice(coord del);
	void print();
	void printPos(int pos);
	int search(dado pos);
	int search(coord pos);
	int getQntVertices();
};

//////////////////////////////  Classe Grafo  ///////////////////////////////
class grafo
{
private:
	vertices *verticesDoGrafo;
	listasAdj *lAdj;
	matrizAdj *mAdj;
	matrizInc *mInc;
	int qualEstrutura; //Vem do main contendo a opção de estrutura de
										 //dados escolhida pelo usuario para armazenar os
										 //vertices e as arestas.
	string orientation;
	bool ponderado;
	bool eucledian;
	void inserctIn(int idA, int idB);						//Insere na estrutura de dados escolhida
	void inserctIn(int idA, int idB, int peso); //Insere na estrutura de dados
																							//escolhida com grafos ponderados
public:
	grafo(string orientation, bool ponderado, bool eucledian, int qualEstrutura);
	~grafo();
	void insertAresta(dado dadosNohA, dado dadosNohB);							 //Para vertices com apenas um valor
	void insertAresta(coord coordenadasNohA, coord coordenadasNohB); //Para vertices com coordenadas
	void insertAresta(dado dadosNohA, dado dadosNohB, int peso);		 //Para grafos ponderados
	void removeVertice(int pos);
	int search(dado dadosNoh);
	int search(coord coordenadas);
	int getQntVertices();
	listasAdj *getLAdj();
	matrizAdj *getMAdj();
	matrizInc *getMInc();
	bool getPonderado();
	bool getEucledian();
	int getQualEstrutura();
	string getOrientation();
	void printPos(int pos);
	void printVertices();
	void printGrafo();
	void printLAdj();
	void printMAdj();
	void printMInc();
	void setEstruturaDados(listasAdj *lAdj);
	void setEstruturaDados(matrizAdj *mAdj);
	void setEstruturaDados(matrizInc *mInc);
};

void listToMatAdj(grafo *G);
void listToMatInc(grafo *G);
void matAdjToList(grafo *G);
void matAdjToMatInc(grafo *G);
void matIncToListAdj(grafo *G);
void matIncToMatAdj(grafo *G);
void obtemVizinhos(grafo *G, int u);
void obtemPred(grafo *G, int u);
void obtemSuc(grafo *G, int u);
void ehVizinho(grafo *G, int u, int v);
void ehPredecessor(grafo *G, int u, int v);
void ehSucessor(grafo *G, int u, int v);
void delVertice(grafo *G, int u);
void delAresta(grafo *G, int u, int v);
grafo *criaSubGrafo(grafo *G);
string nomeArq();
bool ePonderado();
int estruturaUtilizada();
bool dadosVertices();
void estruturaDeDadosGrafo(grafo *G, int comando);
int comand();
int getVertice(grafo *G);
void menu(grafo *G);

#endif
