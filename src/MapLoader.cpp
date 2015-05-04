#include "MapLoader.h"
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <string>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>
#include <ctime>
#include "SDL2/SDL_timer.h"
#include "SDL_image.h"
//------------------------------------------------------------------------------------------------------------
/// @file MapLoader.cpp
/// @brief Implementation files for mapLoader class
//------------------------------------------------------------------------------------------------------------
mapLoader::mapLoader( const std::string &_filename )
{
  loadMap( _filename );
}

void mapLoader::loadMap( const std::string &_filename )
{
  int mapZ = 0;
  m_DisplayList.clear();

  std::fstream fileIn;
  fileIn.open( _filename.c_str(), std::ios::in );
  if( !fileIn.is_open() )
  {
    std::cerr<<"Could not open "<<_filename<<"\n";
    exit( EXIT_FAILURE );
  }

  // boost parser separator
  boost::char_separator<char> sep( " \t\r\n" );
  std::string lineBuffer;
  while( !fileIn.eof() )
  {
    getline( fileIn,lineBuffer, '\n' );
    if( lineBuffer.size() !=0 )
    {
      tokenizer tokens( lineBuffer, sep );
      tokenizer::iterator firstWord=tokens.begin();

      if( *firstWord == "map" )
      {
        for( int mapX=0; mapX<13; ++mapX )
        {
          map[mapZ][mapX] = boost::lexical_cast<int>( *++firstWord );
        }
        mapZ++;
      }

      else
      {
        ++firstWord;
      }
    }
  }
  fileIn.close();
}

void mapLoader::draw()
{
  for( int i=0; i<13; ++i )
  {
    for( int j=0; j<13; ++j )
    {
      if( map[i][j] == 1 )
      {
        glPushMatrix();
          glTranslatef( 0.6 * j, 0.3, 0.6 * i );
          glCallList( mt.m_DisplayList );
        glPopMatrix();
      }
      if( map[i][j] == 2 )
      {
        glPushMatrix();
          glTranslatef( 0.6 * j, 0.3, 0.6 * i );
          glCallList( ct.m_DisplayList );
        glPopMatrix();
      }
      if( map[i][j] == 3 )
      {
        glPushMatrix();
          glTranslatef( 0.6 * bMan.m_xMove, 0, 0.6 * bMan.m_zMove );
          glRotatef( bMan.m_Rot, 0, 1.0, 0 );
          glCallList( bMan.m_DisplayList );
        glPopMatrix();
      }

      checkCollisions();

    }

  }
  if( bomb.m_PlaceBomb == true )
  {
    glPushMatrix();
      glTranslatef( 0.6 * bomb.m_xPos, 0.15, 0.6 * bomb.m_zPos );
      glCallList( bomb.m_DisplayList );
    glPopMatrix();
    bomb.m_Life++;
    if( bomb.m_Life == 100 )
    {
      bomb.m_Life = 0;
      exp.m_Life = 0;
      bomb.m_PlaceBomb = false;
      bomb.m_CanPlaceBomb = true;
    }
    if( bomb.m_Life == 1 )
    {
      bomb.m_CanPlaceBomb = false;
      bomb.m_NextExpUp = true;
      bomb.m_NextExpDown = true;
      bomb.m_NextExpLeft = true;
      bomb.m_NextExpRight = true;
    }
  }

  if( exp.m_Life != 50 )
  {
    for( int i=bomb.m_Range; i>=0; i-- )
    {
      if( bomb.m_NextExpRight == true )
      {
        glPushMatrix();
          glTranslatef( (0.6 * bomb.m_xPos) + (0.6 * i), 0.15, 0.6 * bomb.m_zPos );
          glCallList( exp.m_DisplayList );
        glPopMatrix();
      }
      if( bomb.m_NextExpLeft == true )
      {
        glPushMatrix();
          glTranslatef( (0.6*bomb.m_xPos) - (0.6 * i), 0.15, 0.6 * bomb.m_zPos );
          glCallList( exp.m_DisplayList );
        glPopMatrix();
      }
      if( bomb.m_NextExpDown == true )
      {
        glPushMatrix();
          glTranslatef( 0.6 * bomb.m_xPos, 0.15, (0.6 * bomb.m_zPos) + (0.6 * i) );
          glCallList( exp.m_DisplayList );
        glPopMatrix();
      }
      if( bomb.m_NextExpUp == true )
      {
        glPushMatrix();
          glTranslatef( 0.6 * bomb.m_xPos, 0.15, (0.6 * bomb.m_zPos) - (0.6*i) );
          glCallList(exp.m_DisplayList);
        glPopMatrix();
      }
    }
    exp.m_Life++;
  }
}


