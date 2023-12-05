/*
    Authors: Genesis Cevallos, Robert Plastina, Praveena Batta
    Description: This file defines the member functions for the "GameEngine" class.
*/

#include "GameEngine.h"
#include "Veggie.h"
#include "Rabbit.h"
#include "Creature.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

//TODO: Define GameEngine functions. Descriptions have been added in header file.
//Order of definitions was based on project instructions.

void GameEngine::initializeGame()
{
    initVeggies();
    initCaptain();
    initRabbits();
    initSnake();

    //initialize score to 0
    score = 0;
}

void GameEngine::initVeggies()
{
    //prompt user for the name of the file
    string filename = "";

    cout << "Please enter the name of the vegetable point file: ";
    cin >> filename;

    ifstream veggieFile;
    veggieFile.open(filename);

    while(!veggieFile.is_open())    //while file does NOT exist in dir
    {
        cout << filename << " does not exist! Please enter the name of the vegetable point file: "; 
        cin >> filename;            //input filename
        veggieFile.open(filename);  //try to open file
    }

    //vector to store raw string
    string line;
    //2D vector to store split data
    vector<vector<string>> data;

    while (getline(veggieFile, line)) 
    {
        //split set up
        stringstream ss(line);
        vector<string> row;
        string cell;

        while (getline(ss, cell, ',')) 
        {
            row.push_back(cell);
        }
        data.push_back(row);
    }

    //get dimensions from row 0 in .csv file
    height = stoi(data[0][1]);
    width = stoi(data[0][2]);

    //starting from row 1 in .csv file
    for (int i = 1; i < data.size(); i++)
    {
        //create new veggie object based on data
        Veggie* veggie = new Veggie(data[i][0], data[i][1], stoi(data[i][2]));
        //push into veggie list
        this->veggies.push_back(veggie);
    }

    //close file after gathering data
    veggieFile.close();

    //generate 2D, dynamic array of FieldInhabitant pointers
    field = new FieldInhabitant**[height];
    for (int i = 0; i < height; i++) 
    {
        field[i] = new FieldInhabitant*[width];
        for (int h = 0; h < width; h++) 
        {
            //set all slots to nullptr
            field[i][h] = nullptr; 
        }
    }

    //seed random
    srand(time(0));

    //populate field with new Veggie Objects
    vector<Position> occupied;

    //until we reach our veggie limit
    while (occupied.size() < NUMBEROFVEGGIES)
    {
        int veggie_x = rand() % width;
        int veggie_y = rand() % height;

        //if this spot is empty
        if (field[veggie_y][veggie_x] == nullptr)
        {
            //reserve position for a veggie object
            occupied.push_back({veggie_x, veggie_y});

            //choose a random vegetable from possibilities
            int randomVeggie = rand() % veggies.size();

            //place random veggie in field at position
            field[veggie_y][veggie_x] = veggies[randomVeggie];
        }
    }
}

void GameEngine::initCaptain()
{

}

void GameEngine::initRabbits()
{
    for (int i = 0; i < NUMBEROFRABBITS; ++i)
    {
        int x, y;
        do
        {
            x = rand() % width;
            y = rand() % height;
        } while (field[y][x] != nullptr);

        Rabbit* newRabbit = new Rabbit(x, y, "R");
        rabbits.push_back(newRabbit);
        field[y][x] = newRabbit;
    }
}

int GameEngine::remainingVeggies()
{
    int veggiesLeft = 0;

    for (int i = 0; i < height; i++)
    {
        for (int h = 0; h < width; h++)
        {
            //pointer for testing
            Veggie* veggie_ptr = dynamic_cast<Veggie*>(field[i][h]);

            if (veggie_ptr != nullptr)
            {
                veggiesLeft++;
            }
        }
    }

    return veggiesLeft;
}

void GameEngine::intro()
{
    cout << "\nWelcome to Captain Veggie!" << endl;
    cout << "The rabbits have invaded your garden and you must harvest" << endl;
    cout << "as many vegetables as possible before the rabbits eat them" << endl;
    cout << "all! Each vegetable is worth a different number of points," << endl;
    cout << "so go for the high score!" << endl;

    cout << "\nBONUS: Watch out for the snake, or else it'll steal your veggies!" << endl;

    cout << "\nThe vegetables are: " << endl;
    for (int i = 0; i < veggies.size(); i++)
    {
        cout << GREEN << veggies[i]->getSymbol() << RESET << ": " << veggies[i]->getVeggieName();
        cout << " " << veggies[i]->getPointVal() << " points" << endl;
    }

    //cout << "\nCaptain Veggie is " << captainVeggie->getSymbol();
    cout << ", the snake is " << BLUE << snake->getSymbol() << RESET;
    cout << ", and the rabbits are " << RED << rabbits[0]->getSymbol() << RESET << endl;

    cout << "\nGood luck!\n" << endl;
}

