/*
    Authors: Genesis Cevallos, Robert Plastina, Praveena Batta
    Description: This file defines the member functions for the "GameEngine" class.
*/

#include "GameEngine.h"
#include "Veggie.h"
#include <cstdlib>
#include <ctime>
//TODO: Define GameEngine functions. Descriptions have been added in header file.
//Order of definitions was based on project instructions.

void GameEngine::initializeGame()
{
    initVeggies();
    //initCaptain();
    //initRabbits();

    //initialize score to 0
    int score = 0;
}

/// @brief This function initializes veggie objects based off of
///        the input configuration file.
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
        } while (field[x][y] != nullptr);

        Rabbit* newRabbit = new Rabbit(x, y, "R");
        rabbits.push_back(newRabbit);
        field[x][y] = newRabbit;
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
    cout << "all! Each vegetable is wroth a different number of points," << endl;
    cout << "so go for the high score!" << endl;

    cout << "\nThe vegetables are: " << endl;
    for (int i = 0; i < veggies.size(); i++)
    {
        cout << veggies[i]->getSymbol() << ": " << veggies[i]->getVeggieName();
        cout << " " << veggies[i]->getPointVal() << " points" << endl;
    }

    //TODO: add in appropriate "get" functions when init functions are done 
    cout << "\nCaptain Veggie is __, and the rabbits are __'s." << endl;

    cout << "\nGood luck!\n" << endl;
}

/// @brief This function outputs the contents of the field in a pleasing, 2D grid
///        format with a border around the entire grid.
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

            if (veggie_ptr != nullptr)
            {
                cout << setw(7) << GREEN << field[i][h]->getSymbol() << RESET;
                //cout << setw(3) << field[i][h]->getSymbol();
            }
            else if (captain_ptr != nullptr)
            {
                cout << setw(7) << YELLOW << "C"; // Assuming "C" is the symbol for Captain and captain is colour coded yellow.
            }
            else if (rabbit_ptr != nullptr)
            {
                cout << setw(7) << RED << "R"; //Assuming Rabbit is red and R is the symbol for rabbit
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
    return 0;
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
            FieldInhabitant* occupant = field[newX][newY];

            Veggie* veggie = dynamic_cast<Veggie*>(occupant);

            if (occupant == nullptr || veggie != nullptr)
            {
                delete occupant;
                field[rabbit->getXPos()][rabbit->getYPos()] = nullptr;
                rabbit->setXPos(newX);
                rabbit->setYPos(newY);
                field[newX][newY] = rabbit;
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

}