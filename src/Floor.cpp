/*
 Copyright 2015 Matt Skellon
 1st Year SDAGE PPP Assignment 2
*/

#include "Floor.h"
//------------------------------------------------------------------------------------------------------------
/// @file Floor.cpp
/// @brief Implementation files for Floor class
//------------------------------------------------------------------------------------------------------------
void Floor::update()
{
  //Re-draw the floor on each frame
  glCallLists( m_DisplayList.size(), GL_UNSIGNED_INT, &m_DisplayList[0] );
}

void Floor::loadFloor()
{
  //Initial loading of the floor
  GLuint id = glGenLists(1);
  glNewList( id, GL_COMPILE );
  glPushMatrix();

    //Assign the texture and begin building the model in triangles
    glBindTexture( GL_TEXTURE_2D, m_Texture );
    glScalef( 0.2, 0.2, 0.2 );
    glTranslatef( 3, 0, 3 );
    glBegin( GL_TRIANGLES );

      for( int i=0; i<(int)m_v_Index.size(); i++ )
      {
        m_Tex[m_t_Index[i] - 1].textureGL();
        m_Normal[m_n_Index[i] - 1].normalGL();
        m_Vertex[m_v_Index[i] - 1].vertexGL();
      }

    glEnd();
  glPopMatrix();
  glEndList();
  m_DisplayList.push_back(id);
}
