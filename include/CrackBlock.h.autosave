/*
 Copyright 2015 Matt Skellon
 1st Year SDAGE PPP Assignment 2
*/

/// \file CrackBlock.h
/// \brief Handles the processes associated with the creation of the breakable "cracked rocks". The destruction of each individual rock is handled in MapLoader.h
/// \author Matthew Skellon
/// \version 1.0
/// \date 4/5/15 Initial Doxygen file creation, updated to NCCA Coding Standard

#ifndef CRACKBLOCK_H_
#define CRACKBLOCK_H_

#include <string>
#include "Scene.h"

class CrackBlock
{
public :
    CrackBlock()
    {
      ObjLoad("models/Crack_Block.obj",
              "textures/CrackedBlockTexture.png",
              m_Vertex,
              m_Normal,
              m_Tex,
              m_v_Index,
              m_t_Index,
              m_n_Index,
              m_Texture);

      loadCBlock();
    }
    ~CrackBlock(){}

    GLuint m_DisplayList;

    void loadCBlock();

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
