#include "grafo.hpp"
using namespace std;

/** Notas:
 *  Matriz de adjacência: Cada célula <x, y> indica o número de arestas ligando aqueles vértices.
 *	Em grafo não-direcionado: usa-se somente a parte triangular superior da matriz.
 *	Em grafo direcionado: usa-se a tabela inteira (não é simétrica).
 *	Grau de um vértice: somatório do valor da linha do vértice.
 *	Grau de entrada: somatório da coluna do vértice.
 *	Grau de saída: somatório da linha do vértice.
 *	Diagonal principal: indica arestas entre o mesmo ponto.
 */


/**	A implementar:
 *	Os métodos da classe 'Grafo'
 */

int menu(Grafo *g)
{
	int operacao = -1;

	puts("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");;
	puts("/*------------------------------------*/");
	puts("Menu:");
	puts("  0. Sair deste utilitário.");
	if (!g->isSet())
		puts("  1. Carregar grafo");
	// else
	// 	puts("  1. Carregar outro grafo");
	puts("  2. Apresenta matriz de adjacência");
	puts("  3. Apresenta matriz de incidência");
	puts("  4. Apresenta lista de adjacência");
	puts("  5. Apresentar grau do nó");
	puts("  6. Apresentar grau do grafo");
	puts("  7. Complemento matriz de adjacência");
	puts("  8. Adicionar vértice");
	puts("  9. Listar vértices");
	puts(" 10. Remover vértice");
	puts(" 11. Adicionar aresta");
	puts(" 12. Listar arestas");
	puts(" 13. Remover aresta");
	puts(" 14. Verificar se grafo é conexo");
	puts(" 15. Verificar se grafo é Euleriano");
	puts(" 16. Colorir o grafo");
	puts(" 17. Passar DFS no grafo");
	puts(" 18. Rodar Dijkstra");
	puts(" 19. Rodar Bellman-Ford");
	puts(" 20. Rodar Floyd-Warshall");
	puts(" 21. Rodar Prim");
	cout << "\nEscolha a operação: ";

	scanf("%d", &operacao);
	//system("clear");

	switch(operacao)
	{
		case 0:
			break;

		case 1:
			g->leGrafo();
			break;

		case 2:
			g->mostraMatAdj(false);
			break;

		case 3:
			g->mostraMatInc();
			break;

		case 4:
			g->mostraListaAdj();
			break;

		case 5:
			g->mostraGrau();
			break;

		case 6:
			g->mostraGrauTotal();
			break;

		case 7:
			g->mostraMatAdj(true);
			break;

		case 8:
			g->addVertice();
			break;

		case 9:
			g->listaVertices(false, false, false);
			break;

		case 10:
			g->remVertice();
			break;

		case 11:
			g->addAresta();
			break;

		case 12:
			g->listaArestas(false);
			break;

		case 13:
			g->remAresta();
			break;

		case 14:
			g->verificaConexo(true);
			break;

		case 15:
			g->rodaFleury();
			break;

		case 16:
			g->colorir(true);
			break;

		case 17:
			g->runDFS();
			break;
			
		case 18:
			g->runDijkstra();
			break;
			
		case 19:
			g->runBellmanFord();
			break;
			
		case 20:
			g->runFloydWarshall();
			break;
			
		case 21:
			g->runPrim();
			break;

		default:
			operacao = -1;
			break;
	}

	if (operacao != 0)
	{
		puts("Pressione 'Enter' para continuar.");
		getc(stdin); getc(stdin);
	}

	return operacao;
}

/*======================================**
			class GAresta
**======================================*/
GAresta::GAresta(uint v1_id, uint v2_id, uint a_id)
{
	ostringstream oss;
	oss << "u" << ((int) a_id);
	this->nome		= oss.str();
	this->id 		= a_id;
	this->v1 		= v1_id;
	this->v2	 	= v2_id;
	this->peso		= 1;
	this->marcado	= false;
}

/*--------------------------------------*/
void GAresta::setPeso(int p)
{
	this->peso = p;
}

/*--------------------------------------*/
int GAresta::getPeso()
{
	return this->peso;
}

/*======================================**
**			class Grafo					**
**======================================*/
bool Grafo::isSet()
{
	return set;
}

void Grafo::leGrafo()
{
	string caminho;
	puts("Insira o nome do arquivo (deve estar na pasta atual):");
	cin >> caminho;
	leGrafo(caminho);
}

/*--------------------------------------*/
void Grafo::leGrafo(string caminho)
{
	vertices.clear();
	arestas.clear();
	ifstream file;
	file.open(caminho);
	if (!file)
	{
		perror("Erro ao abrir arquivo.");
		exit(EXIT_FAILURE);
	}

	int nn, na, tipo, peso;

	file >> nn >> na >> tipo;
	this->tipo = tipo;

	for (int i = 0; i < nn; i++)
	{
		string v;
		file >> v;
		addVertice(v);
	}

	for (int i = 0; i < na; i++)
	{
		string vAux1, vAux2;
		file >> vAux1 >> vAux2;
		if (tipo & PONDERADO)
		{
			file >> peso;
			//puts("é ponderado");
		}
		else
			peso = 1;
		addAresta(vAux1, vAux2, peso);
	}

	file.close();
}

/*--------------------------------------*/
void Grafo::mostraComplMatAdj() {
	mostraMatAdj(true);
}

/*--------------------------------------*/
void Grafo::mostraMatAdj(bool complemento) {
	if (complemento)
		puts("Matriz de adjacência complementar:");
	else
		puts("Matriz de adjacência:");

	vector<vector<int> > adj(num_vertices, vector<int>(num_vertices, 0));
	uint v1_index, v2_index, maxNameSize = 0;
	for (uint i = 0; i < num_arestas; i++)
	{
		v1_index = getIndexV(arestas[i].v1);
		v2_index = getIndexV(arestas[i].v2);
		maxNameSize = MAX(MAX(vertices[v1_index].nome.size(), vertices[v2_index].nome.size()), maxNameSize);
		adj[v1_index][v2_index]++;
		if (!(tipo & DIRECIONADO) && v1_index != v2_index)
			adj[v2_index][v1_index]++;
	}

	cout << setw(maxNameSize) << "";
	for (uint i = 0; i < num_vertices; i++)
		cout << setw(vertices[i].nome.size() + 2) << vertices[i].nome;

	cout << endl;

	for (uint i = 0; i < num_vertices; i++)
	{
		cout << setw(maxNameSize) << vertices[i].nome;
		for (uint j = 0; j < num_vertices; j++)
			cout << setw(vertices[j].nome.size() + 2) << ((complemento) ? !adj[i][j]:adj[i][j]);

		cout << endl;
	}
}

