/*
 Copyright 2015 Matt Skellon
 1st Year SDAGE PPP Assignment 2
*/

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
  //Load in the map, taking a given string to be the .txt file name/loaction
  loadMap( _filename );
}

//------------------------------------------------------------------------------------------------------------
void mapLoader::loadMap( const std::string &_filename )
{
  //Map loading begins
  int mapZ = 0;
  m_DisplayList.clear();

  //Open the .txt file
  std::fstream fileIn;
  fileIn.open( _filename.c_str(), std::ios::in );
  //If the file is not opened, exit
  if( !fileIn.is_open() )
  {
    std::cerr<<"Could not open "<<_filename<<"\n";
    exit( EXIT_FAILURE );
  }

  //Boost parser separators
  boost::char_separator<char> sep( " \t\r\n" );
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

      //If the current "word" is map, parse the line and store the numbers found in each instance
      if( *firstWord == "map" )
      {
        for( int mapX=0; mapX<13; ++mapX )
        {
          map[mapZ][mapX] = boost::lexical_cast<int>( *++firstWord );
        }
        mapZ++;
      }

      //Otherwise skip ahead
      else
      {
        ++firstWord;
      }
    }
  }
  //Close the file
  fileIn.close();
}

//------------------------------------------------------------------------------------------------------------
void mapLoader::draw()
{
  //To draw the map we run through the values stored by the loadMap function and place a model based on the value
  for( int i=0; i<13; ++i )
  {
    for( int j=0; j<13; ++j )
    {
      //If the value is 1, place a "Metal Block"
      if( map[i][j] == 1 )
      {
        glPushMatrix();
          glTranslatef( 0.6 * j, 0.3, 0.6 * i );
          glCallList( mt.m_DisplayList );
        glPopMatrix();
      }
      //If the value is 2, place a "Cracked Block"
      if( map[i][j] == 2 )
      {
        glPushMatrix();
          glTranslatef( 0.6 * j, 0.3, 0.6 * i );
          glCallList( ct.m_DisplayList );
        glPopMatrix();
      }
      //If the value is 3, place the player character
      if( map[i][j] == 3 )
      {
        glPushMatrix();
          glTranslatef( 0.6 * bMan.m_xMove, 0, 0.6 * bMan.m_zMove );
          glRotatef( bMan.m_Rot, 0, 1.0, 0 );
          glCallList( bMan.m_DisplayList );
        glPopMatrix();
      }

      //Now check for collisions
      checkCollisions();

    }

  }
  //If we are told to place a bomb, place it, update it and start the countdown to remove it
  if( bomb.m_PlaceBomb == true )
  {
    glPushMatrix();
      glTranslatef( 0.6 * bomb.m_xPos, 0.15, 0.6 * bomb.m_zPos );
      glCallList( bomb.m_DisplayList );
    glPopMatrix();
    bomb.m_Life++;
    //If the end of the bomb's life is reached, start the explosion procedure,
    //remove the bomb, reset the countdown and allow another to be placed
    if( bomb.m_Life == 100 )
    {
      bomb.m_Life = 0;
      exp.m_Life = 0;
      bomb.m_PlaceBomb = false;
      bomb.m_CanPlaceBomb = true;
    }
    //Upon the bomb being placed, disallow placing of bombs, allow initial placing of explosions
    if( bomb.m_Life == 1 )
    {
      bomb.m_CanPlaceBomb = false;
      bomb.m_NextExpUp = true;
      bomb.m_NextExpDown = true;
      bomb.m_NextExpLeft = true;
      bomb.m_NextExpRight = true;
    }
  }

  //While the explosions' lives are not over
  if( exp.m_Life != 50 )
  {
    //Check if we can spawn each explosion texture up to maximum range
    //(i.e. can the explosions continue)
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
    //Increment the explosions' lives
    exp.m_Life++;
  }
}

//------------------------------------------------------------------------------------------------------------
void mapLoader::checkCollisions()
{
  //Turn the bomb's position from a float to an int to check explosion spawning
  int xE=static_cast<int>( bomb.m_xPos );
  int zE=static_cast<int>( bomb.m_zPos );

  //Check the decimal portion of Bomberman's location
  float presPosX = ( fmod(bMan.m_xMove, 1.0f) );
  float presPosZ = ( fmod(bMan.m_zMove, 1.0f) );

  //Round Bomberman's position to the nearest int
  int curPosX = (int)( presPosX > 0.49f ? ceil(bMan.m_xMove) : floor(bMan.m_xMove) );
  int curPosZ = (int)( presPosZ > 0.49f ? ceil(bMan.m_zMove) : floor(bMan.m_zMove) );

  //Collision checking
  //If the block above is not empty and the player character is close enough
  //Disallow moving up
  if( ( (map[curPosZ - 1][curPosX] == 1) ||
        (map[curPosZ - 1][curPosX] == 2) ) &&
      presPosZ < 0.05f )
  {
    bMan.m_CanMoveUp = false;
  }
  //Otherwise the player can move up
  else
  {
    bMan.m_CanMoveUp = true;
  }

  //If the block below is not empty and the player character is close enough
  //Disallow moving down
  if( ( (map[curPosZ + 1][curPosX] == 1) ||
        (map[curPosZ+1][curPosX] == 2) ) &&
      presPosZ < 0.05f )
  {
    bMan.m_CanMoveDown = false;
  }
  //Otherwise the player can move up
  else
  {
    bMan.m_CanMoveDown = true;
  }

  //If the block to the left is not empty and the player character is close enough
  //Disallow moving left
  if( ( (map[curPosZ][curPosX - 1] == 1) ||
        (map[curPosZ][curPosX - 1] == 2)) &&
      presPosX < 0.05f )
  {
    bMan.m_CanMoveLeft = false;
  }
  //Otherwise the player can move up
  else
  {
    bMan.m_CanMoveLeft = true;
  }

  //If the block to the right is not empty and the player character is close enough
  //Disallow moving right
  if( ( (map[curPosZ][curPosX + 1] == 1) ||
        (map[curPosZ][curPosX + 1] == 2)) &&
      presPosX < 0.05f )
  {
    bMan.m_CanMoveRight = false;
  }
  //Otherwise the player can move up
  else
  {
    bMan.m_CanMoveRight = true;
  }

  //Once the bomb reaches the end of its life, we check to see if it destroys blocks
  if( bomb.m_Life == 99 )
  {
    for( int i=0; i<=bomb.m_Range; i++ )
    {
      //If the block below is a "cracked block", turn it to an empty space
      //and disallow further explosions in this direction
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

      //If the block below is a "metal block", disallow further explosions in this direction
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
