#include <iostream>
#include <fstream>

using namespace std;

typedef int dado; //Para fácilitar a substituição do valor por uma struct no futuro

/////////////////////////////////////////////////////////////////////////
//// Classe noh que guardara as informações de cada vertice do grafo ////
class noh{
	friend class vertices;
	private:
		int id; //id que guarda a posição no vetor com vertices no grafo
		dado dadosNoh;
	public:
		noh(int id, dado dadosNoh);
};

noh::noh(int id, dado dadosNoh) {
	this->id = id;
	this->dadosNoh = dadosNoh;
}

////////////////////////////////////////////////////////////////////////
/////////////////////////Classe Vertice///////////////////////////////
class verticeDeAdj {
	friend class lista;
	friend class listasAdj;
	private:
		int id;
		verticeDeAdj* proximo;
	public:
		verticeDeAdj(int id);
		int getId();
		verticeDeAdj* getProximo();
};

verticeDeAdj::verticeDeAdj(int id) {
	this->id = id;
	proximo = NULL;
};

int verticeDeAdj::getId() {
	return id;
}

verticeDeAdj* verticeDeAdj::getProximo() {
	return proximo;
}

////////////////////////////////////////////////////////////////////////
/////////////////////////Classe Lista///////////////////////////////////
class lista {
	private:
		verticeDeAdj* primeiro;
		verticeDeAdj* ultimo;
		int tamanhoLista;
		void copyList(lista* copy); // copia a lista
	public:
		lista();
		~lista();
		void insert(int id);
		bool remove(int id);
		bool search(int valor);
		bool deleteList();
		verticeDeAdj* getFirst(); //Retorna uma copia do primeiro verticeDeAdj da lista
		void print();
};

lista::lista() {
	primeiro = NULL;
	ultimo = NULL;
	tamanhoLista = 0;
}

lista::~lista() {
	deleteList();
}

void lista::insert(int id) {
	verticeDeAdj* novo = new verticeDeAdj(id);

	if (primeiro == NULL) {
		primeiro = novo;
		ultimo = novo;
		tamanhoLista++;
	} else {
		ultimo->proximo = novo;
		ultimo = novo;
		tamanhoLista++;
	}
}

bool lista::remove(int id) {
	if (primeiro == NULL) {
		return false;
	} else {
		if(primeiro->id == id) {
			return false;
		} else {
			verticeDeAdj* aux = primeiro;;
			verticeDeAdj* ant;

			while(aux->proximo and aux->id != id) {
				ant = aux;
				aux = aux->proximo;
			}

			if(aux->id == id) {
				ant->proximo = aux->proximo;
				delete aux;
				tamanhoLista--;

				return true;
			} else {
				return false;
			}
		}
	}
}

