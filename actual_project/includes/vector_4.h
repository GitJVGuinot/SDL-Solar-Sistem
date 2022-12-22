/// @author Marcos Jiménez Saz <jimenezsa@esat-alumni.com>

/** @file Vector_4.h
 *--------------------------------------------------------------
 *  Math Library
 *  Vector 4 Class Definition.
 *--------------------------------------------------------------
 */

/////////////////////////
#ifndef __VECTOR_4_H__
#define __VECTOR_4_H__ 1
/////////////////////////

#include "vector_3.h"
#include "matrix_3.h"
#include <stdio.h>

/**
 * @class Vec4.
 *
 * @brief A class for Vec4.
 *
 * This class provides methods for creating and manipulating 3D vectors. It includes
 * constructors for creating vectors from different inputs, as well as functions for
 * performing vector operations such as addition, subtraction, multiplication, and division.
 * It also includes overloaded operators for these operations.
 */
class Vec4
{
public:

  /**
   * @brief Prints the vector coordinates to the console.
   *
   * @param[in] name (optional) the name of the vector.
   *
   * @return void.
   */
  inline void print(char *name = (char *)"Vec4")
  {
    printf("%s: %f, %f, %f, %f\n", name, this->x, this->y, this->z, this->w);
  }

  /*
   * @brief Constructs a Vec4 with default value of 0.
   *
   * @param value The default value to set all components of the Vec3 to.
   */
  Vec4(float value = 0);

  /**
   * @brief Constructs a Vec4 with the given x and y components.
   *
   * @param x The x component of the Vec4.
   * @param y The y component of the Vec4.
   * @param z The y component of the Vec4.
   * @param w The y component of the Vec4.
   */
  Vec4(float x, float y, float z, float w);

  /**
   * @brief Constructs a Vec4 using an array of values.
   *
   * @param values_array An array of values to use as the x, y, z and w components of the Vec4.
   */
  Vec4(float *values_array);

  /**
   * @brief Constructs a Vec4 as a copy of another Vec4.
   *
   * @param other The Vec4 to be copied.
   */
  Vec4(const Vec4 &other);

  /**
   * @brief Destructor for Vec4.
   */
  ~Vec4();

  // Static functions
  /**
   * @brief Adds two Vec4s together and returns the result.
   *
   * @param first The first Vec4 to be added.
   * @param second The second Vec4 to be added.
   *
   * @return The sum of the two Vec4s.
  */
  static inline Vec4 Sum(const Vec4 &first, const Vec4 &second)
  {
    return Vec4(first.x + second.x, first.y + second.y, first.z + second.z, first.w + second.w);
  }

  /**
   * @brief Adds a value to each component of a Vec4 and returns the result.
   *
   * @param first The Vec4 to be modified.
   * @param value The value to be added to each component of the Vec4.
   *
   * @return The modified Vec4.
  */
  static inline Vec4 Sum(const Vec4 &first, float value)
  {
    return Vec4(first.x + value, first.y + value, first.z + value, first.w + value);
  }

  /**
   * @brief Substract a value to each component of a Vec4 and returns the result.
   *
   * @param first The Vec4 to be subtracted from.
   * @param second The Vec4 to subtract.
   *
   * @return The result of the subtraction.
  */
  static inline Vec4 Substract(const Vec4 &first, const Vec4 &second)
  {
    return Vec4(first.x - second.x, first.y - second.y, first.z - second.z, first.w - second.w);
  }

  /*
   * @brief Subtracts a float value from a Vec4 object.
   *
   * @param first The Vec4 object to subtract from.
   * @param value The float value to subtract.
   *
   * @return The resulting Vec4 object.
   */
  static inline Vec4 Substract(const Vec4 &first, float value)
  {
    return Vec4(first.x - value, first.y - value, first.z - value, first.w - value);
  }

  /**
   * @brief Multiplies two Vec4 objects.
   *
   * @param first The first Vec4 object.
   * @param second The second Vec4 object.
   *
   * @return The resulting Vec4 object.
   */
  static inline Vec4 Multiply(const Vec4 &first, const Vec4 &second)
  {
    return Vec4(first.x * second.x, first.y * second.y, first.z * second.z, first.w * second.w);
  }

  /**
   * @brief Multiplies a Vec4 object and a float value.
   *
   * @param first The Vec4 object.
   * @param value The float value.
   *
   * @return The resulting Vec4 object.
   */
  static inline Vec4 Multiply(const Vec4 &first, float value)
  {
    return Vec4(first.x * value, first.y * value, first.z * value, first.w * value);
  }

