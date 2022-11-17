#include <esfera_3d.h>

// Obtiene los puntos de la esfera
void Esfera::obtenerEsfera()
{
    vertices_ = (2 * res_) * (res_ + 1);

    float incremento = (PI / res_);

    int i = 0;
    for (int fila = 0; fila <= res_; fila++)
    {
        for (int columna = 0; columna < (2 * res_); columna++)
        {
            (points_ + i)->z = ((float)sin(fila * incremento)) * ((float)cos(columna * incremento));
            (points_ + i)->x = ((float)sin(fila * incremento)) * ((float)sin(columna * incremento));
            (points_ + i)->y = ((float)cos(fila * incremento));
            i++;
        }
    }

    i = 0;
    for (int filas = 0; filas <= res_; filas++)
    {
        for (int columnas = 0; columnas < (res_ * 2); columnas++)
        {
            caras[i].n_points = 4;
            caras[i].points = (int *)calloc(caras[i].n_points, sizeof(int));

            caras[i].points[0] = i;
            caras[i].points[1] = i + 1;
            caras[i].points[2] = ((filas + 1) * res_ * 2) + columnas + 1;
            caras[i].points[3] = ((filas + 1) * res_ * 2) + columnas;

            if (columnas + 1 == res_ * 2)
            {
                caras[i].points[1] = (filas * res_ * 2);
                caras[i].points[2] = ((filas + 1) * res_ * 2);
            }
            if (filas + 1 > res_)
            {
                caras[i].points[2] = ((filas)*res_ * 2) + columnas + 1;
                caras[i].points[3] = ((filas)*res_ * 2) + columnas;
            }
            if (filas + 1 > res_ && columnas + 1 == res_ * 2)
            {
                caras[i].points[2] = ((filas)*res_ * 2) + columnas;
            }

            i++;
        }
    }

    for (int i = 0; i < vertices_; i++)
    {
        centros_[i] = Vec_Resta(points_[caras[i].points[0]], points_[caras[i].points[2]]);
        centros_[i] = Vec_Escalado(centros_[i], 0.5f);
        centros_[i] = Vec_Sum(centros_[i], points_[caras[i].points[2]]);
    }
}

// Inicializa la esfera
Esfera::Esfera()
{
    escala_ = {0, 0, 0};
    rotado_ = {0, 0, 0};
    res_ = 0;
    dim_ = 0;
    vertices_ = 0;
    desp_ = {0, 0, 0};
    orbita_ = {0, 0, 0};
    centro_orbita_ = {0, 0, 0};
    color_ = {0, 0, 0};
};

void Esfera::init(SDL_Color color, int res, MV::Pnt3 escala, MV::Pnt3 desp, MV::Pnt3 rot, MV::Pnt3 orbita, MV::Pnt3 centro_orbita)
{
    color_ = color;
    res_ = res;
    orbita_ = orbita;
    centro_orbita_ = centro_orbita;
    rotado_ = {0, 0, 0};
    escala_ = {1, 1, 1};
    dim_ = 1;
    desp_ = {0, 0, 0};

    obtenerEsfera();

    if ((escala.x + escala.y + escala.z) != 3)
        escalar(escala);

    if ((desp.x + desp.y + desp.z) != 0)
        desplazar(desp);

    if ((rot.x + rot.y + rot.z) != 0)
        rotar(rot);
}

MV::Pnt3 Esfera::point(int i)
{
    return *(points_ + i);
}

void Esfera::rotar(MV::Pnt3 p_rot)
{
    rotado_ = MV::Vec_Sum(rotado_, p_rot);
    if (rotado_.x >= 360)
        rotado_.x -= 360;
    if (rotado_.y >= 360)
        rotado_.y -= 360;
    if (rotado_.z >= 360)
        rotado_.z -= 360;

    MV::Mat4 rot_x;
    if (p_rot.x != 0)
        rot_x = MV::Mat4RotateX((p_rot.x * PI) / 180);

    MV::Mat4 rot_y;
    if (p_rot.y != 0)
        rot_y = MV::Mat4RotateY((p_rot.y * PI) / 180);

    MV::Mat4 rot_z;
    if (p_rot.z != 0)
        rot_z = MV::Mat4RotateZ((p_rot.z * PI) / 180);

    MV::Mat4 model = MV::Mat4Identity();
    if (p_rot.x != 0)
        model = MV::Mat4Multiply(model, rot_x);
    if (p_rot.y != 0)
        model = MV::Mat4Multiply(model, rot_y);
    if (p_rot.z != 0)
        model = MV::Mat4Multiply(model, rot_z);

    MV::Pnt3 desp__ = desp_;
    desplazar({-desp_.x, -desp_.y, -desp_.z});
    for (int i = 0; i < vertices_; i++)
    {
        *(points_ + i) = MV::Mat4TransformVec3(model, *(points_ + i));
        *(centros_ + i) = MV::Mat4TransformVec3(model, *(centros_ + i));
    }
    desplazar(desp__);
}

