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

int menu() {
	int comando = -1;
	return comando;
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
			Grafo->printGrafo();
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
