/// @author Marcos Jiménez Saz <jimenezsa@esat-alumni.com>

#include <objects.h>

void Not_Set_Controls(Objects &object)
{
  ImGui::Text("Type: notSet, 0 triangles");
  ImGui::Text("Size: %d", object.figure.getSize());

  char str[200];
  memset(str, 0, sizeof(str));
  snprintf(str, 200, "set sphere: %d, set cube: %d, set charged figure (.obj): %d", typeSphere, typeCube, typeFigure);
  ImGui::Text("%s", str);
  static int type;
  ImGui::DragInt("Type", &type, 0.25f, 0, MAX_OBJECTS_TYPE - 1);

  static char path[1000];

  if (type == typeFigure)
  {
    ImGui::Text("Please select the file to charge: ");
    ImGui::InputText(" ", path, 1000);
  }

  static SDL_Color color = {0, 0, 0, 255};
  float newColor[4];
  newColor[0] = (float)color.r / 255;
  newColor[1] = (float)color.g / 255;
  newColor[2] = (float)color.b / 255;
  newColor[3] = (float)color.a / 255;
  ImGui::ColorEdit4("Color", newColor);
  color.r = (Uint8)(newColor[0] * 255);
  color.g = (Uint8)(newColor[1] * 255);
  color.b = (Uint8)(newColor[2] * 255);
  color.a = (Uint8)(newColor[3] * 255);

  static bool fill = false;
  ImGui::Checkbox("Fill?", &fill);

  static Vec3 scale = {1, 1, 1};
  ImGui::DragFloat3("Scale", &scale.x, -1000, 1000);

  static Vec3 mov = {0, 0, 0};
  ImGui::DragFloat3("Translate", &mov.x, -10000, 10000);

  static Vec3 rot = {0, 0, 0};
  ImGui::DragFloat3("Rotate", &rot.x, -10000, 10000);

  static Vec3 orbit = {0, 0, 0};
  ImGui::DragFloat3("Orbit Angle", &orbit.x, -0.5, 0.5);

  static Vec3 orbit_center = {0, 0, 0};
  ImGui::DragFloat3("Orbit Center", &orbit_center.x, -10000, 10000);

  static int res = 10;

  if (type == typeSphere)
    ImGui::DragInt("Res", &res, 0.25f, 0, 50);

  if (ImGui::Button("Set new values"))
  {
    switch (type)
    {
    case typeSphere:
      object.type = type;
      object.sphere.init(color, fill, res, scale, mov, rot, orbit, orbit_center);
      break;
    case typeCube:
      object.type = type;
      object.cube.init(color, fill, scale, mov, rot, orbit, orbit_center);
      break;
    case typeFigure:
      std::cout << path << std::endl;
      if (fopen(path, "r") != NULL)
      {
        object.type = type;
        object.figure.init(path, color, fill, scale, mov, rot, orbit, orbit_center);
      }
      break;
    }
    type = 0;
    color = {0, 0, 0, 255};
    fill = false;
    res = 10;
    scale = {1, 1, 1};
    mov = {0, 0, 0};
    rot = {0, 0, 0};
    orbit = {0, 0, 0};
    orbit_center = {0, 0, 0};
  }
}

