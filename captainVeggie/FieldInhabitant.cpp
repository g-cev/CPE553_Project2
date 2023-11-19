/*
    Authors: Genesis Cevallos, Robert Plastina
    Description: This file defines the member functions for the "Field Inhabitant" class.
*/

#include "FieldInhabitant.h"

//constructor
FieldInhabitant::FieldInhabitant(string symbol)
{
    this->symbol = symbol;
}

//getter and setter functions

string FieldInhabitant::getSymbol()
{
    return symbol;
}

void FieldInhabitant::setSymbol(string newSymbol)
{
    this->symbol = newSymbol;
}

//do-nothing destructor
FieldInhabitant::~FieldInhabitant()
{
    //does nothing
}