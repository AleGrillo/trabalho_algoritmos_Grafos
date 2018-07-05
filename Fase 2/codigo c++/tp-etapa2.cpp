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
				mat[i][j] = 0;
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
	if (verticeA < tamanhoMat and verticeB < tamanhoMat)
	{
		return matriz[verticeA][verticeB];
	}
	
	else{
		//O elemento não está na matriz
		return -1;
	}
}

void matrizAdj::remove(int verticeA, int verticeB){
	matriz[verticeA][verticeB] = -1;
}

void matrizAdj::removeVertice(int vertice){
	if(vertice < tamanhoMat){
		for (int i = 0; i < tamanhoMat; i++)
		{
			remove(vertice, i);
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

verticeDeAdj* lista::getFirst(){
	if(primeiro){
		verticeDeAdj* aux = new verticeDeAdj(primeiro->id, primeiro->distancia);
		return aux;
	}
	else return NULL;
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

void listasAdj::insertIn(int posVertice, int verticeInserir, double distancia)
{
	if (posVertice < qntListas)
	{
		listas[posVertice]->insert(verticeInserir, distancia);
	}
	else
	{
		cout << "Posição maior que a quantidade de vertices alocados\n";
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

verticeDeAdj* listasAdj::getFirst(int pos){
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

void vertices::deleteVetor(){
	for (int i = 0; i < qntVertices; i++)
	{
		delete vetor[i];
	}
	
	delete[] vetor;
}

void vertices::create(int qntVertices){
	pos = 0;
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
			noh* novo = new noh(vetor[i]->id, vetor[i]->peso);
			vetorAux[i] = novo;
		}
		else
		{
			vetorAux[i] = NULL;
		}
	}

	deleteVetor();

	vetor = vetorAux;
	qntVertices = qntAux;
}

int vertices::insertVertice(dado novo, int id)
{
	if(pos == qntVertices){
		expandVetor();
		pos = qntVertices - 1;
	}
	noh *novoNoh = new noh(id, novo); //Para inserir no grupo de alunos
	vetor[pos] = novoNoh;
	pos++;
	return pos - 1;
	//Ao inserir, retorna a posição para assim, inserir uma vizinhança
	//nas estruturas de dados dos vertices
}

int vertices::insertVertice(dado novo)
{
	if(pos == qntVertices){
		expandVetor();
		pos = qntVertices - 1;
	}
	noh *novoNoh = new noh(pos, novo);
	vetor[pos] = novoNoh;
	pos++;
	return pos - 1;
	//Ao inserir, retorna a posição para assim, inserir uma vizinhança
	//nas estruturas de dados dos vertices
}

void vertices::print()
{
	for (int i = 0; i < qntVertices; i++)
	{
		if (vetor[i])
		{
			cout << vetor[i]->id << "->" ;
		}
	}
	cout << endl;
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

dado vertices::getVertice(int pos){
	if(pos < qntVertices and vetor[pos]){
		return vetor[pos]->peso;
	}
	
	else{
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

int* vertices::getIds(){
	int* vetorAux = new int[qntVertices];
	
	for (int i = 0; i < qntVertices; i++)
	{
		if(vetor[i]){
			vetorAux[i] = vetor[i]->id;
		}
		else{
			vetorAux[i] = -1;
		}
	}
	return vetorAux;
}

inline bool vertices::isEmpty(){
	if(tamanho == 0){
		return true;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////
//////////////////////////Classe Group//////////////////////////////////

group::group(int L, int U){
	alunos = new vertices();
	qntAlunos = 0;
	this->L = L;
	this->U = U;
	peso_total = 0;
	distancia_total = 0.0;
}

group::~group(){
	delete alunos;
}

void group::insertAluno(dado peso, int id){
	alunos->insertVertice(peso, id);
	peso_total += peso;
}

int group::getQntAlunos(){
	return alunos->getQntVertices();
}

vertices* group::getGroup(){
	return alunos;
}

void group::print(){
	alunos->print();
	cout << "Peso total: " << peso_total << endl;
	cout << "Quantidade de alunos: " << getQntAlunos() << endl;
	cout << "Distancia Total: " << getDistancia() << endl;
}

int group::getPeso(){
	return peso_total;
}

int* group::getIds(){
	return alunos->getIds();
}

int group::getL(){
	return L;
}

int group::getU(){
	return U;
}

void group::setDistancia(double distancia){
	distancia_total += distancia;
}

double group::getDistancia(){
	return distancia_total;
}

////////////////////////////////////////////////////////////////////////
/////////////////////////  Classe Vetor de Grupos //////////////////////

vetGroup::vetGroup(int qntGrupos){
	tamanho = qntGrupos;
	this->qntGrupos = qntGrupos;
	grupos = new group *[qntGrupos];
	
	for (int i = 0; i < qntGrupos; i++)
	{
		grupos[i] = NULL;
	}
}

vetGroup::~vetGroup(){
	for (int i = 0; i < qntGrupos; i++)
	{
		delete grupos[i];
	}
	
	delete []grupos;
}

void vetGroup::insertIn(int pos, dado peso, int id){
	if(pos < qntGrupos){
		grupos[pos]->insertAluno(peso, id);
	}
}

group* vetGroup::removeGroup(int pos){
	if(pos == qntGrupos -1){
		qntGrupos--;
		return grupos[qntGrupos];
	}
	else if(pos < qntGrupos -1){
		swap(grupos[pos], grupos[qntGrupos - 1]);
		qntGrupos--;
		return grupos[qntGrupos];
	}
	else{
		return NULL;
	}
}

int vetGroup::getPeso(int pos){
	if(pos < qntGrupos){
		return grupos[pos]->getPeso();
	}
	
	else return -1;
}

void vetGroup::insertGroup(int pos, int L, int U){
	if(pos < qntGrupos){
		group* grupo = new group(L, U);
		grupos[pos] = grupo;
	}
}

int vetGroup::getTam(){
	return tamanho;
}

int* vetGroup::getIds(int pos){
	if(pos < qntGrupos){
		return grupos[pos]->getIds();
	}
	else return NULL;
}

group* vetGroup::getGroup(int pos){
	return grupos[pos];
}

void vetGroup::print(){
	for (int i = 0; i < qntGrupos; i++)
	{
		cout << "Grupo " << i << ": ";
		grupos[i]->print();
	}
	cout << endl;
}

int vetGroup::getL(int pos){
	if(pos < qntGrupos){
		return grupos[pos]->getL();
	}
	else{
		return -1;
	}
}

int vetGroup::getU(int pos){
	if(pos < qntGrupos){
		return grupos[pos]->getU();
	}
	else{
		return -1;
	}
}

void vetGroup::reset(){
	qntGrupos = tamanho;
}

int vetGroup::getQnt(){
	return qntGrupos;
}

////////////////////////////////////////////////////////////////////////
///////////////////////////Funções basicas//////////////////////////////

void read(fstream &arquivo, vetGroup* &grupos, vertices* &vertices_grafo, listasAdj* &lAdj, matrizAdj* &mAdj,
		  int &qntVertices, int &qntGrupos){
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

	while(arquivo.good()){
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

void quickSort(int* vetorId, int* vetor, int qnt, int esq, int dir){
	//Para ordenar o vetor de contadores e retirar cada vértice para um grupo por vez
	int i = esq;
	int j = dir;
	int pivo = vetor[(dir + esq) / 2];

	while(i <= j){
		while(vetor[i] > pivo) i++;
		while(vetor[j] < pivo) j--;
		if(i <= j){
			swap(vetor[i],vetor[j]);
			swap(vetorId[i],vetorId[j]);
			i++;
			j--;
		}
	}
	if(esq < j) quickSort(vetorId, vetor, qnt, esq, j);
	if(i < dir) quickSort(vetorId, vetor, qnt, i, dir);
}

int* vetorContador(listasAdj* lAdj, int qnt){
	int* vetorID = new int[qnt];
	int* vetor = new int[qnt];
	verticeDeAdj* vAdj = NULL;
	
	for (int i = 0; i < qnt; i++)
	{
		vetor[i] = 0;
	}
	
	for (int i = 0; i < qnt; i++)
	{
		vAdj = lAdj->getFirst(i);
		vetorID[i] = vAdj->getId();
		vetor[vAdj->getId()]++;
	}
	
	quickSort(vetorID, vetor, qnt, 0, qnt - 1);
	delete []vetor;
	return vetorID;
}

double max_distance(vetGroup* grupos, matrizAdj* mAdj){
	double distancia = 0.0;
	int tam = grupos->getQnt();
	group* grupo = NULL;
	int* vetorIds = NULL;
	int verticeA, verticeB;
	
	for (int i = 0; i < tam; i++)
	{
		grupo = grupos->getGroup(i);
		vetorIds = grupo->getIds();
		int qnt = grupo->getQntAlunos();
		for (int j = 0; j < qnt; j++)
		{
			verticeA = vetorIds[j];
			for (int k = 0; k< qnt; k++)
			{
				verticeB = vetorIds[k];
				distancia += mAdj->getDistancia(verticeA, verticeB);
			}
		}
	}
	
	return distancia;
}

void initializeGroups(vetGroup* grupos, listasAdj* lAdj, vertices* vert, int* vetorID, int qntGrupos){
	for (int i = 0; i < qntGrupos; i++)
	{
		dado peso = vert->getVertice(vetorID[i]);
		grupos->insertIn(i, peso, vetorID[i]);
		lAdj->removeVertice(vetorID[i]);
		vert->remove(vetorID[i]);
	}
}

void insert_to_group(vetGroup* grupos, vertices* vertices_grafo, listasAdj* lAdj,
						int pos, dado peso, int insert){
							
	grupos->insertIn(pos, peso, insert); //Insere esse vertice no grupo que poderá aceitar a maior
												//distância
	vertices_grafo->remove(insert); //Apaga o vértice inserido no grupo do conjunto de vértices
										   //para que o mesmo não possa ser inserido em outros grupos
	lAdj->removeVertice(insert); //Remove o mesmo das listas de adjacências para que ele não possa
										//ser incontrado como maior distância novamente
}

int searchMaxInsercion(vetGroup* grupos, listasAdj* lAdj, int qntGrupos, int& max_insercion){
	double maior_dist = DBL_MIN; 
	int pos = -1;
	int id;
	double distancia;
	verticeDeAdj* vertice;
	for (int i = 0; i < qntGrupos; i++)
	{
		group* aux = grupos->getGroup(i); //Retorna cada grupo já previamente criado
		int* ids = aux->getIds(); //Um vetor com todos os ids dos vertices do grupo
		int tam = aux->getQntAlunos(); //A quantidade de alunos que está presente em um grupo
		for (int j = 0; j < tam; j++)
		{
			id = ids[j];
			vertice = lAdj->getFirst(id);//Retorna o primeiro elemento da lista de
										 //adjacencias de um grupo
			if(vertice){
				distancia = vertice->getDistancia(); //A maior distancia será dada pelo primeiro vértice
													 //da lista de adjacências da posição
				if(maior_dist < distancia){ //Se a maior distância encontrada for menor que a distância do
											//do próximo vértice
					maior_dist = distancia;
					max_insercion = vertice->getId();
					pos = i;
				}
			}
		}
	}
	return pos;
}

void attain_upper_limit(vertices* vertices_grafo, vetGroup* grupos, listasAdj* lAdj, int qntGrupos){
	dado peso;
	int max_insercion, U, peso_total;
	int pos = -1;
					 
	while(grupos->getQnt() > 0 and vertices_grafo->isEmpty() == false){
		qntGrupos = grupos->getQnt();
		pos = searchMaxInsercion(grupos, lAdj, qntGrupos, max_insercion);//Encontra a distancia mais longa possível
																		 //dentre todos os vértices do grupo
		if(pos > -1){//Se foi achado uma distância mais longa para inserção
			peso = vertices_grafo->getVertice(max_insercion);//O peso será o valor do vertice
															 //com a maior distancia da maior inserção
			peso_total = grupos->getPeso(pos); //Peso atual do grupo que é um somatório
											   //dos pesos de todos os vértices do grupo
			U = grupos->getU(pos);
			if(peso > -1){
				if(peso + peso_total <= U){
					insert_to_group(grupos, vertices_grafo, lAdj, pos, peso, max_insercion);
				}
				else{
					grupos->removeGroup(pos);
				}
			}
			else{
				lAdj->removeVertice(max_insercion);
			}
		}
	}
	
	grupos->reset();
}

void mount_groups(vertices* vertices_grafo, vetGroup* grupos, listasAdj* lAdj, int qntGrupos){
	int pos = -1;
	int max_insercion, L, peso_total;
	dado peso;
	
	
	//Esse loop irá rodar enquanto estiverem grupos abaixo do limitante inferior
	while(grupos->getQnt() > 0){
		qntGrupos = grupos->getQnt();
		pos = searchMaxInsercion(grupos, lAdj, qntGrupos, max_insercion);//Encontra a distancia mais longa possível
																					//dentre todos os vértices do grupo
		if(pos > -1){//Se foi achado uma distância mais longa para inserção
			peso = vertices_grafo->getVertice(max_insercion);//O peso será o valor do vertice
															 //com a maior distancia da maior inserção
			if(peso > -1){ //Se o peso for maior que -1 significa que o vértice ainda não
						   //possui um grupo
				insert_to_group(grupos, vertices_grafo, lAdj, pos, peso, max_insercion);
			}
			else{
				//Se o peso for igual a -1 significa que o vértice já foi inserido 
				//em um grupo e removido do vetor original de vertices
				lAdj->removeVertice(max_insercion);//Então o vértice é apagado das listas de adjacências para não ser inserido
												   //em outros grupos
			}
			L = grupos->getL(pos); //Limitante inferior do grupo
			peso_total = grupos->getPeso(pos); //Peso atual do grupo que é um somatório
											   //dos pesos de todos os vértices do grupo
			if(L >= 0){
				if(peso_total >= L){ //Se o peso total do grupo for maior que o limitante inferior
					grupos->removeGroup(pos); //O grupo é removido para a ultima posição do vetor e
											  //o tamanho desse vetor é reduzido
				}
			}
		}
	}
	
	grupos->reset(); //Restaura a quantidade de grupos pois a mesma é reduzida
					 //quando um grupo atinge o limitante inferior (L)
	
	attain_upper_limit(vertices_grafo, grupos, lAdj, qntGrupos);
}

//////////////////////////////////////////////////////////////////////////
/////////////////////////Metodos Solução Dois/////////////////////////////

void insert_to_Group(vetGroup* grupos, vertices* vertices_grafo, matrizAdj* mAdj,
						int pos, dado peso, int insert){
							
	grupos->insertIn(pos, peso, insert); //Insere esse vertice no grupo que poderá aceitar a maior
												//distância
	vertices_grafo->remove(insert); //Apaga o vértice inserido no grupo do conjunto de vértices
										   //para que o mesmo não possa ser inserido em outros grupos
	mAdj->removeVertice(insert); //Remove o mesmo das listas de adjacências para que ele não possa
										//ser incontrado como maior distância novamente
}

double compute_total_distance(int verticeA, matrizAdj* mAdj, int* ids, int tam){
	double distancia_total = 0.0;
	double distancia;
	for (int i = 0; i < tam; i++)
	{
		distancia = mAdj->getDistancia(verticeA, ids[i]);
		if(distancia > -1){
			distancia_total += distancia;
		}
	}
	return distancia_total;
}

int searchMaxDistance(group* grupo, vertices* vertices_grafo, matrizAdj* mAdj, double &distancia){
	int vertice = -1;
	double max_distance = DBL_MIN;
	double new_distance = 0.0;
	int* ids = grupo->getIds();
	int tam = grupo->getQntAlunos();
	int qntVertices = vertices_grafo->getQntVertices();
	
	for (int i = 0; i < qntVertices; i++)
	{
		new_distance = compute_total_distance(i, mAdj, ids, tam);
		if(new_distance + grupo->getDistancia() > max_distance){
			vertice = i;
			distancia =  new_distance; //Para inserirmos essa distancia no grupo depois
			max_distance = new_distance + grupo->getDistancia();
		}
	}
	//~ cout << vertice << " " << distancia << endl;
	return vertice;
}

void attain_upper_limit(vertices* vertices_grafo, vetGroup* grupos, matrizAdj* mAdj){
	group* grupo = NULL;
	double distancia;
	int pos = -1;
	int peso = -1;
	int max_distance = 0;
	int U, peso_total;
	int qntGrupos = grupos->getQnt();
					 
	while(qntGrupos > 0 and vertices_grafo->isEmpty() == false){
		qntGrupos = grupos->getQnt();
		for (int i = 0; i < qntGrupos; i++)
		{
			pos = i;
			grupo = grupos->getGroup(i);
		}
		
		max_distance = searchMaxDistance(grupo, vertices_grafo, mAdj, distancia);//Encontra a distancia mais longa possível
																		 //dentre todos os vértices do grupo
		if(max_distance > -1){
			peso = vertices_grafo->getVertice(max_distance);//O peso será o valor do vertice
															 //com a maior distancia da maior inserção
			peso_total = grupos->getPeso(pos); //Peso atual do grupo que é um somatório
											   //dos pesos de todos os vértices do grupo
			U = grupos->getU(pos);
			if(peso > -1){
				if(peso + peso_total <= U){
					insert_to_Group(grupos, vertices_grafo, mAdj, pos, peso, max_distance);
					grupo->setDistancia(distancia);
				}
				else{
					grupos->removeGroup(pos);
				}
			}
			else{
				mAdj->removeVertice(max_distance);
			}
		}
	}
	
	grupos->reset();
}

void mount_groups(vertices* vertices_grafo, vetGroup* grupos, matrizAdj* mAdj){
	group* grupo = NULL;
	double distancia;
	int qntGrupos;
	int pos = -1;
	int peso = -1;
	int max_distance = 0;
	int L, peso_total;
	
	//Esse loop irá rodar enquanto estiverem grupos abaixo do limitante inferior
	while(grupos->getQnt() > 0 and max_distance > -1){
		qntGrupos = grupos->getQnt();
		for (int i = 0; i < qntGrupos; i++)
		{
			pos = i;
			grupo = grupos->getGroup(i);
		}
		
		max_distance = searchMaxDistance(grupo, vertices_grafo, mAdj, distancia);
		if(max_distance > -1){//Se foi achado uma distância mais longa para inserção
			peso = vertices_grafo->getVertice(max_distance);//O peso será o valor do vertice
												   //com a maior distancia da maior inserção
			if(peso > -1){ //Se o peso for maior que -1 significa que o vértice ainda não
						   //possui um grupo
				insert_to_Group(grupos, vertices_grafo, mAdj, pos, peso, max_distance);
				grupo->setDistancia(distancia);
			}
			else{
				//Se o peso for igual a -1 significa que o vértice já foi inserido 
				//em um grupo e removido do vetor original de vertices
				mAdj->removeVertice(max_distance);//Então o vértice é apagado das listas de adjacências para não ser inserido
												   //em outros grupos
			}
			L = grupos->getL(pos); //Limitante inferior do grupo
			peso_total = grupos->getPeso(pos); //Peso atual do grupo que é um somatório
											   //dos pesos de todos os vértices do grupo
			if(L >= 0){
				if(peso_total >= L){ //Se o peso total do grupo for maior que o limitante inferior
					grupos->removeGroup(pos); //O grupo é removido para a ultima posição do vetor e
											  //o tamanho desse vetor é reduzido
				}
			}
		}
	}
	
	grupos->reset(); //Restaura a quantidade de grupos pois a mesma é reduzida
					 //quando um grupo atinge o limitante inferior (L)
	qntGrupos = grupos->getQnt();
	
	attain_upper_limit(vertices_grafo, grupos, mAdj);
}

double compute_max_distance(vetGroup* grupos){
	double max_distance = 0.0;
	group* grupo = NULL;
	int qntGrupos = grupos->getQnt();
	
	for (int i = 0; i < qntGrupos; i++)
	{
			grupo = grupos->getGroup(i);
			max_distance += grupo->getDistancia();
	}
	
	return max_distance;
}
