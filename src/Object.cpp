/*
 Copyright 2015 Matt Skellon
 1st Year SDAGE PPP Assignment 2
*/

#include "Bomb.h"
#include "Bomberman.h"
#include "CrackBlock.h"
#include "Explosion.h"
#include "MetalBlock.h"

void Object::loadObject()
{
  m_DisplayList = glGenLists(1);
  glNewList( m_DisplayList, GL_COMPILE );

    //Assign the texture and begin building the model in triangles
    glBindTexture( GL_TEXTURE_2D, m_Texture );
    glScalef( m_scale, m_scale, m_scale );
    glBegin( GL_TRIANGLES );

      for( int i=0; i<(int)m_v_Index.size(); i++ )
      {
        m_Tex[m_t_Index[i] - 1].textureGL();
        m_Normal[m_n_Index[i] - 1].normalGL();
        m_Vertex[m_v_Index[i] - 1].vertexGL();
      }

    glEnd();
  glEndList();
}
