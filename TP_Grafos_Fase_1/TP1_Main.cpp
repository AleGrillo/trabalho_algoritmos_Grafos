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
// #include "TP1.cpp"

using namespace std;

////////////////////////////////////////////////////////////////////////
//////////////////////////Funções do Main///////////////////////////////
int getVertice(grafo* G){
	bool eucledian = G->getEucledian();
	int vertice;
	
	if(eucledian == true){
		cout << "Digite as coordenadas do vertice\n";
		cout << "X									";
		coord coordenadas;
		cin >> coordenadas.x;
		cout << "Y									";
		cin >> coordenadas.y;
		vertice = G->search(coordenadas);
	}
	else{
		cout << "Digite o valor do vertice: ";
		dado dadosNoh;
		cin >> dadosNoh;
		vertice = G->search(dadosNoh);
	}
	
	return vertice;
}

bool ePonderado() {
  cout << "##############################################################" << endl;
	cout << "################### O Grafo é Ponderado? #####################" << endl;
  cout << "##############################################################" << endl;
	cout << "###################### Sim	-----> [0] ########################" << endl;
	cout << "###################### Não -----> [1] ########################" << endl;
  cout << "##############################################################" << endl;

	int comando;
	cin >> comando;

	if(comando == 0) {
		return true;
	} else if (comando == 1) {
		return false;
	} else {
    cout << "##############################################################" << endl;
    cout << "####################     Opção invalida     ##################" << endl;
    cout << "##############################################################" << endl;
		exit(EXIT_FAILURE);
	}
}


bool dadosVertices() {
  cout << "## Quais os tipos de dados serão passados para os vertices? ##" << endl;
  cout << "##############################################################" << endl;
  cout << "########### Coordenadas(Euclediano)  -----> [0] ##############" << endl;
  cout << "################  Apenas valores	    -----> [1] ##############" << endl;
  cout << "##############################################################" << endl;

	int comando;
	cin >> comando;

	if (comando == 0) {
		return true;
	} else if (comando == 1) {
		return false;
	} else {
    cout << "##############################################################" << endl;
    cout << "####################     Opção invalida     ##################" << endl;
    cout << "##############################################################" << endl;
		exit(EXIT_FAILURE);
	}
}

string nomeArq() {
  cout << "##############   Digite o nome do Arquivo:";
  cout << "#############################################################" << endl;

	string nome;
	cin >> nome;

	return nome;
}

int estruturaUtilizada() {
  cout << "######## Qual a Estrutura de Dados deseja utilizar? #########" << endl;
  cout << "#############################################################" << endl;
  cout << "########### Lista de Adjacencias	 -----> [1]  ###############" << endl;
  cout << "########### Matriz de Adjacencias -----> [2]  ###############" << endl;
  cout << "########### Matriz de Incidencias -----> [3]  ###############" << endl;
  cout << "#############################################################" << endl;

	int comando;
	cin >> comando;

	if(comando > 0 and comando < 4) {
		return comando;
	}	else {
    cout << "##############################################################" << endl;
    cout << "####################     Opção invalida     ##################" << endl;
    cout << "##############################################################" << endl;
		exit(EXIT_FAILURE);
	}
}

void estruturaDeDadosGrafo(grafo* G, int comando){
	int estrutura = G->getQualEstrutura();
	if(comando == estrutura){
		G->printGrafo();
	}
	else{
		if(comando == 1){
			if(estrutura == 2){
				matAdjToList(G);
			}
			else if(estrutura == 3){
				matIncToListAdj(G);
			}
			G->printLAdj();
		}
		else if(comando == 2){
			if(estrutura == 1){
				listToMatAdj(G);
			}
			else if(estrutura == 3){
				matIncToMatAdj(G);
			}
			G->printMAdj();
		}
		else if(comando == 3){
			if(estrutura == 1){
				listToMatInc(G);
			}
			else if(estrutura == 2){
				matAdjToMatInc(G);
			}
			G->printMInc();
		}
	}
}

int comand(){
	int comando;
	
	cout << "Obter Lista de Adjacencias do Grafo				1\n";
	cout << "Obter Matriz de Adjacencias do Grafo				2\n";
	cout << "Obter Matriz de Incidencias do Grafo				3\n";
	cout << "Obter vizinhos de um vertice u					4\n";
	cout << "Obter predecessores de um vertice u				5\n";
	cout << "Obter Sucessores de um vertice u				6\n";
	cout << "Verificar se dois vertices u e v sao vizinhos			7\n";
	cout << "Verificar se v e predecessor de u				8\n";
	cout << "Verificar se v e sucessor de u					9\n";
	cout << "Deletar um vertice						10\n";
	cout << "Deletar uma aresta						11\n";
	cout << "Gerar subGrafo induzido por vertices				12\n";
	cout << "Gerar subGrafo induzido por arestas				13\n";
	cout << "Sair								0\n";
	
	cin >> comando;
	
	return comando;
}