/*--------------------------------------*/
void Grafo::mostraMatInc() {
	puts("Matriz de incidência:");
	int maxASize = 4;
	int conta;
	int colSize[num_vertices];

	cout << setw(maxASize) << "";
	for (uint i = 0; i < num_vertices; i++)
	{
		colSize[i] = vertices[i].nome.size() + 2;
		cout << setw(colSize[i]) << vertices[i].nome;
	}

	cout << endl;

	for (uint i = 0; i < num_arestas; i++)
	{
		cout << setw(maxASize) << arestas[i].nome;
		for (uint j = 0; j < num_vertices; j++)
		{
			conta = 0;
			if (arestas[i].v1 == vertices[j].id)
				if (arestas[i].v2 == vertices[j].id)
					conta = 2;
				else
					conta = (tipo & DIRECIONADO) ? -1 : 1;
			else if (arestas[i].v2 == vertices[j].id)
				conta = 1;

			if (conta) printf("%*d", colSize[j], conta); else printf("%*s", colSize[j], "-");
		}
		cout << "\n";
	}
}

/*--------------------------------------*/
void Grafo::mostraListaAdj() {
	for (uint i = 0; i < num_vertices; i++)
	{
		printf("%s:", vertices[i].nome.data());
		for (uint j = 0; j < vertices[i].arestas.size(); j++)
		{
			uint dest = percorreAresta(vertices[i].arestas[j], vertices[i].id, false);
			printf("--%u--", dest);
			printf("%s %s", (j && dest)?",":"",
					getNomeV(dest).data());
		}
		puts("");
	}
}

/*--------------------------------------*/
// Apresenta o grau de todos os nós do grafo de forma bonita.
void Grafo::mostraGrau() {
	for(uint i = 0; i < num_vertices; i++)
	{
		printf("d(%s) = %d\n", vertices[i].nome.data(), vertices[i].grau);
	}
}

/*--------------------------------------*/
void Grafo::mostraGrauTotal()
{
	uint total = 0, mini = 1<<31, maxi = 0;
	for (uint i = 0; i < num_vertices; i++)
	{
		mini = MIN(mini, vertices[i].grau);
		maxi = MAX(maxi, vertices[i].grau);
		total += vertices[i].grau;
	}

	printf("Grau mínimo = %d\nGrau máximo = %d\nGrau total  = %d\n", mini, maxi, total);
}

/*-----------------------------------*/
void Grafo::listaVertices(bool marcado, bool grau, bool cor)
{
	int maxColSize = (int) round(log10(num_vertices)) + 1;
	printf("Vértices = %u\n", num_vertices);
	for (uint i = 0; i < vertices.size(); i++)
	{
		printf("ID: %*u | Nome: %s", maxColSize, vertices[i].id, vertices[i].nome.data());
		if (grau)
			printf(" | Grau: %*d", maxColSize, vertices[i].grau);
		if (cor)
			printf(" | Cor: %*d", maxColSize, vertices[i].cor);
		if (marcado)
			printf(" | Marcado: %s", getMarcadoVertice(vertices[i].id) ? "Sim":"Não");
		printf("\n");
	}

	puts("");
}

/*-----------------------------------*/
void Grafo::listaArestas(bool marcado)
{
	int maxColSize = (int) round(log10(num_arestas)) + 1;
	printf("Arestas = %u\n", num_arestas);
	for (uint i = 0; i < num_arestas; i++)
	{
		printf("ID: %*u | Nome: %*s | Vértices: %s %s-> %s",
				maxColSize, arestas[i].id, maxColSize+1, arestas[i].nome.data(),
				getNomeV(arestas[i].v1).data(), (tipo & DIRECIONADO) ? "":"<", getNomeV(arestas[i].v2).data());
		if (marcado) printf(" | Marcado: %s", getMarcadoAresta(arestas[i].id) ? "Sim":"Não");
		if (tipo & PONDERADO) printf(" | Peso: %d", arestas[i].getPeso());
		printf("\n");
	}

	puts("");
}

/*--------------------------------------*/
void Grafo::atualizaNumVertices()
{
	num_vertices = vertices.size();
	set = (num_vertices > 0);
}

/*--------------------------------------*/
void Grafo::atualizaNumArestas()
{
	num_arestas = arestas.size();
}

/*--------------------------------------*/
void Grafo::addVertice()
{
	string nome;
	puts("Informe o nome do novo vértice. Não pode conter espaços.");
	cin >> nome;
	addVertice(nome);	// Chama função com parâmetro nome.
}

/*--------------------------------------*/
// Só esse faz a adição de verdade.
void Grafo::addVertice(string nome)
{
	if (getIndexV(nome) != -1)
	{
		puts("Já existe um vértice com esse nome, vértice não adicionado.");
		return;
	}

	GVertice nv(nome, ++v_id_c);	// Criar item GVertice para inclusão. Do 1 pra cima.
	vertices.push_back(nv);			// Incluir vértice na lista de vértices.

	atualizaNumVertices();
}

/*--------------------------------------*/
void Grafo::remVertice()
{
	// Lista todos os vértices e solicita qual deve ser removido.
	puts("Lista de vértices:");
	for (uint i = 0; i < num_vertices; i++)
		printf("ID: %2u | Nome: %s\n", vertices[i].id, vertices[i].nome.data());
	puts("\nDigite o ID do vértice que deseja remover ou digite '0' para cancelar.");
	uint v_id;
	scanf("%u", &v_id);
	if (v_id == 0)
		return;
	remVertice(v_id);					// Chama o método que faz a remoção.
}

