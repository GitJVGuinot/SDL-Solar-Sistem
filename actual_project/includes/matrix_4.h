/// @author F.c.o Javier Guinot Almenar <guinotal@esat-alumni.com>

/** @file Matrix_4.h
 *--------------------------------------------------------------
 *  Math Library
 *  Matrix 3 Class Definition.
 *--------------------------------------------------------------
 *
 *   m0  m1  m2  m3
 *   m4  m5  m6  m7
 *   m8  m9  m10 m11
 *   m12 m13 m14 m15
 *
 *--------------------------------------------------------------
 */

////////////////////////
#ifndef __MATRIX_4_H__
#define __MATRIX_4_H__ 1
////////////////////////

#include "vector_3.h"
#include "vector_4.h"
#include "matrix_3.h"
#include <stdio.h>

/**
 * @class Mat4
 * @brief A class representing a 4x4 matrix.
 *
 * The Mat4 class represents a 4x4 matrix, which is a mathematical object
 * used to represent transformations in 3D space. It consists of 16 elements,
 * arranged in a 4x4 grid, and can be used to perform operations such as
 * translation, scaling, and rotation.
 */
class Mat4
{
public:

  /**
   * @brief Prints the matrix to the console.
   *
   * This function prints the matrix to the console, with the given name
   * displayed as a label.
   *
   * @param name The name of the matrix to be displayed.
   */
  inline void print(char *name = (char *)"Mat4")
  {
    printf("%s:@n", name);
    printf("%f, %f, %f, %f,@n", this->m[0], this->m[1], this->m[2], this->m[3]);
    printf("%f, %f, %f, %f,@n", this->m[4], this->m[5], this->m[6], this->m[7]);
    printf("%f, %f, %f, %f,@n", this->m[8], this->m[9], this->m[10], this->m[11]);
    printf("%f, %f, %f, %f@n", this->m[12], this->m[13], this->m[14], this->m[15]);
  }

  /**
   * @brief Constructs a new matrix with all elements initialized to the given value.
   *
   * @param value The value to initialize all elements to.
   */
  Mat4(const float &value = 0);

  /**
   * @brief Constructs a new matrix with elements initialized to the values in the given array.
   *
   * @param a The array of values to initialize the matrix with.
   */
  Mat4(const float a[16]);

  /**
   * @brief Constructs a new matrix with elements initialized to the values in the given column vectors.
   *
   * @param a The first column vector.
   * @param b The second column vector.
   * @param c The third column vector.
   * @param d The fourth column vector.
 */
  Mat4(const Vec4 &a, const Vec4 &b, const Vec4 &c, const Vec4 &d);

  /**
   * @brief Constructs a new matrix as a copy of the given matrix.
   *
   * @param copy The matrix to copy.
   */
  Mat4(const Mat4 &copy);

  /**
   * @brief Destroys the matrix.
   */
  ~Mat4();

  /**
   * @brief Returns the identity matrix.
   *
   * The identity matrix is a matrix with all elements initialized to zero, except for
   * the main diagonal (top-left to bottom-right) which is initialized to 1.
   *
   * @return The identity matrix.
   */
  static Mat4 Identity();

  /**
   * @brief Returns the projection matrix.
   *
   * The projection matrix is used to transform 3D coordinates into 2D coordinates,
   * as they will be displayed on the screen.
   *
   * @return The projection matrix.
   */
  static Mat4 Projection();

  /**
   * @brief Calculates the determinant of the matrix.
   *
   * The determinant is a scalar value that can be used to determine the invertibility
   * of a matrix.
   *
   * @return The determinant of the matrix.
   */
  float Determinant() const;

  /**
   * @brief Computes the adjoint of this matrix.
   * @return The adjoint matrix.
   * The adjoint matrix is the transpose of the cofactor matrix. It is used
   * in the computation of the inverse matrix.
   */
  Mat4 Adjoint() const;

