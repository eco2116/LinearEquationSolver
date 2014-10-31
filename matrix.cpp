/*
 * Evan O'Connor - eco2116
 * matrix.cpp
 */

#include <iostream>
#include "matrix.h"

using namespace std;

Matrix::Matrix() : mRows(1), mCols(1)
{
	allocMatrixMem();
	m[0][0] = 0;
}

Matrix::Matrix(int rows, int cols) : mRows(rows), mCols(cols)
{
	allocMatrixMem();
	for (int i=0; i<mRows; ++i) {
		for (int j=0; j<mCols; ++j) {
			m[i][j] = 0;
		}
	}
}

Matrix::~Matrix()
{

	for (int i=0; i<mRows; ++i) {
		delete[] m[i];
	}
	delete[] m;
}

Matrix::Matrix(const Matrix& c) : mRows(c.mRows), mCols(c.mCols)
{
	allocMatrixMem();
	for (int i=0; i<mRows; ++i) {
		for (int j=0; j<mCols; ++j) {
			m[i][j] = c.m[i][j];
		}
	}
}

Matrix& Matrix::operator=(const Matrix& c)
{
	if (this == &c) {
		return *this;
	}

	if (mRows != c.mRows || mCols != c.mCols) {
		for (int i=0; i<mRows; ++i) {
			delete[] m[i];
		}
		delete[] m;
		
		allocMatrixMem();
		mRows = c.mRows;
		mCols = c.mCols;
	}

	for (int i=0; i<mRows; ++i) {
		for (int j=0; j<mCols; ++j) {
			m[i][j] = c.m[i][j];
		}
	}
	return *this;
}

Matrix Matrix::createIDMatrix(int x)
{
	Matrix temp(x,x);
	for (int i=0; i<temp.mRows; ++i) {
		for (int j=0; j<temp.mCols; ++j) {
			if (i!=j) {
				temp.m[i][j] = 0;
			}
			else {
				temp.m[i][j] = 1;
			}
		}
	}
	return temp;
}

Matrix Matrix::expSolver(const Matrix& c, int x)
{
	if (x==0) {
		return createIDMatrix(c.mRows);
	}
	else if (x==1) {
		return c;
	}
	else if (x%2 != 0) {
		return c * expSolver(c*c, (x-1)/2);
	}
	else {
		return expSolver(c*c, x/2);
	}
}

Matrix Matrix::operator^(int x)
{
	Matrix temp(*this);
	return expSolver(temp, x);
}

void Matrix::allocMatrixMem()
{

	m = new double*[mRows];
	for (int i=0; i<mRows; ++i) {
		m[i] = new double[mCols];
	}
}

ostream& operator<<(ostream& os, const Matrix& c)
{
	for (int i=0; i<c.mRows; ++i) {
		os << c.m[i][0];
		for (int j=1; j<c.mCols; ++j) {
			os << " " << c.m[i][j];
		}
		os << endl;
	}
	return os;
}

double Matrix::accessElement(int row, int col)
{
	return m[row][col];
}

Matrix& Matrix::insertElement(int row, int col, double e)
{
	m[row][col] = e;
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& c)
{
	Matrix temp(mRows, c.mCols);
	for (int i=0; i<temp.mRows; ++i) {
		for (int j=0; j<temp.mCols; ++j) {
			for (int k=0; k<mCols; ++k) {
				temp.m[i][j] += (m[i][k] * c.m[k][j]);
			}
		}
	}
	return (*this = temp);
}

Matrix operator*(const Matrix& c1, const Matrix& c2)
{
	Matrix temp(c1);
	return (temp *= c2);
}

Matrix Matrix::solveOddDiagMatrix(Matrix A, Matrix B, int m)
{
	Matrix X(B.mRows,1);
	int below = (m-1)/2;
	
	for (int i=0; i<A.mRows; ++i) {
		if (A.m[i][i]==0) {
			perror("Error: coefficient matrix has a 0 pivot.");
			exit(1);
		}
		for (int j=i+1; j<=i+below && j<A.mRows; ++j) {
			int k=i+1;
			while (k<A.mCols && A.m[j][k]) {
				A.m[j][k] -= A.m[i][k] * (A.m[j][i] / A.m[i][i]);
				k++;
			}
			B.m[j][0] -= B.m[i][0] * (A.m[j][i] / A.m[i][i]);
			A.m[j][i] = 0;
		}
	}
	X.m[X.mRows-1][0] = B.m[X.mRows-1][0] / A.m[X.mRows-1][X.mRows-1];
	for (int i=X.mRows-2; i>=0; --i) {
		int z=0;
		for (int j=i+1; j<X.mRows; ++j) {
			z+=A.m[i][j]*X.m[j][0];
		}
		X.m[i][0] = (B.m[i][0]-z) / A.m[i][i];
	}
	return X;
}

