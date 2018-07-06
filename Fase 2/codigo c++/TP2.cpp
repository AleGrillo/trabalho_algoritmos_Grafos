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

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cfloat>
#include "TP2.h"

using namespace std;

typedef int dado;

////////////////////////////////////////////////////////////////////////
///////////////////////////Classe Noh///////////////////////////////////

noh::noh(int id, dado peso)
{
	this->id = id;
	this->peso = peso;
}

////////////////////////////////////////////////////////////////////////
///////////////////////Classe MatrizAdj/////////////////////////////////

matrizAdj::matrizAdj()
{
	create(0);
}

matrizAdj::matrizAdj(int tamanhoMat)
{
	create(tamanhoMat);
}

matrizAdj::~matrizAdj()
{
	deleteMat();
}

void matrizAdj::create(int tamanhoMat)
{
	this->tamanhoMat = tamanhoMat;
	matriz = new double *[tamanhoMat];

	for (int i = 0; i < tamanhoMat; i++)
	{
		matriz[i] = new double[tamanhoMat];
		for (int j = 0; j < tamanhoMat; j++)
		{
			matriz[i][j] = 0;
		}
	}
}

void matrizAdj::deleteMat()
{
	for (int i = 0; i < tamanhoMat; i++)
	{
		delete[] matriz[i];
	}

	delete[] matriz;
}

void matrizAdj::insert(int linha, int coluna, double distancia)
{
	if (linha >= tamanhoMat or coluna >= tamanhoMat)
	{
		if (linha < coluna)
		{
			expand((coluna - tamanhoMat) + 1);
		}
		else
		{
			expand((linha - tamanhoMat) + 1);
		}
	}

	int l = linha;
	int c = coluna;
	if (matriz[l][c] == 0)
	{
		matriz[l][c] = distancia;
	}
}

void matrizAdj::expand(int t)
{
	int tam = tamanhoMat + t; //Como foi passado somente a diferença de tamanho
														// do tamanho atual para o que tem de ser expandido
	double **mat = new double *[tam];

	for (int i = 0; i < tam; i++)
	{
		mat[i] = new double[tam];
		for (int j = 0; j < tam; j++)
		{
			if (i < tamanhoMat and j < tamanhoMat)
			{
				mat[i][j] = matriz[i][j];
			}
			else
			{
				mat[i][j] = 0;//Posições novas criadas
			}
		}
	}

	deleteMat();
	tamanhoMat = tam;
	matriz = mat;
}

void matrizAdj::print()
{
	for (int i = 0; i < tamanhoMat; i++)
	{
		for (int j = 0; j < tamanhoMat; j++)
		{
			cout << matriz[i][j] << " ";
		}
		cout << endl;
	}
}

int matrizAdj::getTam()
{
	return tamanhoMat;
}

double matrizAdj::getDistancia(int verticeA, int verticeB)
{
	if (verticeA >= 0 and verticeB >= 0 and
		verticeA < tamanhoMat and verticeB < tamanhoMat)
	{
		return matriz[verticeA][verticeB];
	}

	else
	{
		//O elemento não está na matriz
		return -1;
	}
}

void matrizAdj::remove(int verticeA, int verticeB)
{
	if (verticeA >= 0 and verticeB >= 0 and
		verticeA < tamanhoMat and verticeB < tamanhoMat)
	{
		matriz[verticeA][verticeB] = -1; //Apenas apaga a posição setando-a com -1
	}
}

void matrizAdj::removeVertice(int vertice)
{
	if (vertice < tamanhoMat)
	{
		for (int i = 0; i < tamanhoMat; i++)
		{
			remove(vertice, i); //Apaga a coluna inteira de um vértice
		}
	}
}

////////////////////////////////////////////////////////////////////////
//////////////////////Classe VerticeAdj/////////////////////////////////

verticeDeAdj::verticeDeAdj(int id, double distancia)
{
	this->id = id;
	this->distancia = distancia;
	proximo = NULL;
}

int verticeDeAdj::getId()
{
	return id;
}

double verticeDeAdj::getDistancia()
{
	return distancia;
}

////////////////////////////////////////////////////////////////////////
///////////////////////////Classe lista/////////////////////////////////

lista::lista()
{
	primeiro = NULL;
	ultimo = NULL;
	tamanhoLista = 0;
}

lista::~lista()
{
	deleteList();
}