/*--------------------------------------*/
void Grafo::remVertice(string v)
{
	int index = getIndexV(v);
	if (index == -1)
		return;

	remVertice(vertices[index].id);		// Chama o método que faz a remoção.
}

/*--------------------------------------*/
// Só esse faz a remoção de verdade.
void Grafo::remVertice(uint v_id)
{
	int index = getIndexV(v_id);
	int a_davez;
	if (index == -1)
	{
		puts("Não há vértice com esse identificador.");
		return;
	}

	for (int i = vertices[index].arestas.size() - 1; i >= 0; i--)
	{
		//printf("entrei na lista de arestas, i = %u, vert[].arestas.size() = %lu\n", i, vertices[index].arestas.size());
		a_davez = vertices[index].arestas[i];
		//cout << "vou remover a aresta ID " << a_davez << "\n";
		remAresta(a_davez);
	}
	//puts("sai da lista de arestas");

	vertices.erase(vertices.begin() + index);

	//puts("deletei do vetor");

	atualizaNumVertices();
}

/*--------------------------------------*/
void Grafo::addAresta()
{
	uint v1_id, v2_id;
	int peso = 0;
	// Lista todos os vértices e solicita qual deve ser removido.
	puts("Lista de vértices. (ID , Nome)");
	for (uint i = 0; i < num_vertices; i++)
		printf("ID: %2u | Nome: %s\n", vertices[i].id, vertices[i].nome.data());
	puts("\nDos vértices acima, digite o ID do vértice origem ou digite '0' para cancelar.");
	scanf("%u", &v1_id);
	if (v1_id == 0)
		return;
	puts("\nDigite o ID do destino ou digite '0' para cancelar.");
	scanf("%u", &v2_id);
	if (v2_id == 0)
		return;
	
	puts("\nDigite o peso da aresta ou 0 para ignorar.");
	cin >> peso;

	addAresta(v1_id, v2_id, peso);
}

/*--------------------------------------*/
// Usado somente na leitura de um arquivo.
void Grafo::addAresta(string v1, string v2, int peso)
{
	int v1_index, v2_index;
	if ((v1_index = getIndexV(v1)) == -1 || (v2_index = getIndexV(v2)) == -1)
	{
		puts("Um dos vértices não existe.");
		return;
	}

	addAresta(vertices[v1_index].id, vertices[v2_index].id, peso);
}

/*--------------------------------------*/
// Só esse faz a adição de verdade.
void Grafo::addAresta(uint v1_id, uint v2_id, int peso)
{
	//printf("Aresta nova:  %u - %u\n", v1_id, v2_id);
	int v1_index = getIndexV(v1_id), v2_index = getIndexV(v2_id);
	//printf("Indices nova: %d - %d\n", v1_index, v2_index);

	if (v1_index == -1 || v2_index == -1)
	{
		puts("Um dos vértices não existe.");
		return;
	}

	GAresta na(vertices[v1_index].id, vertices[v2_index].id, ++a_id_c);

	//printf("na.nome = %s\tna.id = %u\n", na.nome.data(), na.id);

	vertices[v1_index].arestas.push_back(na.id);
	if (v1_id != v2_id)
		vertices[v2_index].arestas.push_back(na.id);

	na.setPeso(peso);

	arestas.push_back(na);
	atualizaNumArestas();

	atualizaGrauV(v1_id);
	atualizaGrauV(v2_id);
}

/*--------------------------------------*/
void Grafo::remAresta()
{
	uint a_id = 0;
	puts("Lista de arestas:");
	for (uint i = 0; i < num_arestas; i++)
		printf("id: %3u | nome: %s | vértices: %s %s-> %s\n",
				arestas[i].id, arestas[i].nome.data(), getNomeV(arestas[i].v1).data(),
				(tipo) ? "":"<", getNomeV(arestas[i].v2).data());

	puts("");
	puts("Digite o ID da aresta a remover ou digite '0' para cancelar.");
	scanf("%u", &a_id);
	if (getIndexA(a_id) == -1)
		return;
	remAresta(a_id);
}

/*--------------------------------------*/
// Só esse faz a remoção de verdade.
void Grafo::remAresta(uint a_id)
{
	//printf("remAresta(%u)\n", a_id);
	int a_index = getIndexA(a_id);
	int v1_id = arestas[a_index].v1;
	int v2_id = arestas[a_index].v2;
	//printf("v1_id = %u, v2_id = %u\n", v1_id, v2_id);
	int v1_index = getIndexV(v1_id);
	int v2_index = getIndexV(v2_id);
	//printf("v1_index = %u, v2_index = %u\n", v1_index, v2_index);

	// Atualizar a lista de arestas em cada vértice da aresta.
	//printf("v1.arestas.size() = %lu\n", vertices[v1_index].arestas.size());
	for (int i = vertices[v1_index].arestas.size() - 1; i >= 0; i--)
		if (vertices[v1_index].arestas[i] == a_id)
		{
			//puts("achei o v1 da aresta");
			vertices[v1_index].arestas.erase(vertices[v1_index].arestas.begin() + i);
			//puts("deleti a referencia v1");
			break;
		}

	//printf("v1.arestas.size() = %lu\n", vertices[v1_index].arestas.size());

	//printf("v2.arestas.size() = %lu\n", vertices[v2_index].arestas.size());
	for (int i = vertices[v2_index].arestas.size() - 1; i >= 0; i--)
		if (vertices[v2_index].arestas[i] == a_id)
		{
			//puts("achei o v2 da aresta");
			vertices[v2_index].arestas.erase(vertices[v2_index].arestas.begin() + i);
			//puts("deleti a referencia v2");
			break;
		}
	//printf("v2.arestas.size() = %lu\n", vertices[v2_index].arestas.size());

	// Atualiza o grau dos vértices.
	atualizaGrauV(v1_id);
	atualizaGrauV(v2_id);

	//printf("REMOVENDO ARESTA ID %u\n", a_id);
	//printf("arestas.size() = %lu\n", arestas.size());
	// Remove da lista de arestas.
	arestas.erase(arestas.begin() + a_index);
	//printf("arestas.size() = %lu\n", arestas.size());

	//puts("atualizaNumArestas()");
	//printf("num_arestas = %u\n", num_arestas);
	atualizaNumArestas();
	//printf("num_arestas = %u\n", num_arestas);
	//puts("SAINDO DO remAresta");
}