void menu(grafo* G){
	
	int comando = -1;
	do{
		comando = comand();
		if(comando >= 1 and comando <= 3){
			estruturaDeDadosGrafo(G,comando);
		}
		else if(comando == 4){
			int u = getVertice(G);
			if(u == -1){
				cout << "Vertice nao esta no Grafo\n";
			}
			else{
				cout << "Vizinhos do vertice ";
				G->printPos(u);
				cout << "\n";
				obtemVizinhos(G,u);
			}
		}
		else if(comando == 5){
			int u = getVertice(G);
			if(u == -1){
				cout << "Vertice nao esta no Grafo\n";
			}
			else{
				cout << "Predecessores do vertice ";
				G->printPos(u);
				cout << "\n";
				obtemPred(G,u);
			}
		}
		else if(comando == 6){
			int u = getVertice(G);
			if(u == -1){
				cout << "Vertice nao esta no Grafo\n";
			}
			else{
				cout << "Sucessores do vertice ";
				G->printPos(u);
				cout << "\n";
				obtemSuc(G,u);
			}
		}
		else if(comando == 7){
			cout << "VERTICE U\n";
			int u = getVertice(G);
			cout << "VERTICE V\n";
			int v = getVertice(G);
			if(u == -1 or v == -1){
				cout << "Vertice nao esta no Grafo\n";
			}
			else{
				ehVizinho(G,u,v);
			}
		}
		else if(comando == 8){
			cout << "VERTICE U\n";
			int u = getVertice(G);
			cout << "VERTICE V\n";
			int v = getVertice(G);
			if(u == -1 or v == -1){
				cout << "Vertice nao esta no Grafo\n";
			}
			else{
				ehPredecessor(G,u,v);
			}
		}
		else if(comando == 9){
			cout << "VERTICE U\n";
			int u = getVertice(G);
			cout << "VERTICE V\n";
			int v = getVertice(G);
			if(u == -1 or v == -1){
				cout << "Vertice nao esta no Grafo\n";
			}
			else{
				ehSucessor(G,u,v);
			}
		}
		else if(comando == 10){
		}
		else if(comando == 11){
		}
		else if(comando == 12){
		}
		else if(comando == 13){
		}
		else{
		}
	}while(comando != 0);
}

int main() {

	bool ponderado = ePonderado();
	bool eucledian = dadosVertices();
	int qualEstrutura = estruturaUtilizada();

	string orientation;
	string nomeArquivo = nomeArq() + ".txt";

  ifstream arquivo(nomeArquivo.c_str());

  if (arquivo) {
		arquivo >> orientation;

		if (orientation == "UNDIRECTED" or orientation == "DIRECTED") {
			grafo* Grafo = new grafo(orientation, ponderado, qualEstrutura);

			while (arquivo.good()) {
				if(ponderado == true) {
					dado dadosNohA;
					dado dadosNohB;
					int peso;

					arquivo >> dadosNohA;
					arquivo >> dadosNohB;
					arquivo >> peso;

          Grafo->insertAresta(dadosNohA, dadosNohB, peso);
				} else {
					if (eucledian == true) {
						coord coordenadasA;
						coord coordenadasB;
						int num;

						arquivo >> num;
						arquivo >> coordenadasA.x;
						arquivo >> coordenadasA.y;
						arquivo >> coordenadasB.x;
						arquivo >> coordenadasB.y;

            Grafo->insertAresta(coordenadasA, coordenadasB);
					} else {
						dado dadosNohA;
						dado dadosNohB;

						arquivo >> dadosNohA;
						arquivo >> dadosNohB;

            Grafo->insertAresta(dadosNohA, dadosNohB);
					}
				}
			}
			menu(Grafo);
		} else {
      cout << "##############################################################" << endl;
      cout << "###################   Falha ao ler Arquivo   #################" << endl;
      cout << "##############################################################" << endl;
			exit(EXIT_FAILURE);
		}
	} else {
    cout << "##############################################################" << endl;
    cout << "##################   Falha ao abrir Arquivo   ################" << endl;
    cout << "##############################################################" << endl;
		exit(EXIT_FAILURE);
	}

return 0;
}