bool lista::deleteList() {
	if(primeiro == NULL) {
		return false;
	}	else {
		verticeDeAdj* aux;

		while(primeiro) {
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

void lista::copyList(lista* copy) {
	verticeDeAdj* aux = primeiro;

	while(aux) {
		verticeDeAdj* novo = new verticeDeAdj(aux->id);
		copy->insert(novo->id);
		aux = aux->proximo;
	}
}

verticeDeAdj* lista::getFirst() {
	lista* copy;
	copy = new lista();
	copyList(copy);

	return copy->primeiro;
}

bool lista::search(int valor) {
	verticeDeAdj* aux = primeiro;
	bool achou = false;

	while(aux and achou == false) {
		if(aux->id == valor) {
			achou = true;
		}
		aux = aux->proximo;
	}

	return achou;
}

void lista::print() {
	verticeDeAdj* aux = primeiro;

	while(aux) {
		if(aux) {
			cout << aux->id << " -> ";
		}
		aux = aux->proximo;
	}
	cout << "NULL" << endl;
}

////////////////////////////////////////////////////////////////////////
///////////////////////Matriz de Adjacencias////////////////////////////
class matrizAdj {
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
		void insert(int linha, int coluna);
		int* getLinha(int linha);
		int getTam();
		void printMat();
		bool ehVizinho(int linha, int coluna);
		void remove(int verticeA, int verticeB);
};

matrizAdj::matrizAdj(int tamanhoMat) {
	create(tamanhoMat);
}

matrizAdj::matrizAdj() {
	create(0);
}

matrizAdj::~matrizAdj() {
	deleteMat();
}

void matrizAdj::create(int tamanhoMat) {
	this->tamanhoMat = tamanhoMat;
	matriz = new int*[tamanhoMat];

	for (int i = 0; i < tamanhoMat; i++) {
		matriz[i] = new int[tamanhoMat];

		for (int j = 0; j < tamanhoMat; j++) {
			matriz[i][j] = 0;
		}
	}
}

void matrizAdj::deleteMat() {
	for (int i = 0; i < tamanhoMat; i++) {
		delete []matriz[i];
	}

	delete []matriz;
}

void matrizAdj::insert(int linha, int coluna) {
	if(linha >= tamanhoMat or coluna >= tamanhoMat) {
		if(linha < coluna) {
			expand((coluna - tamanhoMat) + 1);
		}
		else{
			expand((linha - tamanhoMat) + 1);
		}
	}

	int l = linha;
	int c = coluna;

	if(matriz[l][c] == 0) {
		matriz[l][c] = 1;
	}
}

void matrizAdj::expand(int t) {
	int tam = tamanhoMat + t; //Como foi passado somente a diferença de tamanho
							  						//do tamanho atual para o que tem de ser expandido
	int** mat = new int*[tam];

	for (int i = 0; i < tam; i++) {
		mat[i] = new int[tam];

		for (int j = 0; j < tam; j++) {
			if(i < tamanhoMat and j <tamanhoMat) {
				mat[i][j] = matriz[i][j];
			}	else {
				mat[i][j] = 0;
			}
		}
	}

	deleteMat();
	tamanhoMat = tam;
	matriz = mat;
}

int* matrizAdj::getLinha(int linha) { //Retorna a linha da matriz
	if(linha >= 0 and linha < tamanhoMat) {
		return &matriz[linha][0];
	}

	return NULL;
}

void matrizAdj::printMat() {
	for (int i = 0; i < tamanhoMat; i++) {
		for (int j = 0; j < tamanhoMat; j++) {
			cout << matriz[i][j] << " ";
		}
		cout << endl;
	}
}

int matrizAdj::getTam() {
	return tamanhoMat;
}

bool matrizAdj::ehVizinho(int linha, int coluna) {
	if(matriz[linha][coluna] == 1) {
		return true;
	}
	return false;
}

void matrizAdj::remove(int verticeA, int verticeB) {
	if(verticeA < tamanhoMat and verticeB < tamanhoMat) {
		matriz[verticeA][verticeB] = 0;
	}
}

////////////////////////////////////////////////////////////////////////
///////////////////////Matriz de Incidencias////////////////////////////
class matrizInc {
	private:
		int** matriz;
		int qntLinhas; //Ou qnt de arestas, considerando que cada
					   		 	//linha da matriz representa uma aresta
		int qntColunas;//Ou qnt de vertices, considerando que
					   			//cada coluna da matriz é um vertice
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
		bool ehVizinho(int verticeA, int verticeB);
		int getQntColunas();
		int getQntLinhas();
		void remove(int verticeA, int verticeB);
};

matrizInc::matrizInc(string orientation, int qntVertices) {
	this->orientation = orientation;
	create(qntVertices);
}

matrizInc::matrizInc(string orientation) {
	this->orientation = orientation;
	create(0);
}

matrizInc::~matrizInc() {
	deleteMat();
}

void matrizInc::create(int qntVertices) {
	qntColunas = qntVertices;
	qntLinhas = 0;
	matriz = new int*[qntLinhas];

	for (int i = 0; i < qntLinhas; i++) {
		matriz[i] = new int[qntColunas];

		for (int j = 0; j < qntColunas; j++) {
			matriz[i][j] = 0;
		}
	}
}

void matrizInc::deleteMat() {
	for (int i = 0; i < qntLinhas; i++)	{
		delete []matriz[i];
	}

	delete []matriz;
	matriz = NULL;
}

void matrizInc::expandLinhas() {
	/*Ira aumentar de uma em uma linha pois será
	 *incerido somente uma aresta por vez */

	 int qntLinhasAux = qntLinhas + 1;
	 int** matrizAux = new int*[qntLinhasAux];

	 for (int i = 0; i < qntLinhasAux; i++) {
		 matrizAux[i] = new int[qntColunas];

		 for (int j = 0; j < qntColunas; j++) {
			 if(i < qntLinhas) {//Copia somente as linhas ja existentes
				 matrizAux[i][j] = matriz[i][j];
			 } else {
				 matrizAux[i][j] = 0;
			 }
		 }
	 }

	 deleteMat();
	 qntLinhas = qntLinhasAux;
	 matriz = matrizAux;
}

void matrizInc::expandColunas(int qntExpand) {
	/* Caso em que a posicao passada do vertice é maior que a quantidade
	 * de vertices já existentes */

	 int qntColunasAux = qntColunas + qntExpand;
	 int** matrizAux = new int*[qntColunasAux];

	 for (int i = 0; i < qntLinhas; i++) {
		 matrizAux[i] = new int[qntColunasAux];

		 for (int j = 0; j < qntColunasAux; j++) {
			 if(j < qntColunas) { //Copia somente as colunas já existentes
				 matrizAux[i][j] = matriz[i][j];
			 } else {
				 matrizAux[i][j] = 0;
			 }
		 }
	 }

	 deleteMat();
	 qntColunas = qntColunasAux;
	 matriz = matrizAux;
}

void matrizInc::insert(int verticeA, int verticeB) {
	if(verticeA >= 0 and verticeB >= 0) {
		expandLinhas();
		if(verticeA < qntColunas and verticeB < qntColunas) {
			if(orientation == "UNDIRECTED") {
				matriz[qntLinhas - 1][verticeA] = 1;
				matriz[qntLinhas - 1][verticeB] = 1;
			} else if (orientation == "DIRECTED") {
				matriz[qntLinhas - 1][verticeA] = -1;
				matriz[qntLinhas - 1][verticeB] = 1;
			}
		}	else {
			if(verticeA > verticeB) {
				if(verticeA >= qntColunas) {
					expandColunas((verticeA - qntColunas) + 1);
				}
			}	else {
				if(verticeB >= qntColunas) {
					expandColunas((verticeB - qntColunas) + 1);
				}
			}
			if(orientation == "UNDIRECTED") {
				matriz[qntLinhas - 1][verticeA] = 1;
				matriz[qntLinhas - 1][verticeB] = 1;
			}
			else if(orientation == "DIRECTED") {
				matriz[qntLinhas - 1][verticeA] = -1;
				matriz[qntLinhas - 1][verticeB] = 1;
			}
		}
	}
}

void matrizInc::printMat() {
	for (int i = 0; i < qntLinhas; i++)	{
		for (int j = 0; j < qntColunas; j++) {
			cout << matriz[i][j] << " ";
		}
		cout << endl;
	}
}

bool matrizInc::ehVizinho(int verticeA, int verticeB) {
	if(verticeA < qntColunas and verticeB < qntColunas) {
		for (int i = 0; i < qntLinhas; i++)	{
			if(matriz[i][verticeA] == 1 and matriz[i][verticeB] == 1) {
				return true;
			}
		}
	}
	return false;
}

int matrizInc::getQntColunas() {
	return qntColunas;
}

int matrizInc::getQntLinhas() {
	return qntLinhas;
}

void matrizInc::remove(int verticeA, int verticeB) {
	if(verticeA < qntColunas and verticeB < qntColunas) {
		for (int i = 0; i < qntLinhas; i++)	{
			if(matriz[i][verticeA] == 1 and matriz[i][verticeB] == 1) {
				matriz[i][verticeA] = 0;
				matriz[i][verticeB] = 0;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////
//////////////////////Classe Listas de Adjacencia///////////////////////
/* Classe que contém um vetor com as listas de adjacencia de cada
 * vertice do grafo */
class listasAdj {
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
		bool deleteVertice(int posVertice);
		inline int getQnt();
		verticeDeAdj* getListaPos(int pos);
		void print();
};

listasAdj::listasAdj() {
	create(0);
}

listasAdj::listasAdj(int qntListas) {
	create(qntListas);
}

listasAdj::~listasAdj() {
	deleteListas();
}

void listasAdj::deleteListas() {
	qntListas = 0;
	delete []listas;
}

void listasAdj::create(int qntListas) {
	this->qntListas = qntListas;
	listas = new lista*[qntListas];

	for (int i = 0; i < qntListas; i++)	{
		listas[i] = new lista();
		listas[i]->insert(i);
	}
}

inline int listasAdj::getQnt() {
	return qntListas;
}

verticeDeAdj* listasAdj::getListaPos(int pos) {
	if(pos < qntListas) {
		return listas[pos]->getFirst();
	}
	return NULL;
}

void listasAdj::expandListas(int qntExpand) {
	int qntAux = qntListas + qntExpand;
	lista** listasAux = new lista*[qntAux];

	for (int i = 0; i < qntAux; i++) {
		if(i < qntListas) {
			listasAux[i] = listas[i];
		}	else {
			listasAux[i] = new lista();
		}
	}

	deleteListas();
	listas = listasAux;
	qntListas = qntAux;
}

void listasAdj::insertIn(int posVertice, int verticeInserir) {
	if(posVertice < qntListas) {
		bool busca = listas[posVertice]->search(verticeInserir);

		if(busca == false) {
			listas[posVertice]->insert(verticeInserir);
		}	else {
			cout << "Vertice ja esta na lista da posicao " << posVertice << endl;
			//Não insere um vizinho repetido porém essa condição pode ser alterada
			//caso seja permitido arestas duplas
		}
	}	else {
		int qnt = (posVertice - qntListas) + 1;
		expandListas(qnt);
		listas[posVertice]->insert(posVertice);//Inserindo o vertice da posição na lista
		listas[posVertice]->insert(verticeInserir);//Inserindo o vizinho
	}
}

bool listasAdj::removeIn(int posVertice, int verticeRemover) {
	if(posVertice < qntListas) {
		return listas[posVertice]->remove(verticeRemover);
	}
	return false;
}

bool listasAdj::deleteVertice(int posVertice) {
	if(posVertice < qntListas) {
		verticeDeAdj* aux = listas[posVertice]->getFirst();
		aux = aux->proximo;

		while(aux) {
			//Apaga o vertice da lista de cada vertice que o tenha como vizinho
			listas[aux->id]->remove(posVertice);
			aux = aux->proximo;
		}

		return listas[posVertice]->deleteList();
	}

	return false;
}

void listasAdj::print() {
	for (int i = 0; i < qntListas; i++)	{
		listas[i]->print();
	}
}

////////////////////////////////////////////////////////////////////////
/////////////////////Classe vertices do Grafo///////////////////////////
class vertices {
	private:
		noh** vetor;
		int qntVertices;
		void expandVetor();
		bool compare(dado A, dado B);
	public:
		vertices(int qntVertices);
		vertices();
		~vertices();
		int insertVertice(dado novo);
		void print();
		int search(dado buscar);
		dado searchDado(int id);
};

vertices::vertices(int qntVertices) {
	this->qntVertices = qntVertices;
	vetor = new noh*[qntVertices];

	for (int i = 0; i < qntVertices; i++)	{
		vetor[i] = NULL;
	}
}

vertices::vertices() {
	qntVertices = 0;
	vetor = new noh*[qntVertices];
	for (int i = 0; i < qntVertices; i++)	{
		vetor[i] = NULL;
	}
}

vertices::~vertices() {
	delete []vetor;
}

void vertices::expandVetor() {
	int qntAux = qntVertices + 1;
	noh** vetorAux = new noh*[qntAux];

	for (int i = 0; i < qntAux; i++) {
		if(i < qntVertices) {
			vetorAux[i] = vetor[i];
		}	else {
			vetorAux[i] = NULL;
		}
	}

	delete []vetor;

	vetor = vetorAux;
	qntVertices = qntAux;
}

int vertices::insertVertice(dado novo) {
	int busca = search(novo);

	if(busca == -1) {
		expandVetor();
		int pos = qntVertices - 1;
		noh* novoNoh = new noh(pos, novo);
		vetor[pos] = novoNoh;
		return pos;
	}	else {
		return busca;
	}
}

int vertices::search(dado buscar) {
	for (int i = 0; i < qntVertices; i++)	{
		if(compare(vetor[i]->dadosNoh, buscar) == true) {
			return i;
		}
	}
	return -1;
}

dado vertices::searchDado(int id) {
	if(id < qntVertices) {
		return vetor[id]->dadosNoh;
	}
	return NULL;
}

bool vertices::compare(dado A, dado B) {
	if(A == B) {
		return true;
	}
	return false;
}

void vertices::print() {
	for (int i = 0; i < qntVertices; i++)	{
		cout << vetor[i]->dadosNoh << " ";
	}
	cout << endl;
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
	public:
		grafo(string orientation, int qualEstrutura);
		~grafo();
		void insertAresta(dado dadosNohA, dado dadosNohB);
};

grafo::grafo(string orientation, int qualEstrutura) {
	verticesDoGrafo = new vertices();
	this->orientation = orientation;
	this->qualEstrutura = qualEstrutura;
	lAdj = new listasAdj();
	mAdj = new matrizAdj();
	mInc = new matrizInc(orientation);
}

grafo::~grafo() {
	delete verticesDoGrafo;
	delete lAdj;
	delete mAdj;
	delete mInc;
}

void grafo::insertAresta(dado dadosNohA, dado dadosNohB) {
	int idA = verticesDoGrafo->insertVertice(dadosNohA);
	int idB = verticesDoGrafo->insertVertice(dadosNohB);

	if(qualEstrutura == 1) {
		if(orientation == "UNDIRECTED") {
			lAdj->insertIn(idA, idB);
			lAdj->insertIn(idB, idA);
		}	else if (orientation == "DIRECTED") {
			lAdj->insertIn(idA, idB);
		}
	}	else if(qualEstrutura == 2) {
		if(orientation == "UNDIRECTED") {
			mAdj->insert(idA, idB);
			mAdj->insert(idB, idA);
		}	else if(orientation == "DIRECTED") {
			mAdj->insert(idA, idB);
		}
	}	else if(qualEstrutura == 3) {
		if(orientation == "UNDIRECTED") {
			mInc->insert(idA, idB);
			mInc->insert(idB, idA);
		}	else if(orientation == "DIRECTED") {
			mInc->insert(idA, idB);
		}
	}
}

////////////////////////////////////////////////////////////////////////
/////////////////////////Funções externas///////////////////////////////
void listToMatAdj(listasAdj* listaAdj, matrizAdj* mAdj) {
	int qnt = listaAdj->getQnt();

	for (int i = 0; i < qnt; i++) {
		int id;
		verticeDeAdj* aux = listaAdj->getListaPos(i);

		if(aux) {
			id = aux->getId();
			aux = aux->getProximo();

			while(aux) {
				mAdj->insert(id, aux->getId());
				aux = aux->getProximo();
			}
		}
	}
}

void listToMatInc(listasAdj* listaAdj, matrizInc* mInc) {
	int qnt = listaAdj->getQnt();

	for (int i = 0; i < qnt; i++)	{
		int id;
		verticeDeAdj* aux = listaAdj->getListaPos(i);

		if(aux) {
			id = aux->getId();
			aux = aux->getProximo();

			while(aux) {
				mInc->insert(id, aux->getId());
				aux = aux->getProximo();
			}
		}
	}
}

void matAdjToList(matrizAdj* mAdj, listasAdj* listaAdj) {
	int tam = mAdj->getTam();
	cout << tam << endl; // verifique

	for (int i = 0; i < tam; i++)	{
		for (int j = 0; j < tam; j++)	{
			if(mAdj->ehVizinho(i,j) == true) {
				listaAdj->insertIn(i,j);
			}
		}
	}
}

void matAdjToMatInc(matrizAdj* mAdj, matrizInc* mInc) {
	int tam = mAdj->getTam();
	for (int i = 0; i < tam; i++)	{
		for (int j = 0; j < tam; j++) {
			if(mAdj->ehVizinho(i,j) == true) {
				mInc->insert(i,j);
			}
		}
	}
}

void matIncToListAdj(matrizInc* mInc, listasAdj* lAdj) {
	int linhas = mInc->getQntLinhas();
	int colunas = mInc->getQntColunas();

	for (int i = 0; i < linhas; i++) {
		for (int j = 0; j < colunas; j++) {
			if(mInc->ehVizinho(i,j) == true and i != j) {
				lAdj->insertIn(i,j);
			}
		}
	}
}

void matIncToMatAdj(matrizInc* mInc, matrizAdj* mAdj) {
	int linhas = mInc->getQntLinhas();
	int colunas = mInc->getQntColunas();

	for (int i = 0; i < linhas; i++) {
		for (int j = 0; j < colunas; j++) {
			if(mInc->ehVizinho(i,j) == true and i != j) {
				mAdj->insert(i,j);
			}
		}
	}
}

int main() {

return 0;
}
//Casos de teste:

	//~ listasAdj* lAdj = new listasAdj();
	//~ matrizInc* mInc = new matrizInc();
	//~ matrizAdj* mAdj = new matrizAdj();
	//~ mInc->insert(0,1);
	//~ mInc->insert(0,2);
	//~ mInc->insert(1,0);
	//~ mInc->insert(1,2);
	//~ mInc->insert(2,0);
	//~ mInc->insert(2,1);
	//~ mInc->insert(2,3);
	//~ mInc->insert(3,2);
	//~ mInc->printMat();
	//~ matIncToListAdj(mInc,lAdj);
	//~ matIncToMatAdj(mInc,mAdj);
	//~ matAdjToMatInc(mAdj,mInc);
	//~ lAdj->print();
	//~ listToMatAdj(lAdj, mAdj);
	//~ cout << endl;
	//~ mAdj->printMat();
	//~ lAdj->insertIn(0,1);
	//~ lAdj->insertIn(1,0);
	//~ lAdj->insertIn(1,2);
	//~ lAdj->insertIn(2,1);
	//~ lAdj->insertIn(2,0);
	//~ lAdj->insertIn(0,2);
	//~ lAdj->insertIn(2,3);
	//~ lAdj->insertIn(3,2);
	//~ listToMatInc(lAdj,mInc);
	//~ mInc->printMat();
	//~ listToMatInc(lAdj,mInc);
	//~ mAdj->insert(0,1);
	//~ mAdj->insert(1,2);
	//~ mAdj->insert(2,0);
	//~ mAdj->insert(2,3);
	//~ mAdj->insert(3,2);
	//~ mAdj->insert(6,7);
	//~ matAdjToList(mAdj, lAdj);
	//~ mAdj->printMat();
	//~ cout << endl;

	//~ matrizInc* mat = new matrizInc(0);
	//~ mat->insert(5, 8);
	//~ mat->insert(5, 1);
	//~ mat->insert(5, 2);
	//~ mat->insert(20, 3);
	//~ mat->insert(5, 6);
	//~ mat->insert(2, 9);
	//~ mat->printMat();

	//~ cout << endl;

	//~ matrizAdj* matA = new matrizAdj(0);
	//~ matA->insert(5, 8);
	//~ matA->insert(5, 1);
	//~ matA->insert(5, 2);
	//~ matA->insert(20, 3);
	//~ matA->insert(5, 6);
	//~ matA->insert(2, 9);
	//~ matA->printMat();

	//~ cout << endl;

	//~ vertices* verticesGrafo = new vertices();
	//~ ifstream arq("instancias.txt");

	//~ while(!arq.eof())
	//~ {
		//~ dado novo;
		//~ arq >> novo;
		//~ verticesGrafo->insertVertice(novo);
	//~ }

	//~ verticesGrafo->print();

	//~ int id;
	//~ dado dadosNoh;
	//~ lista* nova = new lista();;
	//~ noh* novo = new noh(1,30);
	//~ nova->insert(novo);
	//~ novo = new noh(10,3);
	//~ nova->insert(novo);
	//~ novo = new noh(5,15);
	//~ nova->insert(novo);
	//~ novo = new noh(2,22);
	//~ nova->insert(novo);
	//~ novo = new noh(6,80);
	//~ nova->insert(novo);
	//~ do{
		//~ cin >> id;
		//~ cin >> dadosNoh;
		//~ if(id >= 0) {
			//~ noh* novo = new noh(id, dadosNoh);
			//~ nova->insert(novo);
		//~ }
	//~ }while(id >= 0);

	//~ nova->print();

	//~ lista** nova = new lista*[3];

	//~ for (int i = 0; i < 3; i++)
	//~ {
		//~ nova[i] = new lista();
		//~ nova[i]->insert(1);
		//~ nova[i]->insert(5);
		//~ nova[i]->insert(2);
		//~ nova[i]->insert(10);
		//~ nova[i]->insert(8);
	//~ }

	//~ nova[0]->print();

	//~ nova[0]->remove(1);
	//~ nova[0]->remove(5);

	//~ nova[0]->print();
	//~ nova[1]->print();
	//~ nova[1]->deleteList();
	//~ nova[1]->print();
