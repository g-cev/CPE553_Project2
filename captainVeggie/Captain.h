/*
    Authors: Genesis Cevallos, Robert Plastina, Praveena Batta
    Description: This header file defines the subclass "Captain".
*/

#ifndef CAPTAIN_H
#define CAPTAIN_H

#include "Creature.h"
#include "Veggie.h"

class Captain : public Creature
{
    private:
        //stores all of the veggies the captain has collected
        vector<Veggie*> veggiesCollected;

    public:
        //public constructor
        Captain(int xPos, int yPos);

        /// @brief This function adds a vegetable to the vector of Veggie objects.
        /// @param veggie A pointer to a Veggie object.
        void addVeggie(Veggie* veggie);

        /// @brief This function removes a vegetable from the Captain's basket.
        /// @param n The number of veggies to remove from the basket.
        /// @param pointsLost A reference to the number of points lost.
        void removeVeggie(int n, int& pointsLost);

        //getter functions
        vector<Veggie*> getVeggiesCollected();

        //setter functions
        void setVeggiesCollected(vector<Veggie*> newVeggiesCollected);
};

#endif