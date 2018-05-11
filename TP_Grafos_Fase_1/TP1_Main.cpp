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
bool ePonderado(){
	cout << "-GRAFO PONDERADO-\n";
	cout << "Sim				0\n";
	cout << "Nao				1\n";
	int comando;
	cin >> comando;

	if(comando == 0){
		return true;
	}
	else if(comando == 1){
		return false;
	}
	else{
		cout << "comando invalido\n";
		exit(EXIT_FAILURE);
	}
}

string nomeArq(){
	cout << "-NOME DO ARQUIVO-\n";
	string nome;
	cin >> nome;
	return nome;
}

int estruturaUtilizada(){
	cout << "-QUAL ESTRUTURA DE DADOS SERA UTILIZADA-\n";
	cout << "Lista de Adjacencias					1\n";
	cout << "Matriz de Adjacencias					2\n";
	cout << "Matriz de Incidencias					3\n";

	int comando;
	cin >> comando;

	if(comando > 0 and comando < 4){
		return comando;
	}
	else{
		cout << "comando invalido\n";
		exit(EXIT_FAILURE);
	}
}

bool dadosVertices(){
	cout << "-QUAIS DADOS SERAO PASSADOS PARA OS VERTICES-\n";
	cout << "Coordenadas (Euclediano)				0\n";
	cout << "Apenas valores						1\n";

	int comando;
	cin >> comando;

	if(comando == 0){
		return true;
	}
	else if(comando == 1){
		return false;
	}
	else{
		cout << "comando invalido\n";
		exit(EXIT_FAILURE);
	}
}


int menu(){
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

  if(arquivo){
		arquivo >> orientation;
		if(orientation == "UNDIRECTED" or orientation == "DIRECTED"){
			grafo* Grafo = new grafo(orientation, ponderado, qualEstrutura);

			while(arquivo.good()){
				if(ponderado == true){
					dado dadosNohA;
					dado dadosNohB;
					int peso;
					arquivo >> dadosNohA;
					arquivo >> dadosNohB;
					arquivo >> peso;
					Grafo->insertAresta(dadosNohA,dadosNohB,peso);
				}
				else{
					if(eucledian == true){
						coord coordenadasA;
						coord coordenadasB;
						int num;
						arquivo >> num;
						arquivo >> coordenadasA.x;
						arquivo >> coordenadasA.y;
						arquivo >> coordenadasB.x;
						arquivo >> coordenadasB.y;
						Grafo->insertAresta(coordenadasA,coordenadasB);
					}
					else{
						dado dadosNohA;
						dado dadosNohB;
						arquivo >> dadosNohA;
						arquivo >> dadosNohB;
						Grafo->insertAresta(dadosNohA,dadosNohB);
					}
				}
			}
			Grafo->printGrafo();
		}
		else{
			cerr << "falha ao ler o arquivo\n";
			exit(EXIT_FAILURE);
		}
	}
	else{
		cerr << "falha ao abrir o arquivo\n";
		exit(EXIT_FAILURE);
	}

return 0;
}