void GameEngine::printField()
{
    int border_width = width * 3 + 3;
    for (int i = 0; i < border_width; i++)
    {
        cout << "#";
    }
    //new line
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        //left border
        cout << "#";        

        for (int h = 0; h < width; h++)
        {
            //pointers for testing
            Veggie* veggie_ptr = dynamic_cast<Veggie*>(field[i][h]);
            Captain* captain_ptr = dynamic_cast<Captain*>(field[i][h]);
            Rabbit* rabbit_ptr = dynamic_cast<Rabbit*>(field[i][h]);
            Snake* snake_ptr = dynamic_cast<Snake*>(field[i][h]);

            if (veggie_ptr != nullptr)
            {
                cout << setw(7) << GREEN << field[i][h]->getSymbol() << RESET;
            }
            else if (captain_ptr != nullptr)
            {
                cout << setw(7) << YELLOW << "C" << RESET; // Assuming "C" is the symbol for Captain and captain is colour coded yellow.
            }
            else if (rabbit_ptr != nullptr)
            {
                cout << setw(7) << RED << "R" << RESET; //Assuming Rabbit is red and R is the symbol for rabbit
            }
            else if (snake_ptr != nullptr)
            {
                cout << setw(7) << BLUE << field[i][h]->getSymbol() << RESET;
            }
            else
            {
                cout << setw(3) << "";
            }
        }

        //right border
        cout << " #" << endl;
    }

    //bottom border
    for (int i = 0; i < border_width; i++)
    {
        cout << "#";
    }
    cout << endl;
}

int GameEngine::getScore()
{
    return score;
}

void GameEngine::moveRabbits()
{
    for (auto rabbit : rabbits)
    {
        int dx = rand() % 3 - 1;  // Generates -1, 0, or 1
        int dy = rand() % 3 - 1;  // Generates -1, 0, or 1

        int newX = rabbit->getXPos() + dx;
        int newY = rabbit->getYPos() + dy;

        if (newX >= 0 && newX < width && newY >= 0 && newY < height)
        {
            FieldInhabitant* occupant = field[newY][newX];

            Veggie* veggie = dynamic_cast<Veggie*>(occupant);

            if (occupant == nullptr || veggie != nullptr)
            {
                field[rabbit->getYPos()][rabbit->getXPos()] = nullptr;
                rabbit->setXPos(newX);
                rabbit->setYPos(newY);
                field[newY][newX] = rabbit;
            }
        }
    }
}

void GameEngine::moveCptVertical(int move)
{

}

void GameEngine::moveCptHorizontal(int move)
{

}

void GameEngine::moveCaptain()
{

}

void GameEngine::gameOver()
{
    cout << "\nGame Over! Thank you for playing \"Captain Veggie\"" << endl;
    if (captainVeggie)
    {
        cout << "Vegetables harvested by Captain: " << endl;
        if (!captainVeggie->getVeggiesCollected().empty())
        {
            for (const auto& veggie : captainVeggie->getVeggiesCollected())
            {
                if (veggie)
                {
                    cout << veggie->getVeggieName() << endl;
                }
            }
        } 
        else 
        {
            cout << "No vegetables were harvested. " << endl;
        }
        cout << "Your final score: " << getScore() << endl;
    } 
    else
    {
        cout << "Error: Captain not initialized." << endl;
    }
}

void GameEngine::initSnake()
{
    //randomize coordinates
    int snake_x = rand() % width;
    int snake_y = rand() % height;

    //while this spot is not empty, 
    while (field[snake_y][snake_x] != nullptr)
    {
        //keep trying to find unique coordinates
        snake_x = rand() % width;
        snake_y = rand() % height;
    }

    //instantiate snake object
    Snake* snake = new Snake(snake_x, snake_y);

    //place snake object in field
    this->snake = snake;
    field[snake_y][snake_x] = snake;
}