  /**
   * @brief Divides a Vec4 object by a float value.
   *
   * @param first The Vec4 object.
   * @param value The float value.
   *
   * @return The resulting Vec4 object.
   */
  static inline Vec4 Divide(const Vec4 &first, float value)
  {
    return Vec4(first.x / value, first.y / value, first.z / value, first.w / value);
  }

  // Normal functions
  /**
   * @brief Adds a Vec4 object to the current object.
   *
   * @param other The Vec4 object to add.
   *
   * @return The resulting Vec4 object.
   */
  inline Vec4 Sum(const Vec4 &other) const
  {
    return Vec4(this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w);
  }

  /**
   * @brief Adds a float value to the current object.
   *
   * @param value The float value to add.
   *
   * @return The resulting Vec4 object.
   */
  inline Vec4 Sum(float value) const
  {
    return Vec4(this->x + value, this->y + value, this->z + value, this->w + value);
  }

  /*
   * @brief Subtracts a Vec4 object from the current object.
   *
   * @param other The Vec4 object to subtract.
   *
   * @return The resulting Vec4 object.
   */
  inline Vec4 Substract(const Vec4 &other) const
  {
    return Vec4(this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w);
  }

  /**
   * @brief Subtracts a float value from the current object.
   *
   * @param value The float value to subtract.
   *
   * @return The resulting Vec4 object.
   */
  inline Vec4 Substract(float value) const
  {
    return Vec4(this->x - value, this->y - value, this->z - value, this->w - value);
  }

  /**
   * @brief Multiplies the current object by another Vec4 object.
   *
   * @param other The Vec4 object to multiply by.
   *
   * @return The resulting Vec4 object.
   */
  inline Vec4 Multiply(const Vec4 &other) const
  {
    return Vec4(this->x * other.x, this->y * other.y, this->z * other.z, this->w * other.w);
  }

  /**
   * @brief Multiplies the current object by a float value.
   *
   * @param value The float value to multiply by.
   *
   * @return The resulting Vec4 object.
   */
  inline Vec4 Multiply(float value) const
  {
    return Vec4(this->x * value, this->y * value, this->z * value, this->w * value);
  }

  /**
   * @brief Divides the current object by a float value.
   *
   * @param value The float value to divide by.
   *
   * @return The resulting Vec4 object.
   */
  inline Vec4 Divide(float value) const
  {
    return Vec4(this->x / value, this->y / value, this->z / value, this->w / value);
  }

  // Operators
  /**
   * @brief Overloads the '+' operator to add a Vec3 object to the current object.
   *
   * @param other The Vec4 object to add.
   *
   * @return The resulting Vec4 object.
   */
  inline Vec4 operator+(const Vec4 &other) const
  {
    return Sum(other);
  }

  /**
   * @brief Overloads the + operator to add a scalar value to the vector.
   *
   * @param value The scalar value to add to the vector.
   *
   * @return The resulting vector after the addition.
   */
  inline Vec4 operator+(float value) const
  {
    return Sum(value);
  }

  /**
   * @brief Overloads the '+=' operator to add a Vec4 object to the current object.
   *
   * @param other The Vec4 object to add.
   *
   * @return A reference to the current Vec4 object.
   */
  inline void operator+=(const Vec4 &other)
  {
    Vec4 ret = Sum(other);
    this->x = ret.x;
    this->y = ret.y;
    this->z = ret.z;
    this->w = ret.w;
  }

  /**
   * @brief Overloads the += operator to add a scalar value to the vector.
   *
   * @param value The scalar value to add to the vector.
   *
   * @return A reference to the modified vector.
   */
  inline void operator+=(float value)
  {
    Vec4 ret = Sum(value);
    this->x = ret.x;
    this->y = ret.y;
    this->z = ret.z;
    this->w = ret.w;
  }

  /**
   * @brief Overloads the - operator to subtract one vector from another.
   *
   * @param other The vector to subtract from this vector.
   *
   * @return The resulting vector after the subtraction.
   */
  inline Vec4 operator-(const Vec4 &other) const
  {
    return Substract(other);
  }

  /**
   * @brief Overloads the - operator to subtract a scalar value from the vector.
   *
   * @param value The scalar value to subtract from the vector.
   *
   * @return The resulting vector after the subtraction.
   */
  inline Vec4 operator-(float value) const
  {
    return Substract(value);
  }

  /**
   * @brief Overloads the -= operator to subtract another vector from this vector.
   *
   * @param other The vector to subtract from this vector.
   *
   * @return A reference to the modified vector.
   */
  inline void operator-=(const Vec4 &other)
  {
    Vec4 ret = Substract(other);
    this->x = ret.x;
    this->y = ret.y;
    this->z = ret.z;
    this->w = ret.w;
  }

