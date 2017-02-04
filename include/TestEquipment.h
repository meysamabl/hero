#ifndef TESTEQUIPMENT_H
#define TESTEQUIPMENT_H

#include "Equipment.h"

class TestEquipment
{
    public:
        /** Default constructor */
        TestEquipment();
        /** Default destructor */
        virtual ~TestEquipment();

        static void testAll(default_random_engine& gen);
        static void testPopulatePowers(default_random_engine& gen);
        static void testAddPower(default_random_engine& gen);
        static void testDisplayEquipment(default_random_engine& gen);
};

#endif // TESTEQUIPMENT_H
