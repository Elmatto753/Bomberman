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
  ///
  /// \brief Bomberman
  ///
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


    //------------------------------------------------------------------------------------------------------------
    /// @brief Storage for some GL functions
    //------------------------------------------------------------------------------------------------------------
    GLuint  m_DisplayList;
    //------------------------------------------------------------------------------------------------------------
    /// @brief The x-position of the player
    //------------------------------------------------------------------------------------------------------------
    float   m_xMove;
    //------------------------------------------------------------------------------------------------------------
    /// @brief The z-position of the player
    //------------------------------------------------------------------------------------------------------------
    float   m_zMove;
    //------------------------------------------------------------------------------------------------------------
    /// @brief The degree of rotation of the player (in 90 degree intervals)
    //------------------------------------------------------------------------------------------------------------
    int     m_Rot;
    //------------------------------------------------------------------------------------------------------------
    /// @brief Allows or disallows movement in the negative-z direction
    //------------------------------------------------------------------------------------------------------------
    bool    m_CanMoveUp;
    //------------------------------------------------------------------------------------------------------------
    /// @brief Allows or disallows movement in the positive-z direction
    //------------------------------------------------------------------------------------------------------------
    bool    m_CanMoveDown;
    //------------------------------------------------------------------------------------------------------------
    /// @brief Allows or disallows movement in the negative-x direction
    //------------------------------------------------------------------------------------------------------------
    bool    m_CanMoveLeft;
    //------------------------------------------------------------------------------------------------------------
    /// @brief Allows or disallows movement in the positive-z direction
    //------------------------------------------------------------------------------------------------------------
    bool    m_CanMoveRight;

    //------------------------------------------------------------------------------------------------------------
    /// @brief Loads the player character
    //------------------------------------------------------------------------------------------------------------
    void loadBMan();

protected :
    //------------------------------------------------------------------------------------------------------------
    /// @brief Stores the vertex coordinates for loading
    //------------------------------------------------------------------------------------------------------------
    std::vector<Vec3> m_Vertex;
    //------------------------------------------------------------------------------------------------------------
    /// @brief Stores the normals for loading
    //------------------------------------------------------------------------------------------------------------
    std::vector<Vec3> m_Normal;
    //------------------------------------------------------------------------------------------------------------
    /// @brief Stores the texture coordinates for loading
    //------------------------------------------------------------------------------------------------------------
    std::vector<Vec3> m_Tex;
    //------------------------------------------------------------------------------------------------------------
    /// @brief Stores the face coordinates for loading
    //------------------------------------------------------------------------------------------------------------
    std::vector<Vec3> m_Face;
    //------------------------------------------------------------------------------------------------------------
    /// @brief Face vertices
    //------------------------------------------------------------------------------------------------------------
    std::vector<int>  m_v_Index;
    //------------------------------------------------------------------------------------------------------------
    /// @brief Face textures
    //------------------------------------------------------------------------------------------------------------
    std::vector<int>  m_t_Index;
    //------------------------------------------------------------------------------------------------------------
    /// @brief Face normals
    //------------------------------------------------------------------------------------------------------------
    std::vector<int>  m_n_Index;
    //------------------------------------------------------------------------------------------------------------
    /// @brief The texture
    //------------------------------------------------------------------------------------------------------------
    GLuint            m_Texture;


};


#endif
