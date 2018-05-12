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

int main()
{
	bool ponderado = ePonderado();
	bool eucledian = dadosVertices();
	int qualEstrutura = estruturaUtilizada();

	string orientation;
	string nomeArquivo = nomeArq() + ".txt";

	ifstream arquivo(nomeArquivo.c_str());

	if (arquivo)
	{
		arquivo >> orientation;
		if (orientation == "UNDIRECTED" or orientation == "DIRECTED")
		{
			grafo *Grafo = new grafo(orientation, ponderado, eucledian, qualEstrutura);

			while (arquivo.good())
			{
				if (ponderado == true)
				{
					dado dadosNohA;
					dado dadosNohB;
					int peso;
					arquivo >> dadosNohA;
					arquivo >> dadosNohB;
					arquivo >> peso;
					Grafo->insertAresta(dadosNohA, dadosNohB, peso);
				}
				else
				{
					if (eucledian == true)
					{
						coord coordenadasA;
						coord coordenadasB;
						int num;
						arquivo >> num;
						arquivo >> coordenadasA.x;
						arquivo >> coordenadasA.y;
						arquivo >> coordenadasB.x;
						arquivo >> coordenadasB.y;
						Grafo->insertAresta(coordenadasA, coordenadasB);
					}
					else
					{
						dado dadosNohA;
						dado dadosNohB;
						arquivo >> dadosNohA;
						arquivo >> dadosNohB;
						Grafo->insertAresta(dadosNohA, dadosNohB);
					}
				}
			}
			menu(Grafo);
		}
		else
		{
			cout << "##############################################################" << endl;
			cerr << "###################   Falha ao ler Arquivo   #################" << endl;
			cout << "##############################################################" << endl;
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		cout << "##############################################################" << endl;
		cerr << "##################   Falha ao abrir Arquivo   ################" << endl;
		cout << "##############################################################" << endl;
		exit(EXIT_FAILURE);
	}

	return 0;
}