  /**
   * @brief Computes the inverse of this matrix.
   * @param[out] out The inverse matrix.
   * @return True if the inverse could be computed, false otherwise.
   * This function computes the inverse of this matrix and stores the result
   * in the specified output parameter. The inverse matrix is used to
   * "undo" the transformation represented by this matrix. If the matrix is
   * not invertible (e.g. it is degenerate or singular), the function
   * returns false and does not modify the output parameter.
*/
  bool GetInverse(Mat4 &out) const;

  /**
   * @brief Computes the inverse of this matrix.
   * @return True if the inverse could be computed, false otherwise.
   * This function computes the inverse of this matrix and overwrites the
   * current matrix with the result. If the matrix is not invertible (e.g.
   * it is degenerate or singular), the function returns false and does not
   * modify the matrix.
   * */
  bool Inverse();

  /**
   * @brief Computes the transpose of this matrix.
   * @return The transposed matrix.
   * The transpose of a matrix is obtained by swapping its rows and columns.
   */
  Mat4 Transpose() const;

  /**
   * @brief Creates a translation matrix from a displacement vector.
   * @param[in] distance The displacement vector.
   * @return The translation matrix.
   * This function generates a 4x4 matrix that represents a translation
   * transformation. The translation is specified by the displacement vector
   * distance.
  */
  static Mat4 Translate(const Vec3 &distance);

  /**
   * @brief Creates a translation matrix from displacement components.
   * @param[in] x The x-axis displacement.
   * @param[in] y The y-axis displacement.
   * @param[in] z The z-axis displacement.
   * @return The translation matrix.
   * This function generates a 4x4 matrix that represents a translation
   * transformation. The translation is specified by the displacement
   * components x, y, and z.
   */
  static Mat4 Translate(float x, float y, float z);

  /**
   * @brief Generates a scaling matrix for the given x, y, and z scale factors.
   *
   * @param x The x scale factor.
   * @param y The y scale factor.
   * @param z The z scale factor.
   *
   * @return The scaling matrix.
   */
  static Mat4 Scale(const Vec3 &scale);

  /**
   * @brief Generates a scaling matrix for the given scale vector.
   *
   * @param scale The scale vector.
   *
   * @return The scaling matrix.
   */
  static Mat4 Scale(float x, float y, float z);

  /**
   * @brief Generates a rotation matrix for rotation around the x axis.
   *
   * @param radians The angle of rotation in radians.
   *
   * @return The rotation matrix.
   */
  static Mat4 RotateX(float radians);

  /**
   * @brief Generates a rotation matrix for rotation around the y axis.
   *
   * @param radians The angle of rotation in radians.
   *
   * @return The rotation matrix.
   */
  static Mat4 RotateY(float radians);

  /**
   * @brief Generates a rotation matrix for rotation around the z axis.
   *
   * @param radians The angle of rotation in radians.
   *
   * @return The rotation matrix.
   */
  static Mat4 RotateZ(float radians);

  /**
   * @brief Generates a transformation matrix for the given translation,
   * scale, and rotation values.
   *
   * @param translate The translation vector.
   * @param scale The scale vector.
   * @param rotateX The angle of rotation around the x axis in radians.
   * @param rotateY The angle of rotation around the y axis in radians.
   * @param rotateZ The angle of rotation around the z axis in radians.
   *
   * @return The transformation matrix.
   */
  static Mat4 GetTransform(const Vec3 &translate, const Vec3 &scale,
                           float rotateX, float rotateY, float rotateZ);

  /**
   * @brief Returns a 4x4 matrix that represents a combination of translation, scale, and rotation transformations.
   * @param trans_x The x-coordinate of the translation.
   * @param trans_y The y-coordinate of the translation.
   * @param trans_z The z-coordinate of the translation.
   * @param scale_x The x-coordinate of the scale.
   * @param scale_y The y-coordinate of the scale.
   * @param scale_Z The z-coordinate of the scale.
   * @param rotateX The angle of rotation around the x-axis, in degrees.
   * @param rotateY The angle of rotation around the y-axis, in degrees.
   * @param rotateZ The angle of rotation around the z-axis, in degrees.
   * @return A 4x4 matrix that represents the combination of the specified transformations.
   */
  static Mat4 GetTransform(float trans_x, float trans_y, float trans_z,
                           float scale_x, float scale_y, float scale_Z,
                           float rotateX, float rotateY, float rotateZ);