/*--------------------------------------*/
string Grafo::getNomeV(uint v_id)
{
	int index = getIndexV(v_id);
	return vertices[index].nome;
}

/*--------------------------------------*/
string Grafo::getNomeA(uint a_id)
{
	int index = getIndexA(a_id);
	return arestas[index].nome;
}

/*--------------------------------------*/
int Grafo::getIndexV(string v)
{
	for (uint i = 0; i < num_vertices; i++)
	{
		if (vertices[i].nome == v)
			return i;
	}
	//puts("Não há um vértice com esse nome.");
	return -1; // Não encontrado.
}

/*--------------------------------------*/
int Grafo::getIndexV(uint v_id)
{
	//printf("v_id = %u\tnum_vertices = %d\n", v_id, num_vertices);
	for (uint i = 0; i < num_vertices; i++)
	{
		//printf("%d %u&&%u\\ ", i, vertices[i].id, v_id);
		if (vertices[i].id == v_id)
		{
			//puts("achei");
			return i;
		}
	}

	//puts("Não há um vértice com esse identificador.");
	return -1;
}

/*--------------------------------------*/
int Grafo::getIndexA(string a)
{
	for (uint i = 0; i < num_arestas; i++)
	{
		if (arestas[i].nome == a)
			return i;
	}
	//puts("Não há uma aresta com esse nome.");
	return -1; // Não encontrado.
}

/*--------------------------------------*/
int Grafo::getIndexA(uint a_id)
{
	//printf("getIndexA(%u)\n", a_id);
	for (uint i = 0; i < num_arestas; i++)
	{
		//printf("arestas[%u].id = %u\n", i, arestas[i].id);
		if (arestas[i].id == a_id)
		{
			//puts("achei");
			return i;
		}
	}

	//puts("Não há uma aresta com esse identificador.");
	return -1;
}

/*--------------------------------------*/
void Grafo::atualizaGrauV(uint v_id)
{
	//printf("atualizaGrauV(%u)\n", v_id);
	int v_index = getIndexV(v_id), a_index = -1;
	uint cont = vertices[v_index].arestas.size();
	//listaArestasDeVertice(v_id);
	for (uint i = 0; i < vertices[v_index].arestas.size(); i++)
	{
		a_index = getIndexA(vertices[v_index].arestas[i]);
		if (v_id == arestas[a_index].v1 &&					// Se for um loop então soma 2 ao
				arestas[a_index].v1 == arestas[a_index].v2)	// invés de 1 no grau do vértice.
			cont++;
	}

	vertices[v_index].grau = cont;
	//printf("grau(%u)=%u\tSaindo.\n", v_id, cont);
}

/*--------------------------------------*/
uint Grafo::percorreAresta(uint a_id, uint v_id, bool reverso)
{
	int a_index = getIndexA(a_id);
	if (arestas[a_index].v1 == v_id)
		// Se a origem for o vértice atual, percorre.
		return arestas[a_index].v2;
	else if (arestas[a_index].v2 == v_id && (reverso || !(tipo & DIRECIONADO)))
		// Se o destino for o vértice atual e o grafo for não-direcionado, percorre.
		return arestas[a_index].v1;
	else
	{
		//puts("Não é possível percorrer essa aresta.");
		return 0;
	}
}

/*--------------------------------------*/
void Grafo::DFS(uint v_davez) {
	marcaVertice(v_davez);
	int v_index = getIndexV(v_davez);
	uint a_davez;
	uint v_proximo;
	for (uint i = 0; i < vertices[v_index].arestas.size(); i++) {
		a_davez = vertices[v_index].arestas[i];
		v_proximo = percorreAresta(a_davez, v_davez, false);
		if (v_proximo == 0 || getMarcadoVertice(v_proximo) == true)
			continue;
		DFS(v_proximo);
	}
}

/*--------------------------------------*/
bool Grafo::verificaConexo(bool print) {
	puts("Grafo é conexo?");
	bool conexo = true;

	if (num_vertices != 0)
	{
		DFS(vertices[0].id);
		for (uint i = 0; i < num_vertices; i++)
		{
			if (getMarcadoVertice(vertices[i].id) == 0)
			{
				conexo = false;
				break;
			}
		}
	}

	if (print) cout << ((conexo)? "SIM. O grafo é conexo":"NÃO. O grafo é desconexo") << endl;

	for (uint i = 0; i < num_vertices; i++)
		desmarcaVertice(vertices[i].id);
	
	return conexo;
}

/*--------------------------------------*/
bool Grafo::getMarcadoVertice(uint v_id)
{
	int index = getIndexV(v_id);
	return vertices[index].marcado;
}

/*--------------------------------------*/
void Grafo::marcaVertice(uint v_id)
{
	int index = getIndexV(v_id);
	if (vertices[index].marcado == false)
		vertices[index].marcado = true;
}

/*--------------------------------------*/
void Grafo::desmarcaVertice(uint v_id)
{
	int index = getIndexV(v_id);
	if (vertices[index].marcado == true)
		vertices[index].marcado = false;
}

/*--------------------------------------*/
void Grafo::desmarcaTodosVertices()
{
	for (uint i = 0; i < num_vertices; i++)
	{
		desmarcaVertice(vertices[i].id);
	}
}

/*--------------------------------------*/
bool Grafo::getMarcadoAresta(uint a_id)
{
	int index = getIndexA(a_id);
	return arestas[index].marcado;
}

/*--------------------------------------*/
void Grafo::marcaAresta(uint a_id)
{
	int index = getIndexA(a_id);
	if (arestas[index].marcado == false)
		arestas[index].marcado = true;
}

/*--------------------------------------*/
void Grafo::desmarcaAresta(uint a_id)
{
	int index = getIndexA(a_id);
	if (arestas[index].marcado == true)
		arestas[index].marcado = false;
}

