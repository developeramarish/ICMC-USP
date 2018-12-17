#include <vector>
#include <queue>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define VISITED 1
#define UNVISITED 0
#define INF 100000
#define TRUE 1
#define FALSE 0

using namespace std;


/*
Vamos fazer uma estrutura de dados usando a classe STL vector..
Esta estrutura considera que o grafo é ponderado, ou seja, tem
um peso.....
*/

#define Vertex int

typedef pair<Vertex,Vertex> ii; // primeiro elemento = vertice w; segundo elem= peso
typedef vector<ii> vii;   // um vetor de pares <w,peso> ...
typedef vector<Vertex> vi;

// o grafo consiste de vértices, numerados de 0, v-1
// vamos assumir que são designados por valores inteiros.



// Para manter a compatibilidade com o que vimos fazendo, podemos definir uma estrutura
// Graph.
typedef struct graph{
	int nVert;
	int nEdge;
	int peso;
    vector<vii> adjList;
}Graph;

Graph initGraph(int nVert){
	Graph g;
	g.nVert = nVert;
	// redefine o vector com nVert elementos...
	g.adjList.resize(nVert);

	return g;
}

// insere um arco (aresta) v, w em g ao final da lista...
void addArc(Graph *g, Vertex v, Vertex w, int peso){
	g->adjList[v].push_back(make_pair(w,peso));
}

void printGraph(Graph g){
	// para todos os vertices...
	for (int i = 0; i < g.nVert; ++i)
	{	
		printf("%d ->> ", i);
		for(int j = 0; j<g.adjList[i].size(); j++){
			printf("%d ", g.adjList[i][j].first);
		}
		printf("\n");
	}
}

/*
	Buscar em largura(breadth-first search): percorre o grafo em "camadas". Seja um 
	vertice v (primeira camada). Selecione todos vertice w adjacente a v e visite-os.
	repita o processo sucessivamente, "cortando" grafo em "camadas de adjacencia" 

	PAra fazer isso, precisamos de uma fila. Antes de chamar a funcao, coloque o vertice 
	v na fila. Enquanto a fila nao for vazia, faca: 
		- retire o vertice v da fila q. (e imprima...)
		- para todos os seus adjacentes, se ainda nao visitados, coloque-os na
			fila.
*/


void dijkstraWithPriQueue(Graph &g, vi &dist, priority_queue< ii, vii, greater<ii> > &pq, Vertex s, vi &pai){
	Vertex v;
	int d;

	while (!pq.empty()) {
		// Alg. Guloso: pega o vertice nao visitado de menor peso
		ii front = pq.top(); pq.pop(); 
		printf(" topo da fila... %d\n", front.second);

		v = front.second;
		d = front.first; 

		if (d > dist[v]) continue;  // esquisito ???? por que isso aqui???

		for (int j = 0; j < g.adjList[v].size(); j++) {
			// para todo vertice w adjacente a v
			ii w = g.adjList[v][j];
			if (dist[v] + w.second < dist[w.first]) {
				dist[w.first] = dist[v] + w.second;
				pai[w.first] = v;
				// coloca este vertice na fila prioridade..
				pq.push(ii(dist[w.first], w.first));
			} 
		} 
	}
}


void printPath(vi &p, Vertex s, Vertex t){
	// chegou no inicio... imprime s...
	if (t == s) { 
		printf("%d ", s);
		return;
	}
	printPath(p, s, p[t]);
	printf("%d ", t);
}

int main(int argc, char const *argv[])
{
	/* code */
	int nVert;
	Vertex v1,v2;
	int peso;

	scanf("%d\n", &nVert);
	Graph g = initGraph(nVert);
	//cout << g.adjList.size();


	//addArc(g,0,1);
	while (scanf("%d %d %d\n", &v1, &v2, &peso)  != EOF){
	  addArc(&g,v1,v2,peso);
	  // para utilizar esta estrutura para grafo, basta chamar..
	  //addArc(&g,v2,v1,peso);
	}

	printGraph(g);

	// cria um vetor de tamanho nVert de distancia inicialmente infinito.
	vi dist(g.nVert, INF);
	//qq um vetor que guarda o pai do vertice i p[i]. Assim podemos
	// tracar a rota de r até qq outro vertice do grafo...
	vi pai(g.nVert);

	// percorre em largura o grafo g, a partir do vertice v, com vetor visited falso 

	Vertex s = 0;
	dist[s] = 0; // a distancia do vertice 0 para ele mesmo eh zero  !!
	
	// fila de prioridade em que o primeiro elemento eh o PESO e o segundo o vertice w
	priority_queue< ii, vii, greater<ii> > pq; 
	pq.push(ii(0, s));

	dijkstraWithPriQueue(g, dist, pq, s, pai);

	// por curiosidade, imprima o caminho de 0 ate 3.....

	for (int i = 0; i < g.nVert; ++i)
	{
		printf("%d ", dist[i]);
	} printf("\n");

	printPath(pai, 0, 4);
	printf("\n");


	return 0;
}
