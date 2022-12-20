/// @author Marcos Jiménez Saz <jimenezsa@esat-alumni.com>

/** @file Vector_3.h
 *--------------------------------------------------------------
 *  Math Library
 *  Vector 3 Class Definition.
 *--------------------------------------------------------------
 */

/////////////////////////
#ifndef __VECTOR_3_H__
#define __VECTOR_3_H__ 1
/////////////////////////

#include <stdio.h>

/**
 * @class Vec3.
 *
 * @brief A class for 3D vectors.
 *
 * This class provides methods for creating and manipulating 3D vectors. It includes
 * constructors for creating vectors from different inputs, as well as functions for
 * performing vector operations such as addition, subtraction, multiplication, and division.
 * It also includes overloaded operators for these operations.
 */
class Vec3
{
public:

  /**
   * @brief Prints the vector coordinates to the console.
   *
   * @param[in] name (optional) the name of the vector.
   *
   * @return void.
   */
  inline void print(char *name = (char *)"Vec3")
  {
    printf("%s: %f, %f, %f\n", name, this->x, this->y, this->z);
  }

  /*
   * @brief Constructs a Vec3 with default value of 0.
   *
   * @param value The default value to set all components of the Vec3 to.
   */
  Vec3(float value = 0);

  /**
   * @brief Constructs a Vec3 with the given x and y components.
   *
   * @param x The x component of the Vec3.
   * @param y The y component of the Vec3.
   * @param z The y component of the Vec3.
   */
  Vec3(float x, float y, float z);

  /**
   * @brief Constructs a Vec3 using an array of values.
   *
   * @param values_array An array of values to use as the x, y and z components of the Vec3.
   */
  Vec3(float *values_array);

  /**
   * @brief Constructs a Vec3 as a copy of another Vec3.
   *
   * @param other The Vec3 to be copied.
   */
  Vec3(const Vec3 &other);

  /**
   * @brief Destructor for Vec3.
   */
  ~Vec3();

  // Static funtions
  /**
   * @brief Adds two Vec3s together and returns the result.
   *
   * @param first The first Vec3 to be added.
   * @param second The second Vec3 to be added.
   *
   * @return The sum of the two Vec3s.
  */
  static inline Vec3 Sum(const Vec3 &first, const Vec3 &second)
  {
    return Vec3(first.x + second.x, first.y + second.y, first.z + second.z);
  }

  /**
   * @brief Adds a value to each component of a Vec3 and returns the result.
   *
   * @param first The Vec3 to be modified.
   * @param value The value to be added to each component of the Vec3.
   *
   * @return The modified Vec3.
  */
  static inline Vec3 Sum(const Vec3 &first, float value)
  {
    return Vec3(first.x + value, first.y + value, first.z + value);
  }

  /**
   * @brief Substract a value to each component of a Vec3 and returns the result.
   *
   * @param first The Vec3 to be subtracted from.
   * @param second The Vec3 to subtract.
   *
   * @return The result of the subtraction.
  */
  static inline Vec3 Substract(const Vec3 &first, const Vec3 &second)
  {
    return Vec3(first.x - second.x, first.y - second.y, first.z - second.z);
  }

  /*
   * @brief Subtracts a float value from a Vec3 object.
   *
   * @param first The Vec3 object to subtract from.
   * @param value The float value to subtract.
   *
   * @return The resulting Vec3 object.
   */
  static inline Vec3 Substract(const Vec3 &first, float value)
  {
    return Vec3(first.x - value, first.y - value, first.z - value);
  }

  /**
   * @brief Multiplies two Vec3 objects.
   *
   * @param first The first Vec3 object.
   * @param second The second Vec3 object.
   *
   * @return The resulting Vec3 object.
   */
  static inline Vec3 Multiply(const Vec3 &first, const Vec3 &second)
  {
    return Vec3(first.x * second.x, first.y * second.y, first.z * second.z);
  }

  /**
   * @brief Multiplies a Vec3 object and a float value.
   *
   * @param first The Vec3 object.
   * @param value The float value.
   *
   * @return The resulting Vec3 object.
   */
  static inline Vec3 Multiply(const Vec3 &first, float value)
  {
    return Vec3(first.x * value, first.y * value, first.z * value);
  }

  /**
   * @brief Divides a Vec3 object by a float value.
   *
   * @param first The Vec3 object.
   * @param value The float value.
   *
   * @return The resulting Vec3 object.
   */
  static inline Vec3 Divide(const Vec3 &first, float value)
  {
    return Vec3(first.x / value, first.y / value, first.z / value);
  }

  // Normal funtions
  /**
   * @brief Adds a Vec3 object to the current object.
   *
   * @param other The Vec3 object to add.
   *
   * @return The resulting Vec3 object.
   */
  inline Vec3 Sum(const Vec3 &other) const
  {
    return Vec3(this->x + other.x, this->y + other.y, this->z + other.z);
  }

