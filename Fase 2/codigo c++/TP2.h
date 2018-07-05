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

using namespace std;

typedef int dado;

//// Classe noh que guardara as informações de cada vertice do grafo ////
class noh
{
	friend class vertices;
	friend void montarGrupos();

private:
	int id;		 //id que guarda a posição no vetor com vertices no grafo
	dado peso; //Para vertices com peso

public:
	noh(int id, dado peso);
};

//////////////////////////  Matriz de Adjacencias  /////////////////////////
//              Estrutura de Dados: Matriz de Adjacêndias                 //
////////////////////////////////////////////////////////////////////////////
class matrizAdj
{
private:
	double **matriz;
	int tamanhoMat;
	void expand(int t);
	void deleteMat();
	void create(int tamanhoMat);
	void remove(int verticeA, int verticeB);

public:
	matrizAdj();
	matrizAdj(int tamanhoMat);
	~matrizAdj();
	void insert(int linha, int coluna, double distancia);
	int getTam();
	double getDistancia(int verticeA, int verticeB);
	void print();
	void removeVertice(int vertice);
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
	friend class listasAdj; //Todas as listas de adjacencias dos vertices do grafo
	friend void searchMaxInsercion();

private:
	int id;
	double distancia; //Caso o grafo seja ponderado
	verticeDeAdj *proximo;

public:
	verticeDeAdj(int id, double distancia);
	int getId();
	double getDistancia();
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
	void insert(int id, double distancia);
	bool removeFirst();
	bool remove(int id);
	bool search(int id);
	bool deleteList();
	void print();
	int getTam();
	verticeDeAdj *getFirst();
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
	void insertIn(int posVertice, int verticeInserir, double distancia);
	bool removeIn(int posVertice, int idRemover);
	void removeVertice(int idRemover); //Remove o vertice das listas dos outros vertices
	verticeDeAdj *getFirst(int pos);
	inline int getQnt();
	void print();
};

//////////////////////  Classe vertices do Grafo  ///////////////////////////
class vertices
{
private:
	noh **vetor;
	int qntVertices;
	int tamanho; //Tamanho total do vetor com os vértices, pode ser reduzido
							 //a medida que um vértice é apagado do vetor
	int pos;		 //Ultima posição inserida no vetor
	void expandVetor();
	void create(int qntVertices);
	void deleteVetor();

public:
	vertices(int qntVertices);
	vertices();
	~vertices();
	int insertVertice(dado peso, int id); //Para inserir no grupo de alunos
	int insertVertice(dado peso);
	void remove(int pos);
	void print();
	int getQntVertices();
	int getTam();
	dado getVertice(int pos); //Petorna o peso de um vértice da posição passada
	int *getIds();						//Retorna somente os id's dos vértices
	inline bool isEmpty();		//Se o tamanho é igual a 0 significa que todos os vértices foram apagados
};

///////////////////////////  Classe Group  //////////////////////////////////
// Estrutura de Dados: Vetor com os alunos presentes no grafo              //
/////////////////////////////////////////////////////////////////////////////

class group
{
private:
	vertices *alunos;
	int qntAlunos;
	int L; //Limitante inferior
	int U; //Limitante superior
	int peso_total;
	double distancia_total;

public:
	group(int L, int U);
	~group();
	void insertAluno(dado peso, int id);
	int getQntAlunos();
	vertices *getGroup();
	void print();
	int *getIds();
	int getPeso();
	int getL();
	int getU();
	void setDistancia(double distancia);
	double getDistancia();
};

/////////////////////////  Classe Vetor de Grupos //////////////////////

class vetGroup
{
private:
	group **grupos;
	int tamanho;	 //Tamanho total do vetor de grupos, pode ser reduzido a medida que mudamos um grupo
								 //para a ultima posição
	int qntGrupos; //A quantidade total de grupos
public:
	vetGroup(int qntGrupos);
	~vetGroup();
	void insertGroup(int pos, int L, int U);
	void insertIn(int pos, dado peso, int id);
	group *removeGroup(int pos); //Apenas troca o grupo com a ultima posição e reduz o tamanho do mesmo
	int getTam();
	int getQnt();
	int *getIds(int pos);			//Retorna todos os id's dos vértices do grupo
	int getPeso(int pos);			//Retorna o peso total de um grupo
	group *getGroup(int pos); //Retorna o grupo de uma posição
	void print();
	int getL(int pos);
	int getU(int pos);
	void reset(); //Reseta o tamanho do grupo, fazendo-o ter o tamanho da quantidade total
};

void read(fstream &arquivo, vetGroup *&grupos, vertices *&vertices_grafo, listasAdj *&lAdj, matrizAdj *&mAdj, int &qntVertices, int &qntGrupos);
void quickSort(int *vetorId, int *vetor, int qnt, int esq, int dir);
int *vetorContador(listasAdj *lAdj, int qnt);
double max_distance(vetGroup *grupos, matrizAdj *mAdj);
void initializeGroups(vetGroup *grupos, listasAdj *lAdj, vertices *vert, int *vetorID, int qntGrupos);
void insert_to_group(vetGroup *grupos, vertices *vertices_grafo, listasAdj *lAdj, int pos, dado peso, int insert);
int searchMaxInsercion(vetGroup *grupos, listasAdj *lAdj, int qntGrupos, int &max_insercion);
void attain_upper_limit(vertices *vertices_grafo, vetGroup *grupos, listasAdj *lAdj, int qntGrupos);
void mount_groups(vertices *vertices_grafo, vetGroup *grupos, listasAdj *lAdj, int qntGrupos);
void insert_to_Group(vetGroup *grupos, vertices *vertices_grafo, matrizAdj *mAdj, int pos, dado peso, int insert);
double compute_total_distance(int verticeA, matrizAdj *mAdj, int *ids, int tam);
int searchMaxDistance(group *grupo, vertices *vertices_grafo, matrizAdj *mAdj, double &distancia);
void attain_upper_limit(vertices *vertices_grafo, vetGroup *grupos, matrizAdj *mAdj);
void mount_groups(vertices *vertices_grafo, vetGroup *grupos, matrizAdj *mAdj);
double compute_max_distance(vetGroup *grupos);

#endif
