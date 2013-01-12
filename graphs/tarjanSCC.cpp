vector<vector<int> > g;
stack<int> S;
int vindex[MAX]; int vlowlink[MAX]; bool vinstack[MAX]; int idx = 0;

void tarjan_init() {
	memset(vindex, -1, sizeof(vindex));
	memset(vlowlink, -1, sizeof(vlowlink));
	memset(vinstack, 0, sizeof(vinstack));
	idx = 0;
	for (int i = 1; i <= n; i++) make_set(i); // init union-find
	while(!S.empty()) S.pop();
}

void tarjan(int node) {
	if(vindex[node] != -1) return;

	vindex[node] = idx;   // Set the depth index for v
	vlowlink[node] = idx;
	idx++;
	S.push(node);	// Push v on the stack
	vinstack[node] = true;
	for(vector<int>::iterator it = g[node].begin(); it != g[node].end(); it++) {
		// Consider successors of v
		if (vindex[*it] == -1) { // Was successor v' visited?
			tarjan(*it); // Recurse
			if(vlowlink[node] > vlowlink[*it])
			vlowlink[node] = vlowlink[*it];
		} else if(vinstack[*it]) {	// Is v' on the stack?
			if(vlowlink[node] > vindex[*it])
			vlowlink[node] = vindex[*it];
		}
	}
	if (vlowlink[node] == vindex[node]) { // Is v the root of an SCC?
		int nodep;

		do {
			nodep = S.top();
			S.pop();
			vinstack[nodep] = false;

			union_set(node, nodep);
			// Add all nodes in SCC to a set
		} while(nodep != node);
	}
}

// tarjan_init()
// for(int i=0; i<NODES; i++) tarjan(i);
