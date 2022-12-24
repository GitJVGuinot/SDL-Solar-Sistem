/// @author F.c.o Javier Guinot Almenar <guinotal@esat-alumni.com>

#include <render.h>
#include <vector>
#include <thread>
#include <algorithm>
#include <functional>

Vec2 Render::getRenderScale()
{
  return render_scale_;
};

Vec2 Render::getRenderCenter()
{
  return {render_centers_.x,render_centers_.y};
}

float Render::getFar()
{
  return far_;
}
float Render::getNear()
{
  return near_;
}

Render::Render()
{
  camera_ = {0, 0, 0};
  draw_order_ = nullptr;
  max_order_ = 0;
};

void Render::init(Vec2 max_win, Vec3 camera, float near, float far)
{
  std::cout << "Creating camera..." << std::endl;
  up_ = {0, 1, 0};
  down_ = {0, -1, 0};
  right_ = {1, 0, 0};
  left_ = {-1, 0, 0};
  front_ = {0, 0, 1};
  back_ = {0, 0, -1};
  camera_ = camera;
  near_ = near;
  far_ = far;
  max_order_ = 0;
  draw_order_ = nullptr;
  current_threads_ = std::thread::hardware_concurrency();
  std::cout << "System Threads: " << current_threads_ << std::endl;

  float newScale = (0.5f * far_);
  render_scale_ = {newScale, newScale};

  Vec3 vector_mira = camera_ - Vec3{camera.x, camera.y, camera.z + 100};
  vector_mira.Normalize();
  render_centers_ = camera_ + (vector_mira * (((far - near) / 2) + near));

  // Near face
  faces_centers_[0] = {max_win.x / 2, max_win.y / 2, camera_.z - near};
  faces_vector_[0] = render_centers_ - faces_centers_[0];
  // Far face
  faces_centers_[1] = {max_win.x / 2, max_win.y / 2, camera_.z - far};
  faces_vector_[1] = render_centers_ - faces_centers_[1];

  // Right face
  faces_centers_[2] = render_centers_;
  faces_centers_[2].x += max_win.x / 2;
  faces_vector_[2] = camera_ - faces_centers_[2];
  faces_vector_[2] = MathUtils::Rotate_Point_3D({0, -90, 0}, faces_vector_[2]);
  // Left face
  faces_centers_[3] = render_centers_;
  faces_centers_[3].x -= max_win.x / 2;
  faces_vector_[3] = camera_ - faces_centers_[3];
  faces_vector_[3] = MathUtils::Rotate_Point_3D({0, 90, 0}, faces_vector_[3]);

  // Up face
  faces_centers_[4] = render_centers_;
  faces_centers_[4].y += max_win.y / 2;
  faces_vector_[4] = camera_ - faces_centers_[4];
  faces_vector_[4] = MathUtils::Rotate_Point_3D({90, 0, 0}, faces_vector_[4]);
  // Down face
  faces_centers_[5] = render_centers_;
  faces_centers_[5].y -= max_win.y / 2;
  faces_vector_[5] = camera_ - faces_centers_[5];
  faces_vector_[5] = MathUtils::Rotate_Point_3D({-90, 0, 0}, faces_vector_[5]);

  for (int i = 0; i < 6; i++)
  {
    faces_vector_[i].Normalize();
  }

  paint_square_[0] = {faces_centers_[3].x, faces_centers_[4].y, faces_centers_[2].z};
  paint_square_[1] = {faces_centers_[2].x, faces_centers_[4].y, faces_centers_[2].z};
  paint_square_[2] = {faces_centers_[2].x, faces_centers_[5].y, faces_centers_[2].z};
  paint_square_[3] = {faces_centers_[3].x, faces_centers_[5].y, faces_centers_[2].z};

  camera_.print((char *)"Camera");
  front_.print((char *)"Front");
  up_.print((char *)"Up");

  std::cout << "Camera created" << std::endl;
};

void Render::reset(Vec2 max_win)
{
  DESTROY(draw_order_);
  init(max_win, {max_win.x / 2, max_win.y / 2, 100});
}

void Render::rotation(Vec3 rot)
{

  up_ = MathUtils::Rotate_Point_3D(rot, up_);
  down_ = MathUtils::Rotate_Point_3D(rot, down_);
  right_ = MathUtils::Rotate_Point_3D(rot, right_);
  left_ = MathUtils::Rotate_Point_3D(rot, left_);
  front_ = MathUtils::Rotate_Point_3D(rot, front_);
  back_ = MathUtils::Rotate_Point_3D(rot, back_);

  for (int i = 0; i < 6; i++)
  {
    if (i < 4)
    {
      MathUtils::Orbit_Point(camera_, rot, paint_square_[i]);
    }
    MathUtils::Orbit_Point(camera_, rot, faces_centers_[i]);
    faces_vector_[i] = MathUtils::Rotate_Point_3D(rot, faces_vector_[i]);
  }
}