  /**
   * @brief Adds a float value to the current object.
   *
   * @param value The float value to add.
   *
   * @return The resulting Vec3 object.
   */
  inline Vec3 Sum(float value) const
  {
    return Vec3(this->x + value, this->y + value, this->z + value);
  }

  /*
   * @brief Subtracts a Vec3 object from the current object.
   *
   * @param other The Vec3 object to subtract.
   *
   * @return The resulting Vec3 object.
   */
  inline Vec3 Substract(const Vec3 &other) const
  {
    return Vec3(this->x - other.x, this->y - other.y, this->z - other.z);
  }

  /**
   * @brief Subtracts a float value from the current object.
   *
   * @param value The float value to subtract.
   *
   * @return The resulting Vec3 object.
   */
  inline Vec3 Substract(float value) const
  {
    return Vec3(this->x - value, this->y - value, this->z - value);
  }

  /**
   * @brief Multiplies the current object by another Vec3 object.
   *
   * @param other The Vec3 object to multiply by.
   *
   * @return The resulting Vec3 object.
   */
  inline Vec3 Multiply(const Vec3 &other) const
  {
    return Vec3(this->x * other.x, this->y * other.y, this->z * other.z);
  }

  /**
   * @brief Multiplies the current object by a float value.
   *
   * @param value The float value to multiply by.
   *
   * @return The resulting Vec3 object.
   */
  inline Vec3 Multiply(float value) const
  {
    return Vec3(this->x * value, this->y * value, this->z * value);
  }

  /**
   * @brief Divides the current object by a float value.
   *
   * @param value The float value to divide by.
   *
   * @return The resulting Vec3 object.
   */
  inline Vec3 Divide(float value) const
  {
    return Vec3(this->x / value, this->y / value, this->z / value);
  }

  // Operators
  /**
   * @brief Overloads the '+' operator to add a Vec3 object to the current object.
   *
   * @param other The Vec3 object to add.
   *
   * @return The resulting Vec3 object.
   */
  inline Vec3 operator+(const Vec3 &other) const
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
  inline Vec3 operator+(float value) const
  {
    return Sum(value);
  }

  /**
   * @brief Overloads the '+=' operator to add a Vec3 object to the current object.
   *
   * @param other The Vec3 object to add.
   *
   * @return A reference to the current Vec3 object.
   */
  inline Vec3 &operator+=(const Vec3 &other)
  {
    Vec3 ret = Sum(other);
    this->x = ret.x;
    this->y = ret.y;
    this->z = ret.z;
    return *this;
  }

  /**
   * @brief Overloads the += operator to add a scalar value to the vector.
   *
   * @param value The scalar value to add to the vector.
   *
   * @return A reference to the modified vector.
   */
  inline Vec3 &operator+=(float value)
  {
    Vec3 ret = Sum(value);
    this->x = ret.x;
    this->y = ret.y;
    this->z = ret.z;
    return *this;
  }

  /**
   * @brief Overloads the - operator to subtract one vector from another.
   *
   * @param other The vector to subtract from this vector.
   *
   * @return The resulting vector after the subtraction.
   */
  inline Vec3 operator-(const Vec3 &other) const
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
  inline Vec3 operator-(float value) const
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
  inline Vec3 &operator-=(const Vec3 &other)
  {
    Vec3 ret = Substract(other);
    this->x = ret.x;
    this->y = ret.y;
    this->z = ret.z;
    return *this;
  }

  /**
   * @brief Overloads the -= operator to subtract a scalar value from the vector.
   *
   * @param value The scalar value to subtract from the vector.
   *
   * @return A reference to the modified vector.
   */
  inline Vec3 &operator-=(float value)
  {
    Vec3 ret = Substract(value);
    this->x = ret.x;
    this->y = ret.y;
    this->z = ret.z;
    return *this;
  }