  /**
   * @brief Returns a 4x4 perspective projection matrix.
   * @param fov The field of view, in degrees.
   * @param aspect The aspect ratio (width divided by height).
   * @param near The distance of the near clipping plane.
   * @param far The distance of the far clipping plane.
   * @return A 4x4 perspective projection matrix.
   */
  Mat4 PerspectiveMatrix(float fov, float aspect,
                         float near, float far) const;

  /**
   * @brief Returns a 4x4 orthographic projection matrix.
   * @param right The x-coordinate of the right edge of the view volume.
   * @param left The x-coordinate of the left edge of the view volume.
   * @param top The y-coordinate of the top edge of the view volume.
   * @param bottom The y-coordinate of the bottom edge of the view volume.
   * @param near The distance of the near clipping plane.
   * @param far The distance of the far clipping plane.
   * @return A 4x4 orthographic projection matrix.
   */
  Mat4 OrthoMatrix(float right, float left, float top, float bottom,
                   float near, float far) const;

  /**
   * @brief Returns the specified column of the matrix as a Vec4.
   * @param colum The index of the column to retrieve (0-based).
   * @return The specified column of the matrix as a Vec4.
   */
  Vec4 GetColum(int colum) const;

  /**
   * @brief Retrieves a specific line from the matrix.
   * @param line The line to retrieve (0-based).
   * @return The requested line as a Vec4 object.
   */
  Vec4 GetLine(int line) const;

  /**
   * @brief Sums this matrix with another matrix.
   * @param other The other matrix to sum with.
   * @return The result of the sum as a new Mat4 object.
   */
  inline Mat4 Sum(const Mat4 &other) const
  {
    float ret[16];
    for (int i = 0; i < 16; i++)
      ret[i] = this->m[i] + other.m[i];
    return Mat4(ret);
  }

  /**
   * @brief Sums this matrix with a scalar value.
   * @param value The scalar value to sum with.
   * @return The result of the sum as a new Mat4 object.
   */
  inline Mat4 Sum(float value) const
  {
    float ret[16];
    for (int i = 0; i < 16; i++)
      ret[i] = this->m[i] + value;
    return Mat4(ret);
  }

  /**
   * @brief Subtracts another matrix from this matrix.
   * @param other The other matrix to subtract.
   * @return The result of the subtraction as a new Mat4 object.
   */
  inline Mat4 Substract(const Mat4 &other) const
  {
    float ret[16];
    for (int i = 0; i < 16; i++)
      ret[i] = this->m[i] - other.m[i];
    return Mat4(ret);
  }

  /**
   * @brief Subtracts a scalar value from this matrix.
   * @param value The scalar value to subtract.
   * @return The result of the subtraction as a new Mat4 object.
   */
  inline Mat4 Substract(float value) const
  {
    float ret[16];
    for (int i = 0; i < 16; i++)
      ret[i] = this->m[i] - value;
    return Mat4(ret);
  }