/*--------------------------------------*/
void Grafo::desmarcaTodasArestas()
{
	for (uint i = 0; i < num_arestas; i++)
	{
		desmarcaAresta(arestas[i].id);
	}
}

/*--------------------------------------*/
void Grafo::rodaFleury()
{
	if (num_vertices < 1)					// Essa condição é para impedir que grafos
	{										// sem vértices causem erros de segmentação
		puts("Grafo não é Euleriano.");		// ao tentar acessar vertices[0].
	}
	else if (fleury(0, vertices[0].id) == 1)
		puts("\nGrafo é Euleriano.");			// Se é euleriano, informe ao usuário.
	else
		puts("Grafo não é Euleriano.");			// Se não, informe também.

	// Reiniciar estado de marcações.
	for (uint i = 0; i < num_arestas; i++)
		desmarcaAresta(arestas[i].id);
}

/*--------------------------------------*/
bool Grafo::fleury(uint v_id_davez, uint v_id_inicial)
{
	uint v_id_prox = 0, v_index_davez, a_davez = 0;
	if (v_id_davez == v_id_inicial)
	{
		// Encontrado um ciclo partindo do vértice inicial.
		int ruim = false;

		// Verificar se todas as arestas foram visitadas.
		for (uint i = 0; i < num_arestas; i++)
		{
			if (!arestas[i].marcado)
			{
				ruim = true;
				break;
			}
		}

		if (!ruim)
		{
			puts("Ciclo:");
			printf("%s", vertices[getIndexV(v_id_davez)].nome.data());
			return true; // Todas as arestas foram percorridas, é ciclo Euleriano.
		}

		// Nem todas as arestas foram percorridas, continue.
		// pois pode haver uma aresta laço no nó atual, e
		// ainda será Euleriano.
	}
	else if (v_id_davez == 0)
	{
		v_id_davez = v_id_inicial;
	}

	v_index_davez = getIndexV(v_id_davez);

	for (uint i = 0; i < vertices[v_index_davez].arestas.size(); i++)
	{
		a_davez = vertices[v_index_davez].arestas[i];
		if (getMarcadoAresta(a_davez) == true)
			continue;
		else
		{
			marcaAresta(a_davez);
			v_id_prox = percorreAresta(a_davez, v_id_davez, false);
			if (v_id_prox == 0)
			{
				desmarcaAresta(a_davez);
				continue;
			}
			if (fleury(v_id_prox, v_id_inicial) == true) // Deu certo, imprima o caminho.
			{
				printf("-%s-%s", arestas[getIndexA(a_davez)].nome.data(),
								 vertices[getIndexV(v_id_davez)].nome.data());
				return true;
			}
			desmarcaAresta(a_davez);
		}
	}

	return false;
}

/*--------------------------------------*/
int Grafo::colorir(bool imprime)
{
	puts("Coloração:");
	uint a_davez;
	int v_vizinho, maxCor = 0;

	vector<bool> vcores(num_vertices + 1); // Cores dos vizinhos.

	// Reiniciar coloraçao do grafo
	for (uint i = 0; i < num_vertices; i++)
		vertices[i].cor = 0; // Não colorido

	for (uint i = 0; i < num_vertices; i++)
	{
		// Reinicia o vetor de cores de vizinhos.
		for (uint j = 0; j < num_vertices; j++) vcores[j] = false;

		// Encontra as cores dos vizinhos e marca elas.
		for (uint j = 0; j < vertices[i].arestas.size(); j++)
		{
			a_davez = vertices[i].arestas[j];
			v_vizinho = getIndexV(percorreAresta(a_davez, vertices[i].id, false));
			vcores[vertices[v_vizinho].cor] = true;
		}

		// Pinta com a primeira cor disponível.
		for (uint j = 1; j <= num_vertices; j++)
			if (vcores[j] == false) { vertices[i].cor = j; maxCor = MAX(maxCor, (int) j); break; }
	}

	if (imprime) this->listaVertices(false, false, true);

	if (imprime) cout << "Número cromático: " << maxCor << "\n";

	return maxCor;
}

/*--------------------------------------*/
void Grafo::listaArestasDeVertice(uint v_id)
{
	for (uint i = 0; i < vertices[getIndexV(v_id)].arestas.size(); i++)
	{
		printf(" | %u", vertices[getIndexV(v_id)].arestas[i]);
	}
	puts("");
}


/*================BEGIN ================*/
/*=== GRANDE BLOCÃO DE CÓDIGO DA DFS ===*/
/*======================================*/
void Grafo::runDFS() {
	// Inicialização
	vector<vector<uint> > listaAdj(num_vertices);
	vector<vector<uint> > arvDfs(num_vertices);
	vector<vector<uint> > rArvDfs(num_vertices);
	vector<uint> vetTopologico;
	vector<bool> visitado(num_vertices, false);
	// Fim

	// Criação da listaAdj (auxiliar)
	for(uint i = 0; i < num_arestas; i++) {
		uint v1_id = arestas[i].v1, v2_id = arestas[i].v2;
		int v1_index = getIndexV(v1_id), v2_index = getIndexV(v2_id);
		listaAdj[v1_index].push_back(v2_index);
		if(!(tipo & DIRECIONADO))
			listaAdj[v2_index].push_back(v1_index);
	}
	// Fim

	// Calculando o vetor topológico do grafo dado
	for(uint i = 0; i < num_vertices; i++) {
		if(!visitado[i]) {
			visitado[i] = true;
			DFS_getTopologico(i, listaAdj, visitado, vetTopologico);
		}
	}
	// Fim

	// Inicializando a arvore e o vetor de visitados
	visitado = vector<bool>(num_vertices, false);
	// Fim

	// Rodando DFS no ultimo elemento do vetor topológico
	DFS_DFS0(vetTopologico.back(), -1, arvDfs, rArvDfs, visitado, listaAdj);
	// Fim

	// Printando Árvore da DFS
	cout << "Árvore gerada pela DFS: " << endl;
	DFS_printArvoreDFS(arvDfs);
	// Fim

	// Fazendo análise dos nós
	cout << "----------------------------------" << endl;
	for(uint i = 0; i < num_vertices; i++) {
		DFS_getInfoNo(i, visitado, listaAdj, arvDfs, rArvDfs);
	}
	// Fim
}