  /**
   * @brief Compares this vector to another vector for equality.
   *
   * @param value The vector to compare against.
   *
   * @return True if the vectors are equal, false otherwise.
   */
  inline bool operator==(const Vec3 &value) const
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
    return true;
  }

  /**
   * @brief Compares this vector to another vector for inequality.
   *
   * @param value The vector to compare against.
   *
   * @return True if the vectors are not equal, false otherwise.
   */
  inline bool operator!=(const Vec3 &value) const
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
    return true;
  }

  /**
   * @brief Assigns the values of another vector to this vector.
   *
   * @param other The vector to assign values from.
   */
  inline void operator=(const Vec3 &other)
  {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
  }

  /**
   * @brief Assigns a scalar value to both coordinates of this vector.
   *
   * @param value The scalar value to assign.
   */
  inline void operator=(float value)
  {
    this->x = value;
    this->y = value;
    this->z = value;
  }

  /**
   * @brief Multiply this vector by a scalar.
   *
   * @param value The scalar to multiply by.
   *
   * @return The result of the multiplication.
   */
  inline Vec3 operator*(float value) const
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
  inline Vec3 &operator*=(float value)
  {
    Vec3 ret = Multiply(value);
    this->x = ret.x;
    this->y = ret.y;
    this->z = ret.z;
    return *this;
  }

  /**
   * @brief Multiply this vector by a scalar.
   *
   * @param other The scalar to multiply by.
   *
   * @return The result of the multiplication.
   */
  inline Vec3 operator*(Vec3 other) const
  {
    return Multiply(other);
  }

  /**
   * @brief Multiply this vector by a vector and assign the result to this vector.
   *
   * @param other The vector to multiply by.
   *
   * @return A reference to this vector.
   */
  inline Vec3 &operator*=(Vec3 other)
  {
    Vec3 ret = Multiply(other);
    this->x = ret.x;
    this->y = ret.y;
    this->z = ret.z;
    return *this;
  }

  /**
   * @brief Divides the vector by a scalar value.
   *
   * @param value The scalar value to divide the vector by.
   *
   * @return The resulting vector.
   */
  inline Vec3 operator/(float value) const
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
  inline Vec3 &operator/=(float value)
  {
    Vec3 ret = Divide(value);
    this->x = ret.x;
    this->y = ret.y;
    this->z = ret.z;
    return *this;
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
  Vec3 Normalized() const;

  /**
   * @brief Calculates the square of the magnitude of the vector.
   *
   * @return The square of the magnitude of the vector.
   */
  float SqrMagnitude() const;

  /**
   * @brief Scales the vector by a given factor.
   *
   * @param scale The factor to scale the vector by.
   */
  void Scale(const Vec3 &scale);

  /**
   * @brief Linearly interpolates between two vectors.
   *
   * @param a The starting vector.
   * @param b The ending vector.
   * @param value The interpolation value, clamped between 0 and 1.
   *
   * @return The interpolated vector.
   */
  static Vec3 Lerp(const Vec3 a, const Vec3 b, float value);

  /**
   * @brief Linearly interpolates between two vectors.
   *
   * @param a The starting vector.
   * @param b The ending vector.
   * @param t The interpolation value, unclamped.
   *
   * @return The interpolated vector.
   */
  static Vec3 LerpUnclamped(const Vec3 a, const Vec3 b, float t);

  /**
   * @brief Calculates the dot product of two vectors.
   *
   * @param a The first vector.
   * @param b The second vector.
   *
   * @return The dot product of the two vectors.
   */
  static float DotProduct(const Vec3 a, const Vec3 b);

  /**
   * @brief Calculates the radiant angle between two vectors.
   *
   * @param a The first vector.
   * @param b The second vector.
   *
   * @return The radiant angle between the two vectors.
   */
  static float Angle(const Vec3 a, const Vec3 b);

  /**
   * @brief Calculates a perpendicular vector between 2 vectors.
   *
   * @param a The first vector.
   * @param b The second vector.
   *
   * @return The perpendicular vector between two vectors.
   */
  static Vec3 CrossProduct(const Vec3 a, const Vec3 b);

  /**
   * @brief Calculates the distance between two vectors.
   *
   * @param a The first vector.
   * @param b The second vector.
   *
   * @return The distance between the two vectors.
   */
  static float Distance(const Vec3 a, const Vec3 b);

  /**
   * @brief Calculates the reflection between two vectors.
   *
   * @param a The first vector.
   * @param b The second vector.
   *
   * @return The reflection between the two vectors based on a normal.
   */
  static Vec3 Reflect(const Vec3 direction, const Vec3 normal);

  static const Vec3 up; ///< A static constant vector pointing upwards (0, 1, 0).
  static const Vec3 down; ///< A static constant vector pointing downwards (0, -1, 0).
  static const Vec3 right; ///< A static constant vector pointing right (1, 0, 0).
  static const Vec3 left; ///< A static constant vector pointing left (-1, 0, 0).
  static const Vec3 forward; ///< A static constant vector pointing forward (0, 0, 1).
  static const Vec3 back; ///< A static constant vector pointing back (0, 0, -1).
  static const Vec3 zero; ///< A static constant vector with all components set to zero.
  static const Vec3 unit; ///< A static constant vector with all components set to one.

  float x; ///< The x component of the vector.
  float y; ///< The y component of the vector.
  float z; ///< The Z component of the vector.
};

/////////////////////////
#endif /* __VECTOR_3_H__ */
/////////////////////////
