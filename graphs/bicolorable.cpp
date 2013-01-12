bool adj[210][210];	// adjacency matrix
int color[210];	// color of each node
int n;

bool bicolor() { // is the graph described in adj bicolorable?
	queue<pair<int,int> > q; // en el queue vamos a poner qué color debe ser el destino
	q.push(make_pair(0, 0));

	while (!q.empty()) {
		pair<int,int> p = q.front(); q.pop();
		if (color[p.first] == !p.second) return false; // inconsistencia
		if (color[p.first] == p.second) continue;
		color[p.first] = p.second;

		for (int i = 0; i < n; i++) {
			 if (adj[p.first][i]) // son compas, agregar a queue
				  q.push(make_pair(i, !p.second));
		}
	}
	return true;
}
