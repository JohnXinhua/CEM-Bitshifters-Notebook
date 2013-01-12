const int NN = 1024;	// the maximum number of vertices
int cap[NN][NN];	// adjacency matrix (fill this up)
int fnet[NN][NN];	// flow network

int q[NN], qf, qb, prev[NN]; // BFS

int fordFulkerson(int n, int s, int t){
	// init the flow network
	memset(fnet, 0, sizeof(fnet));
	int flow = 0;

	while (true){
		// find an augmenting path
		memset(prev, -1, sizeof(prev));
		qf = qb = 0;
		prev[q[qb++] = s] = -2;
		while (qb > qf && prev[t] == -1)
			for (int u = q[qf++], v = 0; v < n; v++)
				if (prev[v] == -1 && fnet[u][v] - fnet[v][u] < cap[u][v])
					prev[q[qb++] = v] = u;

		// see if we're done
		if (prev[t] == -1 ) break;

		// get the bottleneck capacity
		int bot = 0x7FFFFFFF;
		for (int v = t, u = prev[v]; u >= 0; v = u, u = prev[v])
			bot = min(bot, cap[u][v] - fnet[u][v] + fnet[v][u]);

		// update the flow network
		for (int v = t, u = prev[v]; u >= 0; v = u, u = prev[v])
			fnet[u][v] += bot;

		flow += bot;
	}
	return flow;
}
