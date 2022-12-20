/// @author F.c.o Javier Guinot Almenar <guinotal@esat-alumni.com>

/** @file Vector_2.h
 *--------------------------------------------------------------
 *  Math Library
 *  Vector 2 Class Definition.
 *--------------------------------------------------------------
 */

/////////////////////////
#ifndef __VECTOR_2_H__
#define __VECTOR_2_H__ 1
/////////////////////////

#include <stdio.h>

/**
 * @class Vec2.
 *
 * @brief A class for 2D vectors.
 *
 * This class provides methods for creating and manipulating 2D vectors. It includes
 * constructors for creating vectors from different inputs, as well as functions for
 * performing vector operations such as addition, subtraction, multiplication, and division.
 * It also includes overloaded operators for these operations.
 */
class Vec2
{
public:

  /**
   * @brief Prints the vector coordinates to the console.
   *
   * @param[in] name (optional) the name of the vector.
   *
   * @return void.
   */
  inline void print(char *name = (char *)"Vec2")
  {
    printf("%s: %f, %f@n", name, this->x, this->y);
  }

  /*
   * @brief Constructs a Vec2 with default value of 0.
   *
   * @param value The default value to set all components of the Vec2 to.
   */
  Vec2(float value = 0);

  /**
   * @brief Constructs a Vec2 with the given x and y components.
   *
   * @param x The x component of the Vec2.
   * @param y The y component of the Vec2.
   */
  Vec2(float x, float y);

  /**
   * @brief Constructs a Vec2 using an array of values.
   *
   * @param values_array An array of values to use as the x and y components of the Vec2.
   */
  Vec2(float *values_array);

  /**
   * @brief Constructs a Vec2 as a copy of another Vec2.
   *
   * @param copy The Vec2 to be copied.
   */
  Vec2(const Vec2 &copy);

  /**
   * @brief Destructor for Vec2.
   */
  ~Vec2();

  // Static funtions
  /**
   * @brief Adds two Vec2s together and returns the result.
   *
   * @param first The first Vec2 to be added.
   * @param second The second Vec2 to be added.
   *
   * @return The sum of the two Vec2s.
  */
  static inline Vec2 Sum(const Vec2 &first, const Vec2 &second)
  {
    return Vec2(first.x + second.x, first.y + second.y);
  }

  /**
   * @brief Adds a value to each component of a Vec2 and returns the result.
   *
   * @param first The Vec2 to be modified.
   * @param value The value to be added to each component of the Vec2.
   *
   * @return The modified Vec2.
  */
  static inline Vec2 Sum(const Vec2 &first, float value)
  {
    return Vec2(first.x + value, first.y + value);
  }

  /**
   * @brief Substract a value to each component of a Vec2 and returns the result.
   *
   * @param first The Vec2 to be subtracted from.
   * @param second The Vec2 to subtract.
   *
   * @return The result of the subtraction.
  */
  static inline Vec2 Substract(const Vec2 &first, const Vec2 &second)
  {
    return Vec2(first.x - second.x, first.y - second.y);
  }

  /*
   * @brief Subtracts a float value from a Vec2 object.
   *
   * @param first The Vec2 object to subtract from.
   * @param value The float value to subtract.
   *
   * @return The resulting Vec2 object.
   */
  static inline Vec2 Substract(const Vec2 & first, float value)
  {
    return Vec2(first.x - value, first.y - value);
  }

  /**
   * @brief Multiplies two Vec2 objects.
   *
   * @param first The first Vec2 object.
   * @param second The second Vec2 object.
   *
   * @return The resulting Vec2 object.
   */
  static inline Vec2 Multiply(const Vec2 &first, const Vec2 &second)
  {
    return Vec2(first.x * second.x, first.y * second.y);
  }

  /**
   * @brief Multiplies a Vec2 object and a float value.
   *
   * @param first The Vec2 object.
   * @param value The float value.
   *
   * @return The resulting Vec2 object.
   */
  static inline Vec2 Multiply(const Vec2 & first, float value)
  {
    return Vec2(first.x * value, first.y * value);
  }

