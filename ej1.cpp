#include <iostream>
#include <vector>
#include <utility>

using namespace std;
bool run = true;
typedef int vertice;
typedef pair<int, int> arista;

struct grafo {
	vector<vector<vertice>> adyacentes;

	// Inicializar grafo vacío
	grafo(int vertices) {
		if (vertices > 0)
			adyacentes = vector<vector<vertice>>(vertices, vector<vertice>());
	}

	// Agregar vertice sin aristas
	void agregar(int v) {
		while (adyacentes.size() <= v)
			adyacentes.push_back(vector<vertice>());
	}

	// Agregar arista y sus vertices si no están
	void agregar(arista a) {
		agregar(a.first);
		agregar(a.second);
		adyacentes[a.first].push_back(a.second);
		adyacentes[a.second].push_back(a.first);
	}
};

void dfs(grafo &graph, vertice v, vector<int> &padres, vector<int> &tiempos,
		 int tiempo, vector<int> &componentes, int raiz) {
	tiempos[v] = tiempo++; // Marcar el momento en el que v fue descubierto
	componentes[v] = raiz; // Marcar que v fue alcanzable desde raiz

	for (vertice w : graph.adyacentes[v]) {
		if (padres[w] == -1) {
			padres[w] = v;
			dfs(graph, w, padres, tiempos, tiempo, componentes, raiz);
		}
	}
}

int obenerpuentes(grafo &graph, vertice v, vector<int> &padres,
				  vector<int> &tiempos, vector<int> &puentes) {
	int cantidad = 0;

	for (vertice w : graph.adyacentes[v]) {
		if (padres[w] == v) {
			cantidad += obenerpuentes(graph, w, padres, tiempos, puentes);
		} else {
			// Si w tenía otro padre y fue descubierto después que v, es backedge
			// que sube
			if (tiempos[v] > tiempos[w] and padres[v] != w)
				cantidad++;

			// Si w tenía otro padre y fue descubierto antes que v, es backedge
			// que viene de abajo
			if (tiempos[v] < tiempos[w])
				cantidad--;
		}
	}

	// Si ninǵun descendiente de v era un backedge que alcanzara a cubrir a v,
	// v forma un puente con su padre
	if (cantidad == 0 and padres[v] != v)
		puentes[v] = padres[v];

	return cantidad;
}

int main() {
	while (run) {
		int n,m;
		cin >> n;
		cin >> m;	
		// Cortar si no hay más input
		// if (habitaciones == 0 and pasillos == 0 and consultas == 0)
		// 	break;
		
		// Armar grafo del laberinto en O(?)
		grafo graph(n);
		for (int i = 0; i < m; ++i) {
			int v, w;
			cin >> v;
			cin >> w;
			graph.agregar(arista(--v, --w));
		}
		
		// Inicializar estructuras en O(4n)
 		vector<vertice> padres(n, -1);
		vector<vertice> tiempos(n, 0);
		vector<vertice> puentes(n, -1);
 		vector<vertice> componentes(n, -1);

		// Obtener puentes de cada componente conexa en O(2(n + m))
		for (int i = 0; i < n; ++i) {
			if (padres[i] == -1) {
				padres[i] = i;
				dfs(graph, i, padres, tiempos, 0, componentes, i);
				obenerpuentes(graph, i, padres, tiempos, puentes);
			}
		}

		// Construir un grafo nuevo a partir de puentes únicamente en O(n)
		grafo solo_puentes(n);
		for (int i = 0; i < n; ++i) {
			if (puentes[i] != -1)
				solo_puentes.agregar(arista(padres[i], i));
		}
		
		// Descubir en que componente vive cada vertice y marcarlo en O(n + m)
		padres = vector<vertice>(n, -1); // Limpiar padres
		for (int i = 0; i < n; ++i) {
			if (padres[i] == -1)
				dfs(solo_puentes, i, padres, tiempos, 0, componentes, i);
		}
		// if componente [i] == componente [j] entonces i y j estan en la misma componente
	run = false;
	}
	return 0;
}