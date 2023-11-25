/*
    Authors: Genesis Cevallos, Robert Plastina, Praveena Batta
    Description: This file defines the member functions for the "Veggie" class.
*/

#include "Veggie.h"

//constructor
Veggie::Veggie(string veggieName, string symbol, int pointVal) : FieldInhabitant(symbol)
{
    this->veggieName = veggieName;
    this->pointVal = pointVal;
};

//getter and setter functions
string Veggie::getVeggieName()
{
    return veggieName;
}

int Veggie::getPointVal()
{
    return pointVal;
}

void Veggie::setVeggieName(string newName)
{
    this->veggieName = newName;
}

void Veggie::setPointVal(int newVal)
{
    this->pointVal = newVal;
}