  /**
   * @brief Divides a Vec2 object by a float value.
   *
   * @param first The Vec2 object.
   * @param value The float value.
   *
   * @return The resulting Vec2 object.
   */
  static inline Vec2 Divide(const Vec2 &first, float value)
  {
    return Vec2(first.x / value, first.y / value);
  }

  // Normal funtions
  /**
   * @brief Adds a Vec2 object to the current object.
   *
   * @param other The Vec2 object to add.
   *
   * @return The resulting Vec2 object.
   */
  inline Vec2 Sum(const Vec2 &other) const
  {
    return Vec2(this->x + other.x, this->y + other.y);
  }

  /**
   * @brief Adds a float value to the current object.
   *
   * @param value The float value to add.
   *
   * @return The resulting Vec2 object.
   */
  inline Vec2 Sum(float value) const
  {
    return Vec2(this->x + value, this->y + value);
  }

  /*
   * @brief Subtracts a Vec2 object from the current object.
   *
   * @param other The Vec2 object to subtract.
   *
   * @return The resulting Vec2 object.
   */
  inline Vec2 Substract(const Vec2 &other) const
  {
    return Vec2(this->x - other.x, this->y - other.y);
  }

  /**
   * @brief Subtracts a float value from the current object.
   *
   * @param value The float value to subtract.
   *
   * @return The resulting Vec2 object.
   */
  inline Vec2 Substract(float value) const
  {
    return Vec2(this->x - value, this->y - value);
  }

  /**
   * @brief Multiplies the current object by another Vec2 object.
   *
   * @param other The Vec2 object to multiply by.
   *
   * @return The resulting Vec2 object.
   */
  inline Vec2 Multiply(const Vec2 &other) const
  {
    return Vec2(this->x * other.x, this->y * other.y);
  }

  /**
   * @brief Multiplies the current object by a float value.
   *
   * @param value The float value to multiply by.
   *
   * @return The resulting Vec2 object.
   */
  inline Vec2 Multiply(float value) const
  {
    return Vec2(this->x * value, this->y * value);
  }

  /**
   * @brief Divides the current object by a float value.
   *
   * @param value The float value to divide by.
   *
   * @return The resulting Vec2 object.
   */
  inline Vec2 Divide(float value) const
  {
    return Vec2(this->x / value, this->y / value);
  }

  /**
   * @brief Overloads the '+' operator to add a Vec2 object to the current object.
   *
   * @param other The Vec2 object to add.
   *
   * @return The resulting Vec2 object.
   */
  inline Vec2 operator+(const Vec2 &other) const
  {
    return Sum(other);
  }

  /**
   * @brief Overloads the '+=' operator to add a Vec2 object to the current object.
   *
   * @param other The Vec2 object to add.
   *
   * @return A reference to the current Vec2 object.
   */
  inline Vec2 &operator+=(const Vec2 &other)
  {
    Vec2 ret = Sum(other);
    this->x = ret.x;
    this->y = ret.y;
    return *this;
  }

  /**
   * @brief Overloads the + operator to add a scalar value to the vector.
   *
   * @param value The scalar value to add to the vector.
   *
   * @return The resulting vector after the addition.
   */
  inline Vec2 operator+(float value) const
  {
    return Sum(value);
  }

  /**
   * @brief Overloads the += operator to add a scalar value to the vector.
   *
   * @param value The scalar value to add to the vector.
   *
   * @return A reference to the modified vector.
   */
  inline Vec2 &operator+=(float value)
  {
    Vec2 ret = Sum(value);
    this->x = ret.x;
    this->y = ret.y;
    return *this;
  }

  /**
   * @brief Overloads the unary - operator to negate the vector.
   *
   * @return The negated vector.
   */
  inline Vec2 operator-() const
  {
    return Vec2(-this->x, -this->y);
  }

