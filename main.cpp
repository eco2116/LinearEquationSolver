/*
 * Evan O'Connor - eco2116
 * main.cpp
 */

#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include "matrix.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc!=2) {
		perror("Usage: ./main input_file");
		exit(1);
	}
	
	ifstream infile;
	infile.open(argv[1]);
	int m=0;
	int n=0;
	infile>>m>>n;
	Matrix A(m,n);	
	Matrix B(n,1);
	double element;
	
	int i, j;
	for (i=0; i<n; ++i)
	{
		for (j=0; j<m; ++j)
		{
			infile>>element;
			A = A.insertElement(i,j,element);
		}
	}
	for (i=0; i<n; ++i)
	{
		infile>>element;
		B = B.insertElement(i,0,element);
	}

	
	Matrix Ab = Matrix::augment(A,B);
	Matrix gauss = Ab.gaussianElim();
	Matrix rref = gauss.rrefFromGauss();
	cout << rref << endl;
	//rref.solutionsFromRREF(cout);
	

}
