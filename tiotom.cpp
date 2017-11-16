#include <bits/stdc++.h>

using namespace std;

vector<vector<int> > mapa;
vector<vector<int> > adj;
vector<bool> visited;
int h, w, source, sink;

int  calculaFluxo(vector<vector<int> > adj)
{
	return 0;
}

void bipartir_com_BFS(vector<vector<int> > &adj)
{
	queue<pair<int, int> > fila;

	pair<int, int> aux;
	int davez, lado;

	for (int i = 1; i < visited.size() - 1; i++)
	{
		if (!visited[i])
		{
			fila.push(make_pair(i, 0));
			visited[i] = true;
			printf("Adicionando %2d na fila.\n", i);
		}

		while (!fila.empty())
		{
			aux = fila.front(); fila.pop();
			davez = aux.first;
			lado = aux.second;
			printf("    nó %2d - lado %d:", davez, lado);

			if (!lado)
			{
				adj[source][davez] = 1; // source -> davez
				printf(" é PAR. source -> %2d\n", davez);
			}
			else
			{
				adj[davez][sink] = 1; // davez -> sink
				printf(" é ÍMPAR. %2d -> sink\n", davez);
			}

			for (int j = 1; j < adj[davez].size() - 1; j++)
			{
				if (adj[davez][j] != 1) continue;
				if (!visited[j])
				{
					fila.push(make_pair(j, !lado));
					visited[j] = true;
					adj[j][davez] = 0;
					printf("        Adicionando vizinho: %2d e removendo retorno.\n", j);
				}
			}
			if (fila.empty()) printf("A fila acabou.\n");
		}
	}

	return;
}

int  main()
{
	int a, b, c, y, x, v1, v2;
	while (cin >> h >> w && h && w)
	{
		a = h; b = w; source = 0; sink = h*w+1;
		// Criar variáveis locais e setar Source e Sink.

		mapa.assign(h + 2, vector<int> (w + 2, 1));
		visited.assign(h * w + 2, false);

		// BEGIN Leitura de lagos
		cin >> a;
		while (a--)
		{
			cin >> x >> y;
			mapa[y][x] = 0;
			visited[y+(x-1)*w] = true;
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
					if (i-1 > 0 && mapa[i-1][j] == 1) {printf("%d (%d,%d) - %d (%d,%d)\n", c, i, j, c-w, i-1, j); adj[c][c-w] = 1; adj[c-w][c] = 1; }
					if (i+1 < h && mapa[i+1][j] == 1) {printf("%d (%d,%d) - %d (%d,%d)\n", c, i, j, c+w, i+1, j); adj[c][c+w] = 1; adj[c+w][c] = 1; }
					if (j-1 > 0 && mapa[i][j-1] == 1) {printf("%d (%d,%d) - %d (%d,%d)\n", c, i, j, c-1, i, j-1); adj[c][c-1] = 1; adj[c-1][c] = 1; }
					if (j+1 < w && mapa[i][j+1] == 1) {printf("%d (%d,%d) - %d (%d,%d)\n", c, i, j, c+1, i, j+1); adj[c][c+1] = 1; adj[c+1][c] = 1; }
				}
				c++;
			}
		}
		// END Transformar para em grafo

		printf("\nTerras:\n");
		for (int i = 0; i <= h*w+1; i++)
		{
			printf("%s%s", visited[i] ? "-": "S", !(i%4)? "\n" : " ");
		} printf("\n");

		bipartir_com_BFS(adj);

		for (int i = 0; i <= h*w + 1; i++)
		{
			for (int j = 0; j <= h*w + 1; j++)
			{
				printf("%s ", adj[i][j] ? "1" : "-");
			} printf("\n");
		}
		

	}

	return 0;
}