#include <iostream>
#include <cstdlib>
#include <fstream>
#include "TP2.h"
#include "TP2.cpp" // Para rodar no Geany, basta retirar o comentario

using namespace std;

int main()
{
	fstream arquivo("P1.txt");
	fstream arquivo2("P1.txt");
	
	int comando = getComando();
	
	if(comando == 0){
		if (arquivo)
		{
			solution_1(arquivo);
			
		}
		if(arquivo2){
			solution_2(arquivo2);
		}
	}
	else if(comando == 1){
		if (arquivo)
		{
			solution_1(arquivo);
		}
	}
	else if(comando == 2){
		if(arquivo2){
			solution_2(arquivo2);
		}
	}
	else{
		cerr << "Comando invalido\n";
	}
	
	arquivo.close();
	arquivo2.close();
	
	return 0;
}