  /**
   * @brief Overloads the -= operator to subtract a scalar value from the vector.
   *
   * @param value The scalar value to subtract from the vector.
   *
   * @return A reference to the modified vector.
   */
  inline void operator-=(float value)
  {
    Vec4 ret = Substract(value);
    this->x = ret.x;
    this->y = ret.y;
    this->z = ret.z;
    this->w = ret.w;
  }

  /**
   * @brief Compares this vector to another vector for equality.
   *
   * @param value The vector to compare against.
   *
   * @return True if the vectors are equal, false otherwise.
   */
  inline bool operator==(const Vec4 &value) const
  {
    if (this->x != value.x)
    {
      return false;
    }
    if (this->y != value.y)
    {
      return false;
    }
    if (this->z != value.z)
    {
      return false;
    }
    if (this->w != value.w)
    {
      return false;
    }
    return true;
  }

  /**
   * @brief Compares this vector to another vector for inequality.
   *
   * @param value The vector to compare against.
   *
   * @return True if the vectors are not equal, false otherwise.
   */
  inline bool operator!=(const Vec4 &value) const
  {
    if (this->x == value.x)
    {
      return false;
    }
    if (this->y == value.y)
    {
      return false;
    }
    if (this->z == value.z)
    {
      return false;
    }
    if (this->w == value.w)
    {
      return false;
    }
    return true;
  }

  /**
   * @brief Assigns the values of another vector to this vector.
   *
   * @param other The vector to assign values from.
   */
  inline void operator=(const Vec4 &other)
  {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    this->w = other.w;
  }

  /**
   * @brief Multiply this vector by a scalar.
   *
   * @param value The scalar to multiply by.
   *
   * @return The result of the multiplication.
   */
  inline Vec4 operator*(float value) const
  {
    return Multiply(value);
  }

  /**
   * @brief Multiply this vector by a scalar and assign the result to this vector.
   *
   * @param value The scalar to multiply by.
   *
   * @return A reference to this vector.
   */
  inline void operator*=(float value)
  {
    Vec4 ret = Multiply(value);
    this->x = ret.x;
    this->y = ret.y;
    this->z = ret.z;
    this->w = ret.w;
  }

  /**
   * @brief Divides the vector by a scalar value.
   *
   * @param value The scalar value to divide the vector by.
   *
   * @return The resulting vector.
   */
  inline Vec4 operator/(float value) const
  {
    return Divide(value);
  }

  /**
   * @brief Divides the vector by a scalar value and assigns the result to the vector.
   *
   * @param value The scalar value to divide the vector by.
   *
   * @return A reference to the vector.
   */
  inline void operator/=(float value)
  {
    Vec4 ret = Divide(value);
    this->x = ret.x;
    this->y = ret.y;
    this->z = ret.z;
    this->w = ret.w;
  }

  /**
   * @brief Calculates the magnitude (length) of the vector.
   *
   * @return The magnitude of the vector.
   */
  float Magnitude() const;

  /**
   * @brief Determines if the vector is normalized (magnitude is equal to 1).
   *
   * @return True if the vector is normalized, false otherwise.
   */
  bool IsNormalized() const;

  /**
   * @brief Normalizes the vector (sets its magnitude to 1).
   */
  void Normalize();

  /**
   * @brief Returns a normalized version of the vector.
   *
   * @return The normalized vector.
   */
  Vec4 Normalized() const;

  /**
   * @brief Scales the vector by a given factor.
   *
   * @param scale The factor to scale the vector by.
   */
  void Scale(Vec4 scale);

  /**
   * @brief Calculates the square of the magnitude of the vector.
   *
   * @return The square of the magnitude of the vector.
   */
  float SqrMagnitude() const;

  /**
   * @brief Calculates the distance between two vectors.
   *
   * @param a The first vector.
   * @param b The second vector.
   *
   * @return The distance between the two vectors.
   */
  static float Distance(const Vec4 a, const Vec4 b);

  /**
   * @brief Calculates the dot product of two vectors.
   *
   * @param a The first vector.
   * @param b The second vector.
   *
   * @return The dot product of the two vectors.
   */
  static float DotProduct(Vec4 a, Vec4 b);

  /**
   * @brief Linearly interpolates between two vectors.
   *
   * @param a The starting vector.
   * @param b The ending vector.
   * @param value The interpolation value, clamped between 0 and 1.
   *
   * @return The interpolated vector.
   */
  static Vec4 Lerp(const Vec4 a, const Vec4 b, float value);

  static const Vec4 one; ///< A static constant vector with all components set to one.
  static const Vec4 zero; ///< A static constant vector with all components set to zero.

  float x; ///< The x component of the vector.
  float y; ///< The y component of the vector.
  float z; ///< The z component of the vector.
  float w; ///< The w component of the vector.
};

/////////////////////////
#endif /* __VECTOR_4_H__ */
/////////////////////////
