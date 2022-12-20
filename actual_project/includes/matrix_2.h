/// @author Marcos Jiménez Saz <jimenezsa@esat-alumni.com>

/** @file Matrix_2.h
 *--------------------------------------------------------------
 *  Math Library
 *  Matrix 2 Class Definition.
 *--------------------------------------------------------------
 *
 *   m0 m1
 *   m2 m3
 *
 *--------------------------------------------------------------
 */

////////////////////////
#ifndef __MATRIX_2_H__
#define __MATRIX_2_H__ 1
////////////////////////

#include "vector_2.h"
#include <iostream>

/**
 * @class Mat2
 *
 * @brief A 2x2 matrix class with basic operations.
 *
 * This class represents a 2x2 matrix and provides methods for basic operations such as multiplication, addition, subtraction, and division. It also overloads various operators for these operations.
*/
class Mat2
{
public:
  /**
   * @brief Prints the matrix to the console.
   *
   * @param name (Optional) Name of the matrix to print.
   */
  inline void print(char *name = (char *)"Mat2")
  {
    printf("%s:\n", name);
    printf("%f, %f,\n", this->m[0], this->m[1]);
    printf("%f, %f\n", this->m[2], this->m[3]);
  }

  /**
   * @brief Constructs a matrix with all elements set to the given value.
   *
   * @param value The value to set the matrix elements to.
   */
  Mat2(const float &value = 0);

  /**
   * @brief Constructs a matrix with the elements in the given array.
   *
   * @param a The array of matrix elements.
   */
  Mat2(const float a[4]);

  /**
   * @brief Constructs a matrix with the given vectors as its rows.
   *
   * @param a The first row of the matrix.
   * @param b The second row of the matrix.
   */
  Mat2(const Vec2 &a, const Vec2 &b);

  /**
   * @brief Constructs a matrix with the elements of the given matrix.
   *
   * @param copy The matrix to copy the elements from.
   */
  Mat2(const Mat2 &copy);

  /**
   * @brief Destructor for the matrix.
   */
  ~Mat2();

  /**
   * @brief Get the identity matrix.
   *
   * @return The identity matrix.
   *
   * The identity matrix is a 2x2 matrix with 1s on the diagonal and 0s
   * everywhere else.
   */
  static Mat2 Identity();

  /**
   * @brief Get the determinant of the matrix.
   *
   * @return The determinant of the matrix.
   *
   * The determinant is a scalar value that can be used to characterize the
   * matrix. It is calculated as the sum of the products of the elements of
   * any one row or column and the cofactors of the elements of the other row
   * or column.
   */
  float Determinant() const;

  /**
   * @brief Get the determinant of a 2x2 matrix.
   *
   * @param val The elements of the matrix in row-major order.
   *
   * @return The determinant of the matrix.
   *
   * This function calculates the determinant of a 2x2 matrix using the same
   * formula as the Determinant() function for the `Mat2` class. It can be used
   * to calculate the determinant of a matrix that is not an instance of the
   * `Mat2` class.
   */
  static float Determinant(float val[4]);

  /**
   * @brief Get the adjoint matrix of the matrix.
   *
   * @return The adjoint matrix.
   *
   * The adjoint matrix is the transpose of the matrix of cofactors of the
   * original matrix. It is used in the calculation of the inverse of a matrix.
   */
  Mat2 Adjoint() const;

  /**
   * @brief Retrieves a row of the matrix.
   *
   * @param line The index of the row to retrieve (0-based).
   *
   * @return The row of the matrix.
   */
  Vec2 GetLine(int line) const;

  /**
   * @brief Retrieves a column of the matrix.
   *
   * @param colum The index of the column to retrieve (0-based).
   *
   * @return The column of the matrix.
   */
  Vec2 GetColum(int line) const;

  /**
   * @brief Calculates the inverse of the matrix.
   *
   * @return True if the inverse was successfully calculated, false if the
   * matrix is singular.
  */
  Mat2 Inverse() const;

  /**
   * @brief Calculates the transpose of the matrix.
   *
   * @return The transpose of the matrix.
   */
  Mat2 Transpose() const;

  /**
   * @brief Overloads the + operator to perform matrix addition.
   *
   * @param other The matrix to add to the current matrix.
   *
   * @return The resulting matrix after the addition.
  */
  inline Mat2 operator+(const Mat2 &other) const;

  /**
   * @brief Overloads the += operator to perform matrix addition and assignment.
   *
   * @param other The matrix to add to the current matrix.
   *
   * @return The current matrix after the addition and assignment.
  */
  inline Mat2 &operator+=(const Mat2 &other);

  /**
   * @brief Returns a new matrix that is the element-wise sum of the calling matrix and the given matrix.
   *
   * @param other The matrix to add to the calling matrix.
   * @return The element-wise sum of the two matrices.
   */
  inline Mat2 Sum(const Mat2 &other) const;

  /**
   * @brief Overloads the + operator to perform scalar addition.
   *
   * @param value The scalar value to add to the current matrix.
   *
   * @return The resulting matrix after the addition.
  */
  inline Mat2 operator+(float value) const;

