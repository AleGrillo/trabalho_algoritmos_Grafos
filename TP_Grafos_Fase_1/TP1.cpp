/*
* Trabalho de Algoritmo Em Grafos - Etapa 1 - Estrutura de Dados
* Copyright 2018 by Alexandre And Hemerson And Ricardo
* TP1.h - Local das assinaturas das funções
* TP1.cpp - Códigos das assinaturas das funções
* TP1_Main.cpp - Função principal que implementa as funções
*/

#include <iostream>
#include <cstdlib>
#include <fstream>
#include "TP1.h"

using namespace std;

noh::noh(int id, dado dadosNoh)
{
	this->id = id;
	this->dadosNoh = dadosNoh;
	eucledian = false; //influencia na hora de imprimir ou retornar o valor do noh
}

noh::noh(int id, coord coordenadas)
{
	this->id = id;
	this->coordenadas.x = coordenadas.x;
	this->coordenadas.y = coordenadas.y;
	eucledian = true; //influencia na hora de imprimir ou retornar o valor do noh
}

verticeDeAdj::verticeDeAdj(int id)
{
	this->id = id;
	peso = 0;
	proximo = NULL;
}

verticeDeAdj::verticeDeAdj(int id, int peso)
{
	this->id = id;
	this->peso = peso;
	proximo = NULL;
}

int verticeDeAdj::getId()
{
	return id;
}

int verticeDeAdj::getPeso()
{
	return peso;
}

verticeDeAdj *verticeDeAdj::getProximo()
{
	return proximo;
}

matrizAdj::matrizAdj(int tamanhoMat)
{
	create(tamanhoMat);
}

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
	matriz = new int *[tamanhoMat];

	for (int i = 0; i < tamanhoMat; i++)
	{
		matriz[i] = new int[tamanhoMat];
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

void matrizAdj::insert(int linha, int coluna)
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
		matriz[l][c] = 1;
	}
}

void matrizAdj::insert(int linha, int coluna, int peso)
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
		matriz[l][c] = peso;
	}
}

void matrizAdj::expand(int t)
{
	int tam = tamanhoMat + t; //Como foi passado somente a diferença de tamanho
							  // do tamanho atual para o que tem de ser expandido
	int **mat = new int *[tam];

	for (int i = 0; i < tam; i++)
	{
		mat[i] = new int[tam];
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

int matrizAdj::getPeso(int verticeA, int verticeB)
{
	if (verticeA < tamanhoMat and verticeB < tamanhoMat)
	{
		return matriz[verticeA][verticeB];
	}

	exit(EXIT_FAILURE);
}

matrizInc::matrizInc(string orientation, int qntVertices)
{
	this->orientation = orientation;
	create(qntVertices);
}

matrizInc::matrizInc(string orientation)
{
	this->orientation = orientation;
	create(0);
}

matrizInc::~matrizInc()
{
	deleteMat();
}

void matrizInc::create(int qntVertices)
{
	qntColunas = qntVertices;
	qntLinhas = 0;
	matriz = new int *[qntLinhas];
	for (int i = 0; i < qntLinhas; i++)
	{
		matriz[i] = new int[qntColunas];
		for (int j = 0; j < qntColunas; j++)
		{
			matriz[i][j] = 0;
		}
	}
}

void matrizInc::deleteMat()
{
	for (int i = 0; i < qntLinhas; i++)
	{
		delete[] matriz[i];
	}

	delete[] matriz;
	matriz = NULL;
}

void matrizInc::expandLinhas()
{
	/* Ira aumentar de uma em uma linha pois será incerido somente
	 * uma aresta por vez */

	int qntLinhasAux = qntLinhas + 1;
	int **matrizAux = new int *[qntLinhasAux];
	for (int i = 0; i < qntLinhasAux; i++)
	{
		matrizAux[i] = new int[qntColunas];
		for (int j = 0; j < qntColunas; j++)
		{
			if (i < qntLinhas) //Copia somente as linhas ja existentes
			{
				matrizAux[i][j] = matriz[i][j];
			}
			else
			{
				matrizAux[i][j] = 0;
			}
		}
	}

	deleteMat();
	qntLinhas = qntLinhasAux;
	matriz = matrizAux;
}

void matrizInc::expandColunas(int qntExpand)
{
	/* Caso em que a posicao passada do vertice é maior que a quantidade
	 * de vertices já existentes */

	int qntColunasAux = qntColunas + qntExpand;
	int **matrizAux = new int *[qntColunasAux];
	for (int i = 0; i < qntLinhas; i++)
	{
		matrizAux[i] = new int[qntColunasAux];
		for (int j = 0; j < qntColunasAux; j++)
		{
			if (j < qntColunas) //Copia somente as colunas já existentes
			{
				matrizAux[i][j] = matriz[i][j];
			}
			else
			{
				matrizAux[i][j] = 0;
			}
		}
	}

	deleteMat();
	qntColunas = qntColunasAux;
	matriz = matrizAux;
}

void matrizInc::insert(int verticeA, int verticeB)
{
	if (verticeA >= 0 and verticeB >= 0)
	{
		expandLinhas();
		if (verticeA < qntColunas and verticeB < qntColunas)
		{
			if (orientation == "UNDIRECTED")
			{
				matriz[qntLinhas - 1][verticeA] = 1;
				matriz[qntLinhas - 1][verticeB] = 1;
			}
			else if (orientation == "DIRECTED")
			{
				matriz[qntLinhas - 1][verticeA] = -1;
				matriz[qntLinhas - 1][verticeB] = 1;
			}
		}
		else
		{
			if (verticeA > verticeB)
			{
				if (verticeA >= qntColunas)
				{
					expandColunas((verticeA - qntColunas) + 1);
				}
			}
			else
			{
				if (verticeB >= qntColunas)
				{
					expandColunas((verticeB - qntColunas) + 1);
				}
			}
			if (orientation == "UNDIRECTED")
			{
				matriz[qntLinhas - 1][verticeA] = 1;
				matriz[qntLinhas - 1][verticeB] = 1;
			}
			else if (orientation == "DIRECTED")
			{
				matriz[qntLinhas - 1][verticeA] = -1;
				matriz[qntLinhas - 1][verticeB] = 1;
			}
		}
	}
}

void matrizInc::printMat()
{
	for (int i = 0; i < qntLinhas; i++)
	{
		for (int j = 0; j < qntColunas; j++)
		{
			cout << matriz[i][j] << " ";
		}
		cout << endl;
	}
}

bool matrizInc::search(int verticeA, int verticeB, int &comecoAresta)
{
	if (verticeA < qntColunas and verticeB < qntColunas)
	{
		for (int i = 0; i < qntLinhas; i++)
		{
			if (orientation == "UNDIRECTED")
			{
				if (matriz[i][verticeA] == 1 and matriz[i][verticeB] == 1)
				{
					comecoAresta = -1;
					return true;
				}
			}
			else
			{
				if (matriz[i][verticeA] == -1 and matriz[i][verticeB] == 1)
				{
					comecoAresta = verticeA;
					return true;
				}
			}
		}
	}
	return false;
}

int matrizInc::getQntColunas()
{
	return qntColunas;
}

int matrizInc::getQntLinhas()
{
	return qntLinhas;
}

void matrizInc::remove(int verticeA, int verticeB)
{
	if (verticeA < qntColunas and verticeB < qntColunas)
	{
		for (int i = 0; i < qntLinhas; i++)
		{
			if (matriz[i][verticeA] != 0 and matriz[i][verticeB] != 0)
			{
				matriz[i][verticeA] = 0;
				matriz[i][verticeB] = 0;
			}
		}
	}
}

void matrizInc::removeVertice(int verticeA)
{
	if (verticeA < qntColunas)
	{
		for (int i = 0; i < qntLinhas; i++)
		{
			for (int j = 0; j < qntColunas; j++)
			{
				if (verticeA != j and matriz[i][verticeA] != 0)
				{
					matriz[i][verticeA] = 0;
					matriz[i][j] = 0;
				}
			}
		}
	}
}

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

void lista::insert(int id)
{
	verticeDeAdj *novo = new verticeDeAdj(id);

	if (primeiro == NULL)
	{
		primeiro = novo;
		ultimo = novo;
		tamanhoLista++;
	}
	else
	{
		ultimo->proximo = novo;
		ultimo = novo;
		tamanhoLista++;
	}
}

void lista::insert(int id, int peso)
{
	verticeDeAdj *novo = new verticeDeAdj(id, peso);

	if (primeiro == NULL)
	{
		primeiro = novo;
		ultimo = novo;
		tamanhoLista++;
	}
	else
	{
		ultimo->proximo = novo;
		ultimo = novo;
		tamanhoLista++;
	}
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
			return false;
		}
		else
		{
			verticeDeAdj *aux = primeiro;
			;
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

void lista::copyList(lista *copy)
{
	verticeDeAdj *aux = primeiro;
	while (aux)
	{
		verticeDeAdj *novo = new verticeDeAdj(aux->id);
		copy->insert(novo->id);
		aux = aux->proximo;
	}
}

verticeDeAdj *lista::getFirst()
{
	//Retorna uma copia da lista
	lista *copy;
	copy = new lista();
	copyList(copy);
	return copy->primeiro;
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
			cout << aux->id << " -> ";
		}
		aux = aux->proximo;
	}
	cout << "NULL" << endl;
}

int lista::getTam()
{
	return tamanhoLista;
}

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
	qntListas = 0;
	delete[] listas;
}

