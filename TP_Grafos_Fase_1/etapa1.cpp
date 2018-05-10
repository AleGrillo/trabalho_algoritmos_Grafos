#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

struct coord{
	int x;
	int y;
};

typedef int dado; //Para ficar mais fácil substituir o tipo no futuro

/**
 * Classe noh que guardara as informações de cada vertice do grafo
 */

class noh{
	friend class vertices;
	private:
		int id; //id que guarda a posição no vetor com vertices no grafo
		dado dadosNoh;
		coord coordenadas;
		bool eucledian;
	public:
		noh(int id, dado dadosNoh);
		noh(int id, coord coordenadas);
};

noh::noh(int id, dado dadosNoh){
	this->id = id;
	this->dadosNoh = dadosNoh;
	eucledian = false;
}

noh::noh(int id, coord coordenadas){
	this->id = id;
	this->coordenadas.x = coordenadas.x;
	this->coordenadas.y = coordenadas.y;
	eucledian = true;
}

////////////////////////////////////////////////////////////////////////
/////////////////////////Classe Vertice///////////////////////////////

class verticeDeAdj{
	friend class lista;
	friend class listasAdj;
	private:
		int id;
		int peso;
		verticeDeAdj* proximo;
	public:
		verticeDeAdj(int id);
		verticeDeAdj(int id, int peso);
		int getId();
		int getPeso();
		verticeDeAdj* getProximo();
};

verticeDeAdj::verticeDeAdj(int id){
	this->id = id;
	peso = 0;
	proximo = NULL;
}

verticeDeAdj::verticeDeAdj(int id, int peso){
	this->id = id;
	this->peso = peso;
	proximo = NULL;
}

int verticeDeAdj::getId(){
	return id;
}

int verticeDeAdj::getPeso(){
	return peso;
}

verticeDeAdj* verticeDeAdj::getProximo(){
	return proximo;
}

////////////////////////////////////////////////////////////////////////
/////////////////////////Classe Lista///////////////////////////////////

class lista{
	private:
		verticeDeAdj* primeiro;
		verticeDeAdj* ultimo;
		int tamanhoLista;
		void copyList(lista* copy);// copia a lista
	public:
		lista();
		~lista();
		void insert(int id);
		void insert(int id, int peso);
		bool remove(int id);
		bool search(int valor);
		bool deleteList();
		verticeDeAdj* getFirst(); //Retorna uma copia do primeiro verticeDeAdj da lista
		void print();
};

lista::lista(){
	primeiro = NULL;
	ultimo = NULL;
	tamanhoLista = 0;
}

lista::~lista(){
	deleteList();
}

void lista::insert(int id){
	verticeDeAdj* novo = new verticeDeAdj(id);
	
	if(primeiro == NULL){
		primeiro = novo;
		ultimo = novo;
		tamanhoLista++;
	}
	else{
		ultimo->proximo = novo;
		ultimo = novo;
		tamanhoLista++;
	}
}

void lista::insert(int id, int peso){
	verticeDeAdj* novo = new verticeDeAdj(id, peso);
	
	if(primeiro == NULL){
		primeiro = novo;
		ultimo = novo;
		tamanhoLista++;
	}
	else{
		ultimo->proximo = novo;
		ultimo = novo;
		tamanhoLista++;
	}
}

bool lista::remove(int id){
	if(primeiro == NULL){
		return false;
	}
	else{
		if(primeiro->id == id){
			return false;
		}
		else{
			verticeDeAdj* aux = primeiro;;
			verticeDeAdj* ant;
			
			while(aux->proximo and aux->id != id){
				ant = aux;
				aux = aux->proximo;
			}
			
			if(aux->id == id){
				ant->proximo = aux->proximo;
				delete aux;
				tamanhoLista--;
				return true;
			}
			else{
				return false;
			}
		}
	}
}

