// Assignment 4 Question #1
// I've labeled each relevant part of a subquestion with their respective letter
// to allow for easier searchability, and have block commented out anything that's 
// not relevant/required for assignment 4 specifically
#include <iostream>
#include <cstdio>
#include <cmath>
#include <fstream>

#include <Windows.h>

#include "2D_graphics.h"
#include "timer.h"

using namespace std;

/*
// setting max matrix size
const int NMAX = 2500;
*/

// equation to map [i,j] matrix to 1D matrix (lowercase is index, upper is length):
// k = m + M * (n - 1), PLAINTEXT: k = column index + total columns * (row index - 1)


class dMatrix{

private: // redundant, but i like how it looks
	/*
	double A[NMAX];
	*/
public:

	// a) declaring pointer for dynamic memory allocation
	double *A;
	// b) static member variable declaration
	// b) static member variable declaration
	static int n_objects;
	int N, M;
	   
	// constructor prototype
	dMatrix(int n, int m);
	// deconstructor prototype
	~dMatrix();

	/*
	// constructor prototype
	dMatrix(char file_name[]);
	// max() function prototype
	double max1();
	*/

	// e() function prototype
	double & e(int i, int j);
	// d) save function prototype
	void save(char my_file[]);
	// e) load function prototype
	void dMatrix::load(char file_name[]);
};

// b) static member variable initialization
int dMatrix::n_objects{ 0 };

// c) modified add function prototype to be call by value
void add(dMatrix A, dMatrix B, dMatrix C);

int main()
{
	// initializing index variables and file name for save/load member functions
	int i{}, j{};
	char file_name[12] = "my_file.bin";

	/*
	cout << "\nInitializing two matrices, one square (5x5) and one non-square (3x5)";

	dMatrix matrix4x4(4, 4);
	dMatrix matrix3x5(3, 5);
	*/

	// f) main program to demonstrate functionality
	dMatrix A(2, 3);
	dMatrix B(2, 2);
	dMatrix C(2, 3);

	for (i = 0; i < A.N; i++) {
		for (j = 0; j < A.M; j++) {
			A.e((i + 1), (j + 1)) = i - j + 3;
		}
	}

	// saving A to file
	A.save(file_name);

	cout << "\nA=\n";
	for (i = 0; i < A.N; i++) {
		for (j = 0; j < A.M; j++) {
			cout << A.e((i + 1), (j + 1)) << "\t";
		}
		cout << "\n";
	}

	cout << "\nB=\n";
	for (i = 0; i < B.N; i++) {
		for (j = 0; j < B.M; j++) {
			cout << B.e((i + 1), (j + 1)) << "\t";
		}
		cout << "\n";
	}

	// loading B from the saved file and comparing
	B.load(file_name);

	cout << "\nA=\n";
	for (i = 0; i < A.N; i++) {
		for (j = 0; j < A.M; j++) {
			cout << A.e((i + 1), (j + 1)) << "\t";
		}
		cout << "\n";
	}

	cout << "\nB=\n";
	for (i = 0; i < B.N; i++) {
		for (j = 0; j < B.M; j++) {
			cout << B.e((i + 1), (j + 1)) << "\t";
		}
		cout << "\n";
	}

	// changing the add(A,B,C) function to call by value causes run-time errors that seem caused by wild pointers,
	// writing to unallocated/random memory in the heap
	// I believe this is happening because instances of the dMatrix object are being passed to the add function
	// these instances don't necessarily have *A* value to pass, and thus there is ambiguity in what is requested.
	// From here, the compiler may do it's best and pass a pointer to memory related to the object, 
	// but is not allocated for that purpose and this "random" address being passed is considered wild.

	//// adding A and B to see the effect that changing call by reference to call by value has:
	//add(A, B, C);
	//
	//// printing resulting matrix 
	//cout << "\nC=\n";
	//for (i = 0; i < C.N; i++) {
	//	for (j = 0; j < C.M; j++) {
	//		cout << C.e((i + 1), (j + 1)) << "\t";
	//	}
	//	cout << "\n";
	//}

	/*
	cout << "\nInputting a square matrix from \"my_data.txt\":";
	dMatrix file_matrix("my_data.txt");
	
	cout << "\nEnter an index (i,j) that you would like to access from the matrix just displayed:\t";
	cin >> i >> j;
	cout << "\nYour selected element is:\t" << file_matrix.e(i, j);
	
	cout << "\nAnd the maximum element is:\t" << file_matrix.max1();
	
	cout << "\nSetting the first matrix equal to the sum of itself and the most recent matrix:";
	
	add(matrix4x4, file_matrix, matrix4x4);
	
	cout << "\n";
	for (i = 0; i < matrix4x4.N; i++) {
		for (j = 0; j < matrix4x4.M; j++) {
			cout << matrix4x4.e(i + 1, j + 1) << "\t";
	
		}
		cout << "\n";
	}
	*/

	cout << "\ndone.\n";
	getchar();

	return 0;
}

