const int MAXSIZE = 100002;
template <class T>
class BIT {
	public:
		BIT() : maxSize(MAXSIZE) { }
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
		T arr[MAXSIZE];
};

const int MAXI = 1002;
const int MAXJ = 1002;
template <class T>
class BiBIT {
	public:
		BiBIT() : maxI(MAXI), maxJ(MAXJ) { }
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
		T arr[MAXI][MAXJ];
};

int main() {
}
