const int MAX_N=10000;
const int MAX_NODO=MAX_N*2+2;
const int IMPOSSIBRU=100000000;

#define parent(a) (a/2)
#define childl(a) (a*2)
#define childr(a) (a*2+1)

int lg2(int a){ 
	int i;
	for(i=0; i<32; i++) {
		if((a>>i)==1) {
			break;
		}
	}
	return i;
}

struct nod {
	int ini, fin, val;
};

class arb {
	public:
		nod arbol[MAX_NODO];
	
		arb(bool min_max, int size) { //Specify size and if the tree is for max or mins
			p_size=size;
			p_min_max=min_max;
			for (int i=1; i<=2*size-1; i++) {
				arbol[i].val=(min_max?IMPOSSIBRU:0);
			}
			cambiar_nod(1, size, 1);
		}
		
		void update(int index, int value) {
			_update(1,p_size,1,index,value);
		}
		
		int query(int a, int b) {
			return _query(a, b, 1);
		}
		
	private:
		int p_size;
		bool p_min_max;
	
		bool F_M(int a, int b) {
			if(p_min_max) return(a<b?a:b);
			return(a>b?a:b);
		}
	
		void cambiar_nod(int a, int b, int index) {
			arbol[index].ini=a;
			arbol[index].fin=b;
			if(a==b) return;
			cambiar_nod(a, (b+a)/2, childl(index));
			cambiar_nod(((b+a)/2)+1, b, childr(index));
		}
		
		void _update(int a, int b, int index, int pos, int val){
			if (a == b){
				arbol[index].val = val;
				return;
			}
			int medio = (a+b)/2, temp1, temp2;
			if(pos<=medio) {
				_update(a,medio,childl(index),pos,val);
			} else {
				_update(medio+1,b,childl(index),pos,val);
			}
			
			arbol[index].val = F_M(arbol[childl(index)].val, arbol[childr(index)].val);
		}
		
		int _query(int a, int b, int index) {
			if(arbol[index].ini==a&&arbol[index].fin==b) {
				return arbol[index].val;
			}
			int medio=(arbol[index].ini+arbol[index].fin)/2;
			int temp1=(p_min_max?IMPOSSIBRU:0);
			int temp2=(p_min_max?IMPOSSIBRU:0);
			if(b<=medio) {
				temp1=_query(a, b, childl(index));
			} else if(a>medio) {
				temp1=_query(a, b, childr(index));
			} else {
				temp1=_query(a, medio, childl(index));
				temp2=_query(medio+1, b, childr(index));
			}
			return F_M(temp1, temp2);
		}
};

