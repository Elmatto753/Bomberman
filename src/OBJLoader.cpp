/*
 Copyright 2015 Matt Skellon
 1st Year SDAGE PPP Assignment 2
*/

#include <iostream>
#include <SDL2/SDL_image.h>
#include "Scene.h"
//------------------------------------------------------------------------------------------------------------
/// @file OBJLoader.cpp
/// @brief Implementation files for the ObjLoad function in the Scene.h file
//------------------------------------------------------------------------------------------------------------
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

  //Take in the give file and open it
  std::fstream fileIn;
  fileIn.open( _objName.c_str(), std::ios::in );
  //If the file is not open, exit
  if( !fileIn.is_open() )
  {
    std::cerr<<"Could not open "<<_objName<<"\n";
    exit( EXIT_FAILURE );
  }

  //Boost parser separator
  boost::char_separator<char> sep(" /\t\r\n");
  std::string lineBuffer;
  //Looping while not at the end of the file
  while( !fileIn.eof() )
  {
    //Get the next line when return is reached
    getline( fileIn,lineBuffer, '\n' );
    //If the line is not empty
    if( lineBuffer.size() !=0 )
    {
      tokenizer tokens( lineBuffer, sep );
      tokenizer::iterator firstWord=tokens.begin();

      //If we encounter the letter "v", we store the numbers as vertices
      if( *firstWord=="v" )
      {
        Vec3 vert(boost::lexical_cast<float>( *++firstWord ),
                  boost::lexical_cast<float>( *++firstWord ),
                  boost::lexical_cast<float>( *++firstWord ));
        _vec.push_back( vert );
      }

      //If we encounter the word "vt", we store the numbers as texture information
      else if( *firstWord=="vt" )
      {
        Vec3 text(boost::lexical_cast<float>( *++firstWord ),
                  boost::lexical_cast<float>( *++firstWord) );
       _text.push_back( text );
      }

      //If we encounter the word "vn", we store the numbers as normals information
      else if( *firstWord=="vn" )
      {
        Vec3 norm(boost::lexical_cast<float>( *++firstWord ),
                  boost::lexical_cast<float>( *++firstWord ),
                  boost::lexical_cast<float>( *++firstWord ));
       _norm.push_back( norm );
      }

      //If we encounter the letter "f",
      //we store the numbers as face information in the order vertex/texture/normal
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
  //Close the file
  fileIn.close();

  //Texture loading
  SDL_Surface *texture;
  //If we don't have the texture, throw an error
  if( !(texture = IMG_Load( _pngName.c_str() )) )
     std::cerr << "Couldn't load the texture : " << IMG_GetError();

  //Generate texture name
  glGenTextures( 1, &_textureID );

  //Bind the texture to our loaded model
  glBindTexture( GL_TEXTURE_2D, _textureID );

  //Describe how we display our texture
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

  //Define how the texture is mapped on to our model
  glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, texture->w, texture->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->pixels );

  //Free the surface
  SDL_FreeSurface( texture );
}