void Esfera::orbitar(float vel)
{
    MV::Pnt3 p_orbita_ = MV::Vec_Escalado(orbita_, vel);

    MV::Mat4 rot_x;
    MV::Mat4 rot_y;
    MV::Mat4 rot_z;

    if (p_orbita_.x != 0)
        rot_x = MV::Mat4RotateX((p_orbita_.x * PI) / 180);
    if (p_orbita_.y != 0)
        rot_y = MV::Mat4RotateY((p_orbita_.y * PI) / 180);
    if (p_orbita_.z != 0)
        rot_z = MV::Mat4RotateZ((p_orbita_.z * PI) / 180);

    MV::Mat4 model = MV::Mat4Identity();
    if (p_orbita_.x != 0)
        model = MV::Mat4Multiply(model, rot_x);
    if (p_orbita_.y != 0)
        model = MV::Mat4Multiply(model, rot_y);
    if (p_orbita_.z != 0)
        model = MV::Mat4Multiply(model, rot_z);

    desplazar(MV::Vec3{-centro_orbita_.x, -centro_orbita_.y, -centro_orbita_.z});
    desp_ = MV::Mat4TransformVec3(model, desp_);
    for (int i = 0; i < vertices_; i++)
    {
        *(points_ + i) = MV::Mat4TransformVec3(model, *(points_ + i));
        *(centros_ + i) = MV::Mat4TransformVec3(model, *(centros_ + i));
    }
    desplazar(centro_orbita_);
}

void Esfera::desplazar(MV::Pnt3 p_desp_)
{
    desp_ = MV::Vec_Sum(desp_, p_desp_);
    for (int i = 0; i < vertices_; i++)
    {
        *(points_ + i) = MV::Vec_Sum(*(points_ + i), p_desp_);
        *(centros_ + i) = MV::Vec_Sum(*(centros_ + i), p_desp_);
    }
}

void Esfera::escalar(MV::Pnt3 p_escala_)
{
    escala_ = MV::Vec_Escalado(escala_, p_escala_);
    dim_ = p_escala_.x * dim_;

    MV::Mat4 m_escala_ = MV::Mat4Scale(p_escala_);

    MV::Mat4 model = MV::Mat4Identity();
    model = MV::Mat4Multiply(model, m_escala_);

    MV::Pnt3 desp__ = desp_;
    desplazar({-desp_.x, -desp_.y, -desp_.z});
    for (int i = 0; i < vertices_; i++)
    {
        *(points_ + i) = MV::Mat4TransformVec3(model, *(points_ + i));
        *(centros_ + i) = MV::Mat4TransformVec3(model, *(centros_ + i));
    }
    desplazar(desp__);
}

void Esfera::inputs(Keys *keys)
{
    if (EVENT_DOWN(DOWN, keys))
        rotar({1.0f, 0.0f, 0.0f});
    if (EVENT_DOWN(UP, keys))
        rotar({-1.0f, 0.0f, 0.0f});
    if (EVENT_DOWN(RIGHT, keys))
        rotar({0.0f, 1.0f, 0.0f});
    if (EVENT_DOWN(LEFT, keys))
        rotar({0.0f, -1.0f, 0.0f});
    if (EVENT_DOWN(K_z, keys))
        rotar({0.0f, 0.0f, -1.0f});
    if (EVENT_DOWN(K_x, keys))
        rotar({0.0f, 0.0f, 1.0f});

    if (EVENT_DOWN(K_a, keys))
        desplazar({-0.1f, 0.0f, 0.0f});
    if (EVENT_DOWN(K_d, keys))
        desplazar({0.1f, 0.0f, 0.0f});
    if (EVENT_DOWN(K_w, keys))
        desplazar({0.0f, -0.1f, 0.0f});
    if (EVENT_DOWN(K_s, keys))
        desplazar({0.0f, 0.1f, 0.0f});
    if (EVENT_DOWN(K_q, keys))
        desplazar({0.0f, 0.0f, 0.1f});
    if (EVENT_DOWN(K_e, keys))
        desplazar({0.0f, 0.0f, -0.1f});

    if (EVENT_DOWN(SHIFT, keys))
        escalar({0.9f, 0.9f, 0.9f});
    if (EVENT_DOWN(SPACE, keys))
        escalar({1.1f, 1.1f, 1.1f});
}