Matrix Matrix::augment(Matrix A, Matrix B)
{
	Matrix aug(A.mRows, A.mCols + B.mCols);
	for (int i=0; i<aug.mRows; ++i) {
		for(int j=0; j<aug.mCols; ++j) {
			if (j<A.mCols)
				aug.m[i][j]=A.m[i][j];
			else
				aug.m[i][j]=B.m[i][j-B.mCols];
		}
	}
	return aug;
}

void Matrix::swap(int one, int two)
{
	double *temp = m[one];
	m[one] = m[two];
	m[two] = temp;
}

Matrix Matrix::gaussianElim()
{
	Matrix elim(*this);
	int rows = elim.mRows;
	int cols = elim.mCols;
	int Acol = cols - 1;
	int i=0; int j=0;

	while (i<rows) {
		bool pivot = false;
		while (!pivot && j<Acol) {
			if (elim.m[i][j] != 0) {
				pivot = true;
			} else {
				int row_check = i;
				double val_check = 0;
				for (int k=i+1; k<rows; ++k)
				{
					double abs = elim.m[k][j] >= 0 ? elim.m[k][j] : -1*elim.m[k][j];
					if (abs > val_check)
					{
						row_check = k;
						val_check = abs;
					}
				}
				if (row_check != i) {
					elim.swap(row_check, i);
					pivot = true;
				} else {
					j++;
				}
			}
		}
		if (pivot)
		{
			for (int x = i+1; x < rows; ++x) {
				for (int y = j+1; y<cols; ++y) {
					elim.m[x][y] = elim.m[x][y] - elim.m[i][y]*(elim.m[x][j]/elim.m[i][j]);
				}
				elim.m[x][j] = 0;
			}
		}
		i++; j++;
	}
	return elim;
}

Matrix Matrix::rrefFromGauss()
{
	Matrix rref(*this);
	int rows = rref.mRows;
	int cols = rref.mCols;

	int row_track=rows-1;
	int col_track=cols-2;

	while(row_track>=0)
	{
		int k=col_track-1;
		while (k>=0) {
			if (rref.m[row_track][col_track]!=0)
				col_track = k;
			k--;
		}
	
		if (rref.m[row_track][col_track]!=0) {
			for (int x=row_track-1; x>=0; --x) {
				for (int y=0; y<cols; ++y) {
					if(y!=col_track) {
						rref.m[x][y]=rref.m[x][y]-rref.m[row_track][y]*(rref.m[x][col_track] / rref.m[row_track][col_track]);
					}
				}
				rref.m[x][col_track] = 0;
			}
			for (int k=col_track+1;k<cols;++k) {
				rref.m[row_track][k] = rref.m[row_track][k] / rref.m[row_track][col_track];
			}
			rref.m[row_track][col_track] = 1;
		}
		row_track--; col_track--;
	}
	return rref;
}

void Matrix::solutionsFromRREF(ostream& os)
{
	Matrix sol(*this);
	bool hasSol = true;
	bool finished = false;
	int i=0;
	while (!finished && i<mRows) {
		bool zeros=true;
		for (int j=0; j<mCols-1; ++j) {
			if(sol.m[i][j] != 0)
				zeros=false;
		}
		if (zeros && sol.m[i][mCols-1] != 0) {
			hasSol = false;
			os << "No solutions" << endl << endl;
			finished = true;
		} else if (zeros && sol.m[i][mCols-1] == 0) {
			os << "Infinite soluitons" << endl << endl;
			finished = true;
		} else if (mRows < mCols -1) {
			os << "Infinite Solutions" << endl << endl;
			finished = true;
		}
		i++;
	}
	if (!finished)
		os << "Unique solution" << endl << endl;
	bool[mCols-1] frees = {};
	if (hasSol) {
		Matrix p(mCols-1, 1);
		Matrix s(mCols-1, 1);
	
		int count = 0;
		for (int i=0; i<mRows; ++i) {
			bool pivot = false;
			
			for (int j=0; j<mCols; ++j) {
				if (sol.m[i][j] != 0) {
					if(!pivot) {
						pivot = true;
						p.m[j][0] = sol.m[i][mCols-1];
						frees[j] = false;
					} else {
						frees[j] = true;
					}
				}
			}
		}
		os << "Particular solution:" << endl << p << endl;
		for (int i=0; i<mCols-1; ++i) {
			if (frees[i]) {
				s.m[i][0] = 1;
				for (int j=0; j<mCols-1; ++j) {
					if (!frees[j]) {
						for (int k=0; k<mRows; ++k) {
							if (s.m[j][k] == 1) {
								s.m[j][0] = sol.m[k][i]*-1;
							}
						}
					}
				}
			}
		}
	}
}




			



}
