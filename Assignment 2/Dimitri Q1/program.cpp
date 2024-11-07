
#include <cstdio>
#include <iostream>
#include <fstream>

using namespace std;



class dMatrix {

	double *A; // declare a pointer for the dynamic array
	size_t size; // size of array N*M

	public:
	
	int N; // number of rows
	int M; // number of columns
	static int n_objects;
	

	// relation between (i,j) and k
	// k = M * (i - 1) + j - 1
		
	dMatrix(int n, int m);

	~dMatrix();

	dMatrix(char file_name[]);

	double max();

	double & e(int i, int j);
	
	// the print function is not needed for this question
	// -- I added it just for illustration purposes
	void print();
	
	void dMatrix::save(char filename[]);

	void dMatrix::load(char filename[]);

};

void add(dMatrix &A, dMatrix &B, dMatrix &C);

int dMatrix::n_objects = 0; // initialize static integer

int main()
{ 
	

	dMatrix A(2, 3);
	for (int i = 1; i <= A.N; i++) {
		for (int j = 1; j <= A.M; j++) {
			A.e(i, j) = i - j + 3;
		}
	}

	A.print();

	A.save("save_data.bin");
	
	dMatrix B(2, 2);

	B.load("save_data.bin");
	B.print();
	
	cout << "\n\ndone.\n";
	getchar();

	return 0;
} 

// compute C = A + B
void add(dMatrix &A, dMatrix &B, dMatrix &C)
{

	int i, j;

	// check if matrix sizes N, M are the same
	if( B.N != A.N || C.N != A.N || B.M != A.M || C.M != A.M ) {
		cout << "\nerror in add(A,B,C) -- matrix sizes are different";
		return;
	}
	
	for(i=1;i<=A.N;i++) {
		for(j=1;j<=A.M;j++) {
			C.e(i,j) = A.e(i,j) + B.e(i,j);
		}
	}
	
} 

dMatrix::dMatrix(int n, int m)
{
	int i, j, k;
	
	N = n;
	M = m;
	size = n*m ;

	A = new double[size];

	// Error Handling: Check for allocation errors
	if (A == NULL) {
		cout << "\nError: Memory cannot be allocated for A";
		exit(1); // Terminate the program to avoid wild pointers
	}

	// initializes matrix to identity matrix if the matrix is square 
	// and zero otherwise.

	for(i=1;i<=N;i++) {
		for(j=1;j<=M;j++) {
			k = M * (i - 1) + j - 1;
			A[k] = 0;
			// e(i,j) = 0; // alternative -- a bit slower due to error check
		}
	}	
	
	// check for identity
	if( N == M ) {
		for(i=1;i<=N;i++) e(i,i) = 1;
	}
	
	n_objects++;
	cout << "\nNumber of dMatrix objects: " << n_objects;
	cout << "\nconstructor dMatrix(n,m)";
}

dMatrix::~dMatrix()
{
	delete[] A;
	n_objects--;
	cout << "\nNumber of dMatrix objects: " << n_objects;
	cout << "\nMemory for dMatrix released";
}

dMatrix::dMatrix(char file_name[])
{
	int i, j;
	ifstream fin;
	
	fin.open(file_name);
	
	if( !fin ) {
		cout << "\nfile open error in dMatrix(file_name)";
		return;
	}
	
	fin >> N;
	fin >> M;
	
	size = N * M;

	A = new double[size];
	
	for(i=1;i<=N;i++) {
		for(j=1;j<=M;j++) {
			fin >> e(i,j);
		}
	}	
	
	fin.close();

	n_objects++;
	cout << "\nNumber of dMatrix objects: " << n_objects;
	cout << "\nconstructor dMatrix(from file)";
}

double dMatrix::max()
{
	double max_A;
	int i, j, k;
	
	max_A = -1e100;
	for(i=1;i<=N;i++) {
		for(j=1;j<=M;j++) {
			k = M * (i - 1) + j - 1;
			if( A[k] > max_A ) max_A = A[k];
		}
	}
	
	return max_A;
}

double & dMatrix::e(int i, int j)
{
	int k;
	
	if( (i < 1) || (i > N) || (j < 1) || (j > M) ) {
		cout << "\nerror in dMatrix::e(i,j) -- out of range";
		return A[0];
	}
	
	// relation between (i,j) and k
	k = M * (i - 1) + j - 1;
	
	return A[k];
}


void dMatrix::print()
{
	cout << "\n";
	int i, j;
	
	for(i=1;i<=N;i++) {
		for(j=1;j<=M;j++) {
			cout << e(i,j) << " ";
		}
		cout << "\n";
	}

}

