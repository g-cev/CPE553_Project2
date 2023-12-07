/*
    Authors: Genesis Cevallos, Robert Plastina, Praveena Batta
    Date: 12/7/2023
    Description: This program starts a game of "Captain Veggie", where the user
                 must collect veggies while avoiding rabbits and other obstacles.
*/

#include "GameEngine.h"

int main()
{
    //instantiate and store GameEngine object
    GameEngine game = GameEngine();

    //initialize the game
    game.initializeGame();

    //display the game's intro
    game.intro();

    //variable to store number of remaining veggies
    int veggiesLeft = game.remainingVeggies();

    //while there are still veggies left in the game
    while (veggiesLeft > 0)
    {
        cout << "\n\n" << veggiesLeft << " veggies remaining.";
        cout << " Current score: " << game.getScore() << endl;

        //print out the field
        game.printField();

        //move the rabbits
        game.moveRabbits();

        //move the captain
        game.moveCaptain();

        //move the snake
        game.moveSnake();

        //update number of remaining veggies
        veggiesLeft = game.remainingVeggies();
    }

    //display game over
    game.gameOver();
    return 0;
}