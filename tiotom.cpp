#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <queue>

#define INF 0xffffff

using namespace std;

vector<vector<int> > 	mapa;
vector<vector<int> > 	adj;
vector<pair<int, int> > previous;
vector<int> 		 	visited;
vector<int>				caminho;
int h, w, n, source, sink, fluxmax;

void bipartir_com_BFS(vector<vector<int> > &adj);
int fordfulkerson();
int dfs(int davez, int sink, int &fluxo);

int  main()
{
	int a, b, c, y, x, v1, v2;
	while (cin >> h >> w && h && w)
	{
		fluxmax = 0;
		a = h; b = w; source = 0; sink = h*w+1; n = sink+1;
		// Criar variáveis locais e setar Source e Sink.

		mapa.assign(h + 2, vector<int> (w + 2, 1));
		visited.assign(h * w + 2, false);

		// BEGIN Leitura de lagos
		cin >> a;
		while (a--)
		{
			cin >> y >> x;
			mapa[y][x] = 0;
			visited[x+(y-1)*w] = true;
		}
		// END Leitura de lagos

		adj.assign(h * w + 2, vector<int> (h * w + 2, 0));

		// BEGIN Transformar mapa em grafo, identificando cada célula com um ID (c)
		c = 1; // 0 é reservado pra source
		for (int i = 1; i <= h; i++)
		{
			for (int j = 1; j <= w; j++)
			{
				if (mapa[i][j] == 1)
				{
					if (i-1 > 0 && mapa[i-1][j] == 1) {/*printf("%d (%d,%d) - %d (%d,%d)\n", c, i, j, c-w, i-1, j);*/ adj[c][c-w] = 1; adj[c-w][c] = 1; }
					if (i+1 < h && mapa[i+1][j] == 1) {/*printf("%d (%d,%d) - %d (%d,%d)\n", c, i, j, c+w, i+1, j);*/ adj[c][c+w] = 1; adj[c+w][c] = 1; }
					if (j-1 > 0 && mapa[i][j-1] == 1) {/*printf("%d (%d,%d) - %d (%d,%d)\n", c, i, j, c-1, i, j-1);*/ adj[c][c-1] = 1; adj[c-1][c] = 1; }
					if (j+1 < w && mapa[i][j+1] == 1) {/*printf("%d (%d,%d) - %d (%d,%d)\n", c, i, j, c+1, i, j+1);*/ adj[c][c+1] = 1; adj[c+1][c] = 1; }
				}
				c++;
			}
		}
		// END Transformar mapa em grafo

		/*
		cout << endl << "  ";
		for (int i = 0; i < n; i++)
			cout << setw(2) << i%10;
		cout << endl;
		for (int i = 0; i < n; i++)
		{
			cout << setw(2) << i%10;
			for (int j = 0; j < n; j++)
			{
				cout << setw(2) << (adj[i][j] ? "1" : "-");
			}
			cout << endl;
		}
		*/
		
		printf("\nTerras:\n");
		for (int i = 1; i < n - 1; i++)
		{
			printf("%s%s", visited[i] ? "-": "S", !(i%3)? "\n" : " ");
		} printf("\n");

		bipartir_com_BFS(adj);
		
		/*
		cout << endl << "  ";
		for (int i = 0; i < n; i++)
			cout << setw(2) << i%10;
		cout << endl;
		for (int i = 0; i < n; i++)
		{
			cout << setw(2) << i%10;
			for (int j = 0; j < n; j++)
			{
				cout << setw(2) << (adj[i][j] ? "1" : "-");
			}
			cout << endl;
		}
		*/

		fordfulkerson();
		cout << fluxmax << endl;

	}

	return 0;
}

// Bipartir o grafo (BFS)
void bipartir_com_BFS(vector<vector<int> > &adj)
{
	queue<pair<int, int> > fila;
	queue<pair<int, int> > bipart;

	pair<int, int> aux;
	int davez, lado;

	for (int i = 1; i < visited.size() - 1; i++)
	{
		if (!visited[i])
		{
			fila.push(make_pair(i, 0));
			bipart.push(make_pair(i, 0));
			visited[i] = true;
		}

		while (!fila.empty())
		{
			aux = fila.front(); fila.pop();
			davez = aux.first;
			lado = aux.second;

			for (int j = 1; j < n - 1; j++)
			{
				if (adj[davez][j] != 1) continue;
				
				if (!visited[j])
				{
					fila.push(make_pair(j, !lado));
					bipart.push(make_pair(j, !lado));
					visited[j] = true;
				}
			}
		}
	}

	while (!bipart.empty())
	{
		aux = bipart.front(); bipart.pop();
		davez = aux.first;
		lado = aux.second;

		if (!lado)
		{
			adj[source][davez] = 1; // source -> davez
			for (int i = 1; i < n; i++)
				adj[i][davez] = 0;
		}
		else
		{
			adj[davez][sink] = 1; // davez -> sink
			for (int i = 0; i < n-1; i++)
				adj[davez][i] = 0;
		}
	}

	return;
}

// Ford-Fulkerson
int fordfulkerson()
{
	int fluxo;

	do
	{
		previous.assign(n, make_pair(-1, INF));
		visited.assign(n, 0);
		fluxo = 0;
		dfs(source, sink, fluxo);
		fluxmax += fluxo;

		cout << "Caminho: s ";
		while (caminho.size() > 0)
		{
			cout << caminho.at(caminho.size() - 1) << " ";
			caminho.pop_back();
		} cout << "t" << endl;
		
	} while (fluxo != 0);

	return fluxmax;
}

// DFS usada pelo Ford-Fulkerson
int dfs(int davez, int sink, int &fluxo)
{
	visited[davez] = true; // Marcar como visitado.
	int peso;
	if (davez == sink)
	{
		fluxo = 0;
		return true;
	}
	
	for (int i = 0; i < n; i++)
	{
		peso = adj[davez][i];
		if (peso != 0)
		{
			if (!visited[i])
			{
				// Peso vai sendo mantido ou diminuido a cada iteração, nunca incrementado.
				peso = min(adj[davez][i], previous[davez].second); 

				// Marcar o histórico do próximo para caso acerte o caminho
				previous[i] = make_pair(davez, peso);

				if (dfs(i, sink, fluxo))  // SUCESSO
				{
					if (fluxo == 0)
						fluxo = peso; // Registrar o último
					else
						peso = min(peso, fluxo); // Reduzir os anteriores

					if (davez != source) caminho.push_back(davez);

					// Fluxo é calculado com base no mínimo peso do caminho.
					adj[davez][i] -= fluxo;
				
					// Ajuste do fluxo residual
					adj[i][davez] += fluxo;

					return true;
				}

				// Desmarcar como visitado
				visited[i] = false;
				
				// Limpar o histórico do próximo
				previous[i] = make_pair(-1, INF);
			}
		}
	}

	return false;
}