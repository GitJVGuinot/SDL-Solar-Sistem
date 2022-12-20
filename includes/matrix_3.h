/// @author F.c.o Javier Guinot Almenar <guinotal@esat-alumni.com>

/** @file Matrix_3.h
 *--------------------------------------------------------------
 *  Math Library
 *  Matrix 3 Class Definition.
 *--------------------------------------------------------------
 *
 *   m0 m1 m2
 *   m3 m4 m5
 *   m6 m7 m8
 *
 *--------------------------------------------------------------
 */

////////////////////////
#ifndef __MATRIX_3_H__
#define __MATRIX_3_H__ 1
////////////////////////

#include "vector_2.h"
#include "vector_3.h"
#include <stdio.h>

/**
 * @class Mat3.
 *
 * @brief A 3x3 matrix class with basic operations.
 *
 * This class represents a 3x3 matrix and provides methods for basic operations
 * such as multiplication, addition, subtraction, and division. It also overloads
 * various operators for these operations.
*/
class Mat3
{
public:
  /**
   * @brief Prints the matrix to the console.
   *
   * @param name (Optional) Name of the matrix to print.
   */
  inline void print(char *name = (char *)"Mat3")
  {
    printf("%s:@n", name);
    printf("%f, %f, %f,@n", this->m[0], this->m[1], this->m[2]);
    printf("%f, %f, %f,@n", this->m[3], this->m[4], this->m[5]);
    printf("%f, %f, %f@n", this->m[6], this->m[7], this->m[8]);
  }

  /**
   * @brief Constructs a matrix with all elements set to the given value.
   *
   * @param value The value to set the matrix elements to.
   */
  Mat3(const float &value = 0);

  /**
   * @brief Constructs a matrix with the elements in the given array.
   *
   * @param value The array of matrix elements.
   */
  Mat3(const float value[9]);

  /**
   * @brief Constructs a matrix with the given vectors as its rows.
   *
   * @param a The first row of the matrix.
   * @param b The second row of the matrix.
   * @param c The third row of the matrix.
   */
  Mat3(const Vec3 &a, const Vec3 &b, const Vec3 &c);

  /**
   * @brief Constructs a matrix with the elements of the given matrix.
   *
   * @param copy The matrix to copy the elements from.
   */
  Mat3(const Mat3 &copy);

  /**
   * @brief Destructor for the matrix.
   */
  ~Mat3();

  /**
   * @brief Returns a new matrix that is the element-wise sum of the calling matrix and the given matrix.
   *
   * @param other The matrix to add to the calling matrix.
   *
   * @return The element-wise sum of the two matrices.
   */
  inline Mat3 Sum(const Mat3 &other) const
  {
    float ret[9];
    for (int i = 0; i < 9; i++)
      ret[i] = this->m[i] + other.m[i];
    return Mat3(ret);
  }

  /**
   * @brief Returns a new matrix that is the element-wise sum of the calling matrix and the given value.
   *
   * @param value The value to add to the matrix elements.
   *
   * @return The element-wise sum of the matrix and the value.
   */
  inline Mat3 Sum(float value) const
  {
    float ret[9];
    for (int i = 0; i < 9; i++)
      ret[i] = this->m[i] + value;
    return Mat3(ret);
  }

  /**
   * @brief Subtracts the given matrix from this matrix.
   *
   * @param other The matrix to subtract.
   *
   * @return A new matrix containing the result.
   */
  inline Mat3 Substract(const Mat3 &other) const
  {
    float ret[9];
    for (int i = 0; i < 9; i++)
      ret[i] = this->m[i] - other.m[i];
    return Mat3(ret);
  }

  /**
   * @brief Subtracts the given value from every element in this matrix.
   *
   * @param value The value to subtract.
   *
   * @return A new matrix containing the result.
   */
  inline Mat3 Substract(float value) const
  {
    float ret[9];
    for (int i = 0; i < 9; i++)
      ret[i] = this->m[i] - value;
    return Mat3(ret);
  }

  /**
   * @brief Multiplies this matrix by the given matrix.
   *
   * @param other The matrix to multiply by.
   *
   * @return A new matrix containing the result.
   */
  inline Mat3 Multiply(const Mat3 &other) const
  {
    float a[9];

    a[0] = (this->m[0] * other.m[0]) + (this->m[3] * other.m[1]) + (this->m[6] * other.m[2]);
    a[1] = (this->m[1] * other.m[0]) + (this->m[4] * other.m[1]) + (this->m[7] * other.m[2]);
    a[2] = (this->m[2] * other.m[0]) + (this->m[5] * other.m[1]) + (this->m[8] * other.m[2]);
    a[3] = (this->m[0] * other.m[3]) + (this->m[3] * other.m[4]) + (this->m[6] * other.m[5]);
    a[4] = (this->m[1] * other.m[3]) + (this->m[4] * other.m[4]) + (this->m[7] * other.m[5]);
    a[5] = (this->m[2] * other.m[3]) + (this->m[5] * other.m[4]) + (this->m[8] * other.m[5]);
    a[6] = (this->m[0] * other.m[6]) + (this->m[3] * other.m[7]) + (this->m[6] * other.m[8]);
    a[7] = (this->m[1] * other.m[6]) + (this->m[4] * other.m[7]) + (this->m[7] * other.m[8]);
    a[8] = (this->m[2] * other.m[6]) + (this->m[5] * other.m[7]) + (this->m[8] * other.m[8]);

    return Mat3(a);
  }

