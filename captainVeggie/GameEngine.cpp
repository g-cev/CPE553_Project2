/*
    Authors: Genesis Cevallos, Robert Plastina, Praveena Batta
    Description: This file defines the member functions for the "GameEngine" class.

    g++ -std=c++11 main.cpp GameEngine.cpp FieldInhabitant.cpp Rabbit.cpp Veggie.cpp Captain.cpp Creature.cpp Snake.cpp -o GameEngine
    g++ -std=c++11 -fsanitize=address main.cpp GameEngine.cpp FieldInhabitant.cpp Rabbit.cpp Veggie.cpp Captain.cpp Creature.cpp Snake.cpp -o GameEngine

    ./GameEngine
*/

#include "GameEngine.h"
#include "Veggie.h"
#include "Rabbit.h"
#include "Creature.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

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
    vector<vector<string> > data;

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
    int initCap_x, initCap_y;
        do
        {
            initCap_x = rand() % width;  // Generate a random x-coordinate
            initCap_y = rand() % height; // Generate a random y-coordinate
        } while (field[initCap_y][initCap_x] != nullptr); // Continue if the position is already occupied

        captainVeggie = new Captain(initCap_x, initCap_y); 
        field[initCap_y][initCap_x] = captainVeggie;
}

/*
 * @brief Initializes the rabbits in the game.This method populates the game field with a predefined number of rabbits. 
 * Each rabbit is placed in a random, unoccupied location on the game field.
 * The number of rabbits is defined by the constant NUMBEROFRABBITS.
 * 
 * @note The position for each rabbit is determined by generating random
 *       x and y coordinates. The loop continues until an empty (nullptr) 
 *       position is found on the field, ensuring that rabbits do not overlap 
 *       with each other or other field inhabitants.
 */

