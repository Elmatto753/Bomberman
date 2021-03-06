/*
 Copyright 2015 Matt Skellon
 1st Year SDAGE PPP Assignment 2
*/

#include "Scene.h"
//------------------------------------------------------------------------------------------------------------
/// @file Scene.cpp
/// @brief Implementation files for classes in the Scene.h file
//------------------------------------------------------------------------------------------------------------
void Vec3::normalGL()
{
  glNormal3f( m_x, m_y, m_z );
}

//------------------------------------------------------------------------------------------------------------
void Vec4::normalGL()
{
  glNormal3f( m_x, m_y, m_z );
}

//------------------------------------------------------------------------------------------------------------
void Vec3::vertexGL()
{
  glVertex3f( m_x, m_y, m_z );
}

//------------------------------------------------------------------------------------------------------------
void Vec4::vertexGL()
{
  glVertex3f( m_x, m_y, m_z );
}

//------------------------------------------------------------------------------------------------------------
void Vec3::textureGL()
{
  glTexCoord2f( m_x, m_y );
}

//------------------------------------------------------------------------------------------------------------
void Vec4::textureGL()
{
  glTexCoord2f( m_x, m_y );
}
