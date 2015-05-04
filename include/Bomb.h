/// \file Bomb.h
/// \brief Handles the processes associated with a bomb's creation, lifetime and destruction
/// \author Matthew Skellon
/// \version 1.0
/// \date 4/5/15 Initial Doxygen file creation, updated to NCCA Coding Standard

#ifndef BOMB_H_
#define BOMB_H_

#include <string>
#include "Scene.h"

class Bomb
{
public :
    Bomb() : m_PlaceBomb(false),
             m_CanPlaceBomb(true),
             m_Life(0),
             m_xPos(0),
             m_zPos(0),
             m_Range(2),
             m_NextExpUp(true),
             m_NextExpDown(true),
             m_NextExpLeft(true),
             m_NextExpRight(true)
    {
      ObjLoad("models/Bomb.obj",
              "textures/BombTexture.png",
              m_Vertex,
              m_Normal,
              m_Tex,
              m_v_Index,
              m_t_Index,
              m_n_Index,
              m_Texture);

      loadBomb();
    }
    ~Bomb(){}

    bool    m_PlaceBomb;
    bool    m_CanPlaceBomb;
    int     m_Life;
    float   m_xPos;
    float   m_zPos;
    int     m_Range;
    bool    m_NextExpUp;
    bool    m_NextExpDown;
    bool    m_NextExpLeft;
    bool    m_NextExpRight;
    GLuint  m_DisplayList;

    void loadBomb();

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

#endif // BOMB_H_