  /*
   * @brief Multiplies the matrix by a scalar value.
   *
   * @param value The scalar value to multiply the matrix by.
   *
   * @return The resulting matrix after the multiplication.
  */
  inline Mat3 Multiply(float value) const
  {
    float ret[9];
    for (int i = 0; i < 9; i++)
      ret[i] = this->m[i] * value;
    return Mat3(ret);
  }

  /**
   * @brief Divides the matrix by a scalar value.
   *
   * @param value The scalar value to divide the matrix by.
   *
   * @return The resulting matrix after the division.
  */
  inline Mat3 Divide(float value) const
  {
    float ret[9];
    for (int i = 0; i < 9; i++)
      ret[i] = this->m[i] / value;
    return Mat3(ret);
  }

  // Operators
  /**
   * @brief Overloads the + operator to perform matrix addition.
   *
   * @param other The matrix to add to the current matrix.
   *
   * @return The resulting matrix after the addition.
  */
  inline Mat3 operator+(const Mat3 &other) const
  {
    return Sum(other);
  }

  /**
   * @brief Overloads the += operator to perform matrix addition and assignment.
   *
   * @param other The matrix to add to the current matrix.
   *
   * @return The current matrix after the addition and assignment.
  */
  inline Mat3 &operator+=(const Mat3 &other)
  {
    Mat3 ret = Sum(other);
    for (int i = 0; i < 9; i++)
      this->m[i] = ret.m[i];
    return (*this);
  }

  /**
   * @brief Overloads the + operator to perform scalar addition.
   *
   * @param value The scalar value to add to the current matrix.
   *
   * @return The resulting matrix after the addition.
  */
  inline Mat3 operator+(float value) const
  {
    return Sum(value);
  }

  /**
   * @brief Overloads the += operator to perform scalar addition and assignment.
   *
   * @param value The scalar value to add to the current matrix.
   *
   * @return The current matrix after the addition and assignment.
  */
  inline Mat3 &operator+=(float value)
  {
    Mat3 ret = Sum(value);
    for (int i = 0; i < 9; i++)
      this->m[i] = ret.m[i];
    return (*this);
  }

  /**
   * @brief Overloads the - operator to perform matrix subtraction.
   *
   * @param other The matrix to subtract from the current matrix.
   *
   * @return The resulting matrix after the subtraction.
  */
  inline Mat3 operator-(const Mat3 &other) const
  {
    return Substract(other);
  }

  /**
   * @brief Overloads the -= operator to perform matrix subtraction and assignment.
   *
   * @param other The matrix to subtract from the current matrix.
   *
   * @return The current matrix after the subtraction and assignment.
  */
  inline Mat3 &operator-=(const Mat3 &other)
  {
    Mat3 ret = Substract(other);
    for (int i = 0; i < 9; i++)
      this->m[i] = ret.m[i];
    return (*this);
  }

  /**
   * @brief Overloads the - operator to perform scalar subtraction.
   *
   * @param value The scalar value to subtract from the current matrix.
   *
   * @return The resulting matrix after the subtraction
  */
  inline Mat3 operator-(float value) const
  {
    return Substract(value);
  }

  /**
   * @brief Subtracts a value from all elements in the matrix.
   *
   * @param value The value to subtract from the matrix elements.
   *
   * @return A reference to the matrix.
  */
  inline Mat3 &operator-=(float value)
  {
    Mat3 ret = Substract(value);
    for (int i = 0; i < 9; i++)
      this->m[i] = ret.m[i];
    return (*this);
  }

  /**
   * @brief Multiplies the matrix by another matrix.
   *
   * @param other The other matrix.
   *
   * @return The result of the multiplication.
   */
  inline Mat3 operator*(const Mat3 &other) const
  {
    return Multiply(other);
  }

  /**
   * @brief Multiplies the matrix by another matrix and assigns the result to the matrix.
   *
   * @param other The other matrix.
   *
   * @return A reference to the matrix.
  */
  inline Mat3 &operator*=(const Mat3 &other)
  {
    Mat3 ret = Multiply(other);
    for (int i = 0; i < 9; i++)
      this->m[i] = ret.m[i];
    return (*this);
  }

  /**
   * @brief Multiplies the matrix by a value.
   *
   * @param value The value to multiply the matrix by.
   *
   * @return The result of the multiplication.
   */
  inline Mat3 operator*(float value) const
  {
    return Multiply(value);
  }

