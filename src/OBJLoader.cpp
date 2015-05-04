#include <iostream>
#include <SDL2/SDL_image.h>
#include "Scene.h"


void ObjLoad(const std::string &_objName,
             const std::string &_pngName,
               std::vector <Vec3> &_vec,
               std::vector <Vec3> &_norm,
               std::vector <Vec3> &_text,
               std::vector<int> &v_index,
               std::vector<int> &t_index,
               std::vector<int> &n_index,
               GLuint &_textureID)
{

  typedef boost::tokenizer<boost::char_separator<char> >tokenizer;

  std::fstream fileIn;
  fileIn.open( _objName.c_str(), std::ios::in );
  if( !fileIn.is_open() )
  {
    std::cerr<<"Could not open "<<_objName<<"\n";
    exit( EXIT_FAILURE );
  }

  // boost parser separator
  boost::char_separator<char> sep(" /\t\r\n");
  std::string lineBuffer;
  while( !fileIn.eof() )
  {
    getline( fileIn,lineBuffer, '\n' );
    if( lineBuffer.size() !=0 )
    {
      tokenizer tokens( lineBuffer, sep );
      tokenizer::iterator firstWord=tokens.begin();

      if( *firstWord=="v" )
      {
        Vec3 vert(boost::lexical_cast<float>( *++firstWord ),
                  boost::lexical_cast<float>( *++firstWord ),
                  boost::lexical_cast<float>( *++firstWord ));
        _vec.push_back( vert );
      }

      else if( *firstWord=="vt" )
      {
        Vec3 text(boost::lexical_cast<float>( *++firstWord ),
                  boost::lexical_cast<float>( *++firstWord) );
       _text.push_back( text );
      }

      else if( *firstWord=="vn" )
      {
        Vec3 norm(boost::lexical_cast<float>( *++firstWord ),
                  boost::lexical_cast<float>( *++firstWord ),
                  boost::lexical_cast<float>( *++firstWord ));
       _norm.push_back( norm );
      }

      else if( *firstWord=="f" )
      {
        v_index.push_back(boost::lexical_cast<int>( *++firstWord ));
        t_index.push_back(boost::lexical_cast<int>( *++firstWord ));
        n_index.push_back(boost::lexical_cast<int>( *++firstWord ));

        v_index.push_back(boost::lexical_cast<int>( *++firstWord ));
        t_index.push_back(boost::lexical_cast<int>( *++firstWord ));
        n_index.push_back(boost::lexical_cast<int>( *++firstWord ));

        v_index.push_back(boost::lexical_cast<int>( *++firstWord ));
        t_index.push_back(boost::lexical_cast<int>( *++firstWord ));
        n_index.push_back(boost::lexical_cast<int>( *++firstWord ));
      }
    }
  }
  fileIn.close();

  /* LOAD TEXTURE */

  SDL_Surface *texture;
  if( !(texture = IMG_Load( _pngName.c_str() )) )
     std::cerr << "Couldn't load the texture : " << IMG_GetError();

  glGenTextures( 1, &_textureID );

  glBindTexture( GL_TEXTURE_2D, _textureID );

  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

  glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, texture->w, texture->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->pixels );

  SDL_FreeSurface( texture );
}