  /**
   * @brief Multiplies this matrix with another matrix.
   * @param other The other matrix to multiply with.
   * @return The result of the multiplication as a new Mat4 object.
   */
  inline Mat4 Multiply(const Mat4 &other) const
  {
    float a[16];

    a[0] = (this->m[0] * other.m[0]) + (this->m[4] * other.m[1]) + (this->m[8] * other.m[2]) + (this->m[12] * other.m[3]);
    a[1] = (this->m[1] * other.m[0]) + (this->m[5] * other.m[1]) + (this->m[9] * other.m[2]) + (this->m[13] * other.m[3]);
    a[2] = (this->m[2] * other.m[0]) + (this->m[6] * other.m[1]) + (this->m[10] * other.m[2]) + (this->m[14] * other.m[3]);
    a[3] = (this->m[3] * other.m[0]) + (this->m[7] * other.m[1]) + (this->m[11] * other.m[2]) + (this->m[15] * other.m[3]);
    a[4] = (this->m[0] * other.m[4]) + (this->m[4] * other.m[5]) + (this->m[8] * other.m[6]) + (this->m[12] * other.m[7]);
    a[5] = (this->m[1] * other.m[4]) + (this->m[5] * other.m[5]) + (this->m[9] * other.m[6]) + (this->m[13] * other.m[7]);
    a[6] = (this->m[2] * other.m[4]) + (this->m[6] * other.m[5]) + (this->m[10] * other.m[6]) + (this->m[14] * other.m[7]);
    a[7] = (this->m[3] * other.m[4]) + (this->m[7] * other.m[5]) + (this->m[11] * other.m[6]) + (this->m[15] * other.m[7]);
    a[8] = (this->m[0] * other.m[8]) + (this->m[4] * other.m[9]) + (this->m[8] * other.m[10]) + (this->m[12] * other.m[11]);
    a[9] = (this->m[1] * other.m[8]) + (this->m[5] * other.m[9]) + (this->m[9] * other.m[10]) + (this->m[13] * other.m[11]);
    a[10] = (this->m[2] * other.m[8]) + (this->m[6] * other.m[9]) + (this->m[10] * other.m[10]) + (this->m[14] * other.m[11]);
    a[11] = (this->m[3] * other.m[8]) + (this->m[7] * other.m[9]) + (this->m[11] * other.m[10]) + (this->m[15] * other.m[11]);
    a[12] = (this->m[0] * other.m[12]) + (this->m[4] * other.m[13]) + (this->m[8] * other.m[14]) + (this->m[12] * other.m[15]);
    a[13] = (this->m[1] * other.m[12]) + (this->m[5] * other.m[13]) + (this->m[9] * other.m[14]) + (this->m[13] * other.m[15]);
    a[14] = (this->m[2] * other.m[12]) + (this->m[6] * other.m[13]) + (this->m[10] * other.m[14]) + (this->m[14] * other.m[15]);
    a[15] = (this->m[3] * other.m[12]) + (this->m[7] * other.m[13]) + (this->m[11] * other.m[14]) + (this->m[15] * other.m[15]);

    return Mat4(a);
  }

  /**
   * @brief Multiply the matrix by a scalar value
   * @param value The scalar value to multiply the matrix by
   * @return The resulting matrix
   */
  inline Mat4 Multiply(float value) const
  {
    float ret[16];
    for (int i = 0; i < 16; i++)
      ret[i] = this->m[i] * value;
    return Mat4(ret);
  }

  /**
   * @brief Divide the matrix by a scalar value
   * @param value The scalar value to divide the matrix by
   * @return The resulting matrix
   */
  inline Mat4 Divide(float value) const
  {
    float ret[16];
    for (int i = 0; i < 16; i++)
      ret[i] = this->m[i] / value;
    return Mat4(ret);
  }

  /**
   * @brief Add two matrices together
   * @param other The matrix to add to the current matrix
   * @return The resulting matrix
   */
  inline Mat4 operator+(const Mat4 &other) const
  {
    return Sum(other);
  }

  /**
   * @brief Add a matrix to the current matrix
   * @param other The matrix to add to the current matrix
   * @return A reference to the current matrix
   */
  inline Mat4 &operator+=(const Mat4 &other)
  {
    Mat4 ret = Sum(other);
    for (int i = 0; i < 16; i++)
      this->m[i] = ret.m[i];
    return (*this);
  }

  /**
   * @brief Add a scalar value to the matrix
   * @param value The scalar value to add to the matrix
   * @return The resulting matrix
   */
  inline Mat4 operator+(float value) const
  {
    return Sum(value);
  }

  /**
   * @brief Add a scalar value to the current matrix
   * @param value The scalar value to add to the matrix
   * @return A reference to the current matrix
   */
  inline Mat4 &operator+=(float value)
  {
    Mat4 ret = Sum(value);
    for (int i = 0; i < 16; i++)
      this->m[i] = ret.m[i];
    return (*this);
  }

  /**
   * @brief Subtract one matrix from another
   * @param other The matrix to subtract from the current matrix
   * @return The resulting matrix
   */
  inline Mat4 operator-(const Mat4 &other) const
  {
    return Substract(other);
  }

