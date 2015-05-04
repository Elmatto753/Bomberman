/*
 Copyright 2015 Matt Skellon
 1st Year SDAGE PPP Assignment 2
*/

/// \file MapLoader.h
/// \brief Calls for the creation of each game element according to a .txt file and updates their position and status, as well as checking for collisions between the player and some of these elements
/// \author Matthew Skellon
/// \version 1.0
/// \date 4/5/15 Initial Doxygen file creation, updated to NCCA Coding Standard

#ifndef MAPLOADER_H_
#define MAPLOADER_H_

#include "MetalBlock.h"
#include "CrackBlock.h"
#include "Bomberman.h"
#include "Bomb.h"
#include "Explosion.h"

typedef boost::tokenizer<boost::char_separator<char> >tokenizer;

class mapLoader
{
public:
  ///
  /// \brief mapLoader
  /// \param _filename
  ///
    mapLoader(const std::string &_filename);

    ~mapLoader(){}

    //------------------------------------------------------------------------------------------------------------
    /// @brief Loads the map by taking in a file and reading it (in this case map.txt)
    //------------------------------------------------------------------------------------------------------------
    void loadMap(const std::string &_filename);
    //------------------------------------------------------------------------------------------------------------
    /// @brief Draws the map
    //------------------------------------------------------------------------------------------------------------
    void draw();
    //------------------------------------------------------------------------------------------------------------
    /// @brief A player character object
    //------------------------------------------------------------------------------------------------------------
    Bomberman bMan;
    //------------------------------------------------------------------------------------------------------------
    /// @brief A metal block object
    //------------------------------------------------------------------------------------------------------------
    MetalBlock mt;
    //------------------------------------------------------------------------------------------------------------
    /// @brief A cracked block object
    //------------------------------------------------------------------------------------------------------------
    CrackBlock ct;
    //------------------------------------------------------------------------------------------------------------
    /// @brief A bomb object
    //------------------------------------------------------------------------------------------------------------
    Bomb bomb;
    //------------------------------------------------------------------------------------------------------------
    /// @brief An explosion object
    //------------------------------------------------------------------------------------------------------------
    Explosion exp;
protected:
    //------------------------------------------------------------------------------------------------------------
    /// @brief The function used to check if certain objects have collided
    //------------------------------------------------------------------------------------------------------------
    void checkCollisions();
    //------------------------------------------------------------------------------------------------------------
    /// @brief Stores the value found in the .txt file for use with drawing and collision detection
    //------------------------------------------------------------------------------------------------------------
    int map[13][13];
    //------------------------------------------------------------------------------------------------------------
    /// @brief Storage for some GL functions
    //------------------------------------------------------------------------------------------------------------
    std::vector<GLint> m_DisplayList;
};

#endif
