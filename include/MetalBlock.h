/*
 Copyright 2015 Matt Skellon
 1st Year SDAGE PPP Assignment 2
*/

/// \file MetalBlock.h
/// \brief Handles the processes associated with the creation of the unbreakable "metal blocks".
/// \author Matthew Skellon
/// \version 1.0
/// \date 4/5/15 Initial Doxygen file creation, updated to NCCA Coding Standard

#ifndef METALBLOCK_H_
#define METALBLOCK_H_

#include <string>
#include "Scene.h"

class MetalBlock
{
public :
    MetalBlock()
    {
      ObjLoad("models/Metal_Block.obj",
              "textures/MetalBlockTexture.png",
              m_Vertex,
              m_Normal,
              m_Tex,
              m_v_Index,
              m_t_Index,
              m_n_Index,
              m_Texture);

      loadMBlock();
    }
    ~MetalBlock(){}

    GLuint m_DisplayList;

    void loadMBlock();

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
