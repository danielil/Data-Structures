/**
 * @author Daniel Sebastian Iliescu
 * @file Matrix.h
 * @instructor Clark Olson
 * @course CSS 487
 * @due 2015-04-08
 *
 * This file contains the header definition for the Matrix class.
 */

#pragma once
#include <iostream>

class Matrix
{
public:
	static double** CreateMatrix(int rows, int columns);
	static void DeleteMatrix(double** matrix, int rows);

	static double** GetAddition(double** leftMatrix, 
								double** rightMatrix, 
								int rows, 
								int columns);
	static double** GetSubtraction(double** leftMatrix, 
								   double** rightMatrix, 
								   int rows, 
								   int columns);
	static double** GetMultiplication2x1(double** leftMatrix, 
										 double** rightMatrix, 
										 int leftMatrixColumns, 
										 int rightMatrixRows);
	static double** GetMultiplication2x2(double** leftMatrix, 
										 double** rightMatrix, 
										 int leftMatrixColumns, 
										 int rightMatrixRows);
	static double** GetInverse(double** matrix);

	static double GetDeterminant(double** matrix);
};

double** Matrix::CreateMatrix(int rows,
    int columns)
{
    double** matrix = NULL;

    if (rows > 0 && columns > 0)
    {
        matrix = new double*[rows];

        for (int row = 0; row < rows; row++)
        {
            matrix[row] = new double[columns];

            for (int column = 0; column < columns; column++)
            {
                matrix[row][column] = 0;
            }
        }
    }

    return matrix;
}

/**
* Deletes the multidimensional array representing a matrix.
*/
void Matrix::DeleteMatrix(double** matrix,
    int rows)
{
    if (matrix)
    {
        for (int row = 0; row < rows; row++)
        {
            delete[] matrix[row];
        }

        delete[] matrix;
    }
}

/**
* Returns the determinant of a 2x2 matrix.
*/
double Matrix::GetDeterminant(double** matrix)
{
    if (matrix)
    {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }
    else
    {
        return 0;
    }
}

/**
* Returns a multidimensional array representing the inverse of the inputted
* 2x2 matrix.
*/
double** Matrix::GetInverse(double** matrix)
{
    double** adjMatrix = NULL;

    if (matrix)
    {
        double multiplier = 1 / GetDeterminant(matrix);

        adjMatrix = CreateMatrix(2, 2);
        adjMatrix[0][0] = matrix[1][1] * multiplier;
        adjMatrix[0][1] = -matrix[0][1] * multiplier;
        adjMatrix[1][0] = -matrix[1][0] * multiplier;
        adjMatrix[1][1] = matrix[0][0] * multiplier;
    }

    return adjMatrix;
}

/**
* Returns a multidimensional array representing the multiplication of two 2x2
* matrices.
*/
double** Matrix::GetMultiplication2x2(double** leftMatrix,
    double** rightMatrix,
    int leftMatrixColumns,
    int rightMatrixRows)
{
    double** multiplicationMatrix = NULL;

    if (leftMatrix && rightMatrix && (leftMatrixColumns == rightMatrixRows))
    {
        multiplicationMatrix = CreateMatrix(2, 2);

        multiplicationMatrix[0][0] =
            (leftMatrix[0][0] * rightMatrix[0][0]) +
            (leftMatrix[0][1] * rightMatrix[1][0]);
        multiplicationMatrix[0][1] =
            (leftMatrix[0][0] * rightMatrix[0][1]) +
            (leftMatrix[0][1] * rightMatrix[1][1]);
        multiplicationMatrix[1][0] =
            (leftMatrix[1][0] * rightMatrix[0][0]) +
            (leftMatrix[1][1] * rightMatrix[1][0]);
        multiplicationMatrix[1][1] =
            (leftMatrix[1][0] * rightMatrix[0][1]) +
            (leftMatrix[1][1] * rightMatrix[1][1]);
    }

    return multiplicationMatrix;
}

/**
* Returns a multidimensional array representing the multiplication of a 2x2
* matrix, and a 2x1 matrix.
*/
double** Matrix::GetMultiplication2x1(double** leftMatrix,
    double** rightMatrix,
    int leftMatrixColumns,
    int rightMatrixRows)
{
    double** multiplicationMatrix = NULL;

    if (leftMatrix && rightMatrix && (leftMatrixColumns == rightMatrixRows))
    {
        multiplicationMatrix = CreateMatrix(2, 1);

        multiplicationMatrix[0][0] =
            (leftMatrix[0][0] * rightMatrix[0][0]) +
            (leftMatrix[0][1] * rightMatrix[1][0]);
        multiplicationMatrix[1][0] =
            (leftMatrix[1][0] * rightMatrix[0][0]) +
            (leftMatrix[1][1] * rightMatrix[1][0]);
    }

    return multiplicationMatrix;
}

/**
* Returns a multidimensional array representing the addition of two 2x2
* matrices.
*/
double** Matrix::GetAddition(double** leftMatrix,
    double** rightMatrix,
    int rows,
    int columns)
{
    double** additionMatrix = NULL;

    if (leftMatrix && rightMatrix)
    {
        additionMatrix = CreateMatrix(2, 2);

        for (int row = 0; row < rows; row++)
        {
            for (int column = 0; column < columns; column++)
            {
                additionMatrix[row][column] =
                    leftMatrix[row][column] + rightMatrix[row][column];
            }
        }
    }

    return additionMatrix;
}

/**
* Returns a multidimensional array representing the subtraction of two 2x2 matrices.
*/
double** Matrix::GetSubtraction(double** leftMatrix,
    double** rightMatrix,
    int rows,
    int columns)
{
    double** substractionMatrix = NULL;

    if (leftMatrix && rightMatrix)
    {
        substractionMatrix = CreateMatrix(2, 2);

        for (int row = 0; row < rows; row++)
        {
            for (int column = 0; column < columns; column++)
            {
                substractionMatrix[row][column] =
                    leftMatrix[row][column] - rightMatrix[row][column];
            }
        }
    }

    return substractionMatrix;
}
