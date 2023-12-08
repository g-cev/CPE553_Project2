/*
    Authors: Genesis Cevallos, Robert Plastina, Praveena Batta
    Description: This header file defines the subclass "Rabbit".
*/

#ifndef RABBIT_H
#define RABBIT_H

#include "Creature.h"
#include "Veggie.h"
#include <string>

/**
 * @file Rabbit.h
 * @brief Declaration of the Rabbit class.
 *
 * This file contains the declaration of the Rabbit class which is a 
 * subclass of Creature. It represents rabbits in the game 'Captain Veggie.'
 */

class Rabbit : public Creature
{
    /**
     * Public constructor for Rabbit class.
     * @param xPos The x-coordinate of the rabbit on the game field.
     * @param yPos The y-coordinate of the rabbit on the game field.
     * @param symbol The symbol representing the rabbit on the game field.
     */

    public:
        Rabbit(int xPos, int yPos,const string& symbol);

};

#endif // RABBIT_H