void lista::insert(int id, double distancia)
{
	if (search(id) == true)
	{
		//Caso o id já estiver na lista
		return;
	}
	
	verticeDeAdj *novo = new verticeDeAdj(id, distancia);

	if (primeiro == NULL)
	{
		primeiro = novo;
		ultimo = novo;
		tamanhoLista++;
	}
	else
	{
		//A inserção na lista será ordenada
		
		if (distancia >= primeiro->distancia)
		{
			//A distancia nova é maior que a menor distancia da lista
			novo->proximo = primeiro;
			primeiro = novo;
			tamanhoLista++;
		}
		else if (distancia <= ultimo->distancia)
		{
			//A distancia nova é menor que a maior distancia da lista
			ultimo->proximo = novo;
			ultimo = novo;
			tamanhoLista++;
		}
		else
		{
			/*
			 *A distancia nova é menor que a maior distancia e
			 *maior que a menor distancia da lista ou seja, 
			 *deve ser inserido no meio da lista 
			*/
			verticeDeAdj *aux = primeiro;
			verticeDeAdj *ant;

			while (aux and aux->distancia > distancia)
			{
				ant = aux;
				aux = aux->proximo;
			}

			novo->proximo = aux;
			ant->proximo = novo;
			tamanhoLista++;
		}
	}
}

bool lista::removeFirst()
{
	if (primeiro)
	{
		verticeDeAdj *aux = primeiro;
		primeiro = primeiro->proximo;
		delete aux;
		tamanhoLista--;
		return true;
	}

	return false;
}

