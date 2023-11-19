/*
    Authors: Genesis Cevallos, Robert Plastina
    Description: This header file defines the subclass "Veggie".
*/

#ifndef VEGGIE_H
#define VEGGIE_H

#include "FieldInhabitant.h"

class Veggie : public FieldInhabitant
{
    private:
        //name of vegetable
        string veggieName;
        //point value of vegetable
        int pointVal;
    
    public:
        //public constructor
        Veggie(string veggieName, string symbol, int pointVal);

        //getter functions
        string getVeggieName();
        int getPointVal();

        //setter functions
        void setVeggieName(string newName);
        void setPointVal(int newVal);
};

#endif