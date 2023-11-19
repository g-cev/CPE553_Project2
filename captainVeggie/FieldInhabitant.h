#ifndef FIELDINHABITANT_H
#define FIELDINHABITANT_H

#include <iostream>
#include <vector>

using namespace std;

/*
    Authors: Genesis Cevallos, Robert Plastina
    Description: This header file defines the superclass "FieldInhabitant".
*/

class FieldInhabitant
{
    protected:
        //symbol to represent a field inhabitant
        string symbol;
    
    public:
        //public constructor
        FieldInhabitant(string symbol);

        //getter functions
        string getSymbol();

        //setter functions
        void setSymbol(string newSymbol);

        //virtual deconstructor
        virtual ~FieldInhabitant() = 0;
};

#endif