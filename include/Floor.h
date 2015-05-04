/*
 Copyright 2015 Matt Skellon
 1st Year SDAGE PPP Assignment 2
*/

/// \file Floor.h
/// \brief Creates and updates the floor of the game
/// \author Matthew Skellon
/// \version 1.0
/// \date 4/5/15 Initial Doxygen file creation, updated to NCCA Coding Standard

#ifndef FLOOR_H_
#define FLOOR_H_

#include <string>
#include "Scene.h"

class Floor
{
public :
    Floor()
    {
      ObjLoad("models/Floor.obj",
              "textures/FloorTexture.png",
              m_Vertex,
              m_Normal,
              m_Tex,
              m_v_Index,
              m_t_Index,
              m_n_Index,
              m_Texture);

      loadFloor();
    }
    ~Floor(){}

    void loadFloor();
    void update();

protected :
    std::vector<Vec3>   m_Vertex;
    std::vector<Vec3>   m_Normal;
    std::vector<Vec3>   m_Tex;
    std::vector<Vec3>   m_Face;
    std::vector<int>    m_v_Index;
    std::vector<int>    m_t_Index;
    std::vector<int>    m_n_Index;
    std::vector<GLuint> m_DisplayList;
    GLuint              m_Texture;

};

#endif
