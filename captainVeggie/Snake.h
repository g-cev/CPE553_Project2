/*
    Authors: Genesis Cevallos, Robert Plastina, Praveena Batta
    Description: This header file defines the subclass "Snake".
*/

#ifndef SNAKE_H
#define SNAKE_H

#include "Creature.h"

class Snake : public Creature
{
    public: 
        //public constructor
        Snake(int xPos, int yPos);
};

#endif