bool lista::deleteList(){
	if(primeiro == NULL){
		return false;
	}
	else{
		verticeDeAdj* aux;
		while(primeiro){
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

void lista::copyList(lista* copy){
	verticeDeAdj* aux = primeiro;
	while(aux){
		verticeDeAdj* novo = new verticeDeAdj(aux->id);
		copy->insert(novo->id);
		aux = aux->proximo;
	}
}

verticeDeAdj* lista::getFirst(){
	lista* copy;
	copy = new lista();
	copyList(copy);
	return copy->primeiro;
}

bool lista::search(int valor){
	verticeDeAdj* aux = primeiro;
	bool achou = false;
	
	while(aux and achou == false){
		if(aux->id == valor){
			achou = true;
		}
		aux = aux->proximo;
	}
	
	return achou;
}

void lista::print(){
	verticeDeAdj* aux = primeiro;
	
	while(aux){
		if(aux){
			cout << aux->id << " -> ";
		}
		aux = aux->proximo;
	}
	cout << "NULL" << endl;
	//~ cout << endl;
}

////////////////////////////////////////////////////////////////////////
///////////////////////Matriz de Adjacencias////////////////////////////

class matrizAdj{
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
		int* getLinha(int linha);
		int getTam();
		int getPeso(int verticeA, int verticeB);
		void printMat();
		bool search(int linha, int coluna);
		void remove(int verticeA, int verticeB);
		void removeVertice(int verticeA);
};

matrizAdj::matrizAdj(int tamanhoMat){
	create(tamanhoMat);
}

matrizAdj::matrizAdj(){
	create(0);	
}

matrizAdj::~matrizAdj(){
	deleteMat();
}

void matrizAdj::create(int tamanhoMat){
	this->tamanhoMat = tamanhoMat;
	matriz = new int*[tamanhoMat];
	
	for (int i = 0; i < tamanhoMat; i++)
	{
		matriz[i] = new int[tamanhoMat];
		for (int j = 0; j < tamanhoMat; j++)
		{
			matriz[i][j] = 0;
		}
	}
}

void matrizAdj::deleteMat(){
	for (int i = 0; i < tamanhoMat; i++)
	{
		delete []matriz[i];
	}
	
	delete []matriz;
}

void matrizAdj::insert(int linha, int coluna){
	if(linha >= tamanhoMat or coluna >= tamanhoMat){
		if(linha < coluna){
			expand((coluna - tamanhoMat) + 1);
		}
		else{
			expand((linha - tamanhoMat) + 1);
		}
	}
	
	int l = linha;
	int c = coluna;
	if(matriz[l][c] == 0){
		matriz[l][c] = 1;
	}
}

void matrizAdj::insert(int linha, int coluna, int peso){
	if(linha >= tamanhoMat or coluna >= tamanhoMat){
		if(linha < coluna){
			expand((coluna - tamanhoMat) + 1);
		}
		else{
			expand((linha - tamanhoMat) + 1);
		}
	}
	
	int l = linha;
	int c = coluna;
	if(matriz[l][c] == 0){
		matriz[l][c] = peso;
	}
}

void matrizAdj::expand(int t){
	int tam = tamanhoMat + t; //Como foi passado somente a diferença de
							  //tamanho do tamanho atual para o que tem de ser expandido
	int** mat = new int*[tam];
	
	for (int i = 0; i < tam; i++)
	{
		mat[i] = new int[tam];
		for (int j = 0; j < tam; j++)
		{
			if(i < tamanhoMat and j <tamanhoMat){
				mat[i][j] = matriz[i][j];
			}
			else{
				mat[i][j] = 0;
			}
		}
	}
	
	deleteMat();
	tamanhoMat = tam;
	matriz = mat;
}

int* matrizAdj::getLinha(int linha){ //Retorna a linha da matriz
	if(linha >= 0 and linha < tamanhoMat){
		return &matriz[linha][0];
	}
	
	return NULL;
}

void matrizAdj::printMat(){
	for (int i = 0; i < tamanhoMat; i++)
	{
		for (int j = 0; j < tamanhoMat; j++)
		{
			cout << matriz[i][j] << " ";
		}
		cout << endl;
	}
}

int matrizAdj::getTam(){
	return tamanhoMat;
}	

bool matrizAdj::search(int linha, int coluna){
	if(matriz[linha][coluna] != 0){
		return true;
	}
	return false;
}

void matrizAdj::remove(int verticeA, int verticeB){
	if(verticeA < tamanhoMat and verticeB < tamanhoMat){
		matriz[verticeA][verticeB] = 0;
	}
}

void matrizAdj::removeVertice(int verticeA){
	if(verticeA < tamanhoMat){
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

int matrizAdj::getPeso(int verticeA, int verticeB){
	if(verticeA < tamanhoMat and verticeB < tamanhoMat){
		return matriz[verticeA][verticeB];
	}
	
	exit(EXIT_FAILURE);
}

////////////////////////////////////////////////////////////////////////
///////////////////////Matriz de Incidencias////////////////////////////

class matrizInc{
	private:
		int** matriz;
		int qntLinhas; //Ou qnt de arestas, considerando que cada linha
					   //da matriz representa uma aresta
		int qntColunas;//Ou qnt de vertices, considerando que cada coluna
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
		bool search(int verticeA, int verticeB, int& comecoAresta);
		int getQntColunas();
		int getQntLinhas();
		void remove(int verticeA, int verticeB);
		void removeVertice(int verticeA);
};

matrizInc::matrizInc(string orientation, int qntVertices){
	this->orientation = orientation;
	create(qntVertices);
}

matrizInc::matrizInc(string orientation){
	this->orientation = orientation;
	create(0);
}

matrizInc::~matrizInc(){
	deleteMat();
}

void matrizInc::create(int qntVertices){
	qntColunas = qntVertices;
	qntLinhas = 0;
	matriz = new int*[qntLinhas];
	for (int i = 0; i < qntLinhas; i++)
	{
		matriz[i] = new int[qntColunas];
		for (int j = 0; j < qntColunas; j++)
		{
			matriz[i][j] = 0;
		}
	}
}

void matrizInc::deleteMat(){
	for (int i = 0; i < qntLinhas; i++)
	{
		delete []matriz[i];
	}
	
	delete []matriz;
	matriz = NULL;
}

void matrizInc::expandLinhas(){
	/*
	 * Ira aumentar de uma em uma linha pois será incerido somente 
	 * uma aresta por vez
	 * */
	 int qntLinhasAux = qntLinhas + 1;
	 int** matrizAux = new int*[qntLinhasAux];
	 for (int i = 0; i < qntLinhasAux; i++)
	 {
		 matrizAux[i] = new int[qntColunas];
		 for (int j = 0; j < qntColunas; j++)
		 {
			 if(i < qntLinhas){//Copia somente as linhas ja existentes
				 matrizAux[i][j] = matriz[i][j];
			 }
			 else{
				 matrizAux[i][j] = 0;
			 }
		 }
	 }
	 
	 deleteMat();
	 qntLinhas = qntLinhasAux;
	 matriz = matrizAux;
}

void matrizInc::expandColunas(int qntExpand){
	/*
	 * Caso em que a posicao passada do vertice é maior que a quantidade
	 * de vertices já existentes 
	 */
	 
	 int qntColunasAux = qntColunas + qntExpand;
	 int** matrizAux = new int*[qntColunasAux];
	 for (int i = 0; i < qntLinhas; i++)
	 {
		 matrizAux[i] = new int[qntColunasAux];
		 for (int j = 0; j < qntColunasAux; j++)
		 {
			 if(j < qntColunas){ //Copia somente as colunas já existentes
				 matrizAux[i][j] = matriz[i][j];
			 }
			 else{
				 matrizAux[i][j] = 0;
			 }
		 }
	 }
	 
	 deleteMat();
	 qntColunas = qntColunasAux;
	 matriz = matrizAux;
}

void matrizInc::insert(int verticeA, int verticeB){
	if(verticeA >= 0 and verticeB >= 0){
		expandLinhas();
		if(verticeA < qntColunas and verticeB < qntColunas){
			if(orientation == "UNDIRECTED"){
				matriz[qntLinhas - 1][verticeA] = 1;
				matriz[qntLinhas - 1][verticeB] = 1;
			}
			else if(orientation == "DIRECTED"){
				matriz[qntLinhas - 1][verticeA] = -1;
				matriz[qntLinhas - 1][verticeB] = 1;
			}
		}
		else{
			if(verticeA > verticeB){
				if(verticeA >= qntColunas){
					expandColunas((verticeA - qntColunas) + 1);
				}
			}
			else{
				if(verticeB >= qntColunas){
					expandColunas((verticeB - qntColunas) + 1);
				}
			}
			if(orientation == "UNDIRECTED"){
				matriz[qntLinhas - 1][verticeA] = 1;
				matriz[qntLinhas - 1][verticeB] = 1;
			}
			else if(orientation == "DIRECTED"){
				matriz[qntLinhas - 1][verticeA] = -1;
				matriz[qntLinhas - 1][verticeB] = 1;
			}
		}
	}
}

void matrizInc::printMat(){
	for (int i = 0; i < qntLinhas; i++)
	{
		for (int j = 0; j < qntColunas; j++)
		{
			cout << matriz[i][j] << " ";
		}
		cout << endl;
	}
}

bool matrizInc::search(int verticeA, int verticeB, int& comecoAresta){
	if(verticeA < qntColunas and verticeB < qntColunas){	
		for (int i = 0; i < qntLinhas; i++)
		{
			if(orientation == "UNDIRECTED"){
				if(matriz[i][verticeA] == 1 and matriz[i][verticeB] == 1){
					comecoAresta = -1;
					return true;
				}
			}
			else{
				if(matriz[i][verticeA] == -1 and matriz[i][verticeB] == 1){
					comecoAresta = verticeA;
					return true;
				}
				else if(matriz[i][verticeA] == 1 and matriz[i][verticeB] == -1){
					comecoAresta = verticeB;
					return true;
				}
			}
		}
	}
	return false;
}

int matrizInc::getQntColunas(){
	return qntColunas;
}

int matrizInc::getQntLinhas(){
	return qntLinhas;
}

void matrizInc::remove(int verticeA, int verticeB){
	if(verticeA < qntColunas and verticeB < qntColunas){
		for (int i = 0; i < qntLinhas; i++)
		{
			if(matriz[i][verticeA] != 0 and matriz[i][verticeB] != 0){
				matriz[i][verticeA] = 0;
				matriz[i][verticeB] = 0;
			}
		}
	}
}

void matrizInc::removeVertice(int verticeA){
	if(verticeA < qntColunas){
		for (int i = 0; i < qntLinhas; i++)
		{
			for (int j = 0; j < qntColunas; j++)
			{
				if(matriz[i][verticeA] != 0 and verticeA != j){
					matriz[i][verticeA] = 0;
					matriz[i][j] = 0;
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////
//////////////////////Classe Listas de Adjacencia///////////////////////

/**
 * Classe que contém um vetor com as listas de adjacencia de cada 
 * vertice do grafo
 */ 

class listasAdj{
	private:
		lista** listas;
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
		verticeDeAdj* getListaPos(int pos);
		void print();
};

listasAdj::listasAdj(){
	create(0);
}

listasAdj::listasAdj(int qntListas){
	create(qntListas);
}

listasAdj::~listasAdj(){
	deleteListas();
}

void listasAdj::deleteListas(){
	qntListas = 0;
	delete []listas;
}

void listasAdj::create(int qntListas){
	this->qntListas = qntListas;
	listas = new lista*[qntListas];
	
	for (int i = 0; i < qntListas; i++)
	{
		listas[i] = new lista();
		listas[i]->insert(i);
	}
}

inline int listasAdj::getQnt(){
	return qntListas;
}

verticeDeAdj* listasAdj::getListaPos(int pos){
	if(pos < qntListas){
		return listas[pos]->getFirst();
	}
	return NULL;
}

void listasAdj::expandListas(int qntExpand){
	int qntAux = qntListas + qntExpand;
	lista** listasAux = new lista*[qntAux];
	for (int i = 0; i < qntAux; i++)
	{
		if(i < qntListas){
			listasAux[i] = listas[i];
		}
		else{
			listasAux[i] = new lista();
		}
	}
	
	deleteListas();
	listas = listasAux;
	qntListas = qntAux;
}

void listasAdj::insertIn(int posVertice, int verticeInserir){
	if(posVertice < qntListas){
		bool busca = listas[posVertice]->search(verticeInserir);
		
		if(busca == false){
			listas[posVertice]->insert(verticeInserir);
		}
		else{
			cout << "Vertice ja esta na lista da posicao " << posVertice << endl;
			//Não insere um vizinho repetido porém essa condição pode ser alterada
			//caso seja permitido arestas duplas
		}
	}
	else{
		int qnt = (posVertice - qntListas) + 1;
		expandListas(qnt);
		listas[posVertice]->insert(posVertice);//Inserindo o vertice da posição na lista
		listas[posVertice]->insert(verticeInserir);//Inserindo o vizinho
	}
}

void listasAdj::insertIn(int posVertice, int verticeInserir, int peso){
	if(posVertice < qntListas){
		bool busca = listas[posVertice]->search(verticeInserir);
		
		if(busca == false){
			listas[posVertice]->insert(verticeInserir,peso);
		}
		else{
			cout << "Vertice ja esta na lista da posicao " << posVertice << endl;
			//Não insere um vizinho repetido porém essa condição pode ser alterada
			//caso seja permitido arestas duplas
		}
	}
	else{
		int qnt = (posVertice - qntListas) + 1;
		expandListas(qnt);
		listas[posVertice]->insert(posVertice,0);//Inserindo o vertice da posição na lista
		listas[posVertice]->insert(verticeInserir,peso);//Inserindo o vizinho
	}
}

bool listasAdj::removeIn(int posVertice, int verticeRemover){
	if(posVertice < qntListas){
		return listas[posVertice]->remove(verticeRemover);
	}
	return false;
}

bool listasAdj::removeVertice(int posVertice){
	if(posVertice < qntListas){
		verticeDeAdj* aux = listas[posVertice]->getFirst();
		aux = aux->proximo;
		
		while(aux){
			//Apaga o vertice da lista de cada vertice que o tenha como vizinho
			listas[aux->id]->remove(posVertice);
			aux = aux->proximo;
		}
		
		return listas[posVertice]->deleteList();
	}
	
	return false;
}

void listasAdj::print(){
	for (int i = 0; i < qntListas; i++)
	{
		listas[i]->print();
	}
}

////////////////////////////////////////////////////////////////////////
/////////////////////Classe vertices do Grafo///////////////////////////

class vertices{
	private:
		noh** vetor;
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
		int deleteVertice(dado del);
		int deleteVertice(coord del);
		void print();
		int search(dado pos);
		int search(coord pos);
};

vertices::vertices(int qntVertices){
	this->qntVertices = qntVertices;
	vetor = new noh*[qntVertices];
	
	for (int i = 0; i < qntVertices; i++)
	{
		vetor[i] = NULL;
	}
}

vertices::vertices(){
	qntVertices = 0;
	vetor = new noh*[qntVertices];
	for (int i = 0; i < qntVertices; i++)
	{
		vetor[i] = NULL;
	}
}

vertices::~vertices(){
	delete []vetor;
}

void vertices::expandVetor(){
	int qntAux = qntVertices + 1;
	noh** vetorAux = new noh*[qntAux];
	
	for (int i = 0; i < qntAux; i++)
	{
		if(i < qntVertices){
			vetorAux[i] = vetor[i];
		}
		else{
			vetorAux[i] = NULL;
		}
	}
	
	delete []vetor;
	
	vetor = vetorAux;
	qntVertices = qntAux;
}

int vertices::insertVertice(dado novo){
	int busca = search(novo);
	if(busca == -1){
		expandVetor();
		int pos = qntVertices - 1;
		noh* novoNoh = new noh(pos, novo);
		vetor[pos] = novoNoh;
		return pos;
	}
	else{
		return busca;
	}
}

int vertices::insertVertice(coord novo){
	int busca = search(novo);
	if(busca == -1){
		expandVetor();
		int pos = qntVertices - 1;
		noh* novoNoh = new noh(pos, novo);
		vetor[pos] = novoNoh;
		return pos;
	}
	else{
		return busca;
	}
}

int vertices::search(dado buscar){
	for (int i = 0; i < qntVertices; i++)
	{
		if(vetor[i]){
			if(compare(vetor[i]->dadosNoh, buscar) == true){
				return i;
			}
		}
		else return i; //Retorna a primeira posição vazia
	}
	return -1;
}

int vertices::search(coord buscar){
	for (int i = 0; i < qntVertices; i++)
	{
		if(vetor[i]){
			if(compare(vetor[i]->coordenadas, buscar) == true){
				return i;
			}
		}
		else return i; //Retorna a primeira posição vazia
	}
	return -1;
}

bool vertices::compare(dado A, dado B){
	if(A == B){
		return true;
	}
	
	return false;
}
bool vertices::compare(coord A, coord B){
	if(A.x == B.x and A.y == B.y){
		return true;
	}
	return false;
}

void vertices::print(){
	for (int i = 0; i < qntVertices; i++)
	{
		if(vetor[i]->eucledian == false){
			cout << vetor[i]->dadosNoh << " ";
		}
		else{
			cout << vetor[i]->coordenadas.x << "/" 
			<< vetor[i]->coordenadas.y << " ";
		}
	}
	cout << endl;
}

int vertices::deleteVertice(dado del){
	int pos = search(del);
	
	if(pos >= 0 and pos < qntVertices){
		noh* aux = vetor[pos];
		vetor[pos] = NULL;
		delete aux;
		qntVertices--;
	}
	
	return pos;
}

int vertices::deleteVertice(coord del){
	int pos = search(del);
	
	if(pos >= 0 and pos < qntVertices){
		noh* aux = vetor[pos];
		vetor[pos] = NULL;
		delete aux;
		qntVertices--;
	}
	
	return pos;
}

////////////////////////////////////////////////////////////////////////
///////////////////////////Classe Grafo/////////////////////////////////

class grafo{
	private:
		vertices* verticesDoGrafo;
		listasAdj* lAdj;
		matrizAdj* mAdj;
		matrizInc* mInc;
		int qualEstrutura;//Vem do main contendo a opção de estrutura de
						  //dados escolhida pelo usuario para armazenar os
						  //vertices e as arestas.
		string orientation;
		bool ponderado;
		void inserctIn(int idA, int idB);//Insere na estrutura de dados escolhida
		void inserctIn(int idA, int idB, int peso);//Insere na estrutura de dados 
												//escolhida com grafos ponderados
	public:
		grafo(string orientation, bool ponderado, int qualEstrutura);
		~grafo();
		void insertAresta(dado dadosNohA, dado dadosNohB);//Para vertices com apenas um valor
		void insertAresta(coord coordenadasNohA, coord coordenadasNohB);//Para vertices com coordenadas
		void insertAresta(dado dadosNohA, dado dadosNohB, int peso);//Para grafos ponderados
		void removeVertice(dado dadosNoh);
		void removeVertice(coord coordenadasNoh);
};

grafo::grafo(string orientation, bool ponderado, int qualEstrutura){
	verticesDoGrafo = new vertices();
	this->orientation = orientation;
	this->ponderado = ponderado;
	this->qualEstrutura = qualEstrutura;
	lAdj = new listasAdj();
	mAdj = new matrizAdj();
	mInc = new matrizInc(orientation);
}

grafo::~grafo(){
	delete verticesDoGrafo;
	delete lAdj;
	delete mAdj;
	delete mInc;
}

void grafo::insertAresta(dado dadosNohA, dado dadosNohB){
	int idA = verticesDoGrafo->insertVertice(dadosNohA);
	int idB = verticesDoGrafo->insertVertice(dadosNohB);
	
	if(orientation == "UNDIRECTED"){
		inserctIn(idA,idB);
		inserctIn(idB,idA);
	}
	else if(orientation == "DIRECTED"){
		inserctIn(idA,idB);
	}
}

void grafo::insertAresta(coord coordenadasNohA, coord coordenadasNohB){
	int idA = verticesDoGrafo->insertVertice(coordenadasNohA);
	int idB = verticesDoGrafo->insertVertice(coordenadasNohB);
	
	if(orientation == "UNDIRECTED"){
		inserctIn(idA,idB);
		inserctIn(idB,idA);
	}
	else if(orientation == "DIRECTED"){
		inserctIn(idA,idB);
	}
}

void grafo::insertAresta(dado dadosNohA, dado dadosNohB, int peso){
	int idA = verticesDoGrafo->insertVertice(dadosNohA);
	int idB = verticesDoGrafo->insertVertice(dadosNohB);
	
	if(orientation == "UNDIRECTED"){
		inserctIn(idA,idB,peso);
		inserctIn(idB,idA,peso);
	}
	else if(orientation == "DIRECTED"){
		inserctIn(idA,idB,peso);
	}
}

void grafo::inserctIn(int idA, int idB){
	if(qualEstrutura == 1){
		lAdj->insertIn(idA, idB);
	}
	else if(qualEstrutura == 2){
		mAdj->insert(idA, idB);
	}
	else if(qualEstrutura == 3){
		mInc->insert(idA, idB);
	}
}

void grafo::inserctIn(int idA, int idB, int peso){
	if(qualEstrutura == 1){
		lAdj->insertIn(idA, idB, peso);
	}
	else if(qualEstrutura == 2){
		mAdj->insert(idA, idB, peso);
	}
	else if(qualEstrutura == 3){
		mInc->insert(idA, idB);
	}
}

void grafo::removeVertice(dado dadosNoh){
	int pos = verticesDoGrafo->deleteVertice(dadosNoh);
	if(qualEstrutura == 1){
		lAdj->removeVertice(pos);
	}
	else if(qualEstrutura == 2){
		mAdj->removeVertice(pos);
	}
	else if(qualEstrutura == 3){
		mInc->removeVertice(pos);
	}
}

void grafo::removeVertice(coord dadosNoh){
	int pos = verticesDoGrafo->deleteVertice(dadosNoh);
	if(qualEstrutura == 1){
		lAdj->removeVertice(pos);
	}
	else if(qualEstrutura == 2){
		mAdj->removeVertice(pos);
	}
	else if(qualEstrutura == 3){
		mInc->removeVertice(pos);
	}
}

////////////////////////////////////////////////////////////////////////
/////////////////////////Funções externas///////////////////////////////

void listToMatAdj(listasAdj* listaAdj, matrizAdj* mAdj, bool ponderado){
	int qnt = listaAdj->getQnt();
	for (int i = 0; i < qnt; i++)
	{
		int id;
		verticeDeAdj* aux = listaAdj->getListaPos(i);
		if(aux){
			id = aux->getId();
			if(ponderado == false){
				aux = aux->getProximo();
				while(aux){
					mAdj->insert(id, aux->getId());
					aux = aux->getProximo();
				}
			}
			else{
				aux = aux->getProximo();
				while(aux){
					mAdj->insert(id, aux->getId(), aux->getPeso());
					aux = aux->getProximo();
				}
			}
		}
	}
}

void listToMatInc(listasAdj* listaAdj, matrizInc* mInc){
	int qnt = listaAdj->getQnt();
	for (int i = 0; i < qnt; i++)
	{
		int id;
		verticeDeAdj* aux = listaAdj->getListaPos(i);
		if(aux){
			id = aux->getId();
			aux = aux->getProximo();
			while(aux){
				mInc->insert(id, aux->getId());
				aux = aux->getProximo();
			}
		}
	}
}

void matAdjToList(matrizAdj* mAdj, listasAdj* listaAdj, bool ponderado){
	int tam = mAdj->getTam();
	cout << tam << endl;
	for (int i = 0; i < tam; i++)
	{
		for (int j = 0; j < tam; j++)
		{
			if(mAdj->search(i,j) == true){
				if(ponderado == true){
					int peso = mAdj->getPeso(i,j);
					listaAdj->insertIn(i,j,peso);
				}
				else{
					listaAdj->insertIn(i,j);
				}
			}
		}
	}
}

void matAdjToMatInc(matrizAdj* mAdj, matrizInc* mInc){
	int tam = mAdj->getTam();
	for (int i = 0; i < tam; i++)
	{
		for (int j = 0; j < tam; j++)
		{
			if(mAdj->search(i,j) == true){
				mInc->insert(i,j);
			}
		}
	}
}

void matIncToListAdj(matrizInc* mInc, listasAdj* lAdj){
	int linhas = mInc->getQntLinhas();
	int colunas = mInc->getQntColunas();
	for (int i = 0; i < linhas; i++)
	{
		for (int j = 0; j < colunas; j++)
		{
			int comecoAresta;
			if(mInc->search(i,j,comecoAresta) == true and i != j){
				if(comecoAresta == -1){
					lAdj->insertIn(i,j);
				}
				else{
					if(comecoAresta == i){
						lAdj->insertIn(i,j);
					}
					else{
						lAdj->insertIn(j,i);
					}
				}
			}
		}
	}
}

void matIncToMatAdj(matrizInc* mInc, matrizAdj* mAdj){
	int linhas = mInc->getQntLinhas();
	int colunas = mInc->getQntColunas();
	for (int i = 0; i < linhas; i++)
	{
		for (int j = 0; j < colunas; j++)
		{
			int comecoAresta;
			if(mInc->search(i,j,comecoAresta) == true and i != j){
				if(comecoAresta == -1){
					mAdj->insert(i,j);
				}
				else{
					if(comecoAresta == i){
						mAdj->insert(i,j);
					}
					else{
						mAdj->insert(j,i);
					}
				}
			}
		}
	}
}



int main(){

return 0;
}
