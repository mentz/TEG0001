#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <cstdlib>
#include <map>
#include <iomanip>
#include <cmath>
#include <queue>

#define MAX(a,b) ((a<b)?b:a)
#define MIN(a,b) ((a<b)?a:b)
#define INFINITO (1<<29)
#define NAODIRECIONADO 0
#define DIRECIONADO 1
#define PONDERADO 2

typedef unsigned int uint;

using namespace std;

struct GVertice {
	string nome;
	uint id;
	int cor; // Não implementado.
	uint grau;
	bool marcado;
	vector<uint> arestas; // Guarda identificador (a_id) das arestas que tocam esse vértice.

	GVertice(string nome, uint v_id)
	{
		this->nome		= nome;
		this->id		= v_id;
		this->cor		= 0;
		this->grau		= 0;
		this->marcado	= false;
		this->arestas	= vector<uint>();
	}
};

struct GAresta {
	string nome;
	uint id;
	uint v1, v2; // Guarda identificador (v_id) dos vértices nas pontas dessa aresta.
	int peso;
	bool marcado;

	// Construtor
	GAresta(uint v1_id, uint v2_id, uint a_id);

	void setPeso(int p);
	int getPeso();
};

class Grafo {
private:
	uint num_vertices, v_id_c; // v_id_c é o identificador único incremental para cada GVertice.
	uint num_arestas, a_id_c; // a_id_c é o identificador único incremental para cada GAresta.
	vector<GVertice> vertices;
	vector<GAresta> arestas;
	bool set;

	int tipo; /* 0 para não-direcionado,
				 1 para direcionado,
				 2 para não-direcionado ponderado,
				 3 para direcionado ponderado.
			  	*/

public:
	Grafo()
	{
		this->num_vertices = 0;
		this->num_arestas = 0;
		this->v_id_c = 0;
		this->a_id_c = 0;
		this->tipo = -1; // Não inicializado.
		this->set = false;
	}

	bool isSet();

	void leGrafo();
	void leGrafo(string caminho);
	void mostraMatAdj(bool complemento);
	void mostraMatInc();
	void mostraListaAdj();
	void mostraGrau();
	void mostraGrauTotal();

	// Apresenta lista de vértices.
	void listaVertices(bool marcado, bool grau, bool cor);

	// Apresenta lista de arestas.
	void listaArestas(bool marcado);

	// Atualiza num_vertices
	void atualizaNumVertices();

	// Atualiza num_arestas
	void atualizaNumArestas();

	/**	void addVertice([string v1|GVertice v1]);
	 *	Pode ter argumentos:
	 *	1. Nada, solicitando nome e peso (opcional) do vértice;
	 *	2. Uma string, gerando um vértice simples (sem peso);
	 */
	void addVertice();
	void addVertice(string v1);

	// Não tem argumentos, pede o nome do vértice a ser removido.
	/** void remVertice([string v1]);
	 *	Pode ter argumentos:
	 *	1. Nenhum. Apresenta lista de vértices e pede o nome do vértice
	 *		a ser removido;
	 *	2. Uma string, removendo o vértice que tem nome igual à string.
	 */
	void remVertice();
	void remVertice(string v);
	void remVertice(uint v_id);

	/** void addAresta();
	 *	Pode ter argumentos:
	 *	1. Nenhum: apresenta os vértices e pede quais serão parte da aresta;
	 *	2. Nome dos dois vértices: gera um nome para a nova aresta.
	 *	3. ID dos dois vértices: gera um nome para a nova aresta.
	 */
	void addAresta();
	void addAresta(string v1, string v2, int peso);
	void addAresta(uint v1_id, uint v2_id, int peso);

	/** void remAresta(..);
	 *	Variações:
	 *	remAresta(); Lista as arestas e pede para o usuário escolher qual deve remover.
	 * 	remAresta(uint a_id); Faz a remoção da aresta indicada. Não é acionado pelo usuário.
	 */
	void remAresta();
	void remAresta(uint a_id);

	// Retorna o nome do vértice baseado no ID dele.
	string getNomeV(uint v_id);

	// Retorna o nome da aresta baseado no ID dela.
	string getNomeA(uint a_id);

	/** uint getIndexV(..);
	 *	Variações:
	 *	getIndexV(string v); Busca pelo nome do vértice.
	 *	getIndexV(uint v_id); Busca pelo ID do vértice.
	 */
	int getIndexV(string v);
	int getIndexV(uint v_id);


	/** uint getIndexA(..);
	 *	Variações:
	 *	getIndexA(string a); Busca pelo nome da aresta.
	 *	getIndexA(uint a_id); Busca pelo ID da aresta.
	 */
	int getIndexA(string a);
	int getIndexA(uint a_id);

	// Calcula grau do vértice fornecido
	void atualizaGrauV(uint v_id);

	// Apresenta os graus de todos os vértices.
	void getGrauVertice();

	// Apresenta o grau do grafo.
	void getGrauGrafo();

	// Percorre a aresta com base no vértice de partida
	uint percorreAresta(uint a_id, uint v_id, bool reverso);

	bool verificaConexo(bool print);

	// DFS. Apenas marca os vértices onde passa.
	void DFS(uint v_davez);

	void mostraComplMatAdj();

	int verificaIsomorfismo(Grafo* g2);

	// Marcação de vértice.
	bool getMarcadoVertice(uint v_id); // Retorna true se está marcado, false se não.
	void marcaVertice(uint v_id);
	void desmarcaVertice(uint v_id);
	void desmarcaTodosVertices();

	// Marcação de aresta.
	bool getMarcadoAresta(uint a_id); // Retorna true se está marcado, false se não.
	void marcaAresta(uint a_id);
	void desmarcaAresta(uint a_id);
	void desmarcaTodasArestas();

	// Verifica se o grafo é Euleriano
	void rodaFleury();
	bool fleury(uint v_davez_id, uint v_inicial_id);

	// Colore o grafo e opcionalmente mostra a coloração dos vértices
	int colorir(bool imprime);

	// DEGUB:
	void listaArestasDeVertice(uint v_id);

	// DFS:
	void runDFS();
	void DFS_DFS0(uint atual, uint anterior, vector<vector<uint> > &arvDfs, vector<vector<uint> > &rArvDfs, vector<bool> &visitado, vector<vector<uint> > &listaAdj);
	void DFS_DFS1(uint atual, vector<uint> &parentes,  vector<vector<uint> > &lista, vector<bool> & visitado);
	void DFS_getTopologico(uint atual, vector<vector<uint> > &listaAdj, vector<bool> &visitado, vector<uint> &vetTopologico);
	void DFS_getInfoNo(uint v, vector<bool> &visitado, vector<vector<uint> > &listaAdj, vector<vector<uint> > &arvDfs, vector<vector<uint> > &rArvDfs);
	void DFS_printArvoreDFS(vector<vector<uint> > &arvDfs);

	// Dijkstra:
	void runDijkstra();
	void Dijkstra(vector<uint> &dist, vector<int> &previous, int v_first);

	// Bellman-Ford:
	void runBellmanFord();
	int  BellmanFord(vector<int> &dist, vector<int> &previous, int v_first);

	// Floyd-Warshall:
	void runFloydWarshall();
	void FloydWarshall(vector<vector<int> > &dist);

	// Prim:
	void runPrim();

	// Ford-Fulkerson:
	void runFordFulkerson();
	int  proxFluxo(int v_origem, int v_destino, vector<int> &caminho);
};

int menu(Grafo* g);