Evan O'Connor
eco2116
Comp Linear Algebra
README.txt
Homework 3

Description of implementation:

I implemented functionality of this assignment by adding functions to
my C++ matrix class. My main class reads in the augmented matrix
Ab from the chosen in put file. Then, it calls a method in the Matrix
class called gaussianElim() that first performs Gaussian elimination
on the augmented matrix. Next, a method called rrefFromGauss() is
called on the post-Gaussian eliminated matrix, which returns
a matrix in reduced-row Echelon form. From this form of the matrix,
we call a method called solutionsFromRREF, which utilizes the RREF
matrix to determine whether it has one solution, infinite solutions,
or no solutions. If the matrices have infinite solutions, the particular
and special solutions are calculated and printed to the ostream.


How to run:

1. In CUNIX, find my homework directory and enter by typing:
cd hw3_eco2116

2. In the hw3_eco2116 directory, enter into the command line:
gcc -g -Wall -c main.cpp matrix.cpp
gcc -g matrix.o main.o -o main -lstdc++
./main input_matrix output_matrix

(input_matrix and output_matrix are chosen locations of the input and
output matrices)

Format of input file:

m
n
[ augmented matrix Ab
  row elements separated by spaces
  columns separated by newlines
  element i,j of matrix A is in location i,j of Ab
  element i,1 of matrix B is in location i,n+1 of Ab
]
