/// @author F.c.o Javier Guinot Almenar <guinotal@esat-alumni.com>
/// @file Render.h

////////////////////////
#ifndef __RENDER_H__
#define __RENDER_H__ 1
////////////////////////

#include <SDL2/SDL.h>
#include <iostream>
#include <common_defs.h>
#include "math_utils.h"
#include "SDL_event_control.h"

/**
 * @struct Render_Vert
 *
 * @brief A structure that represents a render vertex.
 *
 * This structure holds a vertex point in the SDL_Vertex format and a flag indicating whether the vertex is active.
 */
struct Render_Vert
{
  SDL_Vertex point;  ///< The vertex point in SDL_Vertex format.
  bool active;  ///< A flag indicating whether the vertex is active.
};

/**
 * @struct Render_Figure
 *
 * @brief A structure that represents a render figure.
 *
 * This structure holds a list of pointers to render vertices, a list of points, the number of points, a displacement vector, a light vector, a color, a model matrix, and a flag indicating whether the figure should be force rendered.
 */
struct Render_Figure
{
  Render_Vert **verts;  ///< A list of pointers to render vertices.
  Vec3 *point;  ///< A list of points.
  int n_points;  ///< The number of points.
  Vec3 desp;  ///< A displacement vector.
  Vec3 light;  ///< A light vector.
  SDL_Color color;  ///< The color of the figure.
  Mat3 model;  ///< The model matrix of the figure.
  bool forceRender = false;  ///< A flag indicating whether the figure should be force rendered.
};

/**
 * @class Render
 *
 * @brief A class for rendering objects in 3D space.
 *
 * This class has functions for initializing the renderer, rotating and translating objects, getting the rendering order of objects, and rendering points and figures. It also has functions for handling inputs, updating the camera, and getting various rendering parameters such as the scale and near and far planes.
 */
class Render
{
public:
  Vec3 camera_;  ///< The camera position.

  /**
   * @brief Constructor for the Render class.
   *
   * Initializes the renderer with default values.
   */
  Render();

  /**
   * @brief Initializes the renderer with specified values.
   *
   * @param[in] max_win The maximum window size.
   * @param[in] camera The camera position.
   * @param[in] near The near plane distance.
   * @param[in] far The far plane distance.
   */
  void init(Vec2 max_win, Vec3 camera, float near = 1, float far = 1000);

  /**
   * @brief Resets the renderer to the specified window size.
   *
   * @param[in] max_win The maximum window size.
   */
  void reset(Vec2 max_win);

  /**
   * @brief Rotates the renderer by the specified amount.
   *
   * @param[in] rot The rotation vector.
   */
  void rotation(Vec3 rot);

  /**
   * @brief Translates the renderer by the specified amount.
   *
   * @param[in] desp The displacement vector.
   */
  void translation(Vec3 desp);

  /**
   *  @brief Set the input keys for the camera.
   *
   *  @param keys A pointer to the keys object.
   */
  void inputs(Keys *keys);

  /**
   *  @brief Calculate the draw order of the objects.
   *
   *  @param objects_mov The movement vectors of the objects.
   *  @param objects_scale The scale vectors of the objects.
   *  @param max_objects The maximum number of objects.
   *
   *  @return A pointer to the array of the draw order.
   */
  int *getOrder(Vec3 *objects_mov, Vec3 *objects_scale, int max_objects);

  /**
   *  @brief Render the points of a figure.
   *
   *  @param figure The figure to be rendered.
   *  @param renderLight A flag indicating whether to render the light or not.
   */
  void renderPoints(Render_Figure &figure, bool renderLight);

  /**
   * @brief Render the points of a figure using multiple threads.
   *
   * @param figure The figure to be rendered.
   * @param renderLight A flag indicating whether to render the light or not.
   */
  void renderThreadedPoints(Render_Figure &figure, bool renderLight);

  /**
   *  @brief Render a single point.
   *
   *  @param ret_vert The returned vertex after the transformation.
   *  @param point The point to be rendered.
   *  @param desp The displacement vector of the point.
   *  @param light The light vector of the point.
   *  @param color The color of the point.
   *  @param model The model matrix of the point.
   *  @param forceRender A flag indicating whether to force the point to be rendered or not.
   *  @param renderLight A flag indicating whether to render the light or not.
   */
  void renderPoint(Render_Vert &ret_vert, Vec3 point, Vec3 desp, Vec3 light, SDL_Color color, Mat3 model, bool forceRender = false, bool renderLight = false );


  /**
   * @brief Draws the camera on the screen using the given keys, renderer, and window dimensions.
   *
   * @param keys A pointer to a Keys object representing the current state of the keyboard.
   * @param render A pointer to the SDL_Renderer object that should be used for rendering.
   * @param max_win A Vec2 object representing the dimensions of the window in pixels.
   */
  void cameraDraw(Keys *keys, SDL_Renderer *render, Vec2 max_win, Vec3 light);

  /**
   * @brief Returns the current render scale as a Vec2 object.
   *
   * @return The current render scale.
   */
  Vec2 getRenderScale();

  /**
   * @brief Returns the current render center as a Vec2 object.
   *
   * @return The current render center.
   */
  Vec2 getRenderCenter();

  /**
   * @brief Returns the current far clipping plane distance.
   *
   * @return The current far clipping plane distance.
   */
  float getFar();

  /**
   * @brief Returns the current near clipping plane distance.
   *
   * @return The current near clipping plane distance.
   */
  float getNear();

  /**
   * @brief Returns the current up vector as a Vec3 object.
   *
   * @return The current up vector.
   */
  Vec3 getUp();

private:
  int *draw_order_; ///< A pointer to an array of integers representing the draw order of 3D objects.
  Vec3 up_; ///< A Vec3 object representing the up vector of the camera.
  Vec3 down_; ///< A Vec3 object representing the up vector of the camera.
  Vec3 right_; ///< A Vec3 object representing the right vector of the camera.
  Vec3 left_; ///< A Vec3 object representing the left vector of the camera.
  Vec3 front_; ///< A Vec3 object representing the front vector of the camera.
  Vec3 back_; ///< A Vec3 object representing the back vector of the camera.
  int max_order_; ///< An integer representing the maximum draw order of 3D objects.
  float far_; ///< A float representing the far clipping plane distance.
  float near_; ///< The distance from the camera to the near clipping plane.
  Vec2 render_scale_; ///< The scale factor for the rendering.

  Vec3 faces_vector_[6]; ///< An array of vectors representing the normals of the faces of the object.
  Vec3 faces_centers_[6]; ///< An array of vectors representing the centers of the faces of the object.
  Vec3 paint_square_[4]; ///< An array of vectors representing the vertices of a square used for painting the object.
  Vec3 render_centers_; ///< The center of the rendering.

  int current_threads_; ///< The number of threads currently in the system.

  /**
   * @brief Check if a point is active.
   *
   * @param point The point to check.
   * @return True if the point is inside the render trapezoid, false otherwise.
   */
  bool active(Vec3 point);
};

/////////////////////////
#endif /* __RENDER_H__ */
/////////////////////////
