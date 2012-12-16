const int MAXSIZE = 1002;
template <class T>
class FastHeap {
	public:
		FastHeap() {
			this->endPointer = 0;
		}
		void push(T val) {
			int currPlace = ++endPointer;
			int nextPlace = currPlace>>1;
			while(currPlace > 1 && val < arr[nextPlace]) {
				arr[currPlace] = arr[nextPlace];
				currPlace = nextPlace;
				nextPlace >>= 1;
			}
			arr[currPlace] = val;
		}
		void pop() {
			T val = arr[endPointer--];
			int curr1 = 1, curr2 = 2, curr3 = 3;
			while(curr2 <= endPointer) {
				if(curr3 <= endPointer && arr[curr3] < arr[curr2])
					curr2 = curr3;
				if(arr[curr2] < val) {
					arr[curr1] = arr[curr2];
					curr1 = curr2;
					curr2 <<= 1;
					curr3 = curr2 + 1;
				} else {
					break;
				}
			}
			arr[curr1] = val;
		}
		T top() { return arr[1]; }
		bool empty() { return endPointer <= 0; }
	private:
		T arr[MAXSIZE];
		int endPointer;
};