void Spheres_Controls(Sphere &sphere)
{
  ImGui::Text("Type: sphere, %d triangles", sphere.getFaces()*2);
  ImGui::Text("Size: %d", sphere.getSize());

  char str[50];
  memset(str, 0, sizeof(str));
  snprintf(str, 50, "Translation %f, %f, %f", sphere.mov_.x, sphere.mov_.y, sphere.mov_.z);
  ImGui::Text("%s", str);

  // Render Light
  ImGui::Checkbox("Render Light?", &sphere.renderLight_);

  // Dots draw change
  ImGui::Checkbox("Fill?", &sphere.fill_);

  // Color change
  float newFillColor[4];
  newFillColor[0] = (float)sphere.fillColor_.r / 255;
  newFillColor[1] = (float)sphere.fillColor_.g / 255;
  newFillColor[2] = (float)sphere.fillColor_.b / 255;
  newFillColor[3] = (float)sphere.fillColor_.a / 255;
  ImGui::ColorEdit4("Fill/Dots Color", newFillColor);
  sphere.fillColor_.r = (Uint8)(newFillColor[0] * 255);
  sphere.fillColor_.g = (Uint8)(newFillColor[1] * 255);
  sphere.fillColor_.b = (Uint8)(newFillColor[2] * 255);
  sphere.fillColor_.a = (Uint8)(newFillColor[3] * 255);

  ImGui::Checkbox("Lines Draw?", &sphere.lines_);
  if (sphere.lines_)
  {
    // Color change
    float newLineColor[4];
    newLineColor[0] = (float)sphere.linesColor_.r / 255;
    newLineColor[1] = (float)sphere.linesColor_.g / 255;
    newLineColor[2] = (float)sphere.linesColor_.b / 255;
    newLineColor[3] = (float)sphere.linesColor_.a / 255;
    ImGui::ColorEdit4("Lines Color", newLineColor);
    sphere.linesColor_.r = (Uint8)(newLineColor[0] * 255);
    sphere.linesColor_.g = (Uint8)(newLineColor[1] * 255);
    sphere.linesColor_.b = (Uint8)(newLineColor[2] * 255);
    sphere.linesColor_.a = (Uint8)(newLineColor[3] * 255);
  }

  // Orbit center
  ImGui::DragFloat3("Orbit Center", &sphere.orbit_center_.x, -10000, 10000);

  // Orbit mov
  ImGui::DragFloat3("Orbit Angle", &sphere.orbit_.x, -0.5, 0.5);

  // Orbit vel if have orbit mov
  ImGui::DragFloat("Orbit Vel", &sphere.orbit_vel_, -100, 100);

  if (ImGui::Button("Stop planet (orbit vel = 0)"))
  {
    sphere.orbit_vel_ = 0.0f;
  }

  // Translate Planets
  Vec3 mov = {0, 0, 0};
  ImGui::DragFloat3("Translate", &mov.x, -1, 1);
  mov.x *= -1;
  mov.z *= -1;
  if (mov.x != 0 || mov.y != 0 || mov.z != 0)
    sphere.translation(mov);

  // Rotate Planets
  Vec3 rot = {0, 0, 0};
  ImGui::DragFloat3("Rotate", &rot.x, -1, 1);
  rot.x *= -1;
  rot.y *= -1;
  if (rot.x != 0 || rot.y != 0 || rot.z != 0)
    sphere.rotation(rot);

  // Escale Planets
  Vec3 scale = {1, 1, 1};
  ImGui::DragFloat3("Scale", &scale.x, 0, 2);
  if (scale.x != 1 || scale.y != 1 || scale.z != 1)
    sphere.scale(scale);

  // Escale Planets in the 3 axis
  float eScale = 1;
  ImGui::DragFloat("Equal scale", &eScale, 0, 2);
  if (eScale != 1)
    sphere.scale({eScale, eScale, eScale});
}

void Cubes_Controls(Cube &cube)
{
  ImGui::Text("Type: cube, %d triangles", cube.getFaces()*2);
  ImGui::Text("Size: %d", cube.getSize());

  char str[50];
  memset(str, 0, sizeof(str));
  snprintf(str, 50, "Translation %f, %f, %f", cube.mov_.x, cube.mov_.y, cube.mov_.z);
  ImGui::Text("%s", str);

  // Render Light
  ImGui::Checkbox("Render Light?", &cube.renderLight_);

  // Dots draw change
  ImGui::Checkbox("Fill?", &cube.fill_);

  // Color change
  float newFillColor[4];
  newFillColor[0] = (float)cube.fillColor_.r / 255;
  newFillColor[1] = (float)cube.fillColor_.g / 255;
  newFillColor[2] = (float)cube.fillColor_.b / 255;
  newFillColor[3] = (float)cube.fillColor_.a / 255;
  ImGui::ColorEdit4("Fill/Dots Color", newFillColor);
  cube.fillColor_.r = (Uint8)(newFillColor[0] * 255);
  cube.fillColor_.g = (Uint8)(newFillColor[1] * 255);
  cube.fillColor_.b = (Uint8)(newFillColor[2] * 255);
  cube.fillColor_.a = (Uint8)(newFillColor[3] * 255);

  ImGui::Checkbox("Lines Draw?", &cube.lines_);
  if (cube.lines_)
  {
    // Color change
    float newLineColor[4];
    newLineColor[0] = (float)cube.linesColor_.r / 255;
    newLineColor[1] = (float)cube.linesColor_.g / 255;
    newLineColor[2] = (float)cube.linesColor_.b / 255;
    newLineColor[3] = (float)cube.linesColor_.a / 255;
    ImGui::ColorEdit4("Lines Color", newLineColor);
    cube.linesColor_.r = (Uint8)(newLineColor[0] * 255);
    cube.linesColor_.g = (Uint8)(newLineColor[1] * 255);
    cube.linesColor_.b = (Uint8)(newLineColor[2] * 255);
    cube.linesColor_.a = (Uint8)(newLineColor[3] * 255);
  }

  // Orbit center
  ImGui::DragFloat3("Orbit Center", &cube.orbit_center_.x, -10000, 10000);

  // Orbit mov
  ImGui::DragFloat3("Orbit Angle", &cube.orbit_.x, -0.5, 0.5);

  // Orbit vel if have orbit mov
  ImGui::DragFloat("Orbit Vel", &cube.orbit_vel_, -100, 100);

  if (ImGui::Button("Stop planet (orbit vel = 0)"))
  {
    cube.orbit_vel_ = 0.0f;
  }

  // Translate Planets
  Vec3 mov = {0, 0, 0};
  ImGui::DragFloat3("Translate", &mov.x, -1, 1);
  mov.x *= -1;
  mov.z *= -1;
  if (mov.x != 0 || mov.y != 0 || mov.z != 0)
    cube.translation(mov);

  // Rotate Planets
  Vec3 rot = {0, 0, 0};
  ImGui::DragFloat3("Rotate", &rot.x, -1, 1);
  rot.x *= -1;
  rot.y *= -1;
  if (rot.x != 0 || rot.y != 0 || rot.z != 0)
    cube.rotation(rot);

  // Escale Planets
  Vec3 scale = {1, 1, 1};
  ImGui::DragFloat3("Scale", &scale.x, 0, 2);
  if (scale.x != 1 || scale.y != 1 || scale.z != 1)
    cube.scale(scale);

  // Escale Planets in the 3 axis
  float eScale = 1;
  ImGui::DragFloat("Equal scale", &eScale, 0, 2);
  if (eScale != 1)
    cube.scale({eScale, eScale, eScale});
}

