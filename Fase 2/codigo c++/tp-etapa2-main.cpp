#include <iostream>
#include <cstdlib>
#include <fstream>
#include "tp-etapa2.hpp"
#include "tp-etapa2.cpp" // Para rodar no Geany, basta retirar o comentario

using namespace std;

int main()
{
	fstream arquivo("P2.txt");
	
	if(arquivo){
		vetGroup* grupos = NULL;
		vertices* vertices_grafo = NULL;
		listasAdj* lAdj = NULL;
		matrizAdj* mAdj = NULL;
		int* vetorId = NULL;
		int qntVertices, qntGrupos;
		read(arquivo, grupos, vertices_grafo, lAdj, mAdj, qntVertices, qntGrupos);
		vetorId = vetorContador(lAdj, qntVertices);
		initializeGroups(grupos, lAdj, vertices_grafo, vetorId, qntGrupos);
		mount_groups(vertices_grafo, grupos, lAdj, qntGrupos);
		double distancia = max_distance(grupos, mAdj);
		cout << distancia << endl;
		delete grupos;
		delete vertices_grafo;
		delete lAdj;
		delete mAdj;
		delete []vetorId;
	}
return 0;
}
