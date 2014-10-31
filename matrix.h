/*
 * Evan O'Connor - eco2116
 * matrix.h
 */

#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <iostream>

class Matrix {

	public:
		Matrix(int, int);
		Matrix();
		~Matrix();
		Matrix(const Matrix&);
		Matrix& operator=(const Matrix&);
		
		double accessElement(int, int);
		Matrix& insertElement(int, int, double);
		Matrix operator^(int);
		Matrix& operator*=(const Matrix&);
		Matrix& operator*(const Matrix&);	
	
		Matrix createIDMatrix(int);
		void swap(int,int);
		static Matrix solveOddDiagMatrix(Matrix, Matrix, int);		
		static Matrix augment(Matrix, Matrix);
		Matrix gaussianElim();
		Matrix rrefFromGauss();
		void solutionsFromRREF(std::ostream& os);

		friend std::ostream& operator<<(std::ostream&, const Matrix&);
	private:
		int mRows, mCols;
		double **m;
		
		void allocMatrixMem();
		Matrix expSolver(const Matrix&, int);
};

Matrix operator*(const Matrix&, const Matrix&);

#endif