void Render::translation(Vec3 desp)
{
  camera_ += desp;
  for (int i = 0; i < 6; i++)
  {
    if (i < 4)
    {
      paint_square_[i] += desp;
    }
    faces_centers_[i] += desp;
  }
}

void Render::inputs(Keys *keys)
{

  if (EVENT_DOWN(UP, keys))
    rotation(right_);
  if (EVENT_DOWN(DOWN, keys))
    rotation(left_);

  if (EVENT_DOWN(RIGHT, keys))
    rotation(up_);
  if (EVENT_DOWN(LEFT, keys))
    rotation(down_);

  if (EVENT_DOWN(K_n, keys))
    rotation(front_);
  if (EVENT_DOWN(K_m, keys))
    rotation(back_);

  if (EVENT_DOWN(K_w, keys))
    translation(back_);
  if (EVENT_DOWN(K_s, keys))
    translation(front_);

  if (EVENT_DOWN(K_a, keys))
    translation(right_);
  if (EVENT_DOWN(K_d, keys))
    translation(left_);

  if (EVENT_DOWN(K_q, keys))
    translation(down_);
  if (EVENT_DOWN(K_e, keys))
    translation(up_);
}

int *Render::getOrder(Vec3 *objects_mov, Vec3 *objects_scale, int max_order)
{
  if (max_order_ != max_order)
  {
    max_order_ = max_order;
    draw_order_ = (int *)realloc(draw_order_, max_order_ * sizeof(int));
  }

  float *magnitudes = (float*)malloc(max_order_ * sizeof(float));
  float *scales = (float*)malloc(max_order_ * sizeof(float));
  for (int i = 0; i < max_order_; i++)
  {
    magnitudes[i] = (objects_mov[i] - camera_).Magnitude();
    scales[i] = (objects_scale[i].x + objects_scale[i].y + objects_scale[i].z);
  }

  // Initialize draw_order_ array
  for (int i = 0; i < max_order_; i++)
  {
    draw_order_[i] = i;
  }

  std::sort(draw_order_, draw_order_ + max_order_,
            [&](const int &a, const int &b)
            {
              if (magnitudes[a] == magnitudes[b])
              {
                return scales[a] < scales[b];
              }
              return magnitudes[a] > magnitudes[b];
            });

  free(magnitudes);
  free(scales);

  return draw_order_;
}

SDL_Color renderColorLight(Vec3 point, Vec3 desp, Vec3 light, SDL_Color color)
{
  if (desp == light)
    return color;

  Uint8 newColor[4] = {
    color.r,
    color.g,
    color.b,
    color.a
  };

  Vec3 point_vector = Vec3::Substract(desp, point); // Director vector to the centre from the point
  Vec3 light_vector = Vec3::Substract(desp, light); // Director vector pointing to the centre from light

  point_vector.Normalize();
  light_vector.Normalize();

  float euler = std::abs(MathUtils::Radian_To_Euler(Vec3::Angle(point_vector, light_vector)));
  euler+=45;
  euler = std::min(euler, 180.0f);

  const float kAngleRestMultiplier = 255.0f / 180.0f;
  float angleRest = euler * kAngleRestMultiplier;

  Uint8 max = newColor[0];
  max = std::max(max, newColor[1]);
  max = std::max(max, newColor[2]);

  angleRest = max / angleRest;
  angleRest = 1 / angleRest;

  for (int i = 0; i < 3; i++)
  {
    if (newColor[i] > 0)
    {
      newColor[i] -= (angleRest * newColor[i]);
    }
    if (newColor[i] < 0)
      newColor[i] = 0;
  }

  SDL_Color ret = {
    newColor[0],
    newColor[1],
    newColor[2],
    newColor[3]
  };

  return ret;
}

SDL_Vertex renderSDLVertex(Vec3 light, Vec2 draw, Vec3 point, Vec3 desp, SDL_Color color, bool renderLight)
{
  if(renderLight)
    return SDL_Vertex{{draw.x, draw.y}, renderColorLight(point, desp, light, color), {0, 0}};
  else
    return SDL_Vertex{{draw.x, draw.y}, color, {0, 0}};
}