void listasAdj::create(int qntListas)
{
	this->qntListas = qntListas;
	listas = new lista *[qntListas];

	for (int i = 0; i < qntListas; i++)
	{
		listas[i] = new lista();
		listas[i]->insert(i);
	}
}

inline int listasAdj::getQnt()
{
	return qntListas;
}

verticeDeAdj *listasAdj::getListaPos(int pos)
{
	if (pos < qntListas)
	{
		return listas[pos]->getFirst();
	}
	return NULL;
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

void listasAdj::insertIn(int posVertice, int verticeInserir)
{
	if (posVertice < qntListas)
	{
		bool busca = listas[posVertice]->search(verticeInserir);
		if (listas[posVertice]->getTam() == 0)
		{
			listas[posVertice]->insert(posVertice);
		}
		if (busca == false)
		{
			listas[posVertice]->insert(verticeInserir);
		}
		//~ else{
		//~ cout << "Vertice ja esta na lista da posicao " << posVertice << endl;
		//~ //Não insere um vizinho repetido porém essa condição pode ser alterada
		//~ //caso seja permitido arestas duplas
		//~ }
	}
	else
	{
		int qnt = (posVertice - qntListas) + 1;
		expandListas(qnt);
		listas[posVertice]->insert(posVertice);		//Inserindo o vertice da posição na lista
		listas[posVertice]->insert(verticeInserir); //Inserindo o vizinho
	}
}

void listasAdj::insertIn(int posVertice, int verticeInserir, int peso)
{
	if (posVertice < qntListas)
	{
		if (listas[posVertice]->getTam() == 0)
		{
			listas[posVertice]->insert(posVertice, 0);
		}
		bool busca = listas[posVertice]->search(verticeInserir);

		if (busca == false)
		{
			listas[posVertice]->insert(verticeInserir, peso);
		}
		else
		{
			cout << "Vertice ja esta na lista da posicao " << posVertice << endl;
			//Não insere um vizinho repetido porém essa condição pode ser alterada
			//caso seja permitido arestas duplas
		}
	}
	else
	{
		int qnt = (posVertice - qntListas) + 1;
		expandListas(qnt);
		listas[posVertice]->insert(posVertice, 0);		  //Inserindo o vertice da posição na lista
		listas[posVertice]->insert(verticeInserir, peso); //Inserindo o vizinho
	}
}

bool listasAdj::removeIn(int posVertice, int verticeRemover)
{
	if (posVertice < qntListas)
	{
		return listas[posVertice]->remove(verticeRemover);
	}
	return false;
}

bool listasAdj::removeVertice(int posVertice)
{
	if (posVertice < qntListas)
	{
		verticeDeAdj *aux = listas[posVertice]->getFirst();
		aux = aux->proximo;

		while (aux)
		{
			//Apaga o vertice da lista de cada vertice que o tenha como vizinho
			listas[aux->id]->remove(posVertice);
			aux = aux->proximo;
		}

		return listas[posVertice]->deleteList();
	}

	return false;
}

void listasAdj::print()
{
	for (int i = 0; i < qntListas; i++)
	{
		if (listas[i])
		{
			listas[i]->print();
		}
	}
}

bool listasAdj::searchIn(int posVertice, int procurar)
{
	if (posVertice >= 0 and posVertice < qntListas)
	{
		if (listas[posVertice])
		{
			return listas[posVertice]->search(procurar);
		}
	}
	return false;
}

vertices::vertices(int qntVertices)
{
	this->qntVertices = qntVertices;
	vetor = new noh *[qntVertices];

	for (int i = 0; i < qntVertices; i++)
	{
		vetor[i] = NULL;
	}
}

vertices::vertices()
{
	qntVertices = 0;
	vetor = new noh *[qntVertices];
	for (int i = 0; i < qntVertices; i++)
	{
		vetor[i] = NULL;
	}
}

vertices::~vertices()
{
	delete[] vetor;
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
	int busca = search(novo);
	if (busca == -1)
	{
		expandVetor();
		int pos = qntVertices - 1;
		noh *novoNoh = new noh(pos, novo);
		vetor[pos] = novoNoh;
		return pos;
		//Ao inserir, retorna a posição para assim, inserir uma vizinhança
		//nas estruturas de dados dos vertices
	}
	else if (vetor[busca] == NULL)
	{
		//Se o busca encontrar uma posição no vetor e esta não
		//tenha algo (== NULL) ou seja vazia, o vertice será inserido nessa
		//posição
		noh *novoNoh = new noh(busca, novo);
		vetor[busca] = novoNoh;
		return busca;
	}
	else
	{
		//Se o busca retorna uma posição e ela tenha algo (!= NULL)
		//significa que o vertice já esteja no vetor
		return busca;
		//Retorna a posição para poder inserir na estrutura
		//de dados de vizinhanças dos vertices
	}
}

int vertices::insertVertice(coord novo)
{
	int busca = search(novo);
	if (busca == -1)
	{
		expandVetor();
		int pos = qntVertices - 1;
		noh *novoNoh = new noh(pos, novo);
		vetor[pos] = novoNoh;
		return pos;
		//Ao inserir, retorna a posição para assim, inserir uma vizinhança
		//nas estruturas de dados dos vertices
	}
	else if (vetor[busca] == NULL)
	{
		//Se o busca encontrar uma posição no vetor e esta não
		//tenha algo (== NULL) ou seja vazia, o vertice será inserido nessa
		//posição
		noh *novoNoh = new noh(busca, novo);
		vetor[busca] = novoNoh;
		return busca;
	}
	else
	{
		//Se o busca retorna uma posição e ela tenha algo (!= NULL)
		//significa que o vertice já esteja no vetor
		return busca;
		//Retorna a posição para poder inserir na estrutura
		//de dados de vizinhanças dos vertices
	}
}

int vertices::search(dado buscar)
{
	for (int i = 0; i < qntVertices; i++)
	{
		if (vetor[i])
		{
			if (compare(vetor[i]->dadosNoh, buscar) == true)
			{
				return i;
				//Não insere o mesmo noh no grafo duas vezes
			}
		}
		else
			return i; //Retorna a primeira posição vazia caso o vetor tenha
					  //essas posições vazias
	}
	return -1; //Se o vetor estiver cheio ou o noh não estiver no vetor
}

int vertices::search(coord buscar)
{
	for (int i = 0; i < qntVertices; i++)
	{
		if (vetor[i])
		{
			if (compare(vetor[i]->coordenadas, buscar) == true)
			{
				return i;
				//Não insere o mesmo noh no grafo duas vezes
			}
		}
		else
			return i; //Retorna a primeira posição vazia caso o vetor tenha
					  //essas posições vazias
	}
	return -1; //Se o vetor estiver cheio ou o noh não estiver no vetor
}

bool vertices::compare(dado A, dado B)
{
	if (A == B)
	{
		return true;
	}

	return false;
}
bool vertices::compare(coord A, coord B)
{
	if (A.x == B.x and A.y == B.y)
	{
		return true;
	}
	return false;
}

void vertices::print()
{
	for (int i = 0; i < qntVertices; i++)
	{
		if (vetor[i]->eucledian == false)
		{
			cout << vetor[i]->dadosNoh << " ";
		}
		else
		{
			cout << vetor[i]->coordenadas.x << "/"
				 << vetor[i]->coordenadas.y << " ";
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

int vertices::deleteVertice(coord del)
{
	int pos = search(del);

	deletePos(pos);

	return pos;
}

void vertices::deletePos(int pos)
{
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
			if (vetor[pos]->eucledian == false)
			{
				cout << vetor[pos]->dadosNoh;
			}
			else
			{
				cout << vetor[pos]->coordenadas.x << "/" << vetor[pos]->coordenadas.y;
			}
		}
		cout << " ";
	}
}

int vertices::getQntVertices()
{
	return qntVertices;
}

grafo::grafo(string orientation, bool ponderado, bool eucledian, int qualEstrutura)
{
	verticesDoGrafo = new vertices();
	this->orientation = orientation;
	this->ponderado = ponderado;
	this->eucledian = eucledian;
	this->qualEstrutura = qualEstrutura;
	lAdj = new listasAdj();
	mAdj = new matrizAdj();
	mInc = new matrizInc(orientation);
}

grafo::~grafo()
{
	delete verticesDoGrafo;
	delete lAdj;
	delete mAdj;
	delete mInc;
}

void grafo::insertAresta(dado dadosNohA, dado dadosNohB)
{
	int idA = verticesDoGrafo->insertVertice(dadosNohA);
	int idB = verticesDoGrafo->insertVertice(dadosNohB);

	inserctIn(idA, idB);
}

void grafo::insertAresta(coord coordenadasNohA, coord coordenadasNohB)
{
	int idA = verticesDoGrafo->insertVertice(coordenadasNohA);
	int idB = verticesDoGrafo->insertVertice(coordenadasNohB);

	inserctIn(idA, idB);
}

void grafo::insertAresta(dado dadosNohA, dado dadosNohB, int peso)
{
	int idA = verticesDoGrafo->insertVertice(dadosNohA);
	int idB = verticesDoGrafo->insertVertice(dadosNohB);

	inserctIn(idA, idB, peso);
}

void grafo::inserctIn(int idA, int idB)
{

	if (orientation == "UNDIRECTED")
	{
		if (qualEstrutura == 1)
		{
			lAdj->insertIn(idA, idB);
			lAdj->insertIn(idB, idA);
		}
		else if (qualEstrutura == 2)
		{
			mAdj->insert(idA, idB);
			mAdj->insert(idB, idA);
		}
		else if (qualEstrutura == 3)
		{
			mInc->insert(idA, idB);
		}
	}
	else if (orientation == "DIRECTED")
	{
		if (qualEstrutura == 1)
		{
			lAdj->insertIn(idA, idB);
		}
		else if (qualEstrutura == 2)
		{
			mAdj->insert(idA, idB);
		}
		else if (qualEstrutura == 3)
		{
			mInc->insert(idA, idB);
		}
	}
}

void grafo::inserctIn(int idA, int idB, int peso)
{

	if (orientation == "UNDIRECTED")
	{
		if (qualEstrutura == 1)
		{
			lAdj->insertIn(idA, idB, peso);
			lAdj->insertIn(idB, idA, peso);
		}
		else if (qualEstrutura == 2)
		{
			mAdj->insert(idA, idB, peso);
			mAdj->insert(idB, idA, peso);
		}
		else if (qualEstrutura == 3)
		{
			mInc->insert(idA, idB);
		}
	}
	else if (orientation == "DIRECTED")
	{
		if (qualEstrutura == 1)
		{
			lAdj->insertIn(idA, idB, peso);
		}
		else if (qualEstrutura == 2)
		{
			mAdj->insert(idA, idB, peso);
		}
		else if (qualEstrutura == 3)
		{
			mInc->insert(idA, idB);
		}
	}
}

void grafo::removeVertice(int pos)
{
	verticesDoGrafo->deletePos(pos);
}

int grafo::search(dado dadosNoh)
{
	return verticesDoGrafo->search(dadosNoh);
}
int grafo::search(coord coordenadas)
{
	return verticesDoGrafo->search(coordenadas);
}

listasAdj *grafo::getLAdj()
{
	return lAdj;
}

matrizAdj *grafo::getMAdj()
{
	return mAdj;
}

matrizInc *grafo::getMInc()
{
	return mInc;
}

bool grafo::getPonderado()
{
	return ponderado;
}

bool grafo::getEucledian()
{
	return eucledian;
}

int grafo::getQualEstrutura()
{
	return qualEstrutura;
}

string grafo::getOrientation()
{
	return orientation;
}

void grafo::printPos(int pos)
{
	verticesDoGrafo->printPos(pos);
}

void grafo::printVertices()
{
	verticesDoGrafo->print();
}

void grafo::printLAdj()
{
	int tam = lAdj->getQnt();
	for (int i = 0; i < tam; i++)
	{
		verticeDeAdj *aux = lAdj->getListaPos(i);
		while (aux)
		{
			int id = aux->getId();
			verticesDoGrafo->printPos(id);
			cout << " -> ";
			aux = aux->getProximo();
		}
		cout << "NULL\n";
	}
}

void grafo::printMAdj()
{
	printVertices();
	mAdj->printMat();
}

void grafo::printMInc()
{
	printVertices();
	mInc->printMat();
}

void grafo::printGrafo()
{
	if (qualEstrutura == 1)
	{
		printLAdj();
	}
	else if (qualEstrutura == 2)
	{
		printMAdj();
	}
	else if (qualEstrutura == 3)
	{
		printMInc();
	}
}

void grafo::setEstruturaDados(listasAdj *lAdj)
{
	delete this->lAdj;
	this->lAdj = lAdj;
}

void grafo::setEstruturaDados(matrizAdj *mAdj)
{
	delete this->mAdj;
	this->mAdj = mAdj;
}

void grafo::setEstruturaDados(matrizInc *mInc)
{
	delete this->mInc;
	this->mInc = mInc;
}

int grafo::getQntVertices()
{
	return verticesDoGrafo->getQntVertices();
}

// Teste das funções
////////////////////////////////////////////////////////////////////////
////////////////////////  Funções do Programa  /////////////////////////

void listToMatAdj(grafo *G)
{
	matrizAdj *mAdj = G->getMAdj();
	listasAdj *lAdj = G->getLAdj();
	int qnt = lAdj->getQnt();
	for (int i = 0; i < qnt; i++)
	{
		int id;
		verticeDeAdj *aux = lAdj->getListaPos(i);
		if (aux)
		{
			id = aux->getId();
			if (G->getPonderado() == false)
			{
				aux = aux->getProximo();
				while (aux)
				{
					mAdj->insert(id, aux->getId());
					aux = aux->getProximo();
				}
			}
			else
			{
				aux = aux->getProximo();
				while (aux)
				{
					mAdj->insert(id, aux->getId(), aux->getPeso());
					aux = aux->getProximo();
				}
			}
		}
	}
}

void listToMatInc(grafo *G)
{
	matrizInc *mInc = G->getMInc();
	listasAdj *lAdj = G->getLAdj();
	int qnt = lAdj->getQnt();
	for (int i = 0; i < qnt; i++)
	{
		int id;
		verticeDeAdj *aux = lAdj->getListaPos(i);
		if (aux)
		{
			id = aux->getId();
			aux = aux->getProximo();
			while (aux)
			{
				mInc->insert(id, aux->getId());
				aux = aux->getProximo();
			}
		}
	}
}

void matAdjToList(grafo *G)
{
	matrizAdj *mAdj = G->getMAdj();
	listasAdj *lAdj = G->getLAdj();
	int tam = mAdj->getTam();
	cout << tam << endl;
	for (int i = 0; i < tam; i++)
	{
		for (int j = 0; j < tam; j++)
		{
			if (mAdj->search(i, j) == true)
			{
				if (G->getPonderado() == true)
				{
					int peso = mAdj->getPeso(i, j);
					lAdj->insertIn(i, j, peso);
				}
				else
				{
					lAdj->insertIn(i, j);
				}
			}
		}
	}
}

void matAdjToMatInc(grafo *G)
{
	matrizInc *mInc = G->getMInc();
	matrizAdj *mAdj = G->getMAdj();
	int tam = mAdj->getTam();
	for (int i = 0; i < tam; i++)
	{
		for (int j = 0; j < tam; j++)
		{
			if (mAdj->search(i, j) == true)
			{
				mInc->insert(i, j);
			}
		}
	}
}

void matIncToListAdj(grafo *G)
{
	matrizInc *mInc = G->getMInc();
	listasAdj *lAdj = G->getLAdj();
	int colunas = mInc->getQntColunas();
	for (int i = 0; i < colunas; i++)
	{
		for (int j = 0; j < colunas; j++)
		{
			int comecoAresta;
			if (i != j and mInc->search(i, j, comecoAresta) == true)
			{
				G->printPos(i);
				cout << " ";
				G->printPos(j);
				cout << " aresta inicial " << comecoAresta << " ";
				if (comecoAresta == -1)
				{
					lAdj->insertIn(i, j);
				}
				else
				{
					G->printPos(comecoAresta);
					if (comecoAresta == i)
					{
						lAdj->insertIn(i, j);
					}
					else if (comecoAresta == j)
					{
						lAdj->insertIn(j, i);
					}
				}
				cout << endl;
			}
		}
	}
}

void matIncToMatAdj(grafo *G)
{
	matrizInc *mInc = G->getMInc();
	matrizAdj *mAdj = G->getMAdj();
	int colunas = mInc->getQntColunas();
	for (int i = 0; i < colunas; i++)
	{
		for (int j = 0; j < colunas; j++)
		{
			int comecoAresta;
			if (mInc->search(i, j, comecoAresta) == true and i != j)
			{
				if (comecoAresta == -1)
				{
					mAdj->insert(i, j);
				}
				else
				{
					if (comecoAresta == i)
					{
						mAdj->insert(i, j);
					}
					else
					{
						mAdj->insert(j, i);
					}
				}
			}
		}
	}
}

void obtemVizinhos(grafo *G, int u)
{
	//Recebe um vértice u como parâmetro e retorna um conjunto de vértices
	//vizinhos a u;
	if (G->getQualEstrutura() == 1)
	{
		listasAdj *lAdj = G->getLAdj();
		int tam = lAdj->getQnt();

		for (int i = 0; i < tam; i++)
		{
			if (i != u and (lAdj->searchIn(i, u) == true or lAdj->searchIn(u, i)))
			{
				G->printPos(i);
			}
			cout << endl;
		}
	}
	else if (G->getQualEstrutura() == 2)
	{
		matrizAdj *mAdj = G->getMAdj();
		int tam = mAdj->getTam();
		for (int i = 0; i < tam; i++)
		{
			if (mAdj->search(i, u) == true or mAdj->search(u, i) == true)
			{
				G->printPos(i);
			}
			cout << endl;
		}
	}
	else if (G->getQualEstrutura() == 3)
	{
		matrizInc *mInc = G->getMInc();
		int tam = mInc->getQntColunas();
		int comecoAresta;
		for (int i = 0; i < tam; i++)
		{
			if (i != u and (mInc->search(i, u, comecoAresta) == true or
							(mInc->search(u, i, comecoAresta) == true)))
			{
				G->printPos(i);
			}
			cout << endl;
		}
	}
}

void obtemPred(grafo *G, int u)
{
	//recebe um vértice u como parâmetro e retorna o conjunto de predecessores
	//do vértice em questão (para grafos direcionados);
	if (G->getOrientation() == "DIRECTED")
	{
		if (G->getQualEstrutura() == 1)
		{
			listasAdj *lAdj = G->getLAdj();
			int tam = lAdj->getQnt();
			for (int i = 0; i < tam; i++)
			{
				if (i != u and lAdj->searchIn(i, u) == true)
				{
					G->printPos(i);
					cout << "e predecessor de ";
					G->printPos(u);
				}
				cout << endl;
			}
		}
		else if (G->getQualEstrutura() == 2)
		{
			matrizAdj *mAdj = G->getMAdj();
			int tam = mAdj->getTam();
			for (int i = 0; i < tam; i++)
			{
				if (mAdj->search(i, u) == true)
				{
					G->printPos(i);
					cout << "e predecessor de ";
					G->printPos(u);
				}
				cout << endl;
			}
		}
		else if (G->getQualEstrutura() == 3)
		{
			matrizInc *mInc = G->getMInc();
			int tam = mInc->getQntColunas();
			int inicioAresta;
			for (int i = 0; i < tam; i++)
			{
				if (mInc->search(i, u, inicioAresta) == true or
					mInc->search(u, i, inicioAresta) == true)
				{
					if (inicioAresta == i)
					{
						G->printPos(i);
						cout << "e predecessor de ";
						G->printPos(u);
					}
					cout << endl;
				}
			}
		}
	}
	else
	{
		cout << "##############################################################" << endl;
		cerr << "#################     Grafo não orientado!     ###############" << endl;
		cout << "##############################################################" << endl;
		exit(EXIT_FAILURE);
	}
}

void obtemSuc(grafo *G, int u)
{
	//recebe um vértice u como parâmetro e retorna o conjunto de sucessores do
	//vértice em questão (para grafos direcionados);
	if (G->getOrientation() == "DIRECTED")
	{
		if (G->getQualEstrutura() == 1)
		{
			listasAdj *lAdj = G->getLAdj();
			int tam = lAdj->getQnt();
			for (int i = 0; i < tam; i++)
			{
				if (i != u and lAdj->searchIn(u, i) == true)
				{
					G->printPos(i);
					cout << "e sucessor de ";
					G->printPos(u);
				}
				cout << endl;
			}
		}
		else if (G->getQualEstrutura() == 2)
		{
			matrizAdj *mAdj = G->getMAdj();
			int tam = mAdj->getTam();
			for (int i = 0; i < tam; i++)
			{
				if (mAdj->search(u, i) == true)
				{
					G->printPos(i);
					cout << "e sucessor de ";
					G->printPos(u);
				}
				cout << endl;
			}
		}
		else if (G->getQualEstrutura() == 3)
		{
			matrizInc *mInc = G->getMInc();
			int tam = mInc->getQntColunas();
			int inicioAresta;
			for (int i = 0; i < tam; i++)
			{
				if (mInc->search(i, u, inicioAresta) == true or
					mInc->search(u, i, inicioAresta) == true)
				{
					if (inicioAresta == u)
					{
						G->printPos(i);
						cout << "e sucessor de ";
						G->printPos(u);
					}
					cout << endl;
				}
			}
		}
	}
	else
	{
		cout << "##############################################################" << endl;
		cerr << "#################     Grafo não orientado!     ###############" << endl;
		cout << "##############################################################" << endl;
		exit(EXIT_FAILURE);
	}
}

void ehVizinho(grafo *G, int u, int v)
{
	//recebe dois vértices u e v como parâmetros e retorna true se os mesmos são
	//vizinhos;
	if (G->getQualEstrutura() == 1)
	{
		listasAdj *lAdj = G->getLAdj();
		if (lAdj->searchIn(u, v) == true or
			lAdj->searchIn(v, u) == true)
		{
			G->printPos(u);
			cout << "e vizinho de ";
			G->printPos(v);
		}
		cout << endl;
	}
	else if (G->getQualEstrutura() == 2)
	{
		matrizAdj *mAdj = G->getMAdj();
		if (mAdj->search(u, v) == true or
			mAdj->search(v, u) == true)
		{
			G->printPos(u);
			cout << "e vizinho de ";
			G->printPos(v);
		}
		cout << endl;
	}
	else if (G->getQualEstrutura() == 3)
	{
		matrizInc *mInc = G->getMInc();
		int aux;
		if (mInc->search(u, v, aux) == true or
			mInc->search(v, u, aux) == true)
		{
			G->printPos(u);
			cout << "e vizinho de ";
			G->printPos(v);
		}
		cout << endl;
	}
}

void ehPredecessor(grafo *G, int u, int v)
{
	//recebe dois vértices u e v como parâmetros e retorna true se v é predecessor
	//de u (para grafos direcionados);
	if (G->getOrientation() == "DIRECTED")
	{
		if (G->getQualEstrutura() == 1)
		{
			listasAdj *lAdj = G->getLAdj();
			if (lAdj->searchIn(v, u) == true)
			{
				G->printPos(v);
				cout << "e predecessor de ";
				G->printPos(u);
			}
			cout << endl;
		}
		else if (G->getQualEstrutura() == 2)
		{
			matrizAdj *mAdj = G->getMAdj();
			if (mAdj->search(v, u) == true)
			{
				G->printPos(v);
				cout << "e predecessor de ";
				G->printPos(u);
			}
			cout << endl;
		}
		else if (G->getQualEstrutura() == 3)
		{
			matrizInc *mInc = G->getMInc();
			int inicioAresta;
			if (mInc->search(v, u, inicioAresta) == true or
				mInc->search(u, v, inicioAresta) == true)
			{
				if (inicioAresta == v)
				{
					G->printPos(v);
					cout << "e predecessor de ";
					G->printPos(u);
				}
				cout << endl;
			}
		}
	}
	else
	{
		cout << "##############################################################" << endl;
		cerr << "#################     Grafo não orientado!     ###############" << endl;
		cout << "##############################################################" << endl;
		exit(EXIT_FAILURE);
	}
}

void ehSucessor(grafo *G, int u, int v)
{
	//recebe dois vértices u e v como parâmetros e retorna true se v é sucessor
	//de u (para grafos direcionados);
	if (G->getOrientation() == "DIRECTED")
	{
		if (G->getQualEstrutura() == 1)
		{
			listasAdj *lAdj = G->getLAdj();
			if (lAdj->searchIn(u, v) == true)
			{
				G->printPos(v);
				cout << "e sucessor de ";
				G->printPos(u);
			}
			cout << endl;
		}
		else if (G->getQualEstrutura() == 2)
		{
			matrizAdj *mAdj = G->getMAdj();
			if (mAdj->search(u, v) == true)
			{
				G->printPos(v);
				cout << "e sucessor de ";
				G->printPos(u);
			}
			cout << endl;
		}
		else if (G->getQualEstrutura() == 3)
		{
			matrizInc *mInc = G->getMInc();
			int inicioAresta;
			if (mInc->search(u, v, inicioAresta) == true)
			{
				if (inicioAresta == u)
				{
					G->printPos(v);
					cout << "e sucessor de ";
					G->printPos(u);
				}
				cout << endl;
			}
		}
	}
	else
	{
		cout << "##############################################################" << endl;
		cerr << "#################     Grafo não orientado!     ###############" << endl;
		cout << "##############################################################" << endl;
		exit(EXIT_FAILURE);
	}
}

void delVertice(grafo *G, int u)
{
	//deleta um vértice do grafo e as arestas incidentes a ele (por consequência);
	int qualEstrutura = G->getQualEstrutura();
	G->removeVertice(u);
	if (qualEstrutura == 1)
	{
		listasAdj *lAdj = G->getLAdj();
		lAdj->removeVertice(u);
	}
	else if (qualEstrutura == 2)
	{
		matrizAdj *mAdj = G->getMAdj();
		mAdj->removeVertice(u);
	}
	else if (qualEstrutura == 3)
	{
		matrizInc *mInc = G->getMInc();
		mInc->removeVertice(u);
	}
}

void delAresta(grafo *G, int u, int v)
{
	//deleta a aresta (u; v) passada como parâmetro;
	int qualEstrutura = G->getQualEstrutura();
	if (qualEstrutura == 1)
	{
		listasAdj *lAdj = G->getLAdj();
		lAdj->removeIn(u, v);
	}
	else if (qualEstrutura == 2)
	{
		matrizAdj *mAdj = G->getMAdj();
		mAdj->remove(u, v);
	}
	else if (qualEstrutura == 3)
	{
		matrizInc *mInc = G->getMInc();
		mInc->remove(u, v);
	}
}

grafo *criaSubGrafo(grafo *G)
{
	//Cria uma cópia do Grafo G para ser o subGrafo
	grafo *subGrafo = new grafo(G->getOrientation(), G->getPonderado(),
								G->getEucledian(), G->getQualEstrutura());

	if (G->getQualEstrutura() == 1)
	{
		subGrafo->setEstruturaDados(G->getLAdj());
	}
	else if (G->getQualEstrutura() == 2)
	{
		subGrafo->setEstruturaDados(G->getMAdj());
	}
	else if (G->getQualEstrutura() == 3)
	{
		subGrafo->setEstruturaDados(G->getMInc());
	}

	return subGrafo;
}

//~ grafo* geraSubGrafoIV(grafo* G){
//~ grafo* subGrafo = criaSubGrafo(G);
//~ return subGrafo;
//~ }

//~ grafo* geraSubGrafoIA(grafo* G){
//~ grafo* subGrafo = criaSubGrafo(G);
//~ return subGrafo;
//~ }

////////////////////////////////////////////////////////////////////////
//////////////////////////Funções do Main///////////////////////////////

string nomeArq()
{
	cout << "##############   Digite o nome do Arquivo: ";
	cout << "#################################################################" << endl;
	string nome;
	cin >> nome;
	return nome;
}

bool ePonderado()
{
	cout << "#################################################################" << endl;
	cout << "##################### O Grafo é Ponderado? ######################" << endl;
	cout << "#################################################################" << endl;
	cout << "######################## Sim	-----> [1] #########################" << endl;
	cout << "######################## Não -----> [2] #########################" << endl;
	cout << "#################################################################" << endl;

	int comando;
	cin >> comando;

	if (comando == 1)
	{
		return true;
	}
	else if (comando == 2)
	{
		return false;
	}
	else
	{
		cout << "#################################################################" << endl;
		cout << "######################     Opção invalida     ###################" << endl;
		cout << "#################################################################" << endl;
		exit(EXIT_FAILURE);
	}
}

int estruturaUtilizada()
{
	cout << "######## Qual a Estrutura de Dados deseja utilizar? #########" << endl;
	cout << "#################################################################" << endl;
	cout << "############## Lista de Adjacencias	-----> [1]  ################" << endl;
	cout << "############## Matriz de Adjacencias -----> [2]  ################" << endl;
	cout << "############## Matriz de Incidencias -----> [3]  ################" << endl;
	cout << "#################################################################" << endl;

	int comando;
	cin >> comando;

	if (comando > 0 and comando < 4)
	{
		return comando;
	}
	else
	{
		cout << "#################################################################" << endl;
		cout << "######################     Opção invalida     ###################" << endl;
		cout << "#################################################################" << endl;
		exit(EXIT_FAILURE);
	}
}

bool dadosVertices()
{
	cout << "## Quais os tipos de dados serão passados para os vertices? ##" << endl;
	cout << "#################################################################" << endl;
	cout << "############# Coordenadas(Euclediano)  -----> [1] ###############" << endl;
	cout << "##################  Apenas valores	    -----> [2] ###############" << endl;
	cout << "#################################################################" << endl;

	int comando;
	cin >> comando;

	if (comando == 1)
	{
		return true;
	}
	else if (comando == 2)
	{
		return false;
	}
	else
	{
		cout << "#################################################################" << endl;
		cout << "#####################     Opção invalida     ####################" << endl;
		cout << "#################################################################" << endl;
		exit(EXIT_FAILURE);
	}
}

void estruturaDeDadosGrafo(grafo *G, int comando)
{
	int estrutura = G->getQualEstrutura();
	if (comando == estrutura)
	{
		G->printGrafo();
	}
	else
	{
		if (comando == 1)
		{
			if (estrutura == 2)
			{
				matAdjToList(G);
			}
			else if (estrutura == 3)
			{
				matIncToListAdj(G);
			}
			G->printLAdj();
		}
		else if (comando == 2)
		{
			if (estrutura == 1)
			{
				listToMatAdj(G);
			}
			else if (estrutura == 3)
			{
				matIncToMatAdj(G);
			}
			G->printMAdj();
		}
		else if (comando == 3)
		{
			if (estrutura == 1)
			{
				listToMatInc(G);
			}
			else if (estrutura == 2)
			{
				matAdjToMatInc(G);
			}
			G->printMInc();
		}
	}
}

int comand()
{
	int comando;

	cout << "#################################################################" << endl;
	cout << "#################################################################" << endl;
	cout << "#################################################################" << endl;
	cout << "### Obter Lista de Adjacencias do Grafo					 -----> [1]  ###" << endl;
	cout << "### Obter Matriz de Adjacencias do Grafo					 -----> [2]  ###" << endl;
	cout << "### Obter Matriz de Incidencias do Grafo					 -----> [3]  ###" << endl;
	cout << "### Obter vizinhos de um vertice u							   -----> [4]  ###" << endl;
	cout << "### Obter predecessores de um vertice u					 -----> [5]  ###" << endl;
	cout << "### Obter Sucessores de um vertice u							 -----> [6]  ###" << endl;
	cout << "### Verificar se dois vertices u e v sao vizinhos -----> [7]  ###" << endl;
	cout << "### Verificar se v e predecessor de u					   -----> [8]  ###" << endl;
	cout << "### Verificar se v e sucessor de u							   -----> [9]  ###" << endl;
	cout << "### Deletar um vertice							               -----> [10] ###" << endl;
	cout << "### Deletar uma aresta							               -----> [11] ###" << endl;
	cout << "### Gerar subGrafo induzido por vertices				   -----> [12] ###" << endl;
	cout << "### Gerar subGrafo induzido por arestas				   -----> [13] ###" << endl;
	cout << "####################### Sair -----> [0] #########################" << endl;
	cout << "#################################################################" << endl;

	cin >> comando;

	return comando;
}

int getVertice(grafo *G)
{
	bool eucledian = G->getEucledian();
	int vertice;

	if (eucledian == true)
	{
		cout << "#################################################################" << endl;
		cout << "############# Digite as coordenadas do vertice:  ################";
		cout << "############# X: ";
		coord coordenadas;
		cin >> coordenadas.x;
		cout << "############# Y: ";
		cin >> coordenadas.y;
		vertice = G->search(coordenadas);
	}
	else
	{
		cout << "#################################################################" << endl;
		cout << "############# Digite o valor do vertice: ";
		dado dadosNoh;
		cin >> dadosNoh;
		vertice = G->search(dadosNoh);
	}

	return vertice;
}

void menu(grafo *G)
{

	int comando = -1;
	do
	{
		comando = comand();
		if (comando >= 1 and comando <= 3)
		{
			estruturaDeDadosGrafo(G, comando);
		}
		else if (comando == 4)
		{
			int u = getVertice(G);
			if (u == -1)
			{
				cout << "#################################################################" << endl;
				cout << "#################  Vertice não está no Grafo   ##################" << endl;
				cout << "#################################################################" << endl;
			}
			else
			{
				cout << "#################################################################" << endl;
				cout << "##################  Vizinhos do vertice  ########################" << endl;
				G->printPos(u);
				cout << "\n";
				obtemVizinhos(G, u);
				cout << "#################################################################" << endl;
			}
		}
		else if (comando == 5)
		{
			int u = getVertice(G);
			if (u == -1)
			{
				cout << "#################################################################" << endl;
				cout << "#################  Vertice não está no Grafo   ##################" << endl;
				cout << "#################################################################" << endl;
			}
			else
			{
				cout << "#################################################################" << endl;
				cout << "################  Predecessores do vertice  ######################" << endl;
				G->printPos(u);
				cout << "\n";
				obtemPred(G, u);
				cout << "#################################################################" << endl;
			}
		}
		else if (comando == 6)
		{
			int u = getVertice(G);
			if (u == -1)
			{
				cout << "#################################################################" << endl;
				cout << "#################  Vertice não está no Grafo   ##################" << endl;
				cout << "#################################################################" << endl;
			}
			else
			{
				cout << "#################################################################" << endl;
				cout << "################   Sucessores do vertice   ######################" << endl;
				G->printPos(u);
				cout << "\n";
				obtemSuc(G, u);
				cout << "#################################################################" << endl;
			}
		}
		else if (comando == 7)
		{
			cout << "#################################################################" << endl;
			cout << "#####################     Vertice u     #########################" << endl;
			int u = getVertice(G);
			cout << "#####################     Vertice v     #########################" << endl;
			int v = getVertice(G);
			if (u == -1 or v == -1)
			{
				cout << "#################################################################" << endl;
				cout << "#################  Vertice não está no Grafo   ##################" << endl;
				cout << "#################################################################" << endl;
			}
			else
			{
				ehVizinho(G, u, v);
			}
		}
		else if (comando == 8)
		{
			cout << "#################################################################" << endl;
			cout << "#####################     Vertice u     #########################" << endl;
			int u = getVertice(G);
			cout << "#####################     Vertice v     #########################" << endl;
			int v = getVertice(G);
			if (u == -1 or v == -1)
			{
				cout << "#################################################################" << endl;
				cout << "#################  Vertice não está no Grafo   ##################" << endl;
				cout << "#################################################################" << endl;
			}
			else
			{
				ehPredecessor(G, u, v);
			}
		}
		else if (comando == 9)
		{
			cout << "#################################################################" << endl;
			cout << "#####################     Vertice u     #########################" << endl;
			int u = getVertice(G);
			cout << "#####################     Vertice v     #########################" << endl;
			int v = getVertice(G);
			if (u == -1 or v == -1)
			{
				cout << "#################################################################" << endl;
				cout << "#################  Vertice não está no Grafo   ##################" << endl;
				cout << "#################################################################" << endl;
			}
			else
			{
				ehSucessor(G, u, v);
			}
		}
		else if (comando == 10)
		{
			cout << "#################################################################" << endl;
			cout << "#################   Vertice a ser removido   ####################" << endl;
			int u = getVertice(G);
			if (u == -1)
			{
				cout << "#################################################################" << endl;
				cout << "#################  Vertice não está no Grafo   ##################" << endl;
				cout << "#################################################################" << endl;
			}
			else
			{
				delVertice(G, u);
			}
		}
		else if (comando == 11)
		{
			cout << "#################################################################" << endl;
			cout << "#####################     Vertice u     #########################" << endl;
			int u = getVertice(G);
			cout << "#####################     Vertice v     #########################" << endl;
			int v = getVertice(G);
			if (u == -1 or v == -1)
			{
				cout << "#################################################################" << endl;
				cout << "#################  Vertice não está no Grafo   ##################" << endl;
				cout << "#################################################################" << endl;
			}
			else
			{
				delAresta(G, u, v);
			}
		}
		else if (comando == 12)
		{
			grafo *subGrafo = criaSubGrafo(G);
			cout << "#################################################################" << endl;
			cout << "####### Quantos vertices deseja eliminar do Grafo: ";

			int qnt;
			cin >> qnt;

			if (qnt > subGrafo->getQntVertices())
			{
				cout << "#################################################################" << endl;
				cout << "##### Quantidade de vertices escolhida maior que quantidade  ####" << endl;
				cout << "##### a de vertices do Grafo                   ##################" << endl;
			}
			else
			{
				for (int i = 0; i < qnt; i++)
				{
					cout << "#################################################################" << endl;
					cout << "#####################     Vertice u     #########################" << endl;
					int u = getVertice(subGrafo);
					if (u == -1)
					{
						cout << "#################################################################" << endl;
						cout << "#################  Vertice não está no Grafo   ##################" << endl;
						cout << "#################################################################" << endl;
					}
					else
					{
						delVertice(subGrafo, u);
					}
				}
			}
		}
		else if (comando == 13)
		{
			grafo *subGrafo = criaSubGrafo(G);
			cout << "#################################################################" << endl;
			cout << "####### Quantas arestas deseja eliminar do Grafo: ";

			int qnt;
			cin >> qnt;

			for (int i = 0; i < qnt; i++)
			{
				cout << "#################################################################" << endl;
				cout << "#####################     Vertice u     #########################" << endl;
				int u = getVertice(subGrafo);
				cout << "#####################     Vertice v     #########################" << endl;
				int v = getVertice(subGrafo);
				if (u == -1 or v == -1)
				{
					cout << "#################################################################" << endl;
					cout << "#################  Vertice não está no Grafo   ##################" << endl;
					cout << "#################################################################" << endl;
				}
				else
				{
					delAresta(subGrafo, u, v);
				}
			}
		}
		else
		{
			cout << "#################################################################" << endl;
			cout << "#####################     Opção invalida     ####################" << endl;
			cout << "#################################################################" << endl;
		}
	} while (comando != 0);
}
