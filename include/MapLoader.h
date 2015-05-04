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
    mapLoader(const std::string &_filename);

    ~mapLoader(){}
    void loadMap(const std::string &_filename);
    void update();
    void storeValue(tokenizer::iterator &firstWord, std::vector<std::vector<int> > &mBlocks);
    void draw();
    Bomberman bMan;
    MetalBlock mt;
    CrackBlock ct;
    Bomb bomb;
    Explosion exp;
private:
    int map[13][13];
    std::vector<GLint> m_DisplayList;

    void loadMBlock(tokenizer::iterator &_firstWord);
    void loadBBlock(tokenizer::iterator &_firstWord);
    void checkCollisions();

};

#endif
