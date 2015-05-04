/*
 Copyright 2015 Matt Skellon
 1st Year SDAGE PPP Assignment 2
*/
//------------------------------------------------------------------------------------------------------------
/// @file Main.cpp
/// @brief The main file from which the game runs
//------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <cstdlib>
#include <string>
#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include "Scene.h"
#include "Bomberman.h"
#include "Bomb.h"
#include "MapLoader.h"
#include "MetalBlock.h"
#include "Floor.h"

#define WINDOW_TITLE "Bomberman"

SDL_Window* gWindow = NULL;

//OpenGL context
SDL_GLContext gContext;

//Function to deal with SDL
int initSDL()
{
  //Initialize SDL, exit if we fail to do so
  if( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) < 0 )
  {
    std::cout<<"SDL uninitialised. SDL Error: "<<SDL_GetError();
    return EXIT_FAILURE;
  }
  else
  {
    //Use OpenGL 2.1
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

    //An SDL_Rect that we use to figure out the size of the screen
    SDL_Rect _r;
    SDL_GetDisplayBounds(0,&_r);
    //Create the window, else exit
    gWindow = SDL_CreateWindow( "Bomberman",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                _r.w / 1.5f,
                                _r.h / 1.5f,
                                SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if( gWindow == NULL )
    {
      std::cout<< "Window could not be created; SDL Error: %s\n" << SDL_GetError();
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------
int main()
{
  //Start up SDL and create the window
  if( initSDL() == EXIT_FAILURE ) return EXIT_FAILURE;

  //Create context
  gContext = SDL_GL_CreateContext( gWindow );

  if( gContext == NULL ) return EXIT_FAILURE;

  //Determine the window size for use with the camera
  SDL_Rect _r;
  SDL_GetDisplayBounds( 0, &_r );

  //Making the window update
  SDL_GL_MakeCurrent( gWindow, gContext );
  SDL_GL_SetSwapInterval(1);

  //Enable lighting for the scene
  glEnable( GL_LIGHTING );
  glEnable( GL_LIGHT0 );
  glColor3f(1,1,1);
  glEnable( GL_COLOR_MATERIAL );
  glEnable( GL_DEPTH_TEST );
  glEnable( GL_TEXTURE_2D );

  //Assign colour and position to our light(s)
  GLfloat lightpos[] = {0.0f, 0.5f, 1.0f, 1.0f};
  GLfloat lightdiff[] = {0.5f, 0.5f, 0.5f, 1.0f};
  GLfloat lightamb[] = {0.0f, 0.0f, 0.0f, 1.0f};
  GLfloat lightspec[] = {0.5f, 0.5f, 0.5f, 1.0f};

  //Specify material parameters
  glMaterialfv( GL_LIGHT0, GL_POSITION, lightpos );
  glMaterialfv( GL_LIGHT0, GL_DIFFUSE, lightdiff );
  glMaterialfv( GL_LIGHT0, GL_AMBIENT, lightamb );
  glMaterialfv( GL_LIGHT0, GL_SPECULAR, lightspec );
  glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );

  //Now we set up our camera's FoV, location and subject
  glMatrixMode( GL_PROJECTION );
  gluPerspective( 25.0f, float(_r.w) / _r.h, 0.1, 10000.0 );
  glMatrixMode( GL_MODELVIEW );
  glEnable( GL_NORMALIZE );
  glLoadIdentity();
  gluLookAt( 3.6, 14, 13, 3.6, 0, 4, 0, 1, 0 );

  //Set the background colour
  glClearColor( 0.1f, 0.1f, 0.1f, 1.0f );

  //Main loop flag
  bool quit = false;

  //Event handler
  SDL_Event e;

  //Allow us to determine keystate for player movement
  const Uint8 *keystate = SDL_GetKeyboardState( NULL );

  //Load in our map from the .txt file using the mapLoader class
  mapLoader map( "data/Map.txt" );

  //initialise the floor of our scene
  Floor plane;

  //Main loop - While application is running
  while( quit == false )
  {
    //Clear the display buffer
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    //Update the floor so it keeps being drawn
    plane.update();

    //Update the map so it also keeps being drawn
    map.draw();

    //Checking if WASD or an arrow key is pressed
    //If so, rotate and check the character can move
    //If it can, move while the key is held
    if( keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_UP] )
    {
      if( map.bMan.m_CanMoveUp == true )
      {
        map.bMan.m_zMove -= 0.05;
      }
      map.bMan.m_Rot = 180;
    }
    else if( keystate[SDL_SCANCODE_S] || keystate[SDL_SCANCODE_DOWN] )
    {
      if( map.bMan.m_CanMoveDown == true )
      {
        map.bMan.m_zMove += 0.05;
      }
      map.bMan.m_Rot = 0;
    }
    else if( keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_LEFT] )
    {
      if( map.bMan.m_CanMoveLeft == true )
      {
        map.bMan.m_xMove -= 0.05;
      }
      map.bMan.m_Rot = 270;
    }
    else if( keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_RIGHT] )
    {
      if( map.bMan.m_CanMoveRight == true )
      {
        map.bMan.m_xMove += 0.05;
      }
      map.bMan.m_Rot = 90;
    }

    //Handle events on queue
    while( SDL_PollEvent( &e ) !=0 )
    {
      //If the user closes the window
      if( e.type == SDL_QUIT )
      {
        quit = true;
      }

//      if((e.type == SDL_WINDOWEVENT) && (e.window.event == SDL_WINDOWEVENT_RESIZED))
//      {
//        SDL_SetWindowSize(gWindow, e.window.data1, e.window.data2);
//        scene->resize(e.window.data1, e.window.data2);
//      }

      //If a key is pressed
      if( e.type == SDL_KEYDOWN )
      {
        switch( e.key.keysym.sym )
        {
          //If key pressed is "escape", close the window
          case SDLK_ESCAPE :
          {
            quit = true; break;
          }

          //If the key pressed is "space" and a bomb is allowed to be placed,
          //place the bomb at the location of the player
          case SDLK_SPACE :
          {
            if( map.bomb.m_CanPlaceBomb == true )
            {
              map.bomb.m_xPos = map.bMan.m_xMove;
              map.bomb.m_zPos = map.bMan.m_zMove;
              map.bomb.m_PlaceBomb = true;
              break;
            }
            //If the key pressed is not one of these, do nothing
            else
            {
              break;
            }
          }
        }
      }
    }
    SDL_GL_SwapWindow( gWindow );
  }

  //Destroy window
  SDL_DestroyWindow( gWindow );

  //Quit SDL subsystems
  SDL_Quit();

  return EXIT_SUCCESS;
}
