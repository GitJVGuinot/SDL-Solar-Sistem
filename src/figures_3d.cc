/// @author Marcos Jiménez Saz <jimenezsa@esat-alumni.com>

#include "figures_3d.h"
#include <string>

void Figure::count_faces(const tinyobj::shape_t &shape)
{
  const std::vector<tinyobj::index_t> &indices = shape.mesh.indices;

  for (int face_ind = 0; face_ind < (int)indices.size(); face_ind += 3)
  {
    nFaces_++;
  }
}

void Figure::load_triangles(const tinyobj::shape_t &shape, int &cont)
{
  const std::vector<tinyobj::index_t> &indices = shape.mesh.indices;

  for (int face_ind = 0; face_ind < (int)indices.size(); face_ind += 3)
  {
    faces_[cont].points[0] = indices[face_ind].vertex_index;
    faces_[cont].points[1] = indices[face_ind + 1].vertex_index;
    faces_[cont].points[2] = indices[face_ind + 2].vertex_index;
    cont++;
  }
}

int Figure::charger(const char *path)
{
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> objmaterials;
  std::string warn;
  std::string err;

  // load all data in Obj file
  //'triangulate'
  bool success = tinyobj::LoadObj(&attrib,
                                  &shapes,
                                  &objmaterials,
                                  &warn,
                                  &err,
                                  path); // model to load

  // boilerplate error handling
  if (!err.empty())
  {
    std::cerr << err << std::endl;
  }
  if (!success)
  {
    return 1;
  }

  vertex_ = attrib.vertices.size() / 3;
  std::cout << "Vertex: " << vertex_ << std::endl;

  points_ = (Vec3 *)calloc(vertex_, sizeof(Vec3));

  draw_sdl_ = (Render_Vert *)calloc(vertex_, sizeof(Render_Vert));

  // Convert the vertices into our format
  int cont = 0;
  for (int i = 0; i < (int)attrib.vertices.size(); i += 3)
  {
    points_[cont].x = attrib.vertices[i];
    points_[cont].y = attrib.vertices[i + 1];
    points_[cont].z = attrib.vertices[i + 2];
    cont++;
  }

  // Convert the face_inds into our format
  // Face_inds should all be triangles due to triangulate=true
  nFaces_ = 1;
  for (auto shape = shapes.begin(); shape < shapes.end(); shape++)
  {
    count_faces(*shape);
  }

  faces_ = (Faces *)calloc(nFaces_, sizeof(Faces));
  std::cout << "nFaces_: " << nFaces_ << std::endl;

  for (int i = 0; i < nFaces_; ++i)
  {
    faces_[i].n_points = 3;
    faces_[i].points = (int *)calloc(faces_[i].n_points, sizeof(int));
  }

  cont = 0;
  for (auto shape = shapes.begin(); shape < shapes.end(); shape++)
  {
    load_triangles(*shape, cont);
  }

  centers_ = (Vec3 *)calloc(nFaces_, sizeof(Vec3));

  for (int i = 0; i < nFaces_; i++)
  {
    centers_[i] = points_[faces_[i].points[0]] - points_[faces_[i].points[2]];
    centers_[i] *= 0.5f;
    centers_[i] += points_[faces_[i].points[2]];
  }

  order_ = (int *)calloc(nFaces_, sizeof(int));

  return 0;
}

int Figure::init(const char *path, SDL_Color color, bool fill, Vec3 p_scale, Vec3 mov, Vec3 rot, Vec3 orbit, Vec3 orbit_center)
{
  std::cout << "Creating figure..." << std::endl;
  res_ = 0;
  fillColor_ = color;
  linesColor_ = color;
  fill_ = fill;
  lines_ = false;
  orbit_ = orbit;
  orbit_center_ = orbit_center;
  orbit_vel_ = 0.0f;
  rotate_ = {0, 0, 0};
  scale_ = {1, 1, 1};
  dim_ = 1;
  mov_ = {0, 0, 0};

  int ret = charger(path);

  if (ret != 0)
  {
    std::cout << "ERROR: Creating figure -> " << ret << std::endl;
    return ret;
  }

  standarize();

  if ((p_scale.x + p_scale.y + p_scale.z) != 3)
    scale(p_scale);

  if ((mov.x + mov.y + mov.z) != 0)
    translation(mov);

  if ((rot.x + rot.y + rot.z) != 0)
    rotation(rot);

  bytesSize = 0;

  bytesSize += sizeof(Vec3);
  bytesSize += sizeof(Vec3);
  bytesSize += sizeof(int);
  bytesSize += sizeof(int);
  bytesSize += sizeof(Vec3) * vertex_;
  bytesSize += sizeof(Vec3) * vertex_;
  bytesSize += sizeof(Render_Vert) * vertex_;
  for (int i = 0; i < nFaces_; i++)
  {
    bytesSize += sizeof(int) * faces_[i].n_points;
  }
  bytesSize += sizeof(int);
  bytesSize += sizeof(int) * vertex_;
  bytesSize += sizeof(int);
  bytesSize += sizeof(float);
  bytesSize += sizeof(Vec3);
  bytesSize += sizeof(Vec3);
  bytesSize += sizeof(Vec3);
  bytesSize += sizeof(SDL_Color);
  bytesSize += sizeof(SDL_Color);
  bytesSize += sizeof(bool);
  bytesSize += sizeof(bool);
  bytesSize += sizeof(float);

  std::cout << "Bytes size: " << bytesSize << std::endl;
  std::cout << "Real size " << sizeof(this) << std::endl;

  std::cout << "Figure created" << std::endl;
  return ret;
}
