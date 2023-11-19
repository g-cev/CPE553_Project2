/*
    Authors: Genesis Cevallos, Robert Plastina
    Description: This header file defines the subclass "Rabbit".
*/

#ifndef RABBIT_H
#define RABBIT_H

#include "Creature.h"
#include "Veggie.h"

class Rabbit : public Creature
{
    public:
        //public constructor
        Rabbit(int xPos, int yPos);

};

#endif