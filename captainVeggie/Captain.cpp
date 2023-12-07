/*
    Authors: Genesis Cevallos, Robert Plastina, Praveena Batta
    Description: This file defines the member functions for the "Captain" class.
*/

#include "Captain.h"

//constructor
Captain::Captain(int xPos, int yPos) : Creature(xPos, yPos, "V")
{
    //do-nothing constructor -> ask in office hours
}

void Captain::addVeggie(Veggie* veggie)
{
    //add input Veggie object to vector
    veggiesCollected.push_back(veggie);
}

void Captain::removeVeggie(int n, int& pointsLost)
{
    //for each removed veggie
    for (int i = 0; i < veggiesCollected.size(); i++)
    {
        //sum up points lost
        pointsLost += veggiesCollected[-1]->getPointVal();
        //pop veggie list
        veggiesCollected.pop_back();
    }
}

//getter and setter functions
vector<Veggie*> Captain::getVeggiesCollected()
{
    return veggiesCollected;
}

void Captain::setVeggiesCollected(vector<Veggie*> newVeggiesCollected)
{
    this->veggiesCollected = newVeggiesCollected;
}