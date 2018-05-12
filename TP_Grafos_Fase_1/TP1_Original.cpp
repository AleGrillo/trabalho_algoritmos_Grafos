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
			cerr << "falha ao ler o arquivo\n";
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		cerr << "falha ao abrir o arquivo\n";
		exit(EXIT_FAILURE);
	}

	return 0;
}