void Esfera::draw(Keys *keys, SDL_Renderer *render, Render drawRender, MV::Pnt3 light, bool puntos)
{

    // Transformacion de puntos 2D
    MV::Mat3 model = MV::Mat3Identity();
    MV::Mat3 scala = MV::Mat3Scale(drawRender.getRenderScale());
    MV::Mat3 desp;

    if ((centro_orbita_.x + centro_orbita_.y + centro_orbita_.z) == 0)
    {
        desp = MV::Mat3Translate({desp_.x,desp_.y});
    }
    else
    {
        desp = MV::Mat3Translate(MV::Vec3_Tr_Vec2(centro_orbita_));
    }
    model = MV::Mat3Multiply(desp, scala);

    for (int i = 0; i < vertices_; i++)
    {
        draw_sdl_[i] = drawRender.renderPoint(points_[i], desp_, light, color_, model);
    }

    // This is to draw with texture | light
    if (!puntos)
    {
        // Ordenado de puntos
        static int *order = (int *)calloc(vertices_, sizeof(int));

        for (int i = 0; i < vertices_; i++)
            order[i] = i;

        for (int i = 0; i < vertices_; i++)
        {
            for (int j = 1; j < vertices_; j++)
            {
                if (MV::Vec_Magn(MV::Vec_Resta(centros_[order[i]], drawRender.camara_)) >= MV::Vec_Magn(MV::Vec_Resta(centros_[order[j]], drawRender.camara_)))
                {
                    int aux = order[i];
                    order[i] = order[j];
                    order[j] = aux;
                }
            }
        }

        for (int i = 0; i < vertices_ - 1; i++)
        {
            int aux = order[i];
            order[i] = order[i + 1];
            order[i + 1] = aux;
        }

        // Draw Triangles
        for (int i = 0; i < vertices_; i++)
        {
          static SDL_Vertex triangle[3];
          triangle[0] = draw_sdl_[caras[order[i]].points[0]].point;
          triangle[1] = draw_sdl_[caras[order[i]].points[1]].point;
          triangle[2] = draw_sdl_[caras[order[i]].points[2]].point;

          static SDL_Vertex triangle1[3];
          triangle1[0] = draw_sdl_[caras[order[i]].points[3]].point;
          triangle1[1] = draw_sdl_[caras[order[i]].points[2]].point;
          triangle1[2] = draw_sdl_[caras[order[i]].points[0]].point;

          /*
          static SDL_Vertex square[4];
          square[0] = draw_sdl_[caras[order[i]].points[0]];
          square[1] = draw_sdl_[caras[order[i]].points[1]];
          square[2] = draw_sdl_[caras[order[i]].points[2]];
          square[3] = draw_sdl_[caras[order[i]].points[3]];
          SDL_RenderGeometry(render, NULL, square, 4, NULL, 0);
          */
          bool draw = false;
          for(int j = 0; j < 4; j++){
            draw = (draw || draw_sdl_[caras[order[i]].points[j]].active);
          }

          if(draw){
            SDL_RenderGeometry(render, NULL, triangle, 3, NULL, 0);
            SDL_RenderGeometry(render, NULL, triangle1, 3, NULL, 0);
          }
        }
    }
    else
    {
        // That is for points_
        for (int i = 0; i < vertices_; i++)
        {
            SDL_SetRenderDrawColor(render, RGBA(draw_sdl_[i].point.color));
            SDL_RenderDrawPoint(render, draw_sdl_[i].point.position.x, draw_sdl_[i].point.position.y);
        }
    }
}

void Esfera::imprime()
{

    std::cout << "Points: " << std::endl;
    for (int i = 0; i < vertices_; i++)
    {
        char *c = (char *)calloc(25, sizeof(char));
        sprintf(c, "point:%d", i);
        MV::Vec_Print(*(points_ + i), c);

        DESTROY(c);
    }

    std::cout << std::endl;
    MV::Vec_Print(desp_, "Desp");
    std::cout << std::endl;
    MV::Vec_Print(rotado_, "Rotado");
    std::cout << std::endl;
    MV::Vec_Print(escala_, "Escala");
    std::cout << std::endl;
}

Esfera::~Esfera()
{

    if (caras != NULL)
    {
        for (int i = 0; i < vertices_; i++)
        {
            DESTROY(caras[i].points);
        }
    }
}
