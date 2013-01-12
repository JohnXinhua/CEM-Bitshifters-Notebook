int graph[110][110]; // -1 is not connected
int distance[110];
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > heap;
int nodes;

memset(distance, -1, sizeof(distance));
heap.push(make_pair(0, 0));
while (!heap.empty()) {
	pair<int, int> toadd = heap.top();
	heap.pop();

	if (distance[toadd.second] != -1) continue;
	distance[toadd.second] = toadd.first;

	for (int j = 0; j < nodes; j++) {
		if (distance[j] == -1 && graph[toadd.second][j] != -1) {
			heap.push(make_pair(toadd.first + graph[toadd.second][j], j));
		}
	}
}