bool Render::active(Vec3 point)
{
  bool ret = true;

  // Create the normal from the centre of the 6 faces to the centre of the cube
  for (int i = 0; i < 6; i++)
  {
    Vec3 pointvec = Vec3::Substract(point, faces_centers_[i]).Normalized();
    float radian = Vec3::Angle(pointvec, faces_vector_[i]);
    if (!Between(PI / 2, radian, -PI / 2))
    {
      return false;
    }
  }

  return ret;
}

// This is the normal one
void Render::renderPoints(Render_Figure &figure, bool renderLight)
{
  Render_Vert *in_vert = *figure.verts;

  for(int i=0; i<figure.n_points; i++)
  {
    renderPoint(in_vert[i], figure.point[i], figure.desp, figure.light, figure.color, figure.model, figure.forceRender, renderLight);
  }
}

// This render the points using threads
void Render::renderThreadedPoints(Render_Figure &figure, bool renderLight)
{
  Render_Vert *in_vert = *figure.verts;

  std::vector<std::thread> threads;

  const int numThreads = std::min(current_threads_, figure.n_points);

  // Divide the points into "numThreads" equal-sized chunks
  int pointsPerThread = figure.n_points / numThreads;
  int remainingPoints = figure.n_points % numThreads;

  // Create and start "numThreads" threads, each thread will render a chunk of points
  for (int i = 0; i < numThreads; i++)
  {
    int start = i * pointsPerThread;
    int end = start + pointsPerThread;

    if(i == numThreads - 1) end += remainingPoints;

    threads.push_back(std::thread([&, start, end]()
    {
      for (int j = start; j < end; j++)
      {
        renderPoint(in_vert[j], figure.point[j], figure.desp, figure.light, figure.color, figure.model, figure.forceRender, renderLight);
      }
    }));
  }

  // wait for all threads to finish
  for (auto &t : threads) t.join();
}

void Render::renderPoint(Render_Vert &ret_vert, Vec3 point, Vec3 desp, Vec3 light, SDL_Color color, Mat3 model, bool forceRender, bool renderLight)
{
  if (active(point) || forceRender)
  {
    // Projection of 3D points to 2D taking the camera into account
    Mat4 vMatrix = MathUtils::Mat4View(camera_, front_, up_);
    Mat4 pro = Mat4::Projection();
    vMatrix = pro * vMatrix;

    Vec3 new_point = MathUtils::Mat4TransformVec3(vMatrix, point);

    new_point = MathUtils::Vec2_Tr_Vec3(MathUtils::Vec3_Tr_Vec2(new_point), 1);

    new_point = MathUtils::Mat3TransformVec3(model, new_point);

    SDL_Vertex ret = renderSDLVertex(light, MathUtils::Vec3_Tr_Vec2(new_point), point, desp, color, renderLight);

    ret_vert = Render_Vert{ret, true};
  }
  else
    ret_vert = Render_Vert{{0, 0, 0}, false};
}

void Render::cameraDraw(Keys *keys, SDL_Renderer *render, Vec2 max_win, Vec3 light)
{
  // 2D point transformation
  Mat3 model = Mat3::Identity();
  Mat3 scale = Mat3::Scale(render_scale_);
  Mat3 desp = Mat3::Translate(getRenderCenter());
  model = desp * scale;

  Render_Vert draw[6];
  Render_Vert square[4];

  for (int i = 0; i < 6; i++)
  {
    if (i < 4)
    {
      renderPoint(square[i], paint_square_[i], Vec3{0,0,0}, Vec3{0,0,0}, {255,0,255,255}, model, true);
    }
    renderPoint(draw[i], faces_centers_[i], Vec3{0,0,0}, Vec3{0,0,0}, {255,0,255,255}, model, true);
  }

  Render_Vert drawLight;
  renderPoint(drawLight, light, Vec3{0,0,0}, light, SDL_Color{255,255,255,255}, model, true);
  SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
  SDL_RenderDrawPoint(render, drawLight.point.position.x, drawLight.point.position.y);

  SDL_SetRenderDrawColor(render, 255, 0, 255, 128);
  SDL_RenderDrawLine(render, square[0].point.position.x, square[0].point.position.y, square[1].point.position.x, square[1].point.position.y);
  SDL_RenderDrawLine(render, square[1].point.position.x, square[1].point.position.y, square[2].point.position.x, square[2].point.position.y);
  SDL_RenderDrawLine(render, square[2].point.position.x, square[2].point.position.y, square[3].point.position.x, square[3].point.position.y);
  SDL_RenderDrawLine(render, square[3].point.position.x, square[3].point.position.y, square[0].point.position.x, square[0].point.position.y);
}

Vec3 Render::getUp()
{
  return up_;
}