  /**
   * @brief Subtract a matrix from the current matrix
   * @param other The matrix to subtract from the current matrix
   * @return A reference to the current matrix
   */
  inline Mat4 &operator-=(const Mat4 &other)
  {
    Mat4 ret = Substract(other);
    for (int i = 0; i < 16; i++)
      this->m[i] = ret.m[i];
    return (*this);
  }

  /**
   * @brief Subtract a scalar value from the matrix
   * @param value The scalar value to subtract from the matrix
   * @return The resulting matrix
   */
  inline Mat4 operator-(float value) const
  {
    return Substract(value);
  }

  /**
   * @brief Subtract a scalar value from the current matrix
   * @param value The scalar value to subtract from the matrix
   * @return A reference to the current matrix
   */
  inline Mat4 &operator-=(float value)
  {
    Mat4 ret = Substract(value);
    for (int i = 0; i < 16; i++)
      this->m[i] = ret.m[i];
    return (*this);
  }

  /**
   * @brief Multiply two matrices together
   * @param other The matrix to multiply the current matrix by
   * @return The resulting matrix
   */
  inline Mat4 operator*(const Mat4 &other) const
  {
    return Multiply(other);
  }

  /**
   * @brief Multiply the current matrix by another matrix
   * @param other The matrix to multiply the current matrix by
   * @return A reference to the current matrix
   */
  inline Mat4 &operator*=(const Mat4 &other)
  {
    Mat4 ret = Multiply(other);
    for (int i = 0; i < 16; i++)
      this->m[i] = ret.m[i];
    return (*this);
  }

  /**
   * @brief Overloads the multiplication operator to perform element-wise multiplication with a scalar value.
   * @param value The scalar value to multiply with.
   * @return A new Mat4 object with the element-wise multiplication applied.
   */
  inline Mat4 operator*(float value) const
  {
    return Multiply(value);
  }

  /**
   * @brief Overloads the compound assignment operator to perform element-wise multiplication with a scalar value.
   * @param value The scalar value to multiply with.
   * @return A reference to the modified Mat4 object.
   */
  inline Mat4 &operator*=(float value)
  {
    Mat4 ret = Multiply(value);
    for (int i = 0; i < 16; i++)
      this->m[i] = ret.m[i];
    return (*this);
  }

  /**
   * @brief Overloads the division operator to perform element-wise division with a scalar value.
   * @param value The scalar value to divide with.
   * @return A new Mat4 object with the element-wise division applied.
   */
  inline Mat4 operator/(float value) const
  {
    return Divide(value);
  }


  /**
   * @brief Overloads the compound assignment operator to perform element-wise division with a scalar value.
   * @param value The scalar value to divide with.
   * @return A reference to the modified Mat4 object.
   */
  inline Mat4 &operator/=(float value)
  {
    Mat4 ret = Divide(value);
    for (int i = 0; i < 16; i++)
      this->m[i] = ret.m[i];
    return (*this);
  }

  /**
   * @brief Overloads the equal to operator to check for element-wise equality between two Mat4 objects.
   * @param other The Mat4 object to compare with.
   * @return True if all elements of the two Mat4 objects are equal, false otherwise.
   */
  inline bool operator==(const Mat4 &other) const
  {
    for (int i = 0; i < 16; ++i)
    {
      if (this->m[i] != other.m[i])
      {
        return false;
      }
    }
    return true;
  }

  /**
   * @brief Overloads the not equal to operator to check for element-wise inequality between two Mat4 objects.
   * @param other The Mat4 object to compare with.
   * @return True if any element of the two Mat4 objects is not equal, false otherwise.
   */
  inline bool operator!=(const Mat4 &other) const
  {
    for (int i = 0; i < 16; ++i)
    {
      if (this->m[i] != other.m[i])
      {
        return true;
      }
    }
    return false;
  }

  /**
   * @brief Overloaded assignment operator
   * @param other The Mat4 object to be copied
   */
  inline void operator=(const Mat4 &other)
  {
    for (int i = 0; i < 16; i++)
      this->m[i] = other.m[i];
  }

  float m[16]; ///< The elements of the matrix, stored in row-column order
};

////////////////////////
#endif /* __MATRIX_4_H__ */
////////////////////////
