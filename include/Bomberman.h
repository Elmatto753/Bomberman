/*
 Copyright 2015 Matt Skellon
 1st Year SDAGE PPP Assignment 2
*/

/// \file Bomberman.h
/// \brief Handles the processes associated with the player character's creation, allowing movement, position and rotation
/// \author Matthew Skellon
/// \version 1.0
/// \date 4/5/15 Initial Doxygen file creation, updated to NCCA Coding Standard

#ifndef BOMBERMAN_H_
#define BOMBERMAN_H_

#include <string>
#include "Scene.h"

class Bomberman
{
public :
    Bomberman() : m_CanMoveUp(true),
                  m_CanMoveDown(true),
                  m_CanMoveLeft(true),
                  m_CanMoveRight(true)
    {
      ObjLoad("models/Bomberman.obj",
              "textures/Bomberman_Texture.png",
              m_Vertex,
              m_Normal,
              m_Tex,
              m_v_Index,
              m_t_Index,
              m_n_Index,
              m_Texture);

      loadBMan();
      m_xMove=1;
      m_zMove=1;
    }
    ~Bomberman(){}

    GLuint  m_DisplayList;
    float   m_xMove;
    float   m_zMove;
    int     m_Rot;
    bool    m_CanMoveUp;
    bool    m_CanMoveDown;
    bool    m_CanMoveLeft;
    bool    m_CanMoveRight;

    void loadBMan();
    void update();

protected :
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
