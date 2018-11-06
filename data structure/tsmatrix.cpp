#include <iostream>
constexpr auto M = 4;
constexpr auto N = 4;
template <typename T>
class TSMatrix;

template <typename T>
class TupNode {
	friend class TSMatrix<T>;
private:
	int r;	//行号
	int c;	//列号
	T d;

public:
	TupNode(int row=0, int col=0, T data= 0) {
		r = row;
		c = col;
		d = data;
	}
	void SetTupNode(int row = 0, int col = 0, T data = 0) {
		r = row;
		c = col;
		d = data;
	}
};

template <typename T>
class TSMatrix {
private:
	int rows;					//行数
	int cols;					//列数
	int nums;					//非零元素个数
	const int MaxSize = 64;	//非零元素最多的个数
	TupNode<T>* data;				//指向三元组数组的指针
public:
	TSMatrix() {
		rows = 0;
		cols = 0;
		nums = 0;
		data = new TupNode<T>[MaxSize];
	}
	TSMatrix(T A[M][N]) {
		rows = M;
		cols = N;
		nums = 0;
data = new TupNode<T>[MaxSize];
for (int i = 0; i < rows; i++) {
	for (int j = 0; j < cols; j++) {
		if (A[i][j] != 0) {
			data[nums].SetTupNode(i, j, A[i][j]);
			nums++;
		}
	}
}
	}

	TSMatrix(T* A, int r, int c) {
		rows = r;
		cols = c;
		nums = 0;
		data = new TupNode<T>[MaxSize];
		T temp;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				temp = *(A + i * cols + j);
				if (temp != 0) {
					data[nums].SetTupNode(i, j, temp);
					nums++;
				}
			}
		}
	}

	void DispMat() {
		if (nums == 0)
			return;

		printf("size: %d*%d\t\nnon-zeros: %d\n", rows, cols, nums);
		printf("\trow\tcol\tdata\n");
		for (int i = 0; i < nums; i++) {
			printf("\t%d\t%d\t%d\n", data[i].r, data[i].c, data[i].d);
		}
	}

	//下标从0开始
	void SetElem(int row, int col, T d) {
		if (row >= rows || col >= cols) {
			printf("Out of bound!");
			return;
		}
		for (int i = 0; i < nums; i++) {
			if (data[i].r == row && data[i].c == col) {
				data[i].d = d;
				break;
			}
			if (data[i].r > row || (data[i].r == row && data[i].c >= col)) {
				for (int k = nums; k > i; k--) {
					data[k] = data[k - 1];		//整体向后移
				}
				data[i].SetTupNode(row, col, d);
				nums++;
				return;
			}
		}
		//如果不在上述范围就在最后一个
		data[nums].SetTupNode(row, col, d);
		nums++;
	}

	T GetElem(int row, int col) {
		if (row >= rows || col >= cols) {
			printf("Out of bound!");
			return 0;
		}
		for (int i = 0; i < nums; i++) {
			if (data[i].r == row && data[i].c == col) {
				return data[i].d;
			}
		}
		return 0;
	}


	//矩阵转置后的三元组
	TSMatrix<T> Transpose() {
		TSMatrix<T> mat;
		mat.nums = nums;		//非零元素个数不变
		mat.rows = rows;		//行数不变
		mat.cols = cols;		//列数不变
		if (nums == 0)
			return mat;
		int count = 0;
		for (int j = 0; j < cols; j++) {
			for (int i = 0; i < nums; i++) {
				//把第j列的元素从上到下放到mat中
				if (data[i].c == j) {
					mat.data[count].SetTupNode(j, data[i].r, data[i].d);
					count++;
				}
			}
			if (count == nums)
				break;
		}
		return mat;
	}

	//复杂度O(m+n)
	TSMatrix<T> operator+(TSMatrix<T>& mat1) {
		TSMatrix<T> mat;
		if (this->rows != mat1.rows || this->cols != mat1.cols) {
			printf("Different size!");
			return mat;
		}
		mat.rows = rows;
		mat.cols = cols;
		int count = 0, index_i = 0, index_j = 0;
		//二路归并的参考
		while (index_i < nums && index_j < mat1.nums) {
			if (data[index_i].r == mat1.data[index_j].r) {
				if (data[index_i].c == mat1.data[index_j].c){
					mat.data[count++].SetTupNode(data[index_i].r, data[index_i].c, data[index_i].d + mat1.data[index_j].d);
					index_i++;
					index_j++;
				}
				else if (data[index_i].c < mat1.data[index_j].c) {
					mat.data[count++].SetTupNode(data[index_i].r, data[index_i].c, data[index_i].d);
					index_i++;
				}
				else
				{
					mat.data[count++].SetTupNode(mat1.data[index_j].r, mat1.data[index_j].c, mat1.data[index_j].d);
					index_j++;
				}
			
			}
			else if	(data[index_i].r < mat1.data[index_j].r){
				mat.data[count++].SetTupNode(data[index_i].r, data[index_i].c, data[index_i].d);
				index_i++;
			}
			else {
				mat.data[count++].SetTupNode(mat1.data[index_j].r, mat1.data[index_j].c, mat1.data[index_j].d);
				index_j++;
			}

		}
		
		//将剩余元素插入
		//不用判断顺序,因为其中有一个已经结束了
		while (index_i < nums ) {
			mat.data[count++].SetTupNode(data[index_i].r, data[index_i].c, data[index_i].d);
			index_i++;
		}
		while (index_j < mat1.nums)
		{
			mat.data[count++].SetTupNode(mat1.data[index_j].r, mat1.data[index_j].c, mat1.data[index_j].d);
			index_j++;
		}
		mat.nums = count;
		return mat;
	}


	//复杂度有点高
	TSMatrix<T> operator*(TSMatrix<T>& mat1) {
		TSMatrix<T> mat;		
		if (this->cols != mat1.rows ) {
			printf("Connot multiply!");
			return mat;
		}
		mat.rows = rows;
		mat.cols = mat1.cols;
		int count = 0;
		int tmp = 0;
;		for(int i = 0; i < mat.rows; i++) {
			for (int j = 0; j < mat.cols; j++) {
				tmp = 0;
				for (int k = 0; k < this->cols; k++) {
					tmp += GetElem(i, k)*mat1.GetElem(k, j);
				}
				if (tmp != 0) {
					mat.data[count++].SetTupNode(i, j, tmp);
				}
			}
		}
		mat.nums = count;
		return mat;

	}
};