void mapLoader::checkCollisions()
{
  int xE=static_cast<int>( bomb.m_xPos );
  int zE=static_cast<int>( bomb.m_zPos );

  float presPosX = ( fmod(bMan.m_xMove, 1.0f) );
  float presPosZ = ( fmod(bMan.m_zMove, 1.0f) );

  int curPosX = (int)( presPosX > 0.49f ? ceil(bMan.m_xMove) : floor(bMan.m_xMove) );
  int curPosZ = (int)( presPosZ > 0.49f ? ceil(bMan.m_zMove) : floor(bMan.m_zMove) );

  std::cout<< curPosX << " " << curPosZ << " " << presPosX << " " << presPosZ <<"\n";


  if( ( (map[curPosZ - 1][curPosX] == 1) ||
        (map[curPosZ - 1][curPosX] == 2) ) &&
      presPosZ < 0.05f )
  {
    bMan.m_CanMoveUp = false;
  }
  else
  {
    bMan.m_CanMoveUp = true;
  }

  if( ( (map[curPosZ + 1][curPosX] == 1) ||
        (map[curPosZ+1][curPosX] == 2) ) &&
      presPosZ < 0.05f )
  {
    bMan.m_CanMoveDown = false;
  }
  else
  {
    bMan.m_CanMoveDown = true;
  }

  if( ( (map[curPosZ][curPosX - 1] == 1) ||
        (map[curPosZ][curPosX - 1] == 2)) &&
      presPosX < 0.05f )
  {
    bMan.m_CanMoveLeft = false;
  }
  else
  {
    bMan.m_CanMoveLeft = true;
  }

  if( ( (map[curPosZ][curPosX + 1] == 1) ||
        (map[curPosZ][curPosX + 1] == 2)) &&
      presPosX < 0.05f )
  {
    bMan.m_CanMoveRight = false;
  }
  else
  {
    bMan.m_CanMoveRight = true;
  }

  if( bomb.m_Life == 99 )
  {
    for( int i=0; i<=bomb.m_Range; i++ )
    {

      if( map[zE+i][xE] == 2 && bomb.m_NextExpDown == true )
      {
        map[zE+i][xE] = 0;
        bomb.m_NextExpDown = false;
      }

      if( map[zE-i][xE] == 2 && bomb.m_NextExpUp == true )
      {
        map[zE-i][xE] = 0;
        bomb.m_NextExpUp = false;
      }

      if( map[zE][xE+i] == 2 && bomb.m_NextExpRight == true )
      {
        map[zE][xE+i] = 0;
        bomb.m_NextExpRight = false;
      }


      if( map[zE][xE-i] == 2 && bomb.m_NextExpLeft == true )
      {
        map[zE][xE-i] = 0;
        bomb.m_NextExpLeft = false;
      }

      if( map[zE+i][xE] == 1 )
      {
        bomb.m_NextExpDown = false;
      }
      if( map[zE-i][xE] == 1 )
      {
        bomb.m_NextExpUp = false;
      }
      if( map[zE][xE+i] == 1 )
      {
        bomb.m_NextExpRight = false;
      }
      if( map[zE][xE-i] == 1 )
      {
        bomb.m_NextExpLeft = false;
      }
    }
  }
}


void mapLoader::update()
{
  glCallLists( m_DisplayList.size(), GL_UNSIGNED_INT, &m_DisplayList[0] );
}


