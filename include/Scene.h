/*
 Copyright 2015 Matt Skellon
 1st Year SDAGE PPP Assignment 2
*/

/// \file Scene.h
/// \brief The basic functions for building the scene, loading in the .obj files and ensuring they look as they should.
/// \author Matthew Skellon
/// \version 1.0
/// \date 4/5/15 Initial Doxygen file creation, updated to NCCA Coding Standard

#ifndef SCENE_H_
#define SCENE_H_

#include <SDL.h>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>
#include <boost/tokenizer.hpp>
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

class Vec3
{
public:
  ///
  /// \brief Vec3
  /// \param _x
  /// \param _y
  /// \param _z
  ///
    Vec3(float _x=0.0f, float _y=0.0f, float _z=0.0f) :
      m_x(_x),m_y(_y),m_z(_z){}

    //------------------------------------------------------------------------------------------------------------
    /// @brief Used in the normalisation of vertices
    //------------------------------------------------------------------------------------------------------------
    void normalGL();
    //------------------------------------------------------------------------------------------------------------
    /// @brief Used in the drawing of verticies
    //------------------------------------------------------------------------------------------------------------
    void vertexGL();
    //------------------------------------------------------------------------------------------------------------
    /// @brief Used in the texturing of an .obj
    //------------------------------------------------------------------------------------------------------------
    void textureGL();

    struct
    {
      float m_x;
      float m_y;
      float m_z;
    };
};

class Vec4
{
public:
  ///
  /// \brief Vec4
  /// \param _x
  /// \param _y
  /// \param _z
  /// \param _w
  ///
    Vec4(float _x=0.0f, float _y=0.0f, float _z=0.0f, float _w=1.0f) :
      m_x(_x),m_y(_y),m_z(_z),m_w(_w){}
    //------------------------------------------------------------------------------------------------------------
    /// @brief Used in the normalisation of vertices
    //------------------------------------------------------------------------------------------------------------
    void normalGL();
    //------------------------------------------------------------------------------------------------------------
    /// @brief Used in the drawing of verticies
    //------------------------------------------------------------------------------------------------------------
    void vertexGL();
    //------------------------------------------------------------------------------------------------------------
    /// @brief Used in the texturing of an .obj
    //------------------------------------------------------------------------------------------------------------
    void textureGL();

    struct
    {
      float m_x;
      float m_y;
      float m_z;
      float m_w;
    };
};

void ObjLoad(const std::string &,
             const std::string &_pngName,
             std::vector<Vec3> &_vec,
             std::vector<Vec3> &_norm,
             std::vector<Vec3> &_text,
             std::vector<int> &v_index,
             std::vector<int> &t_index,
             std::vector<int> &n_index,
             GLuint &_textureID);

#endif
