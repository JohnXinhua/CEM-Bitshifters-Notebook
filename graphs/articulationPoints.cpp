vector<list<int> > grafo(30);
int LOW[30], visitado[30], dfs_number[30], padre[30];
int i, cont, n;
int origen, destino;
list<pair<int, int> > T;
list<int> articulaciones;

void limpia_grafo() {
	cont = 0;
	for(i = 0; i < 30; i++){
		LOW[i] = visitado[i] = dfs_number[i] = padre[i] = 0;
		grafo[i].clear();
	}

	T.clear();
	articulaciones.clear();
}

void searchb(int v) {
	list<int>::iterator aux, fin;
	pair<int, int> arista;

	visitado[v] = 1;
	dfs_number[v] = cont;
	cont++;
	LOW[v] = dfs_number[v];
	aux = grafo[v].begin();
	fin = grafo[v].end();
	arista.first = v;

	while(aux != fin){
		if(!visitado[*aux]){
			arista.second = *aux;
			T.push_back(arista);
			padre[*aux] = v;
			searchb(*aux);

			if(LOW[*aux] >= dfs_number[v])
				articulaciones.push_back(v);

			LOW[v] = min( LOW[v], LOW[*aux]);
		} else {
			if(*aux != padre[v])
			   LOW[v] = min( LOW[v], dfs_number[*aux]);
		}

		aux++;
	}
}

// inicializa el grafo y llama
// searchb(0);
