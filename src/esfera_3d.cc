#include <esfera_3d.h>


        // Obtiene los puntos de la esfera
    void Esfera::obtenerEsfera()
    {
        vertices_ = (2 * res_) * (res_ + 1);

        points_ = (MV::Pnt3 *)calloc(vertices_, sizeof(MV::Pnt3));
        centros_ = (MV::Pnt3 *)calloc(vertices_, sizeof(MV::Pnt3));
        caras = (Caras *)calloc(vertices_, sizeof(Caras));

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

        for(int i=0; i<vertices_; i++)
        {
          centros_[i]=Vec_Resta(points_[caras[i].points[0]], points_[caras[i].points[2]]);
          centros_[i]=Vec_Escalado(centros_[i], 0.5f);
          centros_[i]=Vec_Sum(centros_[i], points_[caras[i].points[2]]);
        }
    }

    // Inicializa la esfera
    Esfera::Esfera(SDL_Color color, int p_res_, MV::Pnt3 p_escala_, MV::Pnt3 p_desp_, MV::Pnt3 p_rot, MV::Pnt3 p_orbita_, MV::Pnt3 centro_orbita)
    {
        color_ = color;
        res_ = p_res_;
        orbita_ = p_orbita_;
        centro_orbita_ = centro_orbita;
        rotado_ = {0, 0, 0};
        escala_ = {1, 1, 1};
        dim_ = 1;
        desp_ = {0, 0, 0};

        obtenerEsfera();

        if ((p_escala_.x + p_escala_.x + p_escala_.x) != 3)
        {
            escalar(p_escala_);
        }
        desplazar(p_desp_);
        rotar(p_rot);
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

        desplazar({-centro_orbita_.x, -centro_orbita_.y, -centro_orbita_.z});
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

    SDL_Color Esfera::obtenerColorLight(MV::Pnt3 point, MV::Pnt3 light)
    {

        SDL_Color ret = color_;

        float angleRest = 255 / 180;

        MV::Vec3 vector = MV::Vec_Resta(point, desp_);  // Vector director contrario al centro desde el punto
        MV::Vec3 vector1 = MV::Vec_Resta(desp_, light); // Vector director apuntando al centro desde la luz

        vector = MV::Normalizar_Vec(vector);
        vector1 = MV::Normalizar_Vec(vector1);

        float angulo = Obten_Angulo(vector, vector1);

        if (angulo < 0)
            angulo *= -1;

        if(angulo>130) angulo+=(130-angulo);
        angleRest *= (angulo+50);

        if(ret.r>0) ret.r -= (Uint8)angleRest;
        if(ret.g>0) ret.g -= (Uint8)angleRest;
        if(ret.a>0) ret.b -= (Uint8)angleRest;
        ret.a = SDL_ALPHA_OPAQUE;

        if(ret.r<0) ret.r=0;
        if(ret.g<0) ret.g=0;
        if(ret.b<0) ret.b=0;

        return ret;
    }

    void Esfera::obtenerSDLVertex(MV::Pnt3 light, MV::Pnt2 draw, MV::Pnt3 point)
    {
      SDL_Color color;
      color = obtenerColorLight(point, light);
      SDL_Vertex valor = {{draw.x,draw.y}, color, {0, 0}};
      draw_sdl_.push_back(valor);
    }

    void Esfera::draw(SDL_Renderer *render, MV::Pnt3 camara /* Ubicacion de la camara */, MV::Pnt3 mira, MV::Pnt3 light, bool puntos)
    {
        // Proyeccion de puntos 3D a 2D teniendo en cuenta la camara
        MV::Mat4 vMatrix = MV::Mat4View(camara, mira);
        MV::Mat4 pro = MV::Mat4Projection();
        vMatrix = MV::Mat4Multiply(pro, vMatrix);

        // Transformacion de puntos 2D
        MV::Mat3 model = MV::Mat3Identity();
        MV::Mat3 scala = MV::Mat3Scale({200, 200});
        MV::Mat3 desp;

        if ((centro_orbita_.x + centro_orbita_.y + centro_orbita_.z) == 0)
        {
            desp = MV::Mat3Translate(MV::Vec3_Tr_Vec2(desp_));
        }
        else
        {
            desp = MV::Mat3Translate(MV::Vec3_Tr_Vec2(centro_orbita_));
        }
        model = MV::Mat3Multiply(desp, scala);

        MV::Pnt2 draw;

        draw_sdl_.clear();
        for (int i = 0; i < vertices_; i++)
        {
            MV::Vec3 new_point = MV::Mat4TransformVec3(vMatrix, *(points_ + i));
            draw = MV::Vec3_Tr_Vec2(new_point);

            new_point = MV::Vec2_Tr_Vec3(draw, 1);

            new_point = MV::Mat3TransformVec3(model, new_point);

            draw = MV::Vec3_Tr_Vec2(new_point);
            obtenerSDLVertex(light, draw, *(points_ + i));
        }


        // Dibujado de puntos
        if (!puntos)
        {
            int *order = (int *)calloc(vertices_, sizeof(int));

            for (int i = 0; i < vertices_; i++)
                order[i] = i;

            for (int i = 0; i < vertices_; i++)
            {
                for (int j = 1; j < vertices_; j++)
                {
                    if (MV::Vec_Magn(MV::Vec_Resta(centros_[order[i]],camara)) <= MV::Vec_Magn(MV::Vec_Resta(centros_[order[j]],camara)))
                    {
                        int aux = order[i];
                        order[i] = order[j];
                        order[j] = aux;
                    }
                }
            }

            for(int i=0; i<vertices_-1; i++){
              int aux=order[i];
              order[i]=order[i+1];
              order[i+1]=aux;
            }

            // That is for lines
            for (int i = 0; i < vertices_; i++)
            {
                SDL_Vertex *point = (SDL_Vertex *)calloc(3, sizeof(SDL_Vertex));
                point[0] = draw_sdl_.at(caras[order[i]].points[0]);
                point[1] = draw_sdl_.at(caras[order[i]].points[1]);
                point[2] = draw_sdl_.at(caras[order[i]].points[2]);

                SDL_Vertex *point1 = (SDL_Vertex *)calloc(3, sizeof(SDL_Vertex));
                point1[1] = draw_sdl_.at(caras[order[i]].points[3]);
                point1[0] = draw_sdl_.at(caras[order[i]].points[2]);
                point1[2] = draw_sdl_.at(caras[order[i]].points[0]);

                SDL_RenderGeometry(render, NULL, point, 3, NULL, 0);
                SDL_RenderGeometry(render, NULL, point1, 3, NULL, 0);

                DESTROY(point);
            }
        }
        else
        {
            // That is for points_
            for (int i = 0; i < vertices_; i++)
            {
                SDL_SetRenderDrawColor(render, RGBA(draw_sdl_.at(i).color));
                SDL_RenderDrawPoint(render, draw_sdl_.at(i).position.x, draw_sdl_.at(i).position.y);
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
