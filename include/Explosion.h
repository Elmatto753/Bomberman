/*
 Copyright 2015 Matt Skellon
 1st Year SDAGE PPP Assignment 2
*/

/// \file Explosion.h
/// \brief Handles the processes associated with the explosion of a bomb, namely the displaying of the explosion texture
/// \author Matthew Skellon
/// \version 1.0
/// \date 4/5/15 Initial Doxygen file creation, updated to NCCA Coding Standard

#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include <string>
#include "Scene.h"

class Explosion
{
public :
    Explosion() : m_Life(50)
    {
      ObjLoad("models/Explosion.obj",
              "textures/Explosion.png",
              m_Vertex,
              m_Normal,
              m_Tex,
              m_v_Index,
              m_t_Index,
              m_n_Index,
              m_Texture);

      loadExp();
    }
    ~Explosion(){}

    int     m_Life;
    float   m_xPos;
    float   m_zPos;
    GLuint  m_DisplayList;

    void loadExp();

private :
    std::vector<Vec3> m_Vertex;
    std::vector<Vec3> m_Normal;
    std::vector<Vec3> m_Tex;
    std::vector<Vec3> m_Face;
    std::vector<int>  m_v_Index;
    std::vector<int>  m_t_Index;
    std::vector<int>  m_n_Index;
    GLuint            m_Texture;
};


#endif
