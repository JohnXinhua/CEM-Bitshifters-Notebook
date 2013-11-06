const int MAXPOWER2=1<<17; // 2^17
const int MAX_BIT=MAXPOWER2+2; // Agrega 2 al inicio y al fin.

inline int F_M(int a, int b) { return(a>b?a:b); } //Cambiar a < para hacer un BIT de minimos.

int BIT[2][MAX_BIT];

void update(int i, int val) {
	int k;
	for(k=i; k<MAX_BIT; k+=(k&-k)) {
		BIT[0][k]=F_M(BIT[0][k], val);
	}
	//Calcular el maximo/minimo en el BIT invertido
	for(k=MAXPOWER2-i+1; k<MAX_BIT; k+=(k&-k)) {//k es el valor reciproco de i
		BIT[1][k]=F_M(BIT[1][k], val);
	}
}

int consult(int a, int b) {
	if(a>b) {
		return 0;
	}
	int k, max=0;
	//Calcula el maximo/minimo en el BIT para todas las posiciones mientras la (siguiente pos k) + 1
	//sea mayor a "a".  
	for(k=b; k-(k&-k)+1>=a&&k>0; k-=(k&-k)) {
		max=F_M(max, BIT[0][k]);
	}
	//Calcula el maximo/minimo en el BIT para todas las posiciones mientras la (siguiente pos k) + 1
	//sea mayor a "b".
	for(k=MAXPOWER2-a+1; k-(k&-k)+1>=MAXPOWER2-b+1&&k>0; k-=(k&-k)) {
		max=F_M(max, BIT[1][k]);
	}
	return max;
}