bool lista::remove(int id)
{
	if (primeiro == NULL)
	{
		return false;
	}
	else
	{
		if (primeiro->id == id)
		{
			//Irá apagar o primeiro elemento da lista
			return removeFirst();
		}
		else
		{
			//Irá apagar um elemento do vértice ou fim da lista
			verticeDeAdj *aux = primeiro;
			verticeDeAdj *ant;

			while (aux->proximo and aux->id != id)
			{
				ant = aux;
				aux = aux->proximo;
			}

			if (aux and aux->id == id)
			{
				ant->proximo = aux->proximo;
				delete aux;
				tamanhoLista--;
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}

bool lista::deleteList()
{
	if (primeiro == NULL)
	{
		return false;
	}
	else
	{
		verticeDeAdj *aux;
		while (primeiro)
		{
			aux = primeiro;
			primeiro = primeiro->proximo;
			delete aux;
			tamanhoLista--;
		}
		primeiro = NULL;
		ultimo = NULL;
		return true;
	}
}

bool lista::search(int id)
{
	verticeDeAdj *aux = primeiro;
	bool achou = false;

	while (aux and achou == false)
	{
		if (aux->id == id)
		{
			achou = true;
		}
		aux = aux->proximo;
	}

	return achou;
}

verticeDeAdj *lista::getFirst()
{
	if (primeiro)
	{
		verticeDeAdj *aux = new verticeDeAdj(primeiro->id, primeiro->distancia);
		return aux;
	}
	else
		return NULL;
}

int lista::getTam()
{
	return tamanhoLista;
}

void lista::print()
{
	verticeDeAdj *aux = primeiro;

	while (aux)
	{
		if (aux)
		{
			cout << aux->id << "\"" << aux->distancia << " -> ";
		}
		aux = aux->proximo;
	}
	cout << "NULL" << endl;
}

////////////////////////////////////////////////////////////////////////
///////////////////////Classe ListasAdj/////////////////////////////////

listasAdj::listasAdj()
{
	create(0);
}

listasAdj::listasAdj(int qntListas)
{
	create(qntListas);
}

listasAdj::~listasAdj()
{
	deleteListas();
}

void listasAdj::deleteListas()
{
	for (int i = 0; i < qntListas; i++)
	{
		listas[i]->deleteList();
		delete listas[i];
	}
	delete[] listas;
	qntListas = 0;
}

void listasAdj::create(int qntListas)
{
	this->qntListas = qntListas;
	listas = new lista *[qntListas];

	for (int i = 0; i < qntListas; i++)
	{
		listas[i] = new lista();
	}
}

void listasAdj::expandListas(int qntExpand)
{
	int qntAux = qntListas + qntExpand;
	lista **listasAux = new lista *[qntAux];
	for (int i = 0; i < qntAux; i++)
	{
		if (i < qntListas)
		{
			listasAux[i] = listas[i];
		}
		else
		{
			listasAux[i] = new lista();//Para posições novas adicionadas
		}
	}

	deleteListas();
	listas = listasAux;
	qntListas = qntAux;
}

void listasAdj::insertIn(int posVertice, int verticeInserir, double distancia)
{
	if (posVertice < qntListas)
	{
		listas[posVertice]->insert(verticeInserir, distancia);
	}
	else
	{
		cerr << "Posição maior que a quantidade de vertices alocados\n";
		//~ exit(EXIT_FAILURE);
	}
}

bool listasAdj::removeIn(int posVertice, int idRemover)
{
	if (posVertice >= 0 and posVertice < qntListas)
	{
		return listas[posVertice]->remove(idRemover);
	}
	return false;
}

void listasAdj::removeVertice(int idRemover)
{
	//Remove o vertice das listas dos outros vertices
	for (int i = 0; i < qntListas; i++)
	{
		removeIn(i, idRemover);
	}
}

inline int listasAdj::getQnt()
{
	return qntListas;
}

verticeDeAdj *listasAdj::getFirst(int pos)
{
	//Retorna o primeiro elemento da lista da posição pos
	return listas[pos]->getFirst();
}

void listasAdj::print()
{
	for (int i = 0; i < qntListas; i++)
	{
		if (listas[i])
		{
			cout << "LISTA DO VERTICE " << i << " -> ";
			listas[i]->print();
			cout << endl;
		}
	}
}

////////////////////////////////////////////////////////////////////////
////////////////////////Classe Vertices/////////////////////////////////

vertices::vertices(int qntVertices)
{
	create(qntVertices);
}

vertices::vertices()
{
	create(0);
}

vertices::~vertices()
{
	deleteVetor();
}

void vertices::deleteVetor()
{
	for (int i = 0; i < qntVertices; i++)
	{
		delete vetor[i];
	}

	delete[] vetor;
}

void vertices::create(int qntVertices)
{
	pos = 0;//Primeira posição que admite inserções
	tamanho = qntVertices;
	this->qntVertices = qntVertices;
	vetor = new noh *[qntVertices];

	for (int i = 0; i < qntVertices; i++)
	{
		vetor[i] = NULL;
	}
}

void vertices::expandVetor()
{
	int qntAux = qntVertices + 1;
	noh **vetorAux = new noh *[qntAux];

	for (int i = 0; i < qntAux; i++)
	{
		if (i < qntVertices)
		{
			noh *novo = new noh(vetor[i]->id, vetor[i]->peso);
			vetorAux[i] = novo;
		}
		else
		{
			vetorAux[i] = NULL;//Novas posições adicionadas
		}
	}

	deleteVetor();
	vetor = vetorAux;
	qntVertices = qntAux;
}

int vertices::insertVertice(dado novo, int id)
{
	if (pos == qntVertices)
	{
		expandVetor();
		pos = qntVertices - 1;//Posição livre para a próxima inserção
	}
	
	noh *novoNoh = new noh(id, novo); //Para inserir no grupo de alunos
	vetor[pos] = novoNoh;
	pos++;//Posição livre para a próxima inserção
	return pos - 1;
	//Ao inserir, retorna a posição para assim, inserir uma vizinhança
	//nas estruturas de dados dos vertices
}

int vertices::insertVertice(dado novo)
{
	if (pos == qntVertices)
	{
		expandVetor();
		pos = qntVertices - 1;//Posição livre para a próxima inserção
	}
	noh *novoNoh = new noh(pos, novo);
	vetor[pos] = novoNoh;
	pos++;
	return pos - 1;//Posição livre para a próxima inserção
	//Ao inserir, retorna a posição para assim, inserir uma vizinhança
	//nas estruturas de dados dos vertices
}

void vertices::remove(int pos)
{
	if (pos >= 0 and pos < qntVertices)
	{
		noh *aux = vetor[pos];
		delete aux;
		vetor[pos] = NULL;
		tamanho--;
	}
}

dado vertices::getPesoVertice(int pos)
{
	if (pos >= 0 and pos < qntVertices and vetor[pos])
	{
		return vetor[pos]->peso;
	}

	else
	{
		return -1;
	}
}

int vertices::getQntVertices()
{
	return qntVertices;
}

int vertices::getTam()
{
	return tamanho;
}

int *vertices::getIds()
{
	//Retornará apenas os id's dos vértices que estão realmente no conjunto
	int *vetorAux = new int[qntVertices];

	for (int i = 0; i < qntVertices; i++)
	{
		if (vetor[i])
		{
			vetorAux[i] = vetor[i]->id;
		}
		else
		{
			vetorAux[i] = -1;
		}
	}
	return vetorAux;
}

inline bool vertices::isEmpty()
{
	if (tamanho == 0)
	{
		return true;
	}
	return false;
}

void vertices::print()
{
	for (int i = 0; i < qntVertices; i++)
	{
		if (vetor[i])
		{
			cout << vetor[i]->id << "->";
		}
	}
	cout << endl;
}

vertices* vertices::getCopy(){
	vertices* copy_origin = new vertices(qntVertices);
	
	for (int i = 0; i < qntVertices; i++)
	{
		copy_origin->insertVertice(vetor[i]->peso, vetor[i]->id);
	}
	
	
	return copy_origin;
}

////////////////////////////////////////////////////////////////////////
//////////////////////////Classe Group//////////////////////////////////

group::group(int L, int U)
{
	alunos = new vertices();
	qntAlunos = 0;
	this->L = L;
	this->U = U;
	peso_total = 0;
	distancia_total = 0.0;
}

group::~group()
{
	delete alunos;
}

void group::insertAluno(dado peso, int id)
{
	alunos->insertVertice(peso, id);
	peso_total += peso;
}

int group::getQntAlunos()
{
	return alunos->getQntVertices();
}

int group::getPeso()
{
	return peso_total;
}

int *group::getIds()
{
	return alunos->getIds();
}

int group::getL()
{
	return L;
}

int group::getU()
{
	return U;
}

void group::setDistancia(double distancia)
{
	distancia_total += distancia;
}

double group::getDistancia()
{
	return distancia_total;
}

void group::print()
{
	alunos->print();
	cout << "Peso total: " << peso_total << endl;
	cout << "Quantidade de alunos: " << getQntAlunos() << endl;
	cout << "Distancia Total: " << getDistancia() << endl;
}

////////////////////////////////////////////////////////////////////////
/////////////////////////  Classe Vetor de Grupos //////////////////////

vetGroup::vetGroup(int qntGrupos)
{
	tamanho = qntGrupos;
	this->qntGrupos = qntGrupos;
	grupos = new group *[qntGrupos];

	for (int i = 0; i < qntGrupos; i++)
	{
		grupos[i] = NULL;
	}
}

vetGroup::~vetGroup()
{
	for (int i = 0; i < qntGrupos; i++)
	{
		delete grupos[i];
	}

	delete[] grupos;
}

void vetGroup::insertIn(int pos, dado peso, int id)
{
	//Irá inserir um aluno id em um grupo da posição pos
	if (pos >= 0 and pos < qntGrupos)
	{
		grupos[pos]->insertAluno(peso, id);
	}
}

bool vetGroup::removeGroup(int pos)
{
	//Na verdade não apaga o grupo, apenas move-o para a ultima posição
	//e reduz a quantidade "existente"
	if (pos == qntGrupos - 1)
	{
		//se for a ultima posição apenas reduz o tamanho
		qntGrupos--;
		return true;
	}
	else if (pos >= 0 and pos < qntGrupos - 1)
	{
		//troca a posição pos com a ultima posição do grupo e reduz o tamanho
		swap(grupos[pos], grupos[qntGrupos - 1]);
		qntGrupos--;
		return true;
	}
	else
	{
		return false;
	}
}

int vetGroup::getPeso(int pos)
{
	//Retorna o peso total de um grupo da posição pos
	if (pos >= 0 and pos < qntGrupos)
	{
		return grupos[pos]->getPeso();
	}

	else
		return -1;
}

void vetGroup::insertGroup(int pos, int L, int U)
{
	if (pos >= 0 and pos < qntGrupos)
	{
		//Insere um grupo novo
		group *grupo = new group(L, U);
		grupos[pos] = grupo;
	}
}

int vetGroup::getTam()
{
	//Retorna a quantidade total de grupos existentes
	return tamanho;
}

int *vetGroup::getIds(int pos)
{
	if (pos >= 0 and pos < qntGrupos)
	{
		return grupos[pos]->getIds();
	}
	else
		return NULL;
}

group *vetGroup::getGroup(int pos)
{
	if (pos >= 0 and pos < qntGrupos){
		return grupos[pos];
	}
	return NULL;
}

int vetGroup::getL(int pos)
{
	if (pos >= 0 and pos < qntGrupos)
	{
		return grupos[pos]->getL();
	}
	else
	{
		return -1;
	}
}

int vetGroup::getU(int pos)
{
	if (pos < qntGrupos)
	{
		return grupos[pos]->getU();
	}
	else
	{
		return -1;
	}
}

void vetGroup::reset()
{
	//Restaura a quantidade de grupos ao tamanho original
	qntGrupos = tamanho;
}

int vetGroup::getQnt()
{
	//Retorna a quantidade de grupos disponiveis para inserção
	return qntGrupos;
}

void vetGroup::print()
{
	for (int i = 0; i < qntGrupos; i++)
	{
		cout << "Grupo " << i << ": ";
		grupos[i]->print();
	}
	cout << endl;
}

////////////////////////////////////////////////////////////////////////
///////////////////////////Funções basicas//////////////////////////////

void read(fstream &arquivo, vetGroup *&grupos, vertices *&vertices_grafo, listasAdj *&lAdj, matrizAdj *&mAdj,
					int &qntVertices, int &qntGrupos)
{
	//Um método para ler do arquivo de texto passado no main
	int L, U;
	dado peso;
	int u, v;
	double distancia;
	arquivo >> qntVertices;
	arquivo >> qntGrupos;
	grupos = new vetGroup(qntGrupos);

	for (int i = 0; i < qntGrupos; i++)
	{
		arquivo >> L;
		arquivo >> U;
		grupos->insertGroup(i, L, U);
	}

	vertices_grafo = new vertices(qntVertices);

	for (int i = 0; i < qntVertices; i++)
	{
		arquivo >> peso;
		vertices_grafo->insertVertice(peso);
	}

	lAdj = new listasAdj(qntVertices);
	mAdj = new matrizAdj(qntVertices);

	while (arquivo.good())
	{
		arquivo >> u;
		arquivo >> v;
		arquivo >> distancia;
		lAdj->insertIn(u, v, distancia);
		mAdj->insert(u, v, distancia);
		lAdj->insertIn(v, u, distancia);
		mAdj->insert(v, u, distancia);
	}
	arquivo.close();
}

////////////////////////////////////////////////////////////////////////
/////////////////////////Funções auxiliares/////////////////////////////

double max_distance(vetGroup *grupos, matrizAdj *mAdj)
{
	//Essa função calculará a distancia total dos grupos com base na matriz de adjacências
	
	double distancia = 0.0;
	int tam = grupos->getQnt();//Quantos grupos existem
	group *grupo = NULL;//Para buscar um grupo
	int *vetorIds = NULL;//Para buscar todos os id's dos vértices grupo
	int verticeA, verticeB;

	for (int i = 0; i < tam; i++)
	{
		grupo = grupos->getGroup(i);//busca um grupo...
		vetorIds = grupo->getIds();//e seus id's...
		int qnt = grupo->getQntAlunos();//e qunatos alunos tem nesse grupo
		for (int j = 0; j < qnt; j++)
		{
			verticeA = vetorIds[j];//Para cada vértice do grupo
			for (int k = 0; k < qnt; k++)
			{
				if(j != k){
					verticeB = vetorIds[k];
					distancia += mAdj->getDistancia(verticeA, verticeB);//retorna a distância entre esse vértice
				}
			}
		}
	}

	return distancia;
}

void quickSort(int *vetorId, int *vetor, int qnt, int esq, int dir)
{
	//Para ordenar o vetor de contadores e o vetor de id's
	int i = esq;
	int j = dir;
	int pivo = vetor[(dir + esq) / 2];

	while (i <= j)
	{
		while (vetor[i] > pivo)
			i++;
		while (vetor[j] < pivo)
			j--;
		if (i <= j)
		{
			swap(vetor[i], vetor[j]);
			swap(vetorId[i], vetorId[j]);
			i++;
			j--;
		}
	}
	if (esq < j)
		quickSort(vetorId, vetor, qnt, esq, j);
	if (i < dir)
		quickSort(vetorId, vetor, qnt, i, dir);
}

int *vetorContador(listasAdj *lAdj, int qntVertices)
{
	/*
	 * Este vetor será usado com o propósito de escolher os vértices que mais 
	 * aparecem como mais distantes de outros vértices.
	 * Vamos considerar que o tamanho dos vetores criados será o tamanho do vetor original 
	 * de vértices pois queremos saber quais dos vértices originais do grafo aparecem mais vezes na 
	 * primeira posição
	 */
	int *vetorID = new int[qntVertices];//Um vetor com cada vértice que aparece na primeira posição da
										//lista de adjacências, ou seja, o mais distante
	int *vetor = new int[qntVertices];//Um vetor de contador que trabalhará em sincronia com o vetor anterior,
									  //ele contara quantas vezes o vértice do id na posição apareceu em primeiro lugar
	verticeDeAdj *vAdj = NULL;//Para buscar o primeiro de cada lista de adjacências

	//atribui o valor 0 a todas as posições do contador
	for (int i = 0; i < qntVertices; i++)
	{
		vetor[i] = 0;
	}

	for (int i = 0; i < qntVertices; i++)
	{
		vAdj = lAdj->getFirst(i);//Reotrna o primeiro da lAdj
		vetorID[i] = vAdj->getId();//Pega o id do mesmo
		vetor[vAdj->getId()]++;//Incrementa a posição (que é o id do vértice)
	}

	quickSort(vetorID, vetor, qntVertices, 0, qntVertices - 1);//Ordena os vetores para 
															  //olharmos somente para as primeiras posições
	delete[] vetor;
	return vetorID;//Retorna o vetor com os vértices que aparecem mais vezes como mais distantes nas primeiras 
				  //posições
}

void initializeGroups(vetGroup *grupos, listasAdj *lAdj, vertices *vert, int *vetorID, int qntGrupos)
{
	//Irá inserir os os vértices que mais apareceram distantes nas listas 
	//Cada um em um grupo diferente
	for (int i = 0; i < qntGrupos; i++)
	{
		dado peso = vert->getPesoVertice(vetorID[i]);
		grupos->insertIn(i, peso, vetorID[i]);//Insere um vértice mais distante em um grupo
											  //por vez
		lAdj->removeVertice(vetorID[i]);//Remove da lista de adjacências para que não possa 
										//ser inserido em outro grupo no futuro
		vert->remove(vetorID[i]);//Remove dos vértices que continuam no grafo
	}
}

void insert_to_group(vetGroup *grupos, vertices *vertices_grafo, listasAdj *lAdj,
										 int pos, dado peso, int insert)
{

	grupos->insertIn(pos, peso, insert); //Insere esse vertice no grupo que poderá aceitar a maior
																			 //distância
	vertices_grafo->remove(insert);			 //Apaga o vértice inserido no grupo do conjunto de vértices
																			 //para que o mesmo não possa ser inserido em outros grupos
	lAdj->removeVertice(insert);				 //Remove o mesmo das listas de adjacências para que ele não possa
																			 //ser incontrado como maior distância novamente
}

int searchMaxInsercion(vetGroup *grupos, listasAdj *lAdj, int qntGrupos, int &max_insercion)
{
	double maior_dist = DBL_MIN;
	int posInserir = -1;
	int id;
	double distancia;
	verticeDeAdj *vertice;
	for (int i = 0; i < qntGrupos; i++)
	{
		group *aux = grupos->getGroup(i); //Retorna cada grupo já previamente criado
		int *ids = aux->getIds();//Um vetor com todos os ids dos vertices do grupo
		int tam = aux->getQntAlunos();//A quantidade de alunos que está presente em um grupo
		
		for (int j = 0; j < tam; j++)
		{
			id = ids[j];
			vertice = lAdj->getFirst(id); //Retorna o primeiro elemento da lista de
										  //adjacencias de cada vértice de um grupo
			if (vertice)
			{
				distancia = vertice->getDistancia(); //A maior distancia será dada pelo primeiro vértice
													//da lista de adjacências da posição
				if (maior_dist < distancia)
				{ //Se a maior distância encontrada for menor que a distância do
					//do próximo vértice
					maior_dist = distancia;
					max_insercion = vertice->getId();
					posInserir = i;
				}
			}
		}
	}
	return posInserir;
}

void attain_upper_limit(vertices *vertices_grafo, vetGroup *grupos, listasAdj *lAdj, int qntGrupos)
{
	dado peso;
	int max_insercion, U, peso_total;
	int posInserir = -1;

	while (grupos->getQnt() > 0 and vertices_grafo->isEmpty() == false)
	{
		qntGrupos = grupos->getQnt();//Quantidade de grupos que ainda podem receber inserções
		posInserir = searchMaxInsercion(grupos, lAdj, qntGrupos, max_insercion); //Encontra a distancia mais longa possível
																				//dentre todos os vértices do grupo
		if (posInserir > -1)
		{	
			//Se foi achado uma distância mais longa para inserção, se não o valor será -1
			//que significa que nenhum grupo pode receber inserções e o loop irá parar
			
			peso = vertices_grafo->getPesoVertice(max_insercion); //O peso será o valor do vertice
															     //com a maior distancia da maior inserção
			peso_total = grupos->getPeso(posInserir);//Peso atual do grupo que é um somatório
											 //dos pesos de todos os vértices do grupo
			U = grupos->getU(posInserir);
			if (peso > -1)
			{
				//Se essa condição se confirmar o vértice a inserir ainda não tem grupos
				if (peso + peso_total <= U)
				{
					//Para verificar se o limitante superior ainda não foi atingido
					insert_to_group(grupos, vertices_grafo, lAdj, posInserir, peso, max_insercion);
				}
				else
				{
					//Se o limitante superior já foi atingido então o grupo não pode receber mais
					//inserções, então o mesmo é movido para a ultima posição e não recebe mais
					//vértices
					grupos->removeGroup(posInserir);
				}
			}
			else
			{
				//Se essa condição se confirmar o vértice já foi inserido mas não 
				//foi removido das listas de adjacencias
				lAdj->removeVertice(max_insercion);
			}
		}
	}

	grupos->reset();//Reseta a quantidade de possiveis inserções para poder
					//calcular a distancia total
}

void mount_groups(vertices *vertices_grafo, vetGroup *grupos, listasAdj *lAdj, int qntGrupos)
{
	int posInserir = -1;
	int max_insercion, L, peso_total;
	dado peso;

	//Esse loop irá rodar enquanto estiverem grupos abaixo do limitante inferior
	while (grupos->getQnt() > 0)
	{
		qntGrupos = grupos->getQnt();//Quantidade de grupos que ainda podem receber inserções
		posInserir = searchMaxInsercion(grupos, lAdj, qntGrupos, max_insercion); //Encontra a distancia mais longa possível
																				//dentre todos os vértices do grupo
		if (posInserir > -1)
		{														//Se foi achado uma distância mais longa para inserção
			peso = vertices_grafo->getPesoVertice(max_insercion); //O peso será o valor do vertice
																//com a maior distancia da maior inserção
			if (peso > -1)
			{ //Se o peso for maior que -1 significa que o vértice ainda não
				//possui um grupo
				insert_to_group(grupos, vertices_grafo, lAdj, posInserir, peso, max_insercion);
			}
			else
			{
				//Se o peso for igual a -1 significa que o vértice já foi inserido
				//em um grupo e removido do vetor original de vertices
				lAdj->removeVertice(max_insercion); //Então o vértice é apagado das listas de adjacências para não ser inserido
													//em outros grupos
			}
			L = grupos->getL(posInserir);//Limitante inferior do grupo
			peso_total = grupos->getPeso(posInserir); //Peso atual do grupo que é um somatório
													//dos pesos de todos os vértices do grupo
			if (L >= 0)
			{
				if (peso_total >= L)
				{									  
					//Se o peso total do grupo for maior que o limitante inferior
					grupos->removeGroup(posInserir); //O grupo é movido para a ultima posição do vetor e
													//o tamanho desse vetor é reduzido para que nesse grupo
													//não possam ser feitas mais inserções
				}
			}
		}
	}

	grupos->reset(); //Restaura a quantidade de grupos pois a mesma é reduzida
					//quando um grupo atinge o limitante inferior (L)
					
	//Quando chega aqui significa que os grupos atingiram o limitante inferior
	//então é chamada a função para atingir um limitante superior e terminar de encher os grupos
	attain_upper_limit(vertices_grafo, grupos, lAdj, qntGrupos);
}

//////////////////////////////////////////////////////////////////////////
/////////////////////////Metodos Solução Dois/////////////////////////////


/*
 * A solução dois irá utilizar como base a matriz de adjacências e basicamente
 * irá procurar um vértice que mais aumenta a distancia total de um grupo
 */

void insert_to_Group(vetGroup *grupos, vertices *vertices_grafo, matrizAdj *mAdj,
										 int pos, dado peso, int insert)
{

	grupos->insertIn(pos, peso, insert); //Insere esse vertice no grupo que poderá aceitar a maior
										//distância
	vertices_grafo->remove(insert);	//Apaga o vértice inserido no grupo do conjunto de vértices
									//para que o mesmo não possa ser inserido em outros grupos
	mAdj->removeVertice(insert); //Faz o mesmo na mtriz de adjacências pelo mesmo motivo
}

double compute_total_distance(int verticeA, matrizAdj *mAdj, int *ids, int tam)
{
	/*
	 * Função para retornar a distancia total de um vértice em relação aos outros 
	 * vértices de um grupo que o mesmo ainda não foi inserido
	 */
	double distancia_total = 0.0;
	double distancia;
	int verticeB;
	for (int i = 0; i < tam; i++)
	{
		distancia = -1;
		verticeB = ids[i];//Cada vértice do grupo
		if(verticeA != verticeB){
			distancia = mAdj->getDistancia(verticeA, verticeB);//Retorna a de A->B distância
		}
		if (distancia > -1)
		{
			//Se for -1 o vértice A já saiu da matriz de Adjacências; se não for
			//então essa distancia é somada a uma distância total
			distancia_total += distancia;
		}
	}
	return distancia_total;
}

int searchMaxDistance(group *grupo, vertices *vertices_grafo, matrizAdj *mAdj, double &distancia)
{
	int vertice = -1;//O vertice que irá guardar a posição que mais acrescentará 
					 //em distancia total ao grupo
	double max_distance = DBL_MIN;
	double new_distance = 0.0;//Será a distancia total somada de um vértice em relação a todos os outros
							  //do grupo
	int *ids = grupo->getIds();//Ids dos vértices do grupo
	int tamGrupo = grupo->getQntAlunos();
	int qntVertices = vertices_grafo->getQntVertices();

	for (int i = 0; i < qntVertices; i++)
	{
		new_distance = compute_total_distance(i, mAdj, ids, tamGrupo);//Recebe a distancia de um vértice
																	  //em relação a todos do grupo
		if (new_distance + grupo->getDistancia() > max_distance)
		{
			//Se a distancia do grupo somada a distancia que o vértice irá 
			//acrescentar for maior que a maior já encontrada...
			vertice = i;//Para retornarmos o vértice que irá aumentar mais a distância
			distancia = new_distance; //Para inserirmos essa distância no grupo depois
									  // a mesma é retornada através do &ndereço presente
									  //na assinatura do método
			max_distance = new_distance + grupo->getDistancia();
		}
	}
	return vertice;
}

void attain_upper_limit(vertices *vertices_grafo, vetGroup *grupos, matrizAdj *mAdj)
{
	group *grupo = NULL;
	double distancia;
	int posInserir = -1;
	int peso = -1;
	int max_distance = 0;
	int U; //Recebera o limitante superior de um grupo
	int peso_total;
	int qntGrupos = grupos->getQnt();

	while (qntGrupos > 0 and vertices_grafo->isEmpty() == false)
	{
		//Irá rodar enquanto existirem grupos que não atingiram o limitante superior
		//e enquanto ainda existirem vértices no vetor de vértices do grafo
		
		qntGrupos = grupos->getQnt();//Quantidade de grupos que admitem inserções
									 //será reduzida quando um grupo atingir U
		for (int i = 0; i < qntGrupos; i++)
		{
			posInserir = i;//Posição do grupo a inserir
			grupo = grupos->getGroup(i);
		}

		max_distance = searchMaxDistance(grupo, vertices_grafo, mAdj, distancia); //Encontra o vértice que mais aumenta
																				  //a distância total do grupo
		if (max_distance > -1)
		{
			//Se max_distance == -1, não foi achado um vértice para aumentar a distância
			
			peso = vertices_grafo->getPesoVertice(max_distance); //O peso será o valor do vertice
																 //que mais aumenta a distâcia total
			peso_total = grupos->getPeso(posInserir);//Peso atual do grupo que é um somatório
												     //dos pesos de todos os vértices do grupo
			U = grupos->getU(posInserir);//Limitante superior do grupo a inserir
			if (peso > -1)
			{
				//Se o peso = -1 então o max_distance já foi inserido em um grupo
				if (peso + peso_total <= U)
				{
					//Se ao somar o peso achado ao peso do grupo e o mesmo não exceder o limitante
					//superior
					insert_to_Group(grupos, vertices_grafo, mAdj, posInserir, peso, max_distance);
					grupo->setDistancia(distancia);
				}
				else
				{
					//Se exceder o limitante superior o grupo é movido para
					//a ultima posição para que o mesmo não receba novas inserções
					grupos->removeGroup(posInserir);
				}
			}
			else
			{
				//Se o peso = -1 max_distance já foi inserido em um grupo
				//então o mesmo será removido de mAdj
				mAdj->removeVertice(max_distance);
			}
		}
	}
	
	//resetará a quantidade de grupos que admitem inserções
	grupos->reset();
}

void mount_groups(vertices *vertices_grafo, vetGroup *grupos, matrizAdj *mAdj)
{
	group *grupo = NULL;
	double distancia;
	int qntGrupos;
	int posInserir = -1;
	int peso = -1;
	int vertice_max_distance = 0;
	int L, peso_total;

	//Esse loop irá rodar enquanto estiverem grupos abaixo do limitante inferior
	qntGrupos = grupos->getQnt();
	while (qntGrupos > 0)
	{
		qntGrupos = grupos->getQnt();
		for (int i = 0; i < qntGrupos; i++)
		{
			//Para cada cada grupo
			posInserir = i;//Posição do grupo que será inserido novos vértices
			grupo = grupos->getGroup(i);//Retorna um grupo para inserir novos vértices
		}

		vertice_max_distance = searchMaxDistance(grupo, vertices_grafo, mAdj, distancia);//O vértice que mais irá aumentar
																						 //na distâcia total de um grupo
		if (vertice_max_distance > -1)
		{
			//Se for -1 o vértice não foi encontrado					  
			peso = vertices_grafo->getPesoVertice(vertice_max_distance); //O peso será o valor do vertice
																		//que mais aumenta a distância total de um grupo
			if (peso > -1)
			{ //Se o peso for maior que -1 significa que o vértice ainda não
			  //possui um grupo
				insert_to_Group(grupos, vertices_grafo, mAdj, posInserir, peso, vertice_max_distance);
				grupo->setDistancia(distancia);//Insere a distância que o vértice irá agregar a distância total do grupo
			}
			else
			{
				//Se o peso for igual a -1 significa que o vértice já foi inserido
				//em um grupo e removido do vetor original de vertices
				mAdj->removeVertice(vertice_max_distance); //Então o vértice é apagado da mAdj para
														   //não ser inserido em outros grupos
			}
			L = grupos->getL(posInserir);			  //Limitante inferior do grupo
			peso_total = grupos->getPeso(posInserir); //Peso atual do grupo que é um somatório
													  //dos pesos de todos os vértices do grupo
			if (L >= 0)
			{
				if (peso_total >= L)
				{	
					//Se o peso total do grupo for maior que o limitante inferior
					grupos->removeGroup(posInserir); //O grupo é movido para a ultima posição do vetor e
													 //o tamanho desse vetor é reduzido para que esse grupo não
													 //receba novas inserções
				}
			}
		}
	}

	grupos->reset(); //Restaura a quantidade de grupos pois a mesma é reduzida
					 //quando um grupo atinge o limitante inferior (L)
					 
	qntGrupos = grupos->getQnt();
	
	//Se chegou a essa parte é porque todos os grupos já atingiram seus limitantes inferiores
	//então agora todos deverão atingir o limitante superior
	attain_upper_limit(vertices_grafo, grupos, mAdj);
}

double compute_max_distance(vetGroup *grupos)
{
	//Para calcular a soma das distancias de todos os grupos
	
	double max_distance = 0.0;
	group *grupo = NULL;
	int qntGrupos = grupos->getQnt();

	for (int i = 0; i < qntGrupos; i++)
	{
		grupo = grupos->getGroup(i);
		max_distance += grupo->getDistancia();
	}

	return max_distance;
}

//////////////////////////// Funções do Menu //////////////////////////////

