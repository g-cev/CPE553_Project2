/*
    Authors: Genesis Cevallos, Robert Plastina
    Description: This file defines the member functions for the "Creature" class.
*/

#include "Creature.h"

//constructor
Creature::Creature(int xPos, int yPos, string symbol) : FieldInhabitant(symbol)
{
    this->xPos = xPos;
    this->yPos = yPos;
}

//getter and setter functions
int Creature::getXPos()
{
    return xPos;
}

int Creature::getYPos()
{
    return yPos;
}

void Creature::setXPos(int newXPos)
{
    this->xPos = newXPos;
}

void Creature::setYPos(int newYPos)
{
    this->yPos = newYPos;
}
