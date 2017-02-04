#ifndef LOCATION_H
#define LOCATION_H
#include <iostream>
#include <vector>
#include "RandomGeneratorHelper.h"

using namespace std;

class Location
{
    public:
        /** Default constructor */
        Location(const int minRange = 0, const int maxRange = 100);

        Location(int x, int y, int z);

        /** Default destructor */
        virtual ~Location();

        void displayLocation();
        /** Access x
         * \return The current value of x
         */
        int Getx() const { return x; }
        /** Set x
         * \param val New value to set
         */
        void Setx(int val) { x = val; }
        /** Access y
         * \return The current value of y
         */
        int Gety() const { return y; }
        /** Set y
         * \param val New value to set
         */
        void Sety(int val) { y = val; }
        /** Access z
         * \return The current value of z
         */
        int Getz() const { return z; }
        /** Set z
         * \param val New value to set
         */
        void Setz(int val) { z = val; }
    protected:
    private:
        int x; //!< Member variable "x"
        int y; //!< Member variable "y"
        int z; //!< Member variable "z"
};

#endif // LOCATION_H