void GameEngine::initRabbits()
{
    for (int i = 0; i < NUMBEROFRABBITS; ++i)
    {
        int x, y;
        do
        {
            x = rand() % width;  // Generate a random x-coordinate
            y = rand() % height; // Generate a random y-coordinate
        } while (field[y][x] != nullptr); // Continue if the position is already occupied

        Rabbit* newRabbit = new Rabbit(x, y, "R"); // Create a new rabbit
        rabbits.push_back(newRabbit); // Add the rabbit to the list of rabbits
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

    cout << "\nCaptain Veggie is " << YELLOW << captainVeggie->getSymbol() << RESET;
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
            if (field[i][h] == nullptr) {
                cout << setw(3) << "";
                continue;
            }
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
                cout << setw(7) << YELLOW << field[i][h]->getSymbol() << RESET; 
            }
            else if (rabbit_ptr != nullptr)
            {
                cout << setw(7) << RED << field[i][h]->getSymbol() << RESET; 
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

/*
 * @brief Moves all rabbits on the game field.This method iterates through each rabbit in the game and attempts to move it
 * to a new, adjacent position on the game field. The new position is determined
 * by adding a random delta (dx, dy) to the rabbit's current position.
 * 
 * @details
 * The deltas dx and dy are randomly generated values that can be -1, 0, or 1, 
 * which correspond to moving left/right, up/down, or staying in the same place.
 * The method ensures that rabbits only move within the bounds of the game field
 * and do not overlap with other rabbits. If the new position is occupied by a 
 * vegetable, the rabbit can still move there (as rabbits can eat vegetables).
 * 
 * @note The function checks for null pointers before attempting to move a rabbit.
 *       This is important for preventing segmentation faults in case of uninitialized
 *       or deleted rabbit objects.
 */

void GameEngine::moveRabbits()
{
    for (auto rabbit : rabbits)
    {
        if (!rabbit) continue; // Skip if the rabbit pointer is null

        int dx = rand() % 3 - 1;  // Generates -1, 0, or 1
        int dy = rand() % 3 - 1;  // Generates -1, 0, or 1

        int newX = rabbit->getXPos() + dx;  // Calculate new x-coordinate
        int newY = rabbit->getYPos() + dy;  // Calculate new y-coordinate

        // Check if new coordinates are within the game field bounds
        if (newX >= 0 && newX < width && newY >= 0 && newY < height)
        {
            FieldInhabitant* occupant = field[newY][newX];
            // Cast occupant to Veggie* to check if it's a vegetable
            Veggie* veggie = dynamic_cast<Veggie*>(occupant);
            // Move the rabbit if the new position is empty or has a vegetable
            if (occupant == nullptr || veggie != nullptr)
            {
                field[rabbit->getYPos()][rabbit->getXPos()] = nullptr;  // Clear old position
                rabbit->setXPos(newX);  // Set new x-coordinate for the rabbit
                rabbit->setYPos(newY);  // Set new y-coordinate for the rabbit
                field[newY][newX] = rabbit;  // Place rabbit in the new position
            }
        }
    }
}

void GameEngine::moveCptVertical(int move)
{
    int capX = captainVeggie->getXPos();
    int capY = captainVeggie->getYPos();

    
    int newY = (move == 1) ? capY - 1 : capY + 1; // Move up or down based on move value
    cout << "Attempting to move to: " << newY << "," << capX << endl;
    if (newY >= 0 && newY < height) {
        FieldInhabitant* occupant = field[newY][capX];

        if (occupant == nullptr) {
            field[capY][capX] = nullptr;
            field[newY][capX] = captainVeggie;
            captainVeggie->setYPos(newY);
        } else if (auto* veggie = dynamic_cast<Veggie*>(occupant)) {
            score += veggie->getPointVal();
            cout << "A delicious " << veggie->getVeggieName() << " has been found! Score: " << score << endl;
            captainVeggie->addVeggie(veggie);
            field[newY][capX] = captainVeggie;
            field[capY][capX] = nullptr;
            captainVeggie->setYPos(newY);
        } else if (dynamic_cast<Rabbit*>(occupant)) {
            cout << "Don't Step on the Rabbits!" << endl;
        } else if (dynamic_cast<Snake*>(occupant)) {
            cout << "Don't Step on the Snake!" << endl;
        }
    } else {
        cout << "You cannot move this way." << endl;
    }
}

void GameEngine::moveCptHorizontal(int move)
{
    int capX = captainVeggie->getXPos();
    int capY = captainVeggie->getYPos();

    int newX = (move == 1) ? capX - 1 : capX + 1;
    cout << "Attempting to move to: " << newX << "," << capX << endl;
    if (newX >= 0 && newX < width) {
        FieldInhabitant* occupant = field[capY][newX];

        if (occupant == nullptr) {
            field[capY][capX] = nullptr;
            field[capY][newX] = captainVeggie;
            captainVeggie->setXPos(newX);
        } else if (auto* veggie = dynamic_cast<Veggie*>(occupant)) {
            score += veggie->getPointVal();
            cout << "A delicious " << veggie->getVeggieName() << " has been found! Score: " << score << endl;
            captainVeggie->addVeggie(veggie);
            field[capY][newX] = captainVeggie;
            field[capY][capX] = nullptr;
            captainVeggie->setXPos(newX);
        } else if (dynamic_cast<Rabbit*>(occupant)) {
            cout << "Don't Step on the Rabbits!" << endl;
        } else if (dynamic_cast<Snake*>(occupant)) {
            cout << "Don't Step on the Snake!" << endl;
        }
    } else {
        cout << "You cannot move this way." << endl;
    }
}

void GameEngine::moveCaptain()
{
    char moveInput;
    cout << "Your Next Move: UP(W), LEFT(A), DOWN(S), RIGHT(D)" << endl;
    cin >> moveInput;
    switch (moveInput)
    {
        // Move Up
        case 'W':
        case 'w':
            {
                moveCptVertical(1); 
                break;
            }

        // Move Left
        case 'A':
        case 'a':
            {
                moveCptHorizontal(1);
                break;
            }
      
        // Move Down
        case 'S':
        case 's':
            {
                moveCptVertical(2);
                break;
            }

        // Move Right
        case 'D':
        case 'd':
            {
                moveCptHorizontal(2);
                break;
            }
        default:
            cout << "Invalid input. Please try again." << endl;
            break;
    }
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
/*
    //instantiate snake object
    Snake* snake = new Snake(snake_x, snake_y);

    //place snake object in field
    this->snake = snake;
    field[snake_y][snake_x] = snake;
    */
   // Instantiate snake object as a class member
    this->snake = new Snake(snake_x, snake_y);

    // Place snake object in the field
    field[snake_y][snake_x] = this->snake;
}

bool GameEngine::nextMoveNotOk(int xPos, int yPos)
{
    bool outOfBounds = true;
    bool obstacleExists = false;

    //if coordinates are out of bounds
    if (xPos >= 0 && xPos < width && yPos >= 0 && yPos < height)
    {
        outOfBounds = false;
    }
    
    //test pointer to see if the captain is the "obstacle"
    Captain* captain_ptr = dynamic_cast<Captain*>(field[yPos][xPos]);

    //if invalid OR (not the captain AND not empty)
    if (outOfBounds || (captain_ptr == nullptr && field[yPos][xPos] != nullptr))
    {
        obstacleExists = true;
        cout << "Obstacle exists at the position." << endl;
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



    if (x_difference != 0)
    {
        x_new += x_direction;
        y_new = snake_y;
    }
    else if (y_difference != 0)
    {
        y_new += y_direction;
        x_new = snake_x;
    }
    else
    {
        x_new += rand() % 3 - 1;
        y_new += rand() % 3 - 1;
    }

    // Ensuring that new position is within boundaries
    x_new = max(0, min(x_new, width - 1));
    y_new = max(0, min(y_new, height - 1));
    
    if (nextMoveNotOk(x_new, y_new))
    {
        //forfeit move
        return;
    }

    //if the snake touches the captain
    Captain* captain_ptr = dynamic_cast<Captain*>(field[y_new][x_new]);
    if (captain_ptr != nullptr)
    {   
        int pointsLost = 0;
        //attempt to pop 5 veggies out of captains basket
        int veggie_count = captainVeggie->getVeggiesCollected().size();
        if (veggie_count > 0)
        {
            if (veggie_count > 5)
            {
                captainVeggie->removeVeggie(5, pointsLost);
                score -= pointsLost;
            }
            else
            {
                captainVeggie->removeVeggie(veggie_count, pointsLost);
                score -= pointsLost;
            }
        }

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

GameEngine::~GameEngine() {
    // Here, you would write the code to free up resources, like deleting pointers
    for (auto rabbit : rabbits) {
        delete rabbit;
    }
    for (auto veggie : veggies) {
        delete veggie;
    }
    delete captainVeggie;
    delete snake;

    for (int i = 0; i < height; i++) {
        delete[] field[i];
    }
    delete[] field;
}

