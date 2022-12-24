/// @author F.c.o Javier Guinot Almenar <guinotal@esat-alumni.com>
/// @file Entity_3d.h

////////////////////////
#ifndef __ENTITY_3D_H__
#define __ENTITY_3D_H__ 1
////////////////////////

#include <SDL2/SDL.h>
#include <iostream>
#include <math_utils.h>
#include <SDL_event_control.h>
#include <common_defs.h>
#include <render.h>
#include <chrono>

/**
 * @struct Faces.
 *
 * @brief Represents a collection of points that make up a face.
 *
 * This struct is used by the Entity class to store information about
 * the faces that make up an entity.
 */
struct Faces
{
  int n_points; ///< The number of points in the face.
  int *points;  ///< An array of indices pointing to the points that make up the face.
};

/**
 * @class Entity
 *
 * @brief Represents a 3D object that can be rendered on screen.
 *
 * The Entity class stores information about a 3D object, such as its scale, rotation, and vertices,
 * and provides functions for rendering the object on screen.
 */
class Entity
{
protected:
  Vec3 scale_;  ///< The scale of the entity.
  Vec3 rotate_; ///< The rotation of the entity.

  int res_;       ///< The resolution of the entity.
  int vertex_;    ///< The number of vertices in the entity.
  Vec3 *points_;  ///< An array of vertices that make up the entity.
  Vec3 *centers_; ///< An array of center points for each face of the entity.

  Render_Vert *draw_sdl_; ///< A pointer to an array of vertices used for rendering the entity with SDL.

  Faces *faces_; ///< A pointer to an array of faces that make up the entity.
  int nFaces_;   ///< The number of faces in the entity.

  int *order_; ///< An array of indices used to specify the order in which the faces are rendered.

  int bytesSize; ///< The size of the entity in bytes.

  bool destroying_; ///< Flag that says if the entity are in the destroying cinematic
  bool destroyed_;  ///< Flag that say if the object is destroyed (Is useless try to draw a destroyed entity)

  std::chrono::time_point<std::chrono::steady_clock> destroying_time_; ///< The current time since the destruction starts
  std::chrono::time_point<std::chrono::steady_clock> check_time_;      ///< A variable to ceck the passed time

  /**
   * @brief Make the entity destruction cinematics
   *
   * This function is called in the draw function if the fla destroing are activated
   */
  void destroying();

public:
  float dim_;            ///< The dimensions of the entity.
  Vec3 mov_;             ///< The movement of the entity.
  Vec3 orbit_;           ///< The orbit of the entity.
  Vec3 orbit_center_;    ///< The center point of the entity's orbit.
  bool renderLight_;     ///< A flag indicating whether to render lighting on the entity.
  SDL_Color fillColor_;  ///< The color to fill the entity with.
  SDL_Color linesColor_; ///< The color of the lines drawn around the edges of the entity.
  bool fill_;            ///< A flag indicating whether to fill the entity.
  bool lines_;           ///< A flag indicating whether to draw lines around the edges of the entity.
  float orbit_vel_;      ///< The velocity of the entity's orbit.

  /**
   * @brief Constructs a new Entity object.
   *
   * This function initializes the member variables of the Entity class.
   */
  Entity();

  /**
   * @brief Start the destruction of an object
   */
  void startDestroy();

  /**
   * @brief Returns the entity state
   *
   * @return Return true if the object was destroyed
   */
  bool isDestroyed();

  /**
   * @brief Assigns the values of another Entity to this one.
   *
   * @param other The Entity to copy from.
   */
  void operator=(const Entity &other);

  /**
   * @brief Calculates the proportions of the Entity.
   */
  void proportion();

  /**
   * @brief Centers the Entity.
   */
  void centered();

  /**
   * @brief Standardizes the Entity.
   */
  void standarize();

  /**
   * @brief Returns the point at a given position in the Entity.
   *
   * @param position The index of the point to retrieve.
   *
   * @return The point at the given position.
   */
  Vec3 point(int position);

  /**
   * @brief Returns the scale of the Entity.
   *
   * @return The scale of the Entity.
   */
  Vec3 getScale();

  /**
   * @brief Returns the number of faces in the Entity.
   *
   * @return The number of faces in the Entity.
   */
  int getFaces();

  /**
   * @brief Returns the size of the Entity.
   *
   * @return The size of the Entity.
   */
  int getSize();

  /**
   * @brief Rotates the Entity by a given amount.
   *
   * @param rot The amount to rotate the Entity by.
   */
  void rotation(Vec3 rot);

  /**
   * @brief Orbits the Entity around a point.
   */
  void orbit();

  /**
   * @brief Translates the Entity by a given amount.
   *
   * @param mov The amount to translate the Entity by.
   */
  void translation(Vec3 mov);

  /**
   * @brief Scales the Entity by a given amount.
   *
   * @param scale The amount to scale the Entity by.
   */
  void scale(Vec3 scale);

  /**
   * @brief Processes input for the Entity.
   *
   * @param keys The Keys object to use for input processing.
   */
  void inputs(Keys *keys);

  /**
   * @brief Calculates the color of a point on the Entity under a given light.
   *
   * @param point The point on the Entity to calculate the color for.
   * @param light The light to use for the calculation.
   *
   * @return The calculated color.
   */
  SDL_Color renderColorLight(Vec3 point, Vec3 light);

  /**
   * @brief Renders a single SDL vertex for the Entity object.
   *
   * @param light The lighting vector for the vertex.
   * @param draw The 2D drawing coordinates for the vertex.
   * @param point The 3D coordinates of the vertex.
   *
   * @return The rendered SDL vertex.
   */
  SDL_Vertex renderSDLVertex(Vec3 light, Vec2 draw, Vec3 point);

  /**
   * @brief Draws the Entity object to the SDL window.
   *
   * @param keys A pointer to the keys currently being pressed.
   * @param render The SDL renderer to use for drawing.
   * @param drawRender The rendering mode to use.
   * @param light The lighting vector for the Entity.
   * @param id An optional identifier for the Entity.
   */
  void draw(Keys *keys, SDL_Renderer *render, Render drawRender, Vec3 light, int id = 0);

  /**
   * @brief Function created to demostrate virtual inheritance.
   */
  void print();

  /**
   * @brief Destroys the Entity object.
   */
  ~Entity();
};

////////////////////////
#endif /* __ENTITY_3D_H__ */
////////////////////////
