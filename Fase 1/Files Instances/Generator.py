# Autor: Mayron Cesar de Oliveira Moreira
# GCC218 - Algoritmos em Grafos
# Gerador de grafos aleatorios

# Bibliotecas a serem inseridas. Caso nao tenham na maquina de voces, basta instala-las via pip ou conda.
import sys
import networkx as nx
import matplotlib.pyplot as plt
import random
import math
import time
import copy
from itertools import permutations

#################################################
# As funções "euclid_dist", "DesenhaGrafo" e "CriaGrafoAleatorio" foram retiradas do Mini-curso de Metaheurísticas, promovido pela profa. Fernanda Sumika (UFSJ), nos dias 05/04 e 06/04, como parte do ERMAC UFLA 2018 (http://www.eventos.ufla.br/ermac2018/) #
#################################################

# -----------------------------------------------#
def euclid_dist(p1,p2):
	return int(math.sqrt((p1[0]-p2[0])**2 + (p1[1]-p2[1])**2) + 0.5)
# -----------------------------------------------#

# -----------------------------------------------#
def DesenhaGrafo(G,cor):

	# Define layout da plotagem pela posicao dos vertices
	pos = nx.get_node_attributes(G,'pos')

	# Define cores e habilita rotulos nos vertices
	nx.draw(G, pos, with_labels = True, edge_color = cor)

	# Define pesos das arestas
	edge_labels = nx.get_edge_attributes(G,'weight')

	# Mostra pesos das arestas
	nx.draw_networkx_edge_labels(G, pos, edge_labels = edge_labels, font_size = 11)

	return pos
# -----------------------------------------------#

# -----------------------------------------------#
def CriaGrafoAleatorio(n, direct, pond):

#	if direct == False:
		# Cria um grafo completo nao direcionado 
#		G = nx.Graph()

#	else: # Cria um grafo completo direcionado 
#		G = nx.DiGraph()

	G = nx.gnm_random_graph(n, random.randint(n-1,n*(n-1)/2), seed=time.time(), directed=direct)

	x = random.sample(range(100), n)
	y = random.sample(range(100), n)

	# Adiciona vertices ao grafo
	for i in range(n):
		G.add_node(i, pos=(x[i],y[i]))

	if pond == True:
		# Adiciona arestas com pesos formando um grafo nao direcionado ponderado completo
		for e in G.edges():
			G.add_edge(e[0], e[1], weight=euclid_dist((x[e[0]],x[e[1]]), (y[e[0]], y[e[1]])))

	return G
# -----------------------------------------------#

# Escrevendo o grafo em um arquivo
# -----------------------------------------------#
def writeGraph(G, orientation, file_name, pond):
	print(file_name)
	file_obj = open(file_name, "w")

	# Padrao para grafos nao-direcionados
	if orientation == False:
		file_obj.write("UNDIRECTED\n")

	# Padrao para grafos direcionados
	else:
		file_obj.write("DIRECTED\n")

	# Impressao das arestas no arquivo
	for e in G.edges():
		for aux in e: # Variável auxiliar para iterar nas tuplas
			file_obj.write(str(aux) + " ")
		if pond == True: # Se for ponderado, acrescentamos mais uma informacao a aresta
			file_obj.write(str(G[e[0]][e[1]]['weight']))
		
		file_obj.write("\n")
	file_obj.close() 

# Geraremos 4 combinacoes, para cada configuracao de: vertice, orientacao e valor nas arestas.
combinations = 4
vertices = [5,10,15,20]
direcionado = [True,False]
ponderado = [True,False]

# Apenas para testar
G = CriaGrafoAleatorio(6, False, False)
pos = DesenhaGrafo(G,'r')
plt.show()
writeGraph(G, False, 0, False)

for n in vertices: # Em cada combinacao de vertices
	for direct in direcionado: # Em cada opcao de orientacao do grafo
		for pond in ponderado: # Em cada combinacao de ponderacao ou nao
			for c in range(0,combinations): # Para cada uma das quatro variacoes
				file_name = "n" + str(n) + "_"
				if direct == True:
					file_name = file_name + "dir_"
				else:
					file_name = file_name + "undir_"

				if pond == True:
					file_name = file_name + "wgt_"

				else:
					file_name = file_name + "unwgt_"

				file_name = file_name + "comb" + str(c) + ".txt"
				
				G = CriaGrafoAleatorio(n, direct, pond)
				writeGraph(G, direct, file_name, pond)
		
