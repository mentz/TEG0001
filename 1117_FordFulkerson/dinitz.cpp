#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <iomanip>

#define INF 0xffffff

using namespace std;

vector<vector<int> > 	adj;
vector<pair<int, int> > previous;
vector<int> 			visited;
vector<vector<int> >	levels;
int n, e, fmax, source, sink;

int dinitz();
int nivela_com_bfs();
int fordfulkerson();
int dfs(int davez, int sink, int &fluxo);

int main()
{
	int v1, v2, p;
	string aux, aux2;

	map<string, int> s_i;

	cin >> n >> e;
	for (int i = 0; i < n; i++)
	{
		cin >> aux;
		s_i[aux] = i;
	}

	adj.assign(n, vector<int> (n, 0));

	for (int i = 0; i < e; i++)
	{
		cin >> aux >> aux2 >> p;
		adj[s_i[aux]][s_i[aux2]] = p;
	}

	cin >> aux >> aux2;
	source = s_i[aux];
	sink   = s_i[aux2];

	dinitz();

	cout << "Fluxo Máximo: " << fmax << endl;

	return 0;
}

// Dinitz
int dinitz()
{
	levels.assign(n, vector<int> (0));
	vector<vector<int> > newadj(n, vector<int> (n, 0));
	visited.assign(n, false);
	nivela_com_bfs();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < levels[i].size() - 1; j++)
		{
			for (int k = 1; k < levels[i].size(); k++)
			{
				newadj[levels[i][j]][levels[i][k]] = adj[levels[i][j]][levels[i][k]];
				adj[levels[i][j]][levels[i][k]] = 0;
				newadj[levels[i][k]][levels[i][j]] = adj[levels[i][k]][levels[i][j]];
				adj[levels[i][k]][levels[i][j]] = 0;
				cout << "nivela " << j << " e " << k << endl;
			}
		}
	}

	visited.assign(n, false);

	cout << "1";

	fordfulkerson();

	cout << "2";

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			adj[i][j] = newadj[i][j];
		}
	}

	cout << "3";

	fordfulkerson();

	cout << "4";
	
	return fmax;
}

// Nivela com BFS para remover arestas verticais
int nivela_com_bfs()
{
	int davez, nivel;
	queue<pair<int, int> > fila;
	pair<int, int> aux;
	fila.push(make_pair(source, 0));

	while(!fila.empty())
	{
		aux = fila.front(); fila.pop();
		davez = aux.first;
		nivel = aux.second;
		visited[davez] = true;
		levels[nivel].push_back(davez);
		for (int i = 0; i < n; i++)
		{
			if (adj[davez][i] && !visited[i])
			{
				fila.push(make_pair(i, nivel++));
				visited[i] = true;
			}
		}
	}

	return 0;
}

// Ford-Fulkerson
int fordfulkerson()
{
	int fluxo;

	do
	{
		cout << endl;		
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cout << setw(5) << adj[i][j] << " ";
			}
			cout << endl;
		}

		previous.assign(n, make_pair(-1, INF));
		visited.assign(n, 0);
		fluxo = 0;
		dfs(source, sink, fluxo);
		fmax += fluxo;

		cout << source << endl << "f: " << fluxo << endl;

	} while (fluxo != 0);

	return fmax;
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
				peso = min(adj[davez][i], previous[davez].second);
				previous[i] = make_pair(davez, peso); // Setar histórico do próximo para caso acerte o caminho.
				if (dfs(i, sink, fluxo)) 
				{
					if (fluxo == 0)
						fluxo = peso;
					else
						peso = min(peso, fluxo);

					//cout << i << " ";
					
					adj[davez][i] -= fluxo;
					adj[i][davez] += fluxo; // Fluxo residual

					return true;
				}
				visited[i] = false; // Desmarcar como visitado.
				previous[i] = make_pair(-1, INF); // Limpar o histórico do próximo pois não acertou o caminho.
			}
		}
	}

	return false;
}