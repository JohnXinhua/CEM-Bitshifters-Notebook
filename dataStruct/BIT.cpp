template <class T>
class BIT {
	public:
		BIT(int maxSize, T* memPnt=NULL) : maxSize(maxSize) {
			if(!memPnt) 
				memPnt = new T[maxSize];
			this->arr = memPnt;
		}
		void addValue(int pos, T val) {
			while(pos<maxSize) {
				this->arr[pos] += val;
				pos += (pos&-pos);
			}
		}
		T getRange(int pos1, int pos2) {
			return getValue(pos2)-getValue(pos1-1);
		}
		T getValue(int pos) {
			T sum = T();
			while(pos) {
				sum += this->arr[pos];
				pos -= (pos&-pos);
			}
			return sum;
		}
	private:
		int maxSize;
		T* arr;
};

template <class T>
class BiBIT {
	public:
		BiBIT(int maxI, int maxJ, T** memPnt=NULL) : maxI(maxI), maxJ(maxJ) {
			if(!memPnt) {
				memPnt = new int*[maxI];
				for(int i = 0; i < maxI; ++i)
					memPnt[i] = new int[maxJ];
			}
			this->arr = memPnt;
		}
		void addValue(int i, int j, T val) {
			while(i < maxI) {
				for(int jT = j; j < maxJ; j += (j&-j)) {
					this->arr[i][jT] += val;
				}
				i += (i&-i);
			}
		}
		T getRange(int i1, int j1, int i2, int j2) {
			return getValue(i2, j2) - getValue(i2, j1-1) - getValue(i1-1, j2) + getValue(i1-1, j1-1);
		}
		T getValue(int i, int j) {
			T sum = T();
			while(i) {
				for(int jT = j; j; j -= (j&-j)) {
					sum += this->arr[i][jT];
				}
				i -= (i&-i);
			}
			return sum;
		}
	private:
		int maxI;
		int maxJ;
		T** arr;
};
