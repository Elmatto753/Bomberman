#include "MetalBlock.h"
//------------------------------------------------------------------------------------------------------------
/// @file MetalBlock.cpp
/// @brief Implementation files for MetalBlock class
//------------------------------------------------------------------------------------------------------------
void MetalBlock::loadMBlock()
{
  m_DisplayList = glGenLists(1);
  glNewList( m_DisplayList, GL_COMPILE );

    glBindTexture( GL_TEXTURE_2D, m_Texture );
    glScalef( 0.2,0.2,0.2 );
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