bool GameEngine::nextMoveNotOk(int xPos, int yPos)
{
    bool outOfBounds = false;
    bool obstacleExists = false;

    //if coordinates are out of bounds
    if (xPos < 0 || yPos < 0 || xPos >= height || yPos >= height)
    {
        outOfBounds = true;
    }
    
    //test pointer to see if the captain is the "obstacle"
    Captain* captain_ptr = dynamic_cast<Captain*>(field[xPos][yPos]);

    //if invalid OR (not the captain AND not empty)
    if (outOfBounds || (captain_ptr == nullptr && field[xPos][yPos] != nullptr))
    {
        obstacleExists = true;
    }

    return obstacleExists;
}

void GameEngine::moveSnake()
{
    //get current position of the snake
    int snake_x = snake->getXPos();
    int snake_y = snake->getYPos();

    //get current position of Captain Veggie
    int captain_x = captainVeggie->getXPos();
    int captain_y = captainVeggie->getYPos();

    //start at the current position
    int x_new = snake_x;
    int y_new = snake_y;

    //determine new position snake should move to
    int x_direction, y_direction;

    int x_difference = snake_x - captain_x;
    if (x_difference < 0)
        x_direction = 1;    //if snake's x is less than captain's, move right
    else if (x_difference > 0)
        x_direction = -1;   //if snake's x is more than captain's, move left
    else
        x_direction = 0;    //stay the same

    int y_difference = snake_y - captain_y;
    if (y_difference < 0)
        y_direction = 1;    //if snake's y is less than captain's, move right
    else if (y_difference > 0)
        y_direction = -1;   //if snake's y is more than captain's, move left
    else
        y_direction = 0;    //stay the same


    //move left or right
    if (x_direction != 0)
    {
        x_new += x_direction;

        if (y_direction == 0)
        {
            //we always want to move in the y direction if x is blocked
            y_direction = -1;
        }
        if (nextMoveNotOk(x_new, y_new))
        {
            //attempt to go around obstacle
            x_new = snake_x;
            y_new += y_direction;
            if (nextMoveNotOk(x_new, y_new))
            {
                //something in the way again, not possible to move closer to captain
                y_new = snake_y;
                //move opposite direction of original
                x_new -= x_direction;

                if (nextMoveNotOk(x_new, y_new))
                {
                    //something blocking us again!
                    x_new = snake_x;
                    y_new -= y_direction;

                    if (nextMoveNotOk(x_new, y_new))
                    {
                        //blocked on all directions, don't move
                        y_new = snake_y;
                    }
                }
            }
        }
    }

    //move up or down
    if (y_direction != 0)
    {
        y_new += y_direction;

        if (x_direction == 0)
        {
            //we always want to move in the x direction if y is blocked
            x_direction = -1;
        }
        if (nextMoveNotOk(x_new, y_new))
        {
            //attempt to go around obstacle
            y_new = snake_y;
            x_new += x_direction;
            if (nextMoveNotOk(x_new, y_new))
            {
                //something in the way again, not possible to move closer to captain
                x_new = snake_x;
                //move opposite direction of original
                y_new -= y_direction;

                if (nextMoveNotOk(x_new, y_new))
                {
                    //something blocking us again!
                    y_new = snake_y;
                    x_new -= x_direction;

                    if (nextMoveNotOk(x_new, y_new))
                    {
                        //blocked on all directions, don't move
                        x_new = snake_x;
                    }
                }
            }
        }
    }

    //if the snake touches the captain
    Captain* captain_ptr = dynamic_cast<Captain*>(field[y_new][x_new]);
    if (captain_ptr != nullptr)
    {   
        //pop 5 veggies out of captains basket -- waiting on Captain func

        //output snake message
        cout << "\nOh no! The snake ate __ veggie(s) from the basket!";
        cout << " You lost __ points!" << endl;

        //randomize new coordinates after trying to touch Captain
        x_new = rand() % width;
        y_new = rand() % height;

        //while this spot is not empty, 
        while (field[y_new][x_new] != nullptr)
        {
            //keep trying to find unique coordinates
            x_new = rand() % width;
            y_new = rand() % height;
        }
    }

    // set snake's new coordinates
    field[snake_y][snake_x] = nullptr;
    snake->setXPos(x_new);
    snake->setYPos(y_new);

    //move snake to new spot
    field[y_new][x_new] = snake;
}