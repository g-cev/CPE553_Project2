/*
    Authors: Genesis Cevallos, Robert Plastina, Praveena Batta
    Description: This file defines the member functions for the "Captain" class.
*/

#include "Captain.h"

//constructor
Captain::Captain(int xPos, int yPos) : Creature(xPos, yPos, "V")
{
    //boring constructor
}

void Captain::addVeggie(Veggie* veggie)
{
    //add input Veggie object to vector
    veggiesCollected.push_back(veggie);
}

void Captain::removeVeggie(int n, int& pointsLost) {
    // The number of veggies to remove should not exceed the number of collected veggies
    n = std::min(n, static_cast<int>(veggiesCollected.size()));

    // Reset points lost
    pointsLost = 0;

    // For each removed veggie
    for (int i = 0; i < n; ++i) {
        // Check if there are veggies left to remove
        if (!veggiesCollected.empty()) {
            // Sum up points lost
            pointsLost += veggiesCollected.back()->getPointVal();

            // Pop veggie from the list
            veggiesCollected.pop_back();
        }
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