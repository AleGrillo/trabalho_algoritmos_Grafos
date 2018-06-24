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
#include "tp-etapa2.hpp"

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

matrizAdj::~matrizAdj()
{
	deleteMat();
}

void matrizAdj::create(int tamanhoMat)
{
	this->tamanhoMat = tamanhoMat;
	matriz = new float *[tamanhoMat];

	for (int i = 0; i < tamanhoMat; i++)
	{
		matriz[i] = new float[tamanhoMat];
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

void matrizAdj::insert(int linha, int coluna, float distancia)
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
	float **mat = new float *[tam];

	for (int i = 0; i < tam; i++)
	{
		mat[i] = new float[tam];
		for (int j = 0; j < tam; j++)
		{
			if (i < tamanhoMat and j < tamanhoMat)
			{
				mat[i][j] = matriz[i][j];
			}
			else
			{
				mat[i][j] = 0;
			}
		}
	}

	deleteMat();
	tamanhoMat = tam;
	matriz = mat;
}

void matrizAdj::printMat()
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

bool matrizAdj::search(int linha, int coluna)
{
	if (matriz[linha][coluna] != 0)
	{
		return true;
	}
	return false;
}

void matrizAdj::remove(int verticeA, int verticeB)
{
	if (verticeA < tamanhoMat and verticeB < tamanhoMat)
	{
		matriz[verticeA][verticeB] = 0;
	}
}

void matrizAdj::removeVertice(int verticeA)
{
	if (verticeA < tamanhoMat)
	{
		for (int i = 0; i < tamanhoMat; i++)
		{
			if (matriz[verticeA][i] != 0)
			{
				matriz[verticeA][i] = 0;
			}
			if (matriz[i][verticeA] != 0)
			{
				matriz[i][verticeA] = 0;
			}
		}
	}
}

float matrizAdj::getDistancia(int verticeA, int verticeB)
{
	if (verticeA < tamanhoMat and verticeB < tamanhoMat)
	{
		return matriz[verticeA][verticeB];
	}
	cerr << "Nao está na matriz\n";
	exit(EXIT_FAILURE);
}

////////////////////////////////////////////////////////////////////////
//////////////////////Classe VerticeAdj/////////////////////////////////

verticeDeAdj::verticeDeAdj(int id, float distancia)
{
	this->id = id;
	this->distancia = distancia;
	proximo = NULL;
}

int verticeDeAdj::getId()
{
	return id;
}

int verticeDeAdj::getDistancia()
{
	return distancia;
}

verticeDeAdj *verticeDeAdj::getProximo()
{
	return proximo;
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

void lista::insert(int id, float distancia)
{
	verticeDeAdj *novo = new verticeDeAdj(id, distancia);
	
	if(search(id) == true){
		return;
	}

	if (primeiro == NULL)
	{
		primeiro = novo;
		ultimo = novo;
		tamanhoLista++;
	}
	else
	{
		if(distancia >= primeiro->distancia){
			 //A distancia nova é maior que a menor distancia da lista 
			novo->proximo = primeiro;
			primeiro = novo;
			tamanhoLista++;
		}
		else if(distancia <= ultimo->distancia){
			 //A distancia nova é menor que a maior distancia da lista 
			ultimo->proximo = novo;
			ultimo = novo;
			tamanhoLista++;
		}
		else{
			/*
			 *A distancia nova é menor que a maior distancia e
			 *maior que a menor distancia da lista ou seja, 
			 *deve ser inserido no meio da lista 
			*/
			verticeDeAdj* aux = primeiro;
			verticeDeAdj* ant;
			
			while(aux and aux->distancia > distancia){
				ant = aux;
				aux = aux->proximo;
			}
			
			novo->proximo = aux;
			ant->proximo = novo;
			tamanhoLista++;
		}
	}
}

bool lista::removeFirst(){
	if(primeiro){
		verticeDeAdj* aux = primeiro;
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

int lista::getTam()
{
	return tamanhoLista;
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
			listasAux[i] = new lista();
		}
	}

	deleteListas();
	listas = listasAux;
	qntListas = qntAux;
}

void listasAdj::insertIn(int posVertice, int verticeInserir, float distancia)
{
	if (posVertice < qntListas)
	{
		listas[posVertice]->insert(verticeInserir, distancia);
	}
	else
	{
		int qnt = (posVertice - qntListas) + 1;
		expandListas(qnt);
		listas[posVertice]->insert(verticeInserir, distancia); //Inserindo o vizinho
	}
}

bool listasAdj::removeIn(int posVertice, int idRemover)
{
	if (posVertice < qntListas)
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

void listasAdj::print()
{
	for (int i = 0; i < qntListas; i++)
	{
		if (listas[i])
		{
			cout << "LISTA DO VERTICE " << i << " -> ";
			listas[i]->print();
			//~ cout << listas[i]->getTam();
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
	delete[] vetor;
}

void vertices::create(int qntVertices){
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
			vetorAux[i] = vetor[i];
		}
		else
		{
			vetorAux[i] = NULL;
		}
	}

	delete[] vetor;

	vetor = vetorAux;
	qntVertices = qntAux;
}

int vertices::insertVertice(dado novo)
{
	expandVetor();
	int pos = qntVertices - 1;
	noh *novoNoh = new noh(pos, novo);
	vetor[pos] = novoNoh;
	return pos;
	//Ao inserir, retorna a posição para assim, inserir uma vizinhança
	//nas estruturas de dados dos vertices
}

int vertices::search(dado buscar)
{
	for (int i = 0; i < qntVertices; i++)
	{
		if (vetor[i])
		{
			if (compare(vetor[i]->id, buscar) == true)
			{
				return i;
				//nao insere o mesmo noh no grafo duas vezes
			}
		}
		else
			return i; //Retorna a primeira posição vazia caso o vetor tenha
					  //essas posições vazias
	}
	return -1; //Se o vetor estiver cheio ou o noh nao estiver no vetor
}

bool vertices::compare(dado A, dado B)
{
	if (A == B)
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
			cout << vetor[i]->peso << " ";
		}
	}
	cout << endl;
}

int vertices::deleteVertice(dado del)
{
	int pos = search(del);

	deletePos(pos);

	return pos;
}

void vertices::deletePos(int pos)
{
	//testar
	if (pos >= 0 and pos < qntVertices)
	{
		noh *aux = vetor[pos];
		vetor[pos] = NULL;
		delete aux;
		qntVertices--;
	}
}

void vertices::printPos(int pos)
{
	if (pos >= 0 and pos < qntVertices)
	{
		if (vetor[pos])
		{
			cout << vetor[pos]->peso;
		}
		cout << " ";
	}
}

int vertices::getQntVertices()
{
	return qntVertices;
}

////////////////////////////////////////////////////////////////////////
//////////////////////////Classe Grafo//////////////////////////////////

grafo::grafo()
{
	verticesDoGrafo = new vertices();
	lAdj = new listasAdj();
	mAdj = new matrizAdj();
}

grafo::~grafo()
{
	delete verticesDoGrafo;
	delete lAdj;
	delete mAdj;
}

void grafo::insertAresta(dado dadosNohA, dado dadosNohB, float distancia)
{
	int idA = verticesDoGrafo->insertVertice(dadosNohA);
	int idB = verticesDoGrafo->insertVertice(dadosNohB);

	inserctIn(idA, idB, distancia);
}

void grafo::inserctIn(int idA, int idB, float distancia)
{
		//Reimplementar
}

void grafo::removeVertice(int pos)
{
	verticesDoGrafo->deletePos(pos);
}

listasAdj *grafo::getLAdj()
{
	return lAdj;
}

matrizAdj *grafo::getMAdj()
{
	return mAdj;
}
