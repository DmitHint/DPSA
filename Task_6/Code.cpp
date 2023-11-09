#include <iostream>
#include <vector>
#include <queue>

using namespace std;


const int V = 6; // число вершин
// матрица смежности графа
int G[V][V] = {
	{0, 2, 6, 4, 0, 0},
	{2, 0, 0, 7, 8, 0},
	{6, 0, 0, 8, 0, 5},
	{4, 7, 8, 0, 2, 8},
	{0, 8, 0, 2, 0, 4},
	{0, 0, 5, 8, 4, 0},
};

int main() {
	int no_edge = 0; // количество ребер
	int selected[V]; // массив обработанных вершин
	// изначально все необработаны
	memset(selected, false, sizeof(selected));
	selected[0] = true;
	int x, y;
	cout << "Edge" << " : " << "Weight" << endl;

	// Для каждой вершины в наборе найти все смежные вершины,
	// вычислить расстояние от вершины, выбранной на шаге 1.
	// Если вершина уже обработана, отбросить ее,
	// иначе выбрать другую вершину, ближайшую к выбранной

	while (no_edge < V - 1) {
		int min = INT_MAX;
		x = 0; y = 0;
		for (int i = 0; i < V; i++) {
			if (selected[i]) {
				for (int j = 0; j < V; j++) {
					if (!selected[j] && G[i][j]) {
						if (min > G[i][j]) {
							min = G[i][j];
							x = i; y = j;
						}
					}
				}
			}
		}
		cout << x + 1 << " - " << y + 1 << " : " << G[x][y] << endl;
		selected[y] = true;
		no_edge++;
	}
	return 0;
}
