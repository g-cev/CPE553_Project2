/*
    Authors: Genesis Cevallos, Robert Plastina, Praveena Batta
    Description: This header file defines the class "GameEngine".
*/

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>

//include subclasses
#include "Captain.h"
#include "Rabbit.h"
#include "Veggie.h"

using namespace std;

struct Position 
{
    int xPos;
    int yPos;
};

class GameEngine
{
    private:
        //triple pointer to store 2D dynamic array
        //to ask: why a triple pointer?
        FieldInhabitant*** field;

        //height and width of the field
        int height;
        int width;

        //important constants
        const int NUMBEROFVEGGIES = 30;
        const int NUMBEROFRABBITS = 5;

        //object pointers and vectors 
        //TODO: Think of different names for vectors?
        Captain* captainVeggie;
        vector<Rabbit*> rabbits;
        vector<Veggie*> veggies;

        /// @brief This function reads in a user-specified veggie file and populates
        ///        the field with veggie objects, located at random locations.
        void initVeggies();

        /// @brief This function places Captain Veggie at a random location.
        void initCaptain();

        /// @brief This function places rabbit objects at random locations.
        void initRabbits();

        //TODO: Specify what the "move" parameter is in further development. 

        /// @brief This function handles the logic of moving Captain Veggie
        ///        vertically. Changes object properties based on end result.
        /// @param move The delta movement.
        void moveCptVertical(int move);

        /// @brief This function handles the logic of moving Captain Veggie
        ///        horizontally. Changes object properties based on end result.
        /// @param move The delta movement.
        void moveCptHorizontal(int move);
    
    public:
        /// @brief This function calls the necessary init functions to start the game.
        void initializeGame();

        /// @brief This function welcomes the player and provides information about the game.
        void intro();

        /// @brief This function outputs the field in a pleasing 2D grid format with a border.
        void printField();

        /// @brief This function moves a rabbit object in the vector of rabbits 1 space in a
        ///        random x or y direction. 
        void moveRabbits();

        /// @brief This function prompts the user for which direction to move Captain Veggie.
        void moveCaptain();

        /// @brief This function informs the player when the game is over and outputs final results.
        void gameOver();

        /// @brief This function returns the player's score.
        /// @return An integer representing the player's score.
        int getScore();

        /// @brief This function returns the number of veggies left on the field.
        /// @return An integer representing the amount of veggies left.
        int remainingVeggies();
};

#endif