void Figures_Controls(Figure &figure)
{
  ImGui::Text("Type: figure, %d triangles", figure.getFaces());
  ImGui::Text("Size: %d", figure.getSize());

  char str[50];
  memset(str, 0, sizeof(str));
  snprintf(str, 50, "Translation %f, %f, %f", figure.mov_.x, figure.mov_.y, figure.mov_.z);
  ImGui::Text("%s", str);

  // Render Light
  ImGui::Checkbox("Render Light?", &figure.renderLight_);

  // Dots draw change
  ImGui::Checkbox("Fill?", &figure.fill_);

  // Color change
  float newFillColor[4];
  newFillColor[0] = (float)figure.fillColor_.r / 255;
  newFillColor[1] = (float)figure.fillColor_.g / 255;
  newFillColor[2] = (float)figure.fillColor_.b / 255;
  newFillColor[3] = (float)figure.fillColor_.a / 255;
  ImGui::ColorEdit4("Fill/Dots Color", newFillColor);
  figure.fillColor_.r = (Uint8)(newFillColor[0] * 255);
  figure.fillColor_.g = (Uint8)(newFillColor[1] * 255);
  figure.fillColor_.b = (Uint8)(newFillColor[2] * 255);
  figure.fillColor_.a = (Uint8)(newFillColor[3] * 255);

  ImGui::Checkbox("Lines Draw?", &figure.lines_);
  if (figure.lines_)
  {
    // Color change
    float newLineColor[4];
    newLineColor[0] = (float)figure.linesColor_.r / 255;
    newLineColor[1] = (float)figure.linesColor_.g / 255;
    newLineColor[2] = (float)figure.linesColor_.b / 255;
    newLineColor[3] = (float)figure.linesColor_.a / 255;
    ImGui::ColorEdit4("Lines Color", newLineColor);
    figure.linesColor_.r = (Uint8)(newLineColor[0] * 255);
    figure.linesColor_.g = (Uint8)(newLineColor[1] * 255);
    figure.linesColor_.b = (Uint8)(newLineColor[2] * 255);
    figure.linesColor_.a = (Uint8)(newLineColor[3] * 255);
  }

  // Orbit center
  ImGui::DragFloat3("Orbit Center", &figure.orbit_center_.x, -10000, 10000);

  // Orbit mov
  ImGui::DragFloat3("Orbit Angle", &figure.orbit_.x, -0.5, 0.5);

  // Orbit vel if have orbit mov
  ImGui::DragFloat("Orbit Vel", &figure.orbit_vel_, -100, 100);

  if (ImGui::Button("Stop planet (orbit vel = 0)"))
  {
    figure.orbit_vel_ = 0.0f;
  }

  // Translate Planets
  Vec3 mov = {0, 0, 0};
  ImGui::DragFloat3("Translate", &mov.x, -1, 1);
  mov.x *= -1;
  mov.z *= -1;
  if (mov.x != 0 || mov.y != 0 || mov.z != 0)
    figure.translation(mov);

  // Rotate Planets
  Vec3 rot = {0, 0, 0};
  ImGui::DragFloat3("Rotate", &rot.x, -1, 1);
  rot.x *= -1;
  rot.y *= -1;
  if (rot.x != 0 || rot.y != 0 || rot.z != 0)
    figure.rotation(rot);

  // Escale Planets
  Vec3 scale = {1, 1, 1};
  ImGui::DragFloat3("Scale", &scale.x, 0, 2);
  if (scale.x != 1 || scale.y != 1 || scale.z != 1)
    figure.scale(scale);

  // Escale Planets in the 3 axis
  float eScale = 1;
  ImGui::DragFloat("Equal scale", &eScale, 0, 2);
  if (eScale != 1)
    figure.scale({eScale, eScale, eScale});
}
