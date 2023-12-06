/*
    Authors: Genesis Cevallos, Robert Plastina, Praveena Batta
    Description: This file defines the member functions for the "Rabbit" class.
*/

/*
 * @file Rabbit.cpp
 * @brief Implementation of the Rabbit class.
 * This file contains the implementation of the Rabbit class which is a 
 * subclass of Creature. It represents rabbits in the game 'Captain Veggie.'
 * Constructor for the Rabbit class.
 * 
 * @param xPos The x-coordinate of the rabbit on the game field.
 * @param yPos The y-coordinate of the rabbit on the game field.
 * @param symbol The symbol representing the rabbit on the game field.
 */

#include "Rabbit.h"

Rabbit::Rabbit(int xPos, int yPos,const string& symbol) : Creature(xPos, yPos, "R")
{
    //do-nothing constructor -> ask in office hours
}