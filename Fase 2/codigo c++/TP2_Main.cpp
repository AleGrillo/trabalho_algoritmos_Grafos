#include <iostream>
#include <cstdlib>
#include <fstream>
#include "TP2.h"
#include "TP2.cpp" // Para rodar no Geany, basta retirar o comentario

using namespace std;

int main()
{
	fstream arquivo("P1.txt");

	if (arquivo)
	{
		vetGroup *grupos = NULL;
		vertices *vertices_grafo = NULL;
		listasAdj *lAdj = NULL;
		matrizAdj *mAdj = NULL;
		int *vetorId = NULL;
		int qntVertices, qntGrupos;
		read(arquivo, grupos, vertices_grafo, lAdj, mAdj, qntVertices, qntGrupos);
		vetorId = vetorContador(lAdj, qntVertices);
		initializeGroups(grupos, lAdj, vertices_grafo, vetorId, qntGrupos);
		/*Solução 1
		//~ mount_groups(vertices_grafo, grupos, lAdj, qntGrupos);
		//~ cout << "Solucao 1\n" << max_distance(grupos, mAdj) << "\n";
		*/

		//~ /*Solução 2
		mount_groups(vertices_grafo, grupos, mAdj);
		max_distance(grupos, mAdj);
		cout << "Solucao 2\n" << compute_max_distance(grupos) << "\n";
		//~ */
		delete grupos;
		delete vertices_grafo;
		delete lAdj;
		delete mAdj;
		delete[] vetorId;
	}

	return 0;
}
