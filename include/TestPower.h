#ifndef TESTPOWER_H
#define TESTPOWER_H

#include <random>
#include "Power.h"
#include <fstream>

class TestPower
{
    public:
        /** Default constructor */
        TestPower();
        /** Default destructor */
        virtual ~TestPower();

        static void testAll();

        static void testDisplayPower();

        static void testGetduration();

        static void testGeteffect();

        static void testGetrange();

        static void testGetname();

        static void testPopulatePower();
};

#endif // TESTPOWER_H
