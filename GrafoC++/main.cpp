#include "grafo.hpp"

using namespace std;

int main(int argc, char **argv)
{
	//system("clear");
	puts("Bem vindo ao utilitário de grafos de Leo e Lucas!");
	int res = 0;

	Grafo g;

	if (argc > 1)
	{
		string cam = argv[1];
		cout << cam;
		g.leGrafo(cam);
	}

	// Loop do menu
	do { res = menu(&g); } while (res != 0);
	
	return 0;
}