// DFS para encontrar a árvore da DFS
void Grafo::DFS_DFS0(uint atual, uint anterior, vector<vector<uint> > &arvDfs, vector<vector<uint> > &rArvDfs, vector<bool> &visitado, vector<vector<uint> > &listaAdj) {
    if(anterior != (uint) -1) {
        arvDfs[anterior].push_back(atual);
        rArvDfs[atual].push_back(anterior);
	}
	else
	{
		visitado[atual] = true;
	}

    for(uint i = 0; i < listaAdj[atual].size(); i++) {
        uint u = listaAdj[atual][i];
        if(!visitado[u]) {
            visitado[u] = true;
            DFS_DFS0(u, atual, arvDfs, rArvDfs, visitado, listaAdj);
        }
    }
}
// Fim

// DFS para encontrar os ancestrais e descendentes de um determinado nó
void Grafo::DFS_DFS1(uint atual, vector<uint> &parentes,  vector<vector<uint> > &lista, vector<bool> &visitado) {

    for(uint i = 0; i < lista[atual].size(); i++) {
        uint u = lista[atual][i];
        if(!visitado[u]) {
            visitado[u] = true;
			parentes.push_back(u);
            DFS_DFS1(u, parentes, lista, visitado);
        }
    }
}
// Fim

// DFS para encontrar o vetor topológico
void Grafo::DFS_getTopologico(uint atual, vector<vector<uint> > &listaAdj, vector<bool> &visitado, vector<uint> &vetTopologico) {
    for(uint i = 0; i < listaAdj[atual].size(); i++) {
        uint u = listaAdj[atual][i];
        if(!visitado[u]) {
            visitado[u] = true;
            DFS_getTopologico(u, listaAdj, visitado, vetTopologico);
        }
    }

    vetTopologico.push_back(atual);
}
// Fim

void Grafo::DFS_getInfoNo(uint v, vector<bool> &visitado, vector<vector<uint> > &listaAdj, vector<vector<uint> > &arvDfs, vector<vector<uint> > &rArvDfs) {
    cout << "Analise do vertice " << vertices[v].nome << endl;
    cout << "Filhos: ";
    visitado = vector<bool> (num_vertices, false);

    for(uint i = 0; i < arvDfs[v].size(); i++) {
        uint u = arvDfs[v][i];
        cout << vertices[u].nome << " ";
        visitado[u] = true;
    }
    cout << endl;

    vector<uint> ancestrais;
    cout << "Ancestrais: ";
    visitado = vector<bool> (num_vertices, false);
    DFS_DFS1(v, ancestrais, rArvDfs, visitado);
    for(uint i = 0; i < ancestrais.size(); i++) {
        cout << vertices[ancestrais[i]].nome << " ";
    }
    cout << endl;

    vector<uint> descendentes;
    cout << "Descendentes: ";
    visitado = vector<bool> (num_vertices, false);
    DFS_DFS1(v, descendentes, arvDfs, visitado);
    for(uint i = 0; i < descendentes.size(); i++) {
        cout << vertices[descendentes[i]].nome << " ";
    }
    cout << endl;
    cout << "----------------------------------" << endl;

}

void Grafo::DFS_printArvoreDFS(vector<vector<uint> > &arvDfs) {
    for(uint i = 0; i < arvDfs.size(); i++) {
        cout << vertices[i].nome << ": ";
        for(uint j = 0; j < arvDfs[i].size(); j++) {
            cout << vertices[arvDfs[i][j]].nome << " ";
        }
        cout << endl;
    }
}
/*=================END =================*/
/*=== GRANDE BLOCÃO DE CÓDIGO DA DFS ===*/
/*======================================*/


/*================BEGIN ================*/
/*============== DIJKSTRA ==============*/
/*======================================*/
void Grafo::runDijkstra()
{
	if (num_vertices == 0)
	{
		puts("Não há vértices.");
		return;
	}
	for (uint i = 0; i < num_arestas; i++)
	{
		if (arestas[i].getPeso() < 0)
		{
			puts("Grafo possui arestas com peso negativo.");
			return;
		}
	}

	listaVertices(false, false, false);
	puts("Qual o vértice de partida? Digite o código dele.");
	uint v_id;
	int v_index;
	cin >> v_id;
	if ((v_index = getIndexV(v_id)) == -1)
	{
		puts("Não existe este vértice.");
		return;
	}

	vector<uint> dist(num_vertices, (uint) -1);
	vector<int> prev(num_vertices, -1);
	dist[v_index] = 0;

	Dijkstra(dist, prev, v_index);

	printf("Vértice origem: %s\n", vertices[v_index].nome.data());
	for (uint i = 0; i < num_vertices; i++)
	{
		printf("Destino: %s", vertices[i].nome.data());
		if (dist[i] != (INFINITO))
			printf(" | Distância: %d | Anterior: %s\n", dist[i], (prev[i] != -1) ? vertices[prev[i]].nome.data():"-");
		else
			printf(" | Inalcançável\n");
	}
}

/*--------------------------------------*/
void Grafo::Dijkstra(vector<uint> &dist, vector<int> &previous, int v_first)
{
	// first = distancia, second = index;
	priority_queue<pair<uint,int>, vector<pair<uint, int> >, greater<pair<uint, int> > > fila;
	fila.push(make_pair(0, v_first));
	pair<uint, int> v_davez_pair;
	uint v_index_davez, v_index_prox, a_davez_dist;
	while (!fila.empty())
	{
		v_davez_pair = fila.top(); fila.pop();
		v_index_davez = v_davez_pair.second;
		for (uint i = 0; i < vertices[v_index_davez].arestas.size(); i++)
		{
			v_index_prox = getIndexV(percorreAresta(vertices[v_index_davez].arestas[i],
													vertices[v_index_davez].id, false));
			if (v_index_prox == (uint) -1) continue; // Caso o grafo seja dirigido
			a_davez_dist = arestas[getIndexA(vertices[v_index_davez].arestas[i])].getPeso();
			if (dist[v_index_prox] > dist[v_index_davez] + a_davez_dist)
			{
				dist[v_index_prox] = dist[v_index_davez] + a_davez_dist;
				fila.push(make_pair(dist[v_index_prox], v_index_prox));
				previous[v_index_prox] = v_index_davez;
			}
		}
	}
}
/*=================END =================*/
/*============== DIJKSTRA ==============*/
/*======================================*/