  /**
   * @brief Overloads the += operator to perform scalar addition and assignment.
   *
   * @param value The scalar value to add to the current matrix.
   *
   * @return The current matrix after the addition and assignment.
  */
  inline Mat2 &operator+=(float value);

  /**
   * @brief Returns a new matrix that is the element-wise sum of the calling matrix and the given value.
   *
   * @param value The value to add to the matrix elements.
   *
   * @return The element-wise sum of the matrix and the value.
   */
  inline Mat2 Sum(float value) const;

  /**
   * @brief Overloads the - operator to perform matrix subtraction.
   *
   * @param other The matrix to subtract from the current matrix.
   *
   * @return The resulting matrix after the subtraction.
  */
  inline Mat2 operator-(const Mat2 &other) const;

  /**
   * @brief Overloads the -= operator to perform matrix subtraction and assignment.
   *
   * @param other The matrix to subtract from the current matrix.
   *
   * @return The current matrix after the subtraction and assignment.
  */
  inline Mat2 &operator-=(const Mat2 &other);

  /**
   * @brief Subtracts the given matrix from this matrix.
   *
   * @param other The matrix to subtract.
   *
   * @return A new matrix containing the result.
   */
  inline Mat2 Substract(const Mat2 &other) const;

  /**
   * @brief Overloads the - operator to perform scalar subtraction.
   *
   * @param value The scalar value to subtract from the current matrix.
   *
   * @return The resulting matrix after the subtraction
  */
  inline Mat2 operator-(float value) const;

  /**
   * @brief Subtracts a value from all elements in the matrix.
   *
   * @param value The value to subtract from the matrix elements.
   *
   * @return A reference to the matrix.
  */
  inline Mat2 &operator-=(float value);

  /**
   * @brief Subtracts the given value from every element in this matrix.
   *
   * @param value The value to subtract.
   *
   * @return A new matrix containing the result.
   */
  inline Mat2 Substract(float value) const;

  /**
   * @brief Multiplies the matrix by another matrix.
   *
   * @param other The other matrix.
   *
   * @return The result of the multiplication.
   */
  inline Mat2 operator*(const Mat2 &other) const;

  /**
   * @brief Multiplies the matrix by another matrix and assigns the result to the matrix.
   *
   * @param other The other matrix.
   *
   * @return A reference to the matrix.
  */
  inline Mat2 &operator*=(const Mat2 &other);

  /**
   * @brief Multiplies this matrix by the given matrix.
   *
   * @param other The matrix to multiply by.
   *
   * @return A new matrix containing the result.
   */
  inline Mat2 Multiply(const Mat2 &other) const;

  /**
   * @brief Multiplies the matrix by a value.
   *
   * @param value The value to multiply the matrix by.
   *
   * @return The result of the multiplication.
   */
  inline Mat2 operator*(float value) const;

  /**
   * @brief Multiplies the matrix by a value and assigns the result to the matrix.
   *
   * @param value The value to multiply the matrix by.
   *
   * @return A reference to the matrix.
   */
  inline Mat2 &operator*=(float value);

  /*
   * @brief Multiplies the matrix by a scalar value.
   *
   * @param value The scalar value to multiply the matrix by.
   *
   * @return The resulting matrix after the multiplication.
  */
  inline Mat2 Multiply(float value) const;

  /**
   * @brief Divides the matrix by a value.
   *
   * @param value The value to divide the matrix by.
   *
   * @return The result of the division.
   */
  inline Mat2 operator/(float value) const;

  /**
   * @brief Divides the matrix by a value and assigns the result to the matrix.
   *
   * @param value The value to divide the matrix by.
   *
   * @return A reference to the matrix.
   */
  inline Mat2 &operator/=(float value);

  /**
   * @brief Divides the matrix by a scalar value.
   *
   * @param value The scalar value to divide the matrix by.
   *
   * @return The resulting matrix after the division.
  */
  inline Mat2 Divide(float value) const;

  /**
   * @brief Compares the matrix to another matrix for equality.
   *
   * @param other The other matrix to compare to.
   *
   * @return `true` if the matrices are equal, `false` otherwise.
   */
  bool operator==(const Mat2 &other) const;

  /**
   * @brief Check if the matrix is not equal to another matrix.
   *
   * @param other The other matrix to compare with.
   *
   * @return True if the matrices are not equal, false otherwise.
   *
   * This function compares each element of the matrix with the corresponding
   * element of the other matrix and returns true if any element is different.
   */
  bool operator!=(const Mat2 &other) const;

  /**
   * @brief Assign the matrix to another matrix.
   *
   * @param other The other matrix to assign from.
   *
   * This function assigns each element of the other matrix to the corresponding
   * element of this matrix.
   */
  inline void operator=(const Mat2 &other);

  /**
   * @brief The matrix elements, stored in row-major order.
   */
  float m[4];
};

////////////////////////
#endif /* __MATRIX_2_H__ */
////////////////////////
