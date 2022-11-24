#include <objects.h>

void Not_Set_Controls(Objects &object){
  ImGui::Text("Type: notSet");

  char str[50];
  memset(str, 0, sizeof(str));
  snprintf(str, 50, "set sphere: %d, set cube: %d", typeSphere, typeCube);
  ImGui::Text("%s",str);
  static int type;
  ImGui::DragInt("Type", &type, 0.25f, 0, MAX_OBJECTS_TYPE-1);

  static SDL_Color color = {0,0,0,255};
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

  static bool fill; false;
  ImGui::Checkbox("Fill?", &object.cube.fill_);

  static MV::Pnt3 scale = {1, 1, 1};
  ImGui::SliderFloat3("Scale", &scale.x, -1000, 1000);

  static MV::Pnt3 mov = {0, 0, 0};
  ImGui::SliderFloat3("Translate", &mov.x, -10000, 10000);

  static MV::Pnt3 rot = {0, 0, 0};
  ImGui::SliderFloat3("Rotate", &rot.x, -10000, 10000);

  static MV::Pnt3 orbit = {0, 0, 0};
  ImGui::SliderFloat3("Orbit Angle", &orbit.x, -0.5, 0.5);

  static MV::Pnt3 orbit_center = {0, 0, 0};
  ImGui::SliderFloat3("Orbit Center", &orbit_center.x, -10000, 10000);

  static int res = 10;

  if(type == typeSphere) ImGui::DragInt("Res", &res, 0.25f, 0, 50);

  if(ImGui::Button("Set new values")){
    object.type=type;
    switch (type) {
      case typeSphere:
        object.sphere.init(color, fill, res, scale, mov, rot, orbit, orbit_center);
      break;
      case typeCube:
        object.cube.init(color, fill, scale, mov, rot, orbit, orbit_center);
      break;
    }
    type = 0;
    color = {0,0,0,255}; fill = false; res = 10; scale = {1,1,1}; mov = {0,0,0}; rot = {0,0,0}; orbit = {0,0,0}; orbit_center = {0,0,0};
  }
}

void Spheres_Controls(Objects &object){
  ImGui::Text("Type: sphere");

  char str[50];
  memset(str, 0, sizeof(str));
  snprintf(str, 50, "Translation %f, %f, %f", object.sphere.mov_.x, object.sphere.mov_.y, object.sphere.mov_.z);
  ImGui::Text("%s",str);

  // Dots draw change
  ImGui::Checkbox("Fill?", &object.sphere.fill_);

  // Color change
  float newColor[4];
  newColor[0] = (float)object.sphere.color_.r / 255;
  newColor[1] = (float)object.sphere.color_.g / 255;
  newColor[2] = (float)object.sphere.color_.b / 255;
  newColor[3] = (float)object.sphere.color_.a / 255;
  ImGui::ColorEdit4("Color", newColor);
  object.sphere.color_.r = (Uint8)(newColor[0] * 255);
  object.sphere.color_.g = (Uint8)(newColor[1] * 255);
  object.sphere.color_.b = (Uint8)(newColor[2] * 255);
  object.sphere.color_.a = (Uint8)(newColor[3] * 255);

  // Orbit center
  ImGui::SliderFloat3("Orbit Center", &object.sphere.orbit_center_.x, -10000, 10000);

  // Orbit mov
  ImGui::SliderFloat3("Orbit Angle", &object.sphere.orbit_.x, -0.5, 0.5);

  // Orbit vel if have orbit mov
  ImGui::SliderFloat("Orbit Vel", &object.sphere.orbit_vel_, -100, 100);

  if (ImGui::Button("Stop planet (orbit vel = 0)")){
    object.sphere.orbit_vel_=0.0f;
  }

  // Translate Planets
  MV::Vec3 mov = {0, 0, 0};
  ImGui::SliderFloat3("Translate", &mov.x, -1, 1);
  mov.x *= -1;
  mov.z *= -1;
  if (mov.x != 0 || mov.y != 0 || mov.z != 0)
    object.sphere.translation(mov);

  // Rotate Planets
  MV::Vec3 rot = {0, 0, 0};
  ImGui::SliderFloat3("Rotate", &rot.x, -1, 1);
  rot.x *= -1;
  rot.y *= -1;
  if (rot.x != 0 || rot.y != 0 || rot.z != 0)
    object.sphere.rotation(rot);

  // Escale Planets
  MV::Vec3 scale = {1, 1, 1};
  ImGui::SliderFloat3("Scale", &scale.x, 0, 2);
  if (scale.x != 1 || scale.y != 1 || scale.z != 1)
    object.sphere.scale(scale);

  // Escale Planets in the 3 axis
  float eScale = 1;
  ImGui::SliderFloat("Equal scale", &eScale, 0, 2);
  if (eScale!=1)
    object.sphere.scale({eScale, eScale, eScale});
}

void Cubes_Controls(Objects &object){
  ImGui::Text("Type: cube");

  char str[50];
  memset(str, 0, sizeof(str));
  snprintf(str, 50, "Translation %f, %f, %f", object.cube.mov_.x, object.cube.mov_.y, object.cube.mov_.z);
  ImGui::Text("%s",str);

  // Dots draw change
  ImGui::Checkbox("Fill?", &object.cube.fill_);

  // Color change
  float newColor[4];
  newColor[0] = (float)object.cube.color_.r / 255;
  newColor[1] = (float)object.cube.color_.g / 255;
  newColor[2] = (float)object.cube.color_.b / 255;
  newColor[3] = (float)object.cube.color_.a / 255;
  ImGui::ColorEdit4("Color", newColor);
  object.cube.color_.r = (Uint8)(newColor[0] * 255);
  object.cube.color_.g = (Uint8)(newColor[1] * 255);
  object.cube.color_.b = (Uint8)(newColor[2] * 255);
  object.cube.color_.a = (Uint8)(newColor[3] * 255);

  // Orbit center
  ImGui::SliderFloat3("Orbit Center", &object.cube.orbit_center_.x, -10000, 10000);

  // Orbit mov
  ImGui::SliderFloat3("Orbit Angle", &object.cube.orbit_.x, -0.5, 0.5);

  // Orbit vel if have orbit mov
  ImGui::SliderFloat("Orbit Vel", &object.cube.orbit_vel_, -100, 100);

  if (ImGui::Button("Stop planet (orbit vel = 0)")){
    object.cube.orbit_vel_=0.0f;
  }

  // Translate Planets
  MV::Vec3 mov = {0, 0, 0};
  ImGui::SliderFloat3("Translate", &mov.x, -1, 1);
  mov.x *= -1;
  mov.z *= -1;
  if (mov.x != 0 || mov.y != 0 || mov.z != 0)
    object.cube.translation(mov);

  // Rotate Planets
  MV::Vec3 rot = {0, 0, 0};
  ImGui::SliderFloat3("Rotate", &rot.x, -1, 1);
  rot.x *= -1;
  rot.y *= -1;
  if (rot.x != 0 || rot.y != 0 || rot.z != 0)
    object.cube.rotation(rot);

  // Escale Planets
  MV::Vec3 scale = {1, 1, 1};
  ImGui::SliderFloat3("Scale", &scale.x, 0, 2);
  if (scale.x != 1 || scale.y != 1 || scale.z != 1)
    object.cube.scale(scale);

  // Escale Planets in the 3 axis
  float eScale = 1;
  ImGui::SliderFloat("Equal scale", &eScale, 0, 2);
  if (eScale!=1)
    object.cube.scale({eScale, eScale, eScale});
}
