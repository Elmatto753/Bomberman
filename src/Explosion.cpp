#include "Explosion.h"
//------------------------------------------------------------------------------------------------------------
/// @file Explosion.cpp
/// @brief Implementation files for Explosion class
//------------------------------------------------------------------------------------------------------------
void Explosion::loadExp()
{
  m_DisplayList = glGenLists(1);
  glNewList( m_DisplayList, GL_COMPILE );

    glBindTexture( GL_TEXTURE_2D, m_Texture );
    glScalef( 0.1,0.1,0.1 );
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