dMatrix::dMatrix(int n, int m){ 
	
	int i{}, j{};
	// initializing member variables
	N = n;
	M = m;

	// a) dynamically allocating memory
	A = new double[N * M];

	if (A == NULL) {
		cout << "\nMemory allocation unsuccessful";
		return;
	}

	//if ((n*m) > NMAX) {
	//	cout << "\nError, matrix is too large!";
	//	return;
	//}

	cout << "\nA[" << N*M << "] = ";

	if (N == M) { // setting unit matrix if square
			
		for (i = 0; i < (N*M); i++) {
			
	// diagonal elements = previous diagonal element + number of columns + 1
			if (i == (j + M + 1) || i == 0) {
				j = i;
				A[i] = 1.0;
			}
			else A[i] = 0.0;
	
		}
	}
	else { // setting all matrix elements to zero if non-square
		for (i = 0; i < (N * M); i++) {
			A[i] = 0.0;
		}
	}
	
	// displaying the constructed matrix
	for (i = 0; i < (N * M); i++) {
		if (!(i % M)) {
			cout << "\n";
		}
		cout << A[i] << " ";
	}

	// b) incrementing and displaying static member variable
	n_objects++;
	cout << "\nn_objects = " << n_objects;
	cout << "\nConstructor dMatrix(n,m) done constructing\n";
}


dMatrix::~dMatrix() {
	delete [] A;

	// b) decrementing and displaying static member variable
	n_objects--;
	cout << "\nn_objects = " << n_objects;

	cout << "\nDestructor for dMatrix done destructing";
	//getchar(); // hold program to see how many times destructor operates

};

/*
dMatrix::dMatrix(char file_name[]) { // I'm not sure why this doesn't consider N and M initialized
	// reading from file
	ifstream fin(file_name);
	if(!fin){
		cout << "\nError ocurred during file opening";
		return;
	}

	int i{},k{};
	fin >> N >> M;
	k = N * M;

	//if (k > NMAX) {
	//	cout << "\nError, matrix is too large!";
	//	return;
	//}

	for (i = 0; i < k; i++) {
		fin >> A[i];
	}

	// displaying the constructed matrix
	for (i = 0; i < k; i++) {
		if (!(i % M)) {
			cout << "\n";
		}
		cout << A[i] << "\t";
	}

	// b) incrementing static member variable
	n_objects++;
	cout << "\nn_objects =" << n_objects;
	cout << "\nConstructor dMatrix(char file_name[]) done constructing\n";
};
*/

/*
double dMatrix::max1() {
	int i{};
	double max_value{ -1.79 * pow(10,308) };

	for (i = 0; i < (N * M); i++) {
		if (A[i] > max_value)max_value = A[i];
	};

	return max_value;
};
*/

double& dMatrix::e(int i, int j) {
	/*
	// check if out of range of user inputs, and NMAX just in case
	if (i<1 || j<1 || (i * j)>NMAX || (i * j)>(N * M)) {
		cout << "error, requested index is out of range";
	}
	*/

	// troubleshooting
	//cout << A[(j + M * (i - 1)) - 1];
	return A[(j + M * (i - 1)) - 1];
};

// c) modified add function definition to be call by value
void add(dMatrix A, dMatrix B, dMatrix C) {
	int i{}, j{}; 

	// cout << endl << A.N << endl << B.N << endl << A.M << endl << B.M;

	if (A.N != B.N || A.M != B.M) {
		cout << "Error: cannot add matrices with different dimensions";
	}

	for (i = 0; i < A.N; i++) {
		for (j = 0; j < A.M; j++) {
			C.e(i + 1, j + 1) = (A.e(i + 1, j + 1) + B.e(i + 1, j + 1));
		}
	}

	return;
};

// d) save function definition
void dMatrix::save(char file_name[]) {
	ofstream fout;
	fout.open(file_name, ios::binary);

	if (!fout) {
		cout << "Error creating file";
	}

	int i{};
	int* p;
	char* a;
	// allocating memory for buffer
	p = new int[N * M + 2];
	// creating 1 byte pointer for byte-wise output
	a = (char *)p;

	// creating new memory buffer in same format as file output
	for (i = 0; i < (N * M + 2); i++) {
		if (i >= 1) {
		p[i] = A[i-2];
		}
		else {
		p[i] = N;
		i++;
		p[i] = M;
		}
	}

	// messy troubleshooting
	//for (i = 0; i < N * M+2; i++) {
	//	cout << p[i] << endl;
	//}

	// writing to binary file opened previously
	fout.write(a, sizeof(int) * (N * M + 2));
	
	cout << "Saving file\n";

	delete [] p;
	fout.close();
};

void dMatrix::load(char file_name[]) {
	int n{}, i{};
	int* p;
	int* q;
	p = new int[2];

	cout << "\nLoading file";

	ifstream fin;
	fin.open(file_name, ios::binary);

	if (!fin) {
		cout << "\nError reading file";
		return;
	}

	// reading first two integers to allocated memory buffer p
	// to determine memory buffer size
	fin.read((char*)p, sizeof(int) * 2);
	N = p[0];
	M = p[1];
	n = N * M;
	q = new int[n];

	// freeing memory that will no longer be used
	delete [] p;
	delete [] A;
	A = new double[n];

	// reading file to dynamically allocated memory buffer
	fin.read((char*)q, sizeof(int) * n);

	// copying buffer to member variable
	for (i = 0; i < n; i++) {
		A[i] = q[i];
	}
	
	delete [] q;
	fin.close();
}