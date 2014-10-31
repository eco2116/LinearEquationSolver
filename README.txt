Evan O'Connor
eco2116
Comp Linear Algebra
README.txt
Homework 2

Description of implementation:

I implemented functionality of this assignment by adding a function called
solveOddDiagMatrix to my C++ matrix class. This function utilizes an
optimized Gaussian elimination to take advantage of the structure of an
m-diagonal matrix where m is odd. Then, the function performs back
substitution on the matrix and returns the solution matrix, X.
The algorithms are modeled after the pseudocode on p. 100. This function
does not perform row swaps and will throw an error if any pivots are equal to 0.
My main class works by reading in a coefficient matrix A (that is m-diagonal
where m is odd), its size, the value m, and the right hand side vector, B.
These are read from an input file, parsed, and then A,B, and m are passed
to the solveOddDiagMatrix method, which returns X. X is then written to 
the output file. 

How to run:

1. In CUNIX, find my homework directory and enter by typing:
cd hw2_eco2116

2. In the hw2_eco2116 directory, 

Format of input file:

n
m
[ matrix A
  row elements separated by spaces
  columns separated by newlines
]
[ matrix B
  columns separated by newlines
]

Format of output file:

[ matrix X
  row elements separated by spaces
  columns separated by newlines
]

*note: brackets not included in files formatting

Test input on n=10, m=5:

Input file:

10
5
1 2 3 0 0 0 0 0 0 0
4 5 6 2 0 0 0 0 0 0
3 3 5 2 3 0 0 0 0 0
0 2 5 2 4 1 0 0 0 0
0 0 2 3 3 6 5 0 0 0
0 0 0 1 2 4 1 7 0 0
0 0 0 0 2 1 2 7 3 0
0 0 0 0 0 2 3 3 3 1
0 0 0 0 0 0 2 3 3 2
0 0 0 0 0 0 0 3 2 1
4
9
2
5
2
2
2
2
2
5

Output file:

81
-38.6667
-20.6364
111.167
-28.5
-41
223.55
-57.7719
-165.502
336.333

Test input on n=10, m=3:

Input file:

10
3
1 2 0 0 0 0 0 0 0 0
4 5 6 0 0 0 0 0 0 0
0 3 5 3 0 0 0 0 0 0
0 0 5 2 4 0 0 0 0 0
0 0 0 3 3 6 0 0 0 0
0 0 0 0 2 4 1 0 0 0
0 0 0 0 0 1 2 7 0 0
0 0 0 0 0 0 3 3 3 0
0 0 0 0 0 0 0 3 3 2
0 0 0 0 0 0 0 0 2 1
4
9
2
5
2
2
2
2
2
5

Output file:

206
-101.333
-51.9091
189
-28.4865
-80.7424
382.974
-97.6623
-285.251
575.857