void dMatrix::save(char filename[]) {


	
	int buffer_size = 2 * sizeof(int) + (N * M) * sizeof(double);  // variable that measures size of buffer required

	char* buffer_start = new char[buffer_size];  // create a character pointer called buffer_start, this is my home address, and it points to a dynamically allocated array of characters of size buffer_size

	if (buffer_start == nullptr) {
		cout << "\nError allocating memory";
		return;  // Error handling
	}

	char* buffer_current = buffer_start; // a pointer that acts as a moving cursor // set our cursor to the start/home address of our buffer 
	
	int* p_int; // integer pointer
	double* p_double; // double pointer

	p_int = (int*)buffer_current;
	*p_int = N;
	buffer_current += sizeof(int);

	p_int = (int*)buffer_current;
	*p_int = M;
	buffer_current += sizeof(int);

	for (int i = 0; i < (N * M); i++) {

		if (buffer_current + sizeof(double) > buffer_start + buffer_size) {
			cout << "\nError. Buffer write out of bounds. End Process.  Check Stored Data";
			break; 
		}

		p_double = (double*)buffer_current;
		*p_double = A[i];
		buffer_current += sizeof(double);
	}

	// now we will write this buffer to a binary file

	int n = (int)(buffer_current - buffer_start);
	cout << "\nNumber of bytes in buffer = " << n;


	ofstream fout;
	fout.open(filename, ios::binary);

	if (!fout) {
		cout << "\nFile opening error.";
		delete[] buffer_start;
		return;
	}

	fout.write(buffer_start, n);
	fout.close();




	delete[] buffer_start; // soon as we create buffer_start, we add this line of code to avoid memory leaks! leakage bad!

}

void dMatrix::load(char filename[]) {


	ifstream fin;								// start input file stream
	fin.open(filename, ios::binary);			// opens filename

	if (!fin) {									// error check fin
		cout << "\nFile opening error.";
		return;
	}



	// declare variables and pointers
	int buffer_size = (2 * sizeof(int));		// size of temp buffer, read two ints
	char* buffer_start = new char[buffer_size];	// creates a pointer, a home address, of our new buffer
	char* buffer_current;						// creates a pointer, our cursor
	int* p_int;									// integer pointer, for reading N and M
	double* p_double;							// double pointer, for reading doubles into a buffer, before passing them into A

	fin.read(buffer_start, buffer_size);		// writes 8 bytes of binary data starting at the address buffer start, then moves fin to the address of the first double
	if (!fin) {                                 // Check if read was successful
		cout << "\nError reading N and M from file.";
		delete[] buffer_start;
		fin.close();
		return;
	}



	buffer_current = buffer_start;				// set our cursor to our home address
	
	p_int = (int*)buffer_current;				// assign address of our cursor to an integer pointer
	N = *p_int;									// dereference that address into our member variable
	buffer_current += sizeof(int);				// move cursor to the next integer's address

	p_int = (int*)buffer_current;				// repeat
	M = *p_int;
	buffer_current += sizeof(int);




	delete[] buffer_start;						// N and M are now saved to our object, we de-allocate buffer_start
	buffer_start = nullptr;						// to avoid dangling pointers

	delete[] A;									// we de-allocate the memory at A, not sure if there is a better way to do this?
	A = nullptr;								//	avoid a dangling pointer

	size = N * M;								// size is a member variable, we re-set it to N*M
	A = new double[size];						// we allocate new memory to A

	if (A == nullptr) {							// error handling
		cout << "\nError allocating memory";
		return;  // Error handling
	}

	
	buffer_size = (N * M) * sizeof(double);		// calculate the number of bytes required for our new buffer
	buffer_start = new char[buffer_size]; // create a new buffer start and allocate new memory


												//  we could also have avoided making an intermediary buffer, 
												// with the following code fin.read((char*)A, buffer_size), 
												// but i think the instructions explicitely ask for a intermediate buffer

	fin.read(buffer_start, buffer_size);		// writes to buffer start, picking up where it left off earlier in the function
	if (!fin) {                                      // Check if read was successful
		cout << "\nError reading double data from file.";
		delete[] buffer_start;
		delete[] A;                                  // Clean up A if reading failed
		A = nullptr;
		fin.close();
		return;
	}

	buffer_current = buffer_start;				// set our cursor to our home address


	for (int i = 0; i < size; i++) {
		if (buffer_current + sizeof(double) > buffer_start + buffer_size) {
			cout << "\nError. Buffer read out of bounds. End Process.  Check Stored Data";
			break;
		}
		p_double = (double*)buffer_current;
		A[i] = *p_double;
		buffer_current += sizeof(double);
	}
	

	fin.close();								// close our input stream


	delete[] buffer_start;						// de-allocate our buffer memory
}







// when using call by value in the add function, we get garbage output.
// i also notice that the number of dmatrix objects is reduced.
//