// CORRIGIR ESSA BOSTA AÍ

/*================BEGIN ================*/
/*============ BELLMAN-FORD ============*/
/*======================================*/
void Grafo::runBellmanFord()
{
	if (num_vertices == 0)
	{
		puts("Não há vértices.");
		return;
	}

	if (!(tipo & DIRECIONADO))
	{
		for (uint i = 0; i < num_arestas; i++)
		{
			if (arestas[i].getPeso() < 0)
			{
				puts("Bellman-Ford não funciona em grafos não direcionados com arestas de peso negativo.");
				return;
			}
		}
	}

	listaVertices(false, false, false);
	puts("Qual o vértice de partida? Digite o código dele.");
	uint v_id;
	int v_index;
	cin >> v_id;
	if ((v_index = getIndexV(v_id)) == -1)
	{
		puts("Não existe este vértice.");
		return;
	}
	vector<int> dist(num_vertices, INFINITO), prev(num_vertices, -1);
	dist[v_index] = 0;

	if (BellmanFord(dist, prev, v_index))
	{
		puts("Há ciclos negativos, não é possível determinar por Bellman-Ford.");
		return;
	}

	printf("Vértice origem: %s\n", vertices[v_index].nome.data());
	for (uint i = 0; i < num_vertices; i++)
	{
		printf("Destino: %s", vertices[i].nome.data());
		if (dist[i] != (INFINITO))
			printf(" | Distância: %d | Anterior: %s\n", dist[i], (prev[i] != -1) ? vertices[prev[i]].nome.data():"-");
		else
			printf(" | Inalcançável\n");
	}
}

/*--------------------------------------*/
int Grafo::BellmanFord(vector<int> &dist, vector<int> &previous, int v_first)
{
	int v_index_prox, a_davez_dist, a_id_davez;
	vector<int> prev(num_vertices, INFINITO);
	
	for (uint i = 0; i < num_vertices; i++)
	{
		for (uint j = 0; j < num_vertices; j++)
		{
			for (uint k = 0; k < vertices[j].arestas.size(); k++)
			{
				if (dist[j] == INFINITO) continue;
				a_id_davez = vertices[j].arestas[k];
				v_index_prox = getIndexV(percorreAresta(a_id_davez, vertices[j].id, false));
				if (v_index_prox == -1) continue; // Caso seja direcionado.
				a_davez_dist = arestas[getIndexA(a_id_davez)].getPeso();
				if (dist[v_index_prox] > dist[j] + a_davez_dist)
				{
					dist[v_index_prox] = dist[j] + a_davez_dist;
					previous[v_index_prox] = j;
				}
			}
		}
		if (i == num_vertices - 2)
			for (uint j = 0; j < num_vertices; j++)
				prev[j] = dist[j];
		
		if (i == num_vertices - 1)
			for (uint j = 0; j < num_vertices; j++)
				if (prev[j] != dist[j])
					return 1;
	}
	return 0;
}
/*=================END =================*/
/*============ BELLMAN-FORD ============*/
/*======================================*/


// CORRIGIR ESSA BOSTA AÍ

/*================BEGIN ================*/
/*=========== FLOYD-WARSHALL ===========*/
/*======================================*/
void Grafo::runFloydWarshall()
{
	if (num_vertices == 0)
	{
		puts("Não há vértices.");
		return;
	}

	if (!(tipo & DIRECIONADO))
	{
		for (uint i = 0; i < num_arestas; i++)
		{
			if (arestas[i].getPeso() < 0)
			{
				puts("Floyd-Warshall não funciona em grafos não direcionados com arestas de peso negativo.");
				return;
			}
		}
	}

	vector<vector<int> > dist(num_vertices, vector<int>(num_vertices, INFINITO));
	for(uint i = 0; i < num_arestas; i++) {
		uint v1_id = arestas[i].v1, v2_id = arestas[i].v2;
		int v1_index = getIndexV(v1_id), v2_index = getIndexV(v2_id);
		dist[v1_index][v2_index] = arestas[i].getPeso();
		if(!(tipo & DIRECIONADO))
			dist[v2_index][v1_index] = arestas[i].getPeso();
	}

	uint maxNameSize, maxNumSize;

	for (uint i = 0; i < num_vertices; i++)
	{
		dist[i][i] = 0;
		maxNameSize = MAX(maxNameSize, vertices[i].nome.size());
	}

	FloydWarshall(dist);
	
	for (uint i = 0; i < num_vertices; i++)
	{
		if (dist[i][i] != 0)
		{
			puts("Há ciclos negativos, não é possível executar Floyd-Warshall.");
			return;
		}
		for (uint j = 0; j < num_vertices; j++) 
		{
			if (dist[i][j] != INFINITO)
				maxNumSize = MAX(maxNumSize, (uint) round(log10(abs(dist[i][j]))) + 1);
		}
	}

	puts("\nDistâncias Mínimas: (Floyd-Warshall)");

	cout << setw(maxNameSize) << "";
	for (uint i = 0; i < num_vertices; i++)
		cout << setw(MAX(vertices[i].nome.size(), maxNumSize) + 2) << vertices[i].nome;

	cout << endl;

	for (uint i = 0; i < num_vertices; i++)
	{
		cout << setw(maxNameSize) << vertices[i].nome;
		for (uint j = 0; j < num_vertices; j++)
			if (dist[i][j] == INFINITO)
				cout << setw(MAX(vertices[j].nome.size(), maxNumSize) + 2) << " ";
			else
				cout << setw(MAX(vertices[j].nome.size(), maxNumSize) + 2) << dist[i][j];

		cout << endl;
	}
}

