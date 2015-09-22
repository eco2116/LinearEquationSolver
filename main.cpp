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
	if (argc!=3) {
		perror("Usage: ./main input_file output_file");
		exit(1);
	}
	
	ifstream infile;
	infile.open(argv[1]);
	int m=0;
	int n=0;
	infile>>m>>n;
	Matrix Ab(m,n+1);
	double element;
	
	int i, j;
	for (i=0; i<m; ++i)
	{
		for (j=0; j<n+1; ++j)
		{
			infile>>element;
			Ab = Ab.insertElement(i,j,element);
		}
	}

	


	Matrix gauss = Ab.gaussianElim();
	Matrix rref = gauss.rrefFromGauss();
	ofstream outfile;
	outfile.open(argv[2]);
	rref.solutionsFromRREF(outfile);
	infile.close();
	outfile.close();

}