  /**
   * @brief Overloads the - operator to subtract one vector from another.
   *
   * @param other The vector to subtract from this vector.
   *
   * @return The resulting vector after the subtraction.
   */
  inline Vec2 operator-(const Vec2 &other) const
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
  inline Vec2 operator-(float value) const
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
  inline Vec2 &operator-=(const Vec2 &other)
  {
    Vec2 ret = Substract(other);
    this->x = ret.x;
    this->y = ret.y;
    return *this;
  }

  /**
   * @brief Overloads the -= operator to subtract a scalar value from the vector.
   *
   * @param value The scalar value to subtract from the vector.
   *
   * @return A reference to the modified vector.
   */
  inline Vec2 &operator-=(float value)
  {
    Vec2 ret = Substract(value);
    this->x = ret.x;
    this->y = ret.y;
    return *this;
  }

  /**
   * @brief Compares this vector to another vector for equality.
   *
   * @param value The vector to compare against.
   *
   * @return True if the vectors are equal, false otherwise.
   */
  inline bool operator==(const Vec2 &value) const
  {
    if (this->x != value.x)
    {
      return false;
    }
    if (this->y != value.y)
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
  inline bool operator!=(const Vec2 &value) const
  {
    if (this->x == value.x)
    {
      return false;
    }
    if (this->y == value.y)
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
  inline void operator=(const Vec2 &other)
  {
    this->x = other.x;
    this->y = other.y;
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
  }

  /**
   * @brief Multiply this vector by a scalar.
   *
   * @param value The scalar to multiply by.
   *
   * @return The result of the multiplication.
   */
  inline Vec2 operator*(float value) const
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
  inline Vec2 &operator*=(float value)
  {
    Vec2 ret = Multiply(value);
    this->x = ret.x;
    this->y = ret.y;
    return *this;
  }

  /**
   * @brief Divides the vector by a scalar value.
   *
   * @param value The scalar value to divide the vector by.
   *
   * @return The resulting vector.
   */
  inline Vec2 operator/(float value) const
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
  inline Vec2 &operator/=(float value)
  {
    Vec2 ret = Divide(value);
    this->x = ret.x;
    this->y = ret.y;
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
  Vec2 Normalized() const;

  /**
   * @brief Scales the vector by a given factor.
   *
   * @param scale The factor to scale the vector by.
   */
  void Scale(const Vec2 scale);

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
  static float Distance(const Vec2 a, const Vec2 b);

  /**
   * @brief Calculates the dot product of two vectors.
   *
   * @param a The first vector.
   * @param b The second vector.
   *
   * @return The dot product of the two vectors.
   */
  static float DotProduct(Vec2 a, Vec2 b);

  /**
   * @brief Linearly interpolates between two vectors.
   *
   * @param a The starting vector.
   * @param b The ending vector.
   * @param t The interpolation value, clamped between 0 and 1.
   *
   * @return The interpolated vector.
   */
  static Vec2 Lerp(const Vec2 a, const Vec2 b, float t);

  /**
   * @brief Linearly interpolates between two vectors.
   *
   * @param a The starting vector.
   * @param b The ending vector.
   * @param t The interpolation value, unclamped.
   *
   * @return The interpolated vector.
   */
  static Vec2 LerpUnclamped(const Vec2 a, const Vec2 b, float t);

  static const Vec2 up; ///< A static constant vector pointing upwards (0, 1).
  static const Vec2 down; ///< A static constant vector pointing downwards (0, -1).
  static const Vec2 right; ///< A static constant vector pointing right (1, 0).
  static const Vec2 left; ///< A static constant vector pointing left (-1, 0).
  static const Vec2 zero; ///< A static constant vector with all components set to zero.
  static const Vec2 one; ///< A static constant vector with all components set to one.

  float x; ///< The x component of the vector.
  float y; ///< The y component of the vector.
};

/////////////////////////
#endif /* __VECTOR_2_H__ */
/////////////////////////
