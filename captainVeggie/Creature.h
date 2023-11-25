/*
    Authors: Genesis Cevallos, Robert Plastina, Praveena Batta
    Description: This header file defines the class "Creature".
*/

#ifndef CREATURE_H
#define CREATURE_H

#include "FieldInhabitant.h"

class Creature : public FieldInhabitant
{
    protected:
        //x position
        int xPos;
        //y position
        int yPos;
    
    public:
        //public constructor
        Creature(int xPos, int yPos, string symbol);

        //getter functions
        int getXPos();
        int getYPos();

        //setter functions
        void setXPos(int newXPos);
        void setYPos(int newYPos);
};

#endif