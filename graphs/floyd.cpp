int graph[1010][1010]; // weighted graph, -1 is no connection
int n;
void shortest() { // floyd-warshall shortest path from every node to very other node - O(n^3)
	for (int k = 0; k < n; k++) for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
		if (graph[i][j] == -1 || graph[i][j] > graph[i][k] + graph[k][j]) {
			graph[i][j] = graph[i][k] + graph[k][j];
		}
}