  /**
   * @brief Multiplies the matrix by a value and assigns the result to the matrix.
   *
   * @param value The value to multiply the matrix by.
   *
   * @return A reference to the matrix.
   */
  inline Mat3 &operator*=(float value)
  {
    Mat3 ret = Multiply(value);
    for (int i = 0; i < 9; i++)
      this->m[i] = ret.m[i];
    return (*this);
  }

  /**
   * @brief Divides the matrix by a value.
   *
   * @param value The value to divide the matrix by.
   *
   * @return The result of the division.
   */
  inline Mat3 operator/(float value) const
  {
    return Divide(value);
  }

  /**
   * @brief Divides the matrix by a value and assigns the result to the matrix.
   *
   * @param value The value to divide the matrix by.
   *
   * @return A reference to the matrix.
   */
  inline Mat3 &operator/=(float value)
  {
    Mat3 ret = Divide(value);
    for (int i = 0; i < 9; i++)
      this->m[i] = ret.m[i];
    return (*this);
  }

  /**
   * @brief Compares the matrix to another matrix for equality.
   *
   * @param other The other matrix to compare to.
   *
   * @return `true` if the matrices are equal, `false` otherwise.
   */
  inline bool operator==(const Mat3 &other) const
  {
    for (int i = 0; i < 9; ++i)
    {
      if (this->m[i] != other.m[i])
      {
        return false;
      }
    }
    return true;
  }

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
  inline bool operator!=(const Mat3 &other) const
  {
    for (int i = 0; i < 9; ++i)
    {
      if (this->m[i] != other.m[i])
      {
        return true;
      }
    }
    return false;
  }

  /**
   * @brief Assign the matrix to another matrix.
   *
   * @param other The other matrix to assign from.
   *
   * This function assigns each element of the other matrix to the corresponding
   * element of this matrix.
   */
  inline void operator=(const Mat3 &other)
  {
    for (int i = 0; i < 9; i++)
      this->m[i] = other.m[i];
  }

  /**
   * @brief Get the identity matrix.
   *
   * @return The identity matrix.
   *
   * The identity matrix is a 3x3 matrix with 1s on the diagonal and 0s
   * everywhere else.
   */
  static Mat3 Identity();

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
   * @brief Get the determinant of a 3x3 matrix.
   *
   * @param value The elements of the matrix in row-major order.
   *
   * @return The determinant of the matrix.
   *
   * This function calculates the determinant of a 3x3 matrix using the same
   * formula as the Determinant() function for the `Mat3` class. It can be used
   * to calculate the determinant of a matrix that is not an instance of the
   * `Mat3` class.
   */
  static float Determinant(float value[9]);

  /**
   * @brief Get the adjoint matrix of the matrix.
   *
   * @return The adjoint matrix.
   *
   * The adjoint matrix is the transpose of the matrix of cofactors of the
   * original matrix. It is used in the calculation of the inverse of a matrix.
   */
  Mat3 Adjoint() const;

  /**
   * @brief Get the inverse of the matrix.
   *
   * @param out The output matrix to store the inverse.
   *
   * @return True if the inverse could be calculated, false otherwise.
   *
   * This function calculates the inverse of the matrix and stores it in the
   * specified output matrix. It returns false if the determinant of the matrix
   * is zero, in which case the matrix is not invertible.
  */
  bool GetInverse(Mat3 &out) const;

  /**
   * @brief Calculates the inverse of the matrix.
   *
   * @return True if the inverse was successfully calculated, false if the
   * matrix is singular.
  */
  bool Inverse();

  /**
   * @brief Calculates the transpose of the matrix.
   *
   * @return The transpose of the matrix.
   */
  Mat3 Transpose() const;

  /**
   * @brief Creates a translation matrix.
   *
   * @param position The translation vector.
   *
   * @return The translation matrix.
   */
  static Mat3 Translate(const Vec2 &position);

  /**
   * @brief Creates a translation matrix.
   *
   * @param x The x-coordinate of the translation vector.
   * @param y The y-coordinate of the translation vector.
   *
   * @return The translation matrix.
   */
  static Mat3 Translate(float x, float y);

  /**
   * @brief Creates a scaling matrix.
   *
   * @param scale The scaling vector.
   *
   * @return The scaling matrix.
   */
  static Mat3 Scale(const Vec2 &scale);


  /**
   * @brief Creates a rotation matrix.
   *
   * @param rotation The angle of rotation, in radians.
   *
   * @return The rotation matrix.
   */
  static Mat3 Rotate(float rotation);

  /**
   * @brief Retrieves a column of the matrix.
   *
   * @param colum The index of the column to retrieve (0-based).
   *
   * @return The column of the matrix.
   */
  Vec3 GetColum(int colum) const;

  /**
   * @brief Retrieves a row of the matrix.
   *
   * @param line The index of the row to retrieve (0-based).
   *
   * @return The row of the matrix.
   */
  Vec3 GetLine(int line) const;

  /**
   * @brief The matrix elements, stored in row-major order.
   */
  float m[9];
};

////////////////////////
#endif /* __MATRIX_3_H__ */
////////////////////////