/*--------------------------------------*/
void Grafo::FloydWarshall(vector<vector<int> > &dist)
{
	for (uint k = 0; k < num_vertices; k++)
	{
		for (uint i = 0; i < num_vertices; i++)
		{
			for (uint j = 0; j < num_vertices; j++)
			{
				if (dist[i][k] == INFINITO || dist[k][j] == INFINITO) continue;
				dist[i][j] = MIN(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}
}
/*=================END =================*/
/*=========== FLOYD-WARSHALL ===========*/
/*======================================*/
/* LINHA 1300 UHUUUUUUUUUUUUUUUUUUUUUUU */

/*================BEGIN ================*/
/*================ PRIM ================*/
/*======================================*/
void Grafo::runPrim()
{
	if (num_vertices < 1)
	{
		puts("Não há vértices.");
		return;
	}

	if (tipo & DIRECIONADO)
	{
		puts("Prim não funciona em grafos direcionados.");
		return;
	}

	vector<vector<pair<int, int> > > listaAdj (num_vertices);

	// Criação da listaAdj (auxiliar)
	for(uint i = 0; i < num_arestas; i++) {
		uint v1_id = arestas[i].v1, v2_id = arestas[i].v2;
		int v1_index = getIndexV(v1_id), v2_index = getIndexV(v2_id);
		listaAdj[v1_index].push_back({v2_index, arestas[i].getPeso()});
		if(!(tipo & DIRECIONADO))
			listaAdj[v2_index].push_back({v1_index, arestas[i].getPeso()});
	}
	// Fim

	vector<vector<pair<int, int> > > arvPrim (num_vertices);
	vector<bool> visitados (num_vertices, false);

	uint daVez = 0; // Tem que começar de algum lugar, né?

	cout << "Caminho percorrido por PRIM, começando por: " << vertices[daVez].nome << endl;
    visitados[daVez] = true;
    pair<int, int> vertice = { -1, -1 }; //vertice, peso
    int vPai = -1;

    do {
        vertice = { -1, -1 }; //vertice, peso
        vPai = -1;
        for (uint i = 0; i < listaAdj.size(); i++) {
            if (visitados[i]) {
                for (uint j = 0; j < listaAdj[i].size(); j++) {
                    int vAtual = listaAdj[i][j].first;
                    if ((listaAdj[i][j].second < vertice.second || vertice.second == -1) && !visitados[vAtual]) {
                        vertice = listaAdj[i][j];
                        vPai = i;
                    }
                }
            }
        }

        if(vPai != -1) {
            visitados[vertice.first] = true;
            cout << vertices[vPai].nome << " -> " << vertices[vertice.first].nome << " - " << vertice.second << endl;
            arvPrim[vPai].push_back(vertice);
        } else 
            cout << "Fim das iterações do Prim." << endl << endl; 
    }while(vertice != make_pair(-1, -1));

	cout << "Árvore geradora mínima" << endl;
    for(uint i = 0; i < arvPrim.size(); i++) {
		if (arvPrim[i].size() < 1) continue;
        cout << vertices[i].nome << " -> ";
        for(uint j = 0; j < arvPrim[i].size(); j++) {
            cout << "(" << vertices[arvPrim[i][j].first].nome << ", " << arvPrim[i][j].second << ")";
            if(j != arvPrim[i].size()-1) 
                cout << ", ";
        }
        cout << endl;
    }
}
/*=================END =================*/
/*================ PRIM ================*/
/*======================================*/

/*================BEGIN ================*/
/*=========== Ford-Fulkerson ===========*/
/*======================================*/
class ArestaParaFF {
public:
	uint v_destino;
	int capacidade;
	int fluxo = 0;
	uint v_source;
	uint v_sink;
};

void Grafo::runFordFulkerson()
{
	if (num_vertices < 1)
	{
		puts("Não há vértices.");
		return;
	}

	if (!(tipo & DIRECIONADO))
	{
		puts("Ford-Fulkerson não funciona em grafos não-direcionados.");
		return;
	}

	vector<vector<ArestaParaFF> > grafo(num_vertices, vector<ArestaParaFF> (0));
	vector<int> caminho;
	ArestaParaFF aresta_aux;
	uint a_id, a_index;

	int origem, destino;
	
	puts("Ford-Fulkerson");
	listaVertices(false, false, false);
	puts("Digite o ID do vértice de origem.");
	cin >> origem;
	if ((origem = getIndexV(origem)) != -1)
	{
		puts("Vértice não existe.");
		return;
	}
	puts("Digite o ID do vértice de destino.");
	cin >> destino;

	for (uint i = 0; i < num_vertices; i++)
	{
		for (uint j = 0; j < vertices[i].arestas.size(); j++)
		{
			a_id = vertices[i].arestas[j];
			a_index = getIndexA(a_id);
			aresta_aux.v_destino  = getIndexV(percorreAresta(a_id, vertices[i].id, false));
			aresta_aux.capacidade = arestas[a_index].peso;
			aresta_aux.fluxo      = 0;
			aresta_aux.v_source   = getIndexV(origem);
			aresta_aux.v_sink     = getIndexV(destino);
			grafo[i].push_back(aresta_aux);
		}
	}

	int fluxo, fluxoTotal = 0;
	while ((fluxo = proxFluxo(origem, destino, caminho)) != 0) fluxoTotal += fluxo;
}

int Grafo::proxFluxo(int v_origem, int v_destino, vector<int> &caminho)
{
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > fila;
	fila.push(make_pair(v_origem, 0));
	pair<int, int> daVez; // first = vértice, second = fluxo;
	int v_id, v_index, v_next_index, a_id, a_index, fluxo;
	while (!fila.empty())
	{
		daVez   = fila.top(); fila.pop;
		v_index = daVez.first;
		fluxo   = daVez.second;
		marcaVertice(vertices[daVez.first].id);
		for (int i = 0; i < vertices[daVez.first].arestas.size(); i++)
		{
			a_id = vertices[]
		}
	}
}

/*=================END =================*/
/*=========== Ford-Fulkerson ===========*/
/*